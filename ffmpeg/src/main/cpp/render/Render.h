//
// Created by coocent-camera002 on 2024/5/15.
//

#ifndef FFMPEGSAMPLE_RENDER_H
#define FFMPEGSAMPLE_RENDER_H

#include <android/native_window.h>
#include <android/native_window_jni.h>
#include <stdint.h>

class Render
{
public:
    Render() {}
    virtual ~Render() {};

    virtual void setNativeWindow(ANativeWindow *nativeWindow) = 0;
    virtual void prepareRender(int videoWidth, int videoHeight, int rotate, const char* pixelFormat) = 0;
    virtual void render(const uint8_t *const srcSlice[], const int srcStride[]) = 0;

protected:
    ANativeWindow *mNativeWindow = nullptr;
    int mVideoWidth;
    int mVideoHeight;
    int mRenderWidth;
    int mRenderHeight;
};

#endif //FFMPEGSAMPLE_RENDER_H
