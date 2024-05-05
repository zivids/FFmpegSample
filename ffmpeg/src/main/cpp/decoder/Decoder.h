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

class Decoder
{
public:
    Decoder(const string &url);

    virtual ~Decoder() {};

    virtual void open() = 0;

    virtual void release() = 0;

protected:
    unique_ptr<string> mUrl = nullptr;

private:
    mutex mLockMutex;
    thread *mThread = nullptr;

    AVFormatContext *mAVFormatContext = nullptr;
};

#endif //FFMPEGSAMPLE_DECODER_H
