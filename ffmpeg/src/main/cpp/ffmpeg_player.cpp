//
// Created by coocent-camera002 on 2024/4/29.
//
#include <jni.h>
#include <cstring>
#include "FFmpegPlayer.h"

extern "C" {
#include <libavcodec/version.h>
#include <libavcodec/avcodec.h>
#include <libavfilter/version.h>
#include <libavformat/version.h>
#include <libavutil/version.h>
#include <libswresample/version.h>
#include <libswscale/version.h>
}

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jstring JNICALL
Java_com_coocent_ffmpeg_FFmpegPlayer_00024Companion_nativeGetFFmpegVersion(JNIEnv *env,
                                                                           jobject thiz)
{
    char strBuffer[4 * 1024] = {0};
    strcat(strBuffer, "libavcodec : ");
    strcat(strBuffer, AV_STRINGIFY(LIBAVCODEC_VERSION));
    strcat(strBuffer, "\nlibavfilter : ");
    strcat(strBuffer, AV_STRINGIFY(LIBAVFILTER_VERSION));
    strcat(strBuffer, "\nlibavformat : ");
    strcat(strBuffer, AV_STRINGIFY(LIBAVFORMAT_VERSION));
    strcat(strBuffer, "\nlibavutil : ");
    strcat(strBuffer, AV_STRINGIFY(LIBAVUTIL_VERSION));
    strcat(strBuffer, "\nlibswresample : ");
    strcat(strBuffer, AV_STRINGIFY(LIBSWRESAMPLE_VERSION));
    strcat(strBuffer, "\nlibswscale : ");
    strcat(strBuffer, AV_STRINGIFY(LIBSWSCALE_VERSION));
    strcat(strBuffer, "\navcodec_configure : \n");
    strcat(strBuffer, avcodec_configuration());
    strcat(strBuffer, "\navcodec_license: ");
    strcat(strBuffer, avcodec_license());
    return env->NewStringUTF(strBuffer);
}

#ifdef __cplusplus
}
#endif
extern "C"
JNIEXPORT jlong JNICALL
Java_com_coocent_ffmpeg_FFmpegPlayer_nativeCreatePlayer(JNIEnv *env, jobject thiz)
{
    auto *player = new FFmpegPlayer();
    return reinterpret_cast<jlong>(player);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_coocent_ffmpeg_FFmpegPlayer_nativeSetDataSource(JNIEnv *env, jobject thiz, jlong handle, jstring path)
{
    const char *jpath = env->GetStringUTFChars(path, JNI_FALSE);
    const string url = string(jpath);
    auto *player = reinterpret_cast<Player *>(handle);
    player->setDataSource(url);
    env->ReleaseStringUTFChars(path, jpath);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_coocent_ffmpeg_FFmpegPlayer_nativePrepareAsync(JNIEnv *env, jobject thiz, jlong handle)
{
    auto *player = reinterpret_cast<Player *>(handle);
    player->prepareAsync();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_coocent_ffmpeg_FFmpegPlayer_nativeStart(JNIEnv *env, jobject thiz, jlong handle)
{
    auto *player = reinterpret_cast<Player *>(handle);
    player->start();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_coocent_ffmpeg_FFmpegPlayer_nativePause(JNIEnv *env, jobject thiz, jlong handle)
{
    auto *player = reinterpret_cast<Player *>(handle);
    player->pause();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_coocent_ffmpeg_FFmpegPlayer_nativeStop(JNIEnv *env, jobject thiz, jlong handle)
{
    auto *player = reinterpret_cast<Player *>(handle);
    player->stop();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_coocent_ffmpeg_FFmpegPlayer_nativeSeekTo(JNIEnv *env, jobject thiz, jlong handle, jlong position)
{
//    auto *player = reinterpret_cast<Player *>(handle);
//    player->seekTo();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_coocent_ffmpeg_FFmpegPlayer_nativeRelease(JNIEnv *env, jobject thiz, jlong handle)
{
    auto *player = reinterpret_cast<Player *>(handle);
    player->release();
    delete player;
}