//
// Created by Administrator on 2024/5/2.
//

#ifndef FFMPEGSAMPLE_JNIPLAYERCALLBACK_H
#define FFMPEGSAMPLE_JNIPLAYERCALLBACK_H

#include "PlayerCallback.h"
#include "JVMUtils.h"

class JNIPlayerCallback : public PlayerCallback
{
public:
    JNIPlayerCallback(jobject obj);

    ~JNIPlayerCallback();

    void onPrepared() override;

private:
    jobject mObj;
};

#endif //FFMPEGSAMPLE_JNIPLAYERCALLBACK_H
