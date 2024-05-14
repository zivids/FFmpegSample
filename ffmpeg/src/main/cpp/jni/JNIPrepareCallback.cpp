//
// Created by xiongzw on 2024/5/14.
//

#include "JNIPrepareCallback.h"

JNIPrepareCallback::JNIPrepareCallback(jobject obj)
{
    JVMUtils::getInstance()->runOnJava([&, this](JNIEnv *env) {
        mObj = env->NewGlobalRef(obj);
    });
}

JNIPrepareCallback::~JNIPrepareCallback()
{
    JVMUtils::getInstance()->runOnJava([&, this](JNIEnv *env) {
        env->DeleteGlobalRef(mObj);
    });

    mObj = nullptr;
}

void JNIPrepareCallback::onPrepared()
{
    JVMUtils::getInstance()->runOnJava([&, this](JNIEnv *env) {
        jclass clz = env->GetObjectClass(mObj);
        jmethodID onPreparedMethod = env->GetMethodID(clz, "onPrepared", "()V");
        env->CallVoidMethod(mObj, onPreparedMethod);
        env->DeleteLocalRef(clz);
    });
}
