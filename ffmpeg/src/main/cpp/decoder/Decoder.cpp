//
// Created by Administrator on 2024/5/3.
//

#include "Decoder.h"

Decoder::Decoder(const string &url)
{
    mUrl = unique_ptr<string>(new string(url));
}

void Decoder::setUrl(const string &url)
{
    mUrl = unique_ptr<string>(new string(url));
}

void Decoder::prepare()
{
    if (mThread == nullptr)
    {
        mThread = new thread(&Decoder::decode, this);
    }
}

void Decoder::decode()
{
    if (!mDecoderPrepared)
    {
        mDecoderPrepared = prepareDecoder();
        onDecoderPrepared();
        mDecoderState = STATE_PAUSE;
    }

    for (;;)
    {
        if (mDecoderState == STATE_PAUSE)
        {
            unique_lock<mutex> lock(mLockMutex);
            mCondition.wait(lock);
        }

        if (mDecoderState == STATE_STOP)
        {
            break;
        }

        mDecoderState = STATE_DECODING;
        if (decodePacket() != 0)
        {
            mDecoderState = STATE_PAUSE;
            unique_lock<mutex> lock(mLockMutex);
        }
    }
}
