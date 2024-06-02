//
// Created by coocent-camera002 on 2024/5/15.
//

#ifndef FFMPEGSAMPLE_NATIVEVIDEORENDER_H
#define FFMPEGSAMPLE_NATIVEVIDEORENDER_H

#include "Render.h"
extern "C" {
#include <libavutil/frame.h>
#include <libavutil/imgutils.h>
#include <libswscale/swscale.h>
}

class NativeVideoRender : public Render
{
public:
    NativeVideoRender() : Render() {}

    ~NativeVideoRender();

    void setNativeWindow(ANativeWindow *nativeWindow) override;

    void prepareRender(int videoWidth, int videoHeight, int rotate, const char* pixelFormat) override;

    void render(const uint8_t *const srcSlice[], const int srcStride[]) override;

private:
    AVFrame *mRGBFrame = nullptr;
    SwsContext *mSwsContext = nullptr;
    uint8_t *mBuffer = nullptr;
};


#endif //FFMPEGSAMPLE_NATIVEVIDEORENDER_H
