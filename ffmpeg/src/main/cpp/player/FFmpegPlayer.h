//
// Created by Administrator on 2024/5/1.
//

#ifndef FFMPEGSAMPLE_FFMPEGPLAYER_H
#define FFMPEGSAMPLE_FFMPEGPLAYER_H

#include <string>
#include <thread>

extern "C" {
#include <libavformat/avformat.h>
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

    void release();

private:
    int open();
    void decoding();

private:
    unique_ptr<string> mUrl = nullptr;
    AVFormatContext *mAvFormatContext;
    AVCodecContext *mAVCodecContext;
    AVCodec *mAVCodec;
    AVPacket *mAVPacket;
    AVFrame *mAVFrame;
    thread *mThread = nullptr;
    mutex mMutex;
    condition_variable mCondition;
};


#endif //FFMPEGSAMPLE_FFMPEGPLAYER_H
