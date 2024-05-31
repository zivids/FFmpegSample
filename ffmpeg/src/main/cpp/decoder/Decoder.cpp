//
// Created by Administrator on 2024/5/3.
//

#include "Decoder.h"

void Decoder::setUrl(const string &url)
{
    mUrl = unique_ptr<string>(new string(url));
}

bool Decoder::prepare()
{
    if (mUrl == nullptr)
    {
        return false;
    }

    mDecoderPrepared = prepareDecoder();
    if (mDecoderPrepared)
    {
        onDecoderPrepared();
    }
    return mDecoderPrepared;
}

int Decoder::decode()
{
    if (!mDecoderPrepared)
    {
        return -1;
    }

    return decodePacket();
}

void Decoder::stop()
{
    mDecoderPrepared = false;
}

const char* Decoder::getPixelFormat() const
{
    return mPixelFormat;
}

int Decoder::getVideoWidth() const
{
    return mVideoWidth;
}

int Decoder::getVideoHeight() const
{
    return mVideoHeight;
}

bool Decoder::isDecoderPrepared() const
{
    return mDecoderPrepared;
}
