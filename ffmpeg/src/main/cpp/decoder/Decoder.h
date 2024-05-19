//
// Created by Administrator on 2024/5/2.
//

#ifndef FFMPEGSAMPLE_DECODER_H
#define FFMPEGSAMPLE_DECODER_H

#include <string>
#include <thread>
#include "LogUtils.h"

using namespace std;

//enum DecoderState
//{
//    STATE_IDLE,
//    STATE_DECODING,
//    STATE_PAUSE,
//    STATE_STOP,
//};

class Decoder
{
public:
    Decoder() {};

    virtual ~Decoder();

    virtual void setUrl(const string &url);

    virtual bool prepare();

    virtual void start();

    virtual void pause();

    virtual void stop();

    bool isDecoderPrepared() const;

//    int decoderState() const;

protected:
    virtual bool prepareDecoder() = 0;

    virtual void onDecoderPrepared() = 0;

    virtual void decode();

    virtual int decodePacket() = 0;

protected:
    unique_ptr<string> mUrl = nullptr;
//    volatile int mDecoderState = STATE_IDLE;

private:
    mutex mLockMutex;
    thread *mThread = nullptr;
    condition_variable mCondition;

    bool mDecoderPrepared = false;
};

#endif //FFMPEGSAMPLE_DECODER_H
