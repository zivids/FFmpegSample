//
// Created by Administrator on 2024/5/2.
//

#ifndef FFMPEGSAMPLE_DECODER_H
#define FFMPEGSAMPLE_DECODER_H

#include <string>
#include <thread>

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

    virtual void prepare();

    virtual void release() = 0;

protected:
    virtual bool prepareDecoder() = 0;

    virtual void onDecoderPrepared() = 0;

    virtual void decode();

    virtual int decodePacket() = 0;

protected:
    unique_ptr<string> mUrl = nullptr;
    volatile int mDecoderState = STATE_IDLE;

private:
    mutex mLockMutex;
    thread *mThread = nullptr;
    condition_variable mCondition;
    bool mDecoderPrepared = false;
};

#endif //FFMPEGSAMPLE_DECODER_H
