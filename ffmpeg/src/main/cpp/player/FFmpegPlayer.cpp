//
// Created by Administrator on 2024/5/1.
//

#include "FFmpegPlayer.h"
#include "VideoDecoder.h"
#include "LogUtils.h"

FFmpegPlayer::~FFmpegPlayer()
{

}

void FFmpegPlayer::setDataSource(const string &url)
{
    mUrl = unique_ptr<string>(new string(url));
}

void FFmpegPlayer::prepareAsync()
{
    if (mThread == nullptr)
    {
        mThread = new thread(&FFmpegPlayer::decoding, this);
    }
    else
    {

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
    if (mAVFrame != nullptr)
    {
        av_frame_free(&mAVFrame);
        mAVFrame = nullptr;
    }

    if (mAVPacket != nullptr)
    {
        av_packet_free(&mAVPacket);
        mAVPacket = nullptr;
    }

    if (mAVCodecContext != nullptr)
    {
        avcodec_close(mAVCodecContext);
        avcodec_free_context(&mAVCodecContext);
        mAVCodecContext = nullptr;
        mAVCodec = nullptr;
    }

    if (mAvFormatContext != nullptr)
    {
        avformat_close_input(&mAvFormatContext);
        avformat_free_context(mAvFormatContext);
        mAvFormatContext = nullptr;
    }
}

int FFmpegPlayer::open()
{
    int result = -1;
    mAvFormatContext = avformat_alloc_context();
    if (avformat_open_input(&mAvFormatContext, mUrl->c_str(), nullptr, nullptr) != 0)
    {
        LOGE("avformat_open_input fail.");
        return result;
    }

    if (avformat_find_stream_info(mAvFormatContext, nullptr) < 0)
    {
        LOGE("avformat_find_stream_info fail.");
        return result;
    }

    int streamIndex = -1;
    for (int i = 0; i < mAvFormatContext->nb_streams; i++)
    {
        AVMediaType mediaType = mAvFormatContext->streams[i]->codecpar->codec_type;
        if (mediaType == AVMEDIA_TYPE_VIDEO)
        {
            streamIndex = i;
            break;
        }
    }

    if (streamIndex < 0)
    {
        LOGE("fail to find stream index.");
        return result;
    }

    AVCodecParameters * avCodecParameters = mAvFormatContext->streams[streamIndex]->codecpar;
    mAVCodec = avcodec_find_decoder(avCodecParameters->codec_id);
    if (mAVCodec == nullptr)
    {
        LOGE("avcodec_find_decoder fail.");
        return result;
    }

    mAVCodecContext = avcodec_alloc_context3(mAVCodec);
    if (avcodec_parameters_to_context(mAVCodecContext, avCodecParameters) != 0)
    {
        LOGE("avcodec_parameters_to_context fail.");
        return result;
    }

    result = avcodec_open2(mAVCodecContext, mAVCodec, nullptr);
    if (result < 0)
    {
        LOGE("avcodec_open2 fail.");
        return result;
    }

    mAVPacket = av_packet_alloc();
    mAVFrame = av_frame_alloc();
    while (av_read_frame(mAvFormatContext, mAVPacket) >= 0)
    {
        if (mAVPacket->stream_index != streamIndex)
        {
            continue;
        }

        if (avcodec_send_packet(mAVCodecContext, mAVPacket) != 0)
        {
            return -1;
        }

        while (avcodec_receive_frame(mAVCodecContext, mAVFrame) == 0)
        {
            //渲染
        }

        av_packet_unref(mAVPacket);
    }

    return result;
}

void FFmpegPlayer::decoding()
{

}