//
// Created by Administrator on 2024/5/1.
//

#include "FFmpegPlayer.h"
#include "VideoDecoder.h"
#include "LogUtils.h"

FFmpegPlayer::~FFmpegPlayer()
{

}

void FFmpegPlayer::prepareAsync()
{
//    if (videoDecoder == nullptr)
//    {
//        videoDecoder = new VideoDecoder(mUrl->c_str());
//        videoDecoder->open();
//    }

    mAvFormatContext = avformat_alloc_context();
    if (avformat_open_input(&mAvFormatContext, mUrl->c_str(), nullptr, nullptr) != 0)
    {
        LOGE("avformat_open_input fail.");
        return;
    }

    if (avformat_find_stream_info(mAvFormatContext, nullptr) < 0)
    {
        LOGE("avformat_find_stream_info fail.");
        return;
    }

    int videoIndex = -1;
    for (int i = 0; i < mAvFormatContext->nb_streams; i++)
    {
        AVMediaType mediaType = mAvFormatContext->streams[i]->codecpar->codec_type;
        if (mediaType == AVMEDIA_TYPE_VIDEO)
        {
            videoIndex = i;
            break;
        }
    }

    if (videoIndex < 0)
    {
        LOGE("fail to find stream index.");
        return;
    }

    AVCodecParameters * avCodecParameters = mAvFormatContext->streams[videoIndex]->codecpar;
    AVCodec *avCodec = avcodec_find_decoder(avCodecParameters->codec_id);
    if (avCodec == nullptr)
    {
        LOGE("avcodec_find_decoder fail.");
        return;
    }

    AVCodecContext *avCodecContext = avcodec_alloc_context3(avCodec);
    if (avcodec_parameters_to_context(avCodecContext, avCodecParameters) != 0)
    {
        LOGE("avcodec_parameters_to_context fail.");
        return;
    }


}

void FFmpegPlayer::start()
{

}

void FFmpegPlayer::pause()
{

}

void FFmpegPlayer::seekTo(float position)
{

}

void FFmpegPlayer::stop()
{

}

void FFmpegPlayer::release()
{

}