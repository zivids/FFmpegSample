//
// Created by coocent-camera002 on 2024/5/15.
//

#ifndef FFMPEGSAMPLE_RENDER_H
#define FFMPEGSAMPLE_RENDER_H

#include <android/native_window.h>
#include <android/native_window_jni.h>
extern "C" {
#include <libavcodec/avcodec.h>
}

class Render
{
public:
    Render() {}
    virtual ~Render() = 0;

    virtual void setNativeWindow(ANativeWindow *nativeWindow) = 0;
    virtual void prepareRender(ANativeWindow *nativeWindow, AVCodecContext *avCodecContext) = 0;
    virtual void render() = 0;

protected:
    ANativeWindow *mNativeWindow = nullptr;
    int mRenderWidth;
    int mRenderHeight;
};

#endif //FFMPEGSAMPLE_RENDER_H
