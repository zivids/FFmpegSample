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

void FFmpegPlayer::setSurface(ANativeWindow *nativeWindow)
{
    mANativeWindow = nativeWindow;
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

int FFmpegPlayer::prepareToDecode()
{
    int result = -1;
    //创建封装格式上下文
    mAvFormatContext = avformat_alloc_context();
    //解封装
    if (avformat_open_input(&mAvFormatContext, mUrl->c_str(), nullptr, nullptr) != 0)
    {
        LOGE("avformat_open_input fail.");
        return result;
    }

    //获取音视频流信息
    if (avformat_find_stream_info(mAvFormatContext, nullptr) < 0)
    {
        LOGE("avformat_find_stream_info fail.");
        return result;
    }

    //获取视频流索引
    videoStreamIndex = av_find_best_stream(mAvFormatContext, AVMEDIA_TYPE_VIDEO,
                        -1, -1, nullptr, 0);
//    int streamIndex = -1;
//    for (int i = 0; i < mAvFormatContext->nb_streams; i++)
//    {
//        AVMediaType mediaType = mAvFormatContext->streams[i]->codecpar->codec_type;
//        if (mediaType == AVMEDIA_TYPE_VIDEO)
//        {
//            streamIndex = i;
//            break;
//        }
//    }

    if (videoStreamIndex < 0)
    {
        LOGE("fail to find stream index.");
        return result;
    }

    //获取解码器参数
    AVCodecParameters * avCodecParameters = mAvFormatContext->streams[videoStreamIndex]->codecpar;
    //根据codec_id获取解码器
    mAVCodec = avcodec_find_decoder(avCodecParameters->codec_id);
    if (mAVCodec == nullptr)
    {
        LOGE("avcodec_find_decoder fail.");
        return result;
    }

    //创建解码器上下文
    mAVCodecContext = avcodec_alloc_context3(mAVCodec);
    if (avcodec_parameters_to_context(mAVCodecContext, avCodecParameters) != 0)
    {
        LOGE("avcodec_parameters_to_context fail.");
        return result;
    }

    //打开解码器
    result = avcodec_open2(mAVCodecContext, mAVCodec, nullptr);
    if (result < 0)
    {
        LOGE("avcodec_open2 fail.");
        return result;
    }

    //创建存储编码数据的结构体
    mAVPacket = av_packet_alloc();
    //创建存储解码数据的结构体
    mAVFrame = av_frame_alloc();

    return result;
}

void FFmpegPlayer::decoding()
{
    if (!mPreparedToDecode)
    {
        mPreparedToDecode = prepareToDecode() >= 0;
    }

    int result = -1;
    //循环解码
    while (!mInputEOF || !mOutputEOF)
    {
        if (!mInputEOF)
        {
            if (mAVPacket->size > 0)
            {
                result = 0;
            }
            else
            {
                //读取packet编码数据包
                result = av_read_frame(mAvFormatContext, mAVPacket);
            }

            if (result == 0)
            {
                if (mAVPacket->stream_index != videoStreamIndex)
                {
                    //释放引用
                    av_packet_unref(mAVPacket);
                    continue;
                }

                //发送packet编码数据包到解码队列
                result = avcodec_send_packet(mAVCodecContext, mAVPacket);
                switch (result)
                {
                    case AVERROR(EAGAIN):
                        /**
                         * 发送给解码器try again的时候，证明解码器中还有缓存，需要先取出缓存
                         * 此处没有调用 av_packet_unref ，保留packet，下次继续发送
                         */
                        break;

                    case AVERROR(ENOMEM):
                    case AVERROR(EINVAL):
                        av_packet_unref(mAVPacket);
                        return;

                    case AVERROR_EOF:
                        av_packet_unref(mAVPacket);
                        mInputEOF = true;
                        break;

                        //发送成功
                    case 0:
                    default:
                        //释放引用
                        av_packet_unref(mAVPacket);
                        break;
                }
            }
            else
            {
                av_packet_unref(mAVPacket);
                if (result == AVERROR_EOF || result == AVERROR_EXIT || avio_feof(mAvFormatContext->pb)) {
                    mInputEOF = true;
                    avcodec_send_packet(mAVCodecContext, nullptr);
                }
            }
        }

        if (!mOutputEOF)
        {
            //接收到一帧解码数据
            result = avcodec_receive_frame(mAVCodecContext, mAVFrame);
            switch (result)
            {
                //成功，转换渲染
                case 0:
                {
                    int videoWidth = mAVCodecContext->width;
                    int videoHeight = mAVCodecContext->height;
                    AVFrame *rgbFrame = av_frame_alloc();
                    int bufferSize = av_image_get_buffer_size(AV_PIX_FMT_RGBA,
                                                              videoWidth, videoHeight, 1);
                    auto *frameBuffer = (uint8_t *) av_malloc(bufferSize * sizeof(uint8_t));
                    av_image_fill_arrays(rgbFrame->data, rgbFrame->linesize,
                                         frameBuffer, AV_PIX_FMT_RGBA, videoWidth,
                                         videoHeight, 1);

                    int windowWidth = ANativeWindow_getWidth(mANativeWindow);
                    int windowHeight = ANativeWindow_getHeight(mANativeWindow);

                    int dstWidth, dstHeight;
                    if (windowWidth < windowHeight * videoWidth / videoHeight)
                    {
                        dstWidth = windowWidth;
                        dstHeight = windowWidth * videoHeight / videoWidth;
                    } else
                    {
                        dstWidth = windowHeight * videoWidth / videoHeight;
                        dstHeight = windowHeight;
                    }
                    SwsContext *swsContext = sws_getContext(videoWidth, videoHeight,
                                                            mAVCodecContext->pix_fmt,
                                                            dstWidth, dstHeight,
                                                            AV_PIX_FMT_RGBA,
                                                            SWS_FAST_BILINEAR, nullptr,
                                                            nullptr, nullptr);
                    sws_scale(swsContext, mAVFrame->data, mAVFrame->linesize,
                              0, videoWidth, rgbFrame->data, rgbFrame->linesize);

                    if (rgbFrame != nullptr)
                    {
                        av_frame_free(&rgbFrame);
                        rgbFrame = nullptr;
                    }

                    if (frameBuffer != nullptr)
                    {
                        free(frameBuffer);
                        frameBuffer = nullptr;
                    }

                    if (swsContext != nullptr)
                    {
                        sws_freeContext(swsContext);
                        swsContext = nullptr;
                    }
                    break;
                }

                //需要更多包
                case AVERROR(EAGAIN):
                {
                    break;
                }

                case AVERROR_EOF:
                {
                    mOutputEOF = true;
                    avcodec_flush_buffers(mAVCodecContext);
                    break;
                }

                    // 解码器错误
                case AVERROR(EINVAL):
                {
                    break;
                }

                    // 解码器参数改变
                case AVERROR_INPUT_CHANGED:
                {
                    break;
                }

                default:
                {
                    break;
                }
            }
        }
    }

    release();
}