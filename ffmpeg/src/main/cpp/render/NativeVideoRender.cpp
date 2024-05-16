//
// Created by coocent-camera002 on 2024/5/15.
//

#include "NativeVideoRender.h"

NativeVideoRender::~NativeVideoRender()
{

}

void NativeVideoRender::prepareRender(ANativeWindow *nativeWindow, AVCodecContext *avCodecContext)
{
    int videoWidth = avCodecContext->width;
    int videoHeight = avCodecContext->height;
    int windowWidth = ANativeWindow_getWidth(nativeWindow);
    int windowHeight = ANativeWindow_getHeight(nativeWindow);

    if (windowWidth < windowHeight * videoWidth / videoHeight)
    {
        mRenderWidth = windowWidth;
        mRenderHeight = windowWidth * videoHeight / videoWidth;
    }
    else
    {
        mRenderWidth = windowHeight * videoWidth / videoHeight;
        mRenderHeight = windowHeight;
    }

    ANativeWindow_setBuffersGeometry(nativeWindow, mRenderWidth,
                                     mRenderHeight, WINDOW_FORMAT_RGBA_8888);

    if (mRGBFrame == nullptr)
    {
        mRGBFrame = av_frame_alloc();
    }

    int bufferSize = av_image_get_buffer_size(AV_PIX_FMT_RGBA, mRenderWidth, mRenderHeight, 1);
    if (mBuffer != nullptr)
    {
        av_freep(mBuffer);
    }
    mBuffer = (uint8_t *) av_malloc(bufferSize * sizeof(uint8_t));
    av_image_fill_arrays(mRGBFrame->data, mRGBFrame->linesize,mBuffer,
                         AV_PIX_FMT_RGBA, mRenderWidth, mRenderHeight, 1);

    mSwsContext = sws_getContext(videoWidth, videoHeight, avCodecContext->pix_fmt,
                                 mRenderWidth, mRenderHeight, AV_PIX_FMT_RGBA,
                                 SWS_FAST_BILINEAR, nullptr, nullptr, nullptr);
}

void NativeVideoRender::render()
{

}