//
// Created by Administrator on 2024/5/3.
//

#include "Decoder.h"

Decoder::~Decoder()
{
    if (mPrepareCallback != nullptr)
    {
        delete mPrepareCallback;
    }
    mPrepareCallback = nullptr;
    if (mThread != nullptr && mThread->joinable())
    {
        mThread->join();
        delete mThread;
        mThread = nullptr;
    }
}

void Decoder::setUrl(const string &url)
{
    mUrl = unique_ptr<string>(new string(url));
}

void Decoder::prepare(PrepareCallback *callback)
{
    if (mUrl == nullptr)
    {
        return;
    }

    if (mPrepareCallback != nullptr)
    {
        delete mPrepareCallback;
    }
    mPrepareCallback = callback;

    if (mThread == nullptr)
    {
        mThread = new thread(&Decoder::decode, this);
    }
}

void Decoder::start()
{
    if (!mDecoderPrepared)
    {
        LOGW("Decoder does not prepared");
        return;
    }

    mDecoderState = STATE_DECODING;
    unique_lock<mutex> lock(mLockMutex);
    mCondition.notify_all();
}

void Decoder::pause()
{
    mDecoderState = STATE_PAUSE;
}

void Decoder::stop()
{
    mDecoderPrepared = false;
    mDecoderState = STATE_STOP;
    unique_lock<mutex> lock(mLockMutex);
    mCondition.notify_all();
}

int Decoder::decoderState() const
{
    return mDecoderState;
}

bool Decoder::isDecoderPrepared() const
{
    return mDecoderPrepared;
}

void Decoder::decode()
{
    if (!mDecoderPrepared)
    {
        mDecoderPrepared = prepareDecoder();
    }

    if (mDecoderPrepared)
    {
        onDecoderPrepared();
        mDecoderState = STATE_PAUSE;
        if (mPrepareCallback != nullptr)
        {
            mPrepareCallback->onPrepared();
        }

        for (;;)
        {
            while (mDecoderState == STATE_PAUSE)
            {
                LOGD("decode pause");
                unique_lock<mutex> lock(mLockMutex);
                mCondition.wait(lock);
            }

            if (mDecoderState == STATE_STOP)
            {
                break;
            }

            LOGD("decoding...");
            if (decodePacket() != 0)
            {
                mDecoderState = STATE_PAUSE;
                unique_lock<mutex> lock(mLockMutex);
                mCondition.wait(lock);
            }
        }
    }
}
