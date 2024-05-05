//
// Created by Administrator on 2024/5/2.
//

#include "JVMUtils.h"

JVMUtils *JVMUtils::instance = nullptr;

JVMUtils::~JVMUtils()
{
    mJavaVm = nullptr;
}

void JVMUtils::init(JavaVM *javaVm)
{
    mJavaVm = javaVm;
}

JVMUtils *JVMUtils::getInstance()
{
    if (JVMUtils::instance == nullptr)
    {
        JVMUtils::instance = new JVMUtils();
    }

    return JVMUtils::instance;
}

void JVMUtils::runOnJava(const std::function<void(JNIEnv *)> &func)
{
    if (mJavaVm == nullptr)
    {
        return;
    }

    JNIEnv *env;
    jint res = mJavaVm->GetEnv((void **) &env, JNI_VERSION_1_6);
    bool otherThread = res != JNI_OK;
    if (otherThread)
    {
        if (mJavaVm->AttachCurrentThread(&env, nullptr) != JNI_OK)
        {
            return;
        }
    }

    func(env);

    if (otherThread)
    {
        mJavaVm->DetachCurrentThread();
    }
}

void JVMUtils::destroyInstance()
{
    delete JVMUtils::instance;
    JVMUtils::instance = nullptr;
}

void JVMUtils::attachCurrentThread()
{
    JNIEnv *env;
    mJavaVm->GetEnv((void **) &env, JNI_VERSION_1_6);
    mJavaVm->AttachCurrentThread(&env, nullptr);
}

void JVMUtils::detachCurrentThread()
{
    mJavaVm->DetachCurrentThread();
}
