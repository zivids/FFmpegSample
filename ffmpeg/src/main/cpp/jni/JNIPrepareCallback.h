//
// Created by xiongzw on 2024/5/14.
//

#ifndef FFMPEGSAMPLE_JNIPREPARECALLBACK_H
#define FFMPEGSAMPLE_JNIPREPARECALLBACK_H

#include "PrepareCallback.h"
#include "JVMUtils.h"

class JNIPrepareCallback : public PrepareCallback
{
public:
    JNIPrepareCallback(jobject obj);

    ~JNIPrepareCallback();

    void onPrepared() override;

private:
    jobject mObj;
};


#endif //FFMPEGSAMPLE_JNIPREPARECALLBACK_H
