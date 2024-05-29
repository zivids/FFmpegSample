//
// Created by Administrator on 2024/5/2.
//

#ifndef FFMPEGSAMPLE_DECODER_H
#define FFMPEGSAMPLE_DECODER_H

#include <string>
#include <thread>
#include <stdint.h>
#include "LogUtils.h"
extern "C" {
#include <libavcodec/avcodec.h>
}

using namespace std;

const int RESULT_ERR = -2;
const int RESULT_EOF = -1;
const int RESULT_DONE = 0;
const int RESULT_AGAIN = 1;

class Decoder
{
public:
    Decoder() {};

    virtual ~Decoder();

    virtual void setUrl(const string &url);

    virtual bool prepare();

    virtual int decode();

    virtual int receiveFrame() = 0;

    virtual void stop();

    bool isDecoderPrepared() const;

    int getVideoWidth() const;

    int getVideoHeight() const;

    AVPixelFormat getPixelFormat() const;

    virtual uint8_t** getSrcSlice() = 0;

    virtual int* getSrcStride() = 0;

protected:
    virtual bool prepareDecoder() = 0;

    virtual void onDecoderPrepared() = 0;

    virtual int decodePacket() = 0;

protected:
    unique_ptr<string> mUrl = nullptr;
    AVPixelFormat mPixelFormat;
    int mVideoWidth = 0;
    int mVideoHeight = 0;

private:
    bool mDecoderPrepared = false;
};

#endif //FFMPEGSAMPLE_DECODER_H
