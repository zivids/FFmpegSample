//
// Created by Administrator on 2024/5/1.
//

#include "Player.h"
#include "LogUtils.h"

Player::~Player()
{
    if (mRender != nullptr)
    {
        delete mRender;
        mRender = nullptr;
    }

    if (mVideoDecoder != nullptr)
    {
        delete mVideoDecoder;
        mVideoDecoder = nullptr;
    }
}

void Player::setDataSource(const string &url)
{
    mVideoDecoder->setUrl(url);
}

void Player::setSurface(ANativeWindow *nativeWindow)
{
    mRender->setNativeWindow(nativeWindow);
}

void Player::prepareAsync(PrepareCallback *callback)
{
    if (mThread == nullptr)
    {
        mThread = new thread(&Player::prepare, this, callback);
    }
}

void Player::prepare(PrepareCallback *callback)
{
    bool decoderPrepared = mVideoDecoder->prepare();
    if (!decoderPrepared)
    {
        return;
    }

    mRender->prepareRender(mVideoDecoder->getVideoWidth(),
                           mVideoDecoder->getVideoHeight(),
                           mVideoDecoder->getPixelFormat());
    mPlayerState = STATE_PREPARED;
    callback->onPrepared();

    for (;;)
    {
        while (mPlayerState == STATE_PAUSED)
        {
            unique_lock<mutex> lock(mLockMutex);
            mCondition.wait(lock);
        }

        if (mPlayerState == STATE_STOPPED)
        {
            break;
        }

        int decodeResult = mVideoDecoder->decode();
        if (decodeResult == DECODE_EOF)
        {
            mPlayerState = STATE_PAUSED;
            unique_lock<mutex> lock(mLockMutex);
            mCondition.wait(lock);
        }
        else if (decodeResult == DECODE_AGAIN)
        {
            continue;
        }
        else if (decodeResult == DECODE_ERR)
        {
            break;
        }
        else
        {
            mVideoDecoder->receiveFrame();
            mRender->render();
        }
    }
}

void Player::start()
{
//    if (!mVideoDecoder->isDecoderPrepared())
//    {
//        return;
//    }
//
//    mVideoDecoder->start();
}

void Player::pause()
{
//    if (!mVideoDecoder->isDecoderPrepared() || mVideoDecoder->decoderState() != STATE_DECODING)
//    {
//        return;
//    }
//
//    mVideoDecoder->pause();
}

void Player::stop()
{
//    if (!mVideoDecoder->isDecoderPrepared() || mVideoDecoder->decoderState() == STATE_STOP
//        || mVideoDecoder->decoderState() == STATE_IDLE)
//    {
//        return;
//    }

    mVideoDecoder->stop();
}

void Player::release()
{
    stop();

    delete mRender;
    mRender = nullptr;

    delete mVideoDecoder;
    mVideoDecoder = nullptr;
}