//
// Created by coocent-camera002 on 2024/5/10.
//

#ifndef FFMPEGSAMPLE_FFMPEGPLAYER_H
#define FFMPEGSAMPLE_FFMPEGPLAYER_H

#include "Player.h"
#include "VideoDecoder.h"
#include "NativeVideoRender.h"
#include <string>

using namespace std;

class FFmpegPlayer : public Player
{
public:
    FFmpegPlayer();

    ~FFmpegPlayer() {};

    void seekTo(float position) override;
};


#endif //FFMPEGSAMPLE_FFMPEGPLAYER_H
