//
// Created by Administrator on 2024/5/3.
//

#ifndef FFMPEGSAMPLE_VIDEODECODER_H
#define FFMPEGSAMPLE_VIDEODECODER_H

#include "Decoder.h"

using namespace std;

class VideoDecoder : public Decoder
{
public:
    VideoDecoder(const string &url) : Decoder(url) {}

//    using Decoder::Decoder;

    ~VideoDecoder();

    void open() override;

    void release() override;
};

#endif //FFMPEGSAMPLE_VIDEODECODER_H
