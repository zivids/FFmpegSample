//
// Created by Administrator on 2024/5/2.
//

#include "JNIPlayerCallback.h"

JNIPlayerCallback::JNIPlayerCallback(jobject obj)
{
    JVMUtils::getInstance()->runOnJava([&, this](JNIEnv *env) {
        mObj = env->NewGlobalRef(obj);
    });
}

JNIPlayerCallback::~JNIPlayerCallback()
{
    JVMUtils::getInstance()->runOnJava([&, this](JNIEnv *env) {
        env->DeleteGlobalRef(mObj);
    });

    mObj = nullptr;
}

void JNIPlayerCallback::onPrepared()
{
    JVMUtils::getInstance()->runOnJava([&, this](JNIEnv *env) {
        jclass clz = env->GetObjectClass(mObj);
        jmethodID onPreparedMethod = env->GetMethodID(clz, "onPrepared", "()V");
        env->CallVoidMethod(mObj, onPreparedMethod);
        env->DeleteLocalRef(clz);
    });
}
