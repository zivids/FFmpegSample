//
// Created by Administrator on 2024/5/2.
//

#ifndef FFMPEGSAMPLE_DECODER_H
#define FFMPEGSAMPLE_DECODER_H

#include <string>
#include <thread>

extern "C" {
#include <libavformat/avformat.h>
}

using namespace std;

enum DecoderState
{
    STATE_IDLE,
    STATE_DECODING,
    STATE_PAUSE,
    STATE_STOP,
};

class Decoder
{
public:
    Decoder(const string &url);

    virtual ~Decoder() {};

    virtual void setUrl(const string &url);

    virtual bool prepareDecode() = 0;

    virtual void prepare();

    virtual void release() = 0;

protected:
    virtual void decode();

protected:
    unique_ptr<string> mUrl = nullptr;

private:
    mutex mLockMutex;
    thread *mThread = nullptr;
    condition_variable mCondition;

    AVFormatContext *mAVFormatContext = nullptr;

    volatile int mDecoderState = STATE_IDLE;
    bool mDecoderPrepared = false;
};

#endif //FFMPEGSAMPLE_DECODER_H
