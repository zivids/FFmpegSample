//
// Created by Administrator on 2024/5/3.
//

#ifndef FFMPEGSAMPLE_VIDEODECODER_H
#define FFMPEGSAMPLE_VIDEODECODER_H

#include "Decoder.h"
extern "C" {
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libavutil/imgutils.h>
#include <libavcodec/jni.h>
}

using namespace std;

class VideoDecoder : public Decoder
{
public:
    VideoDecoder() : Decoder() {};

    ~VideoDecoder();

protected:
    bool prepareDecoder() override;

    void onDecoderPrepared() override;

    int decodePacket() override;

    void stop() override;

private:
    AVFormatContext *mAVFormatContext;
    AVCodec *mAVCodec;
    AVCodecContext *mAVCodecContext;
    AVPacket *mAVPacket;
    AVFrame *mAVFrame;
    int mStreamIndex = -1;
};

#endif //FFMPEGSAMPLE_VIDEODECODER_H
