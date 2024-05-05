//
// Created by Administrator on 2024/5/1.
//

#ifndef FFMPEGSAMPLE_FFMPEGPLAYER_H
#define FFMPEGSAMPLE_FFMPEGPLAYER_H

#include "Player.h"

using namespace std;

class FFmpegPlayer : public Player
{
public:
    FFmpegPlayer() {};

    ~FFmpegPlayer() override;

    void prepareAsync() override;

    void start() override;

    void pause() override;

    void seekTo(float position) override;

    void stop() override;

    void release() override;

private:
    AVFormatContext *mAvFormatContext;
};


#endif //FFMPEGSAMPLE_FFMPEGPLAYER_H
