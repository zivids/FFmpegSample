//
// Created by Administrator on 2024/5/1.
//

#ifndef FFMPEGSAMPLE_FFMPEGPLAYER_H
#define FFMPEGSAMPLE_FFMPEGPLAYER_H

#include <android/native_window.h>
#include <android/native_window_jni.h>
#include <string>
#include <thread>
#include "ImageDef.h"

extern "C" {
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libavutil/imgutils.h>
#include <libavcodec/jni.h>
}

using namespace std;

class FFmpegPlayer
{
public:
    FFmpegPlayer() {};

    ~FFmpegPlayer();

    void setDataSource(const string &url);

    void prepareAsync();

    void start();

    void pause();

    void seekTo(float position);

    void stop();

    void setSurface(ANativeWindow *nativeWindow);

    void release();

private:
    int prepareToDecode();
    void decoding();

private:
    unique_ptr<string> mUrl = nullptr;
    AVFormatContext *mAvFormatContext;
    AVCodecContext *mAVCodecContext;
    AVCodec *mAVCodec;
    AVPacket *mAVPacket;
    AVFrame *mAVFrame;
    ANativeWindow *mANativeWindow;
    thread *mThread = nullptr;
    mutex mMutex;
    condition_variable mCondition;
    int videoStreamIndex = -1;
    bool mPreparedToDecode;
    bool mInputEOF;
    bool mOutputEOF;
};


#endif //FFMPEGSAMPLE_FFMPEGPLAYER_H
