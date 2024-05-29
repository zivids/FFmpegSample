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
    mPlayerState = STATE_PAUSED;
    callback->onPrepared();

    while (!mInputEOF || !mOutputEOF)
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

        if (!mInputEOF)
        {
            int decodeResult = mVideoDecoder->decode();
            if (decodeResult == RESULT_EOF || decodeResult == RESULT_ERR)
            {
                mInputEOF = true;
            }
            else if (decodeResult == RESULT_AGAIN)
            {
                continue;
            }
        }

        if (!mOutputEOF)
        {
            int receiveResult = mVideoDecoder->receiveFrame();
            if (receiveResult == RESULT_EOF || receiveResult == RESULT_ERR)
            {
                mPlayerState = STATE_STOPPED;
                mOutputEOF = true;
            }
            else if (receiveResult == RESULT_AGAIN)
            {
                continue;
            }
            else
            {
                mRender->render(mVideoDecoder->getSrcSlice(),
                                mVideoDecoder->getSrcStride());
            }
        }
    }
}

void Player::start()
{
    mPlayerState = STATE_STARTED;
    unique_lock<mutex> lock(mLockMutex);
    mCondition.notify_all();
}

void Player::pause()
{
    mPlayerState = STATE_PAUSED;
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