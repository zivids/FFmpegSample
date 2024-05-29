//
// Created by Administrator on 2024/5/3.
//
#include "VideoDecoder.h"

VideoDecoder::~VideoDecoder()
{
    av_packet_free(&mAVPacket);
    mAVPacket = nullptr;
}

bool VideoDecoder::prepareDecoder()
{
    //创建封装格式上下文
    mAVFormatContext = avformat_alloc_context();
    //打开输入文件，解封装
    if (avformat_open_input(&mAVFormatContext, mUrl->c_str(), nullptr, nullptr) != 0)
    {
        LOGE("avformat_open_input fail.");
        return false;
    }

    //获取音视频流信息
    if (avformat_find_stream_info(mAVFormatContext, nullptr) < 0)
    {
        LOGE("avformat_find_stream_info fail.");
        return false;
    }

    //获取视频流索引
//    streamIndex = av_find_best_stream(mAVFormatContext, AVMEDIA_TYPE_VIDEO,
//                        -1, -1, nullptr, 0);
    for (int i = 0; i < mAVFormatContext->nb_streams; i++)
    {
        AVMediaType mediaType = mAVFormatContext->streams[i]->codecpar->codec_type;
        if (mediaType == AVMEDIA_TYPE_VIDEO)
        {
            mStreamIndex = i;
            break;
        }
    }

    if (mStreamIndex < 0)
    {
        LOGE("fail to find stream index.");
        return false;
    }

    //获取解码器参数
    AVCodecParameters *avCodecParameters = mAVFormatContext->streams[mStreamIndex]->codecpar;
    //根据codec_id获取解码器
    mAVCodec = avcodec_find_decoder(avCodecParameters->codec_id);
    if (mAVCodec == nullptr)
    {
        LOGE("avcodec_find_decoder fail.");
        return false;
    }

    //创建解码器上下文
    mAVCodecContext = avcodec_alloc_context3(mAVCodec);
    if (avcodec_parameters_to_context(mAVCodecContext, avCodecParameters) != 0)
    {
        LOGE("avcodec_parameters_to_context fail.");
        return false;
    }

    //打开解码器
    if (avcodec_open2(mAVCodecContext, mAVCodec, nullptr) < 0)
    {
        LOGE("avcodec_open2 fail.");
        return false;
    }

    return true;
}

void VideoDecoder::onDecoderPrepared()
{
    //创建存储编码数据的结构体
    mAVPacket = av_packet_alloc();
    //创建存储解码数据的结构体
    mAVFrame = av_frame_alloc();

    mVideoWidth = mAVCodecContext->width;
    mVideoHeight = mAVCodecContext->height;
    mPixelFormat = mAVCodecContext->pix_fmt;
}

int VideoDecoder::decodePacket()
{
    if (mAVPacket->size > 0)
    {
        return RESULT_DONE;
    }
    else
    {
        int result = av_read_frame(mAVFormatContext, mAVPacket);
        if (result == 0)
        {
            if (mAVPacket->stream_index != mStreamIndex)
            {
                av_packet_unref(mAVPacket);
                return RESULT_AGAIN;
            }

            switch (avcodec_send_packet(mAVCodecContext, mAVPacket))
            {
                case 0:
                {
//                    av_packet_unref(mAVPacket);
                    return RESULT_DONE;
                }

                case AVERROR_EOF:
                {
                    av_packet_unref(mAVPacket);
                    return RESULT_EOF;
                }

                case AVERROR(EAGAIN):
                {
                    return RESULT_AGAIN;
                }

                case AVERROR(ENOMEM):
                case AVERROR(EINVAL):
                default:
                {
                    av_packet_unref(mAVPacket);
                    return RESULT_ERR;
                }
            }
        }
        else
        {
            av_packet_unref(mAVPacket);
            if (result == AVERROR_EOF || result == AVERROR_EXIT || avio_feof(mAVFormatContext->pb))
            {
                avcodec_send_packet(mAVCodecContext, nullptr);
            }
            return RESULT_EOF;
        }
    }
}

int VideoDecoder::receiveFrame()
{
    switch (avcodec_receive_frame(mAVCodecContext, mAVFrame))
    {
        case 0:
        {
            av_packet_unref(mAVPacket);
            return RESULT_DONE;
        }

        case AVERROR_EOF:
        {
            avcodec_flush_buffers(mAVCodecContext);
            return RESULT_EOF;
        }

        case AVERROR(EAGAIN):
        {
            avcodec_flush_buffers(mAVCodecContext);
            return RESULT_AGAIN;
        }

        case AVERROR(EINVAL):
        case AVERROR_INPUT_CHANGED:
        default:
        {
            avcodec_flush_buffers(mAVCodecContext);
            return RESULT_ERR;
        }
    }
}

uint8_t** VideoDecoder::getSrcSlice()
{
    return mAVFrame->data;
}

int* VideoDecoder::getSrcStride()
{
    return mAVFrame->linesize;
}

void VideoDecoder::stop()
{

}