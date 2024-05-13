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
    VideoDecoder() : Decoder() {};

    ~VideoDecoder();

    bool prepareDecoder() override;

    void onDecoderPrepared() override;

    int decodePacket() override;

    void stop() override;
};

#endif //FFMPEGSAMPLE_VIDEODECODER_H
