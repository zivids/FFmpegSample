//
// Created by coocent-camera002 on 2024/5/15.
//

#include "NativeVideoRender.h"

NativeVideoRender::~NativeVideoRender()
{

}

void NativeVideoRender::setNativeWindow(ANativeWindow *nativeWindow)
{
    mNativeWindow = nativeWindow;
}

void NativeVideoRender::prepareRender(int videoWidth, int videoHeight, int rotate, const char* pixelFormat)
{
    mVideoWidth = videoWidth;
    mVideoHeight = videoHeight;
    int windowWidth = ANativeWindow_getWidth(mNativeWindow);
    int windowHeight = ANativeWindow_getHeight(mNativeWindow);

    if (rotate == 0 || rotate == 180)
    {
        mRenderWidth = windowWidth;
        mRenderHeight = windowWidth * videoHeight / videoWidth;
    }
    else
    {
        mRenderWidth = windowHeight * videoWidth / videoHeight;
        mRenderHeight = windowHeight;
    }

    ANativeWindow_setBuffersGeometry(mNativeWindow, mRenderWidth,
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

    if (mSwsContext != nullptr)
    {
        sws_freeContext(mSwsContext);
    }
    mSwsContext = sws_getContext(videoWidth, videoHeight, av_get_pix_fmt(pixelFormat),
                                 mRenderWidth, mRenderHeight, AV_PIX_FMT_RGBA,
                                 SWS_FAST_BILINEAR, nullptr, nullptr, nullptr);
}

void NativeVideoRender::render(const uint8_t *const srcSlice[], const int srcStride[])
{
    sws_scale(mSwsContext, srcSlice, srcStride, 0, mVideoHeight,
              mRGBFrame->data, mRGBFrame->linesize);
    ANativeWindow_Buffer nativeWindowBuffer;
    ANativeWindow_lock(mNativeWindow, &nativeWindowBuffer, nullptr);
    auto *dstBuffer = static_cast<uint8_t *>(nativeWindowBuffer.bits);

    int srcLineSize = mRenderWidth * 4;
    int dstLineSize = nativeWindowBuffer.stride * 4;
    for (int i = 0; i < mRenderHeight; ++i) {
        memcpy(dstBuffer + i * dstLineSize, mRGBFrame->data[0] + i * srcLineSize, srcLineSize);
    }
    ANativeWindow_unlockAndPost(mNativeWindow);
}