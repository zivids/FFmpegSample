//
// Created by Administrator on 2024/5/2.
//

#ifndef FFMPEGSAMPLE_JVMUTILS_H
#define FFMPEGSAMPLE_JVMUTILS_H

#include <jni.h>
#include <functional>

class JVMUtils
{
public:
    static JVMUtils *getInstance();

    static void destroyInstance();

    void init(JavaVM *javaVm);

    void runOnJava(const std::function<void(JNIEnv *env)> &func);

    inline JavaVM *getJvm()
    {
        return mJavaVm;
    }

    void attachCurrentThread();

    void detachCurrentThread();

private:
    JVMUtils() {}

    ~JVMUtils();

private:
    static JVMUtils *instance;
    JavaVM *mJavaVm;
};

#endif //FFMPEGSAMPLE_JVMUTILS_H
