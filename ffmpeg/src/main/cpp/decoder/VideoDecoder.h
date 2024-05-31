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

    int receiveFrame() override;

    uint8_t** getSrcSlice() override;

    int* getSrcStride() override;

protected:
    bool prepareDecoder() override;

    void onDecoderPrepared() override;

    int decodePacket() override;

    void stop() override;

private:
    AVFormatContext *mAVFormatContext = nullptr;
    AVCodec *mAVCodec = nullptr;
    AVCodecContext *mAVCodecContext = nullptr;
    AVPacket *mAVPacket = nullptr;
    AVFrame *mAVFrame = nullptr;
    int mStreamIndex = -1;
};

#endif //FFMPEGSAMPLE_VIDEODECODER_H
