//
// Created by Administrator on 2024/5/2.
//

#ifndef FFMPEGSAMPLE_LOGUTILS_H
#define FFMPEGSAMPLE_LOGUTILS_H

#include <android/log.h>

#define TAG "FFmpegSample"

#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, TAG, __VA_ARGS__)
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL, TAG, __VA_ARGS__)

#endif //FFMPEGSAMPLE_LOGUTILS_H
