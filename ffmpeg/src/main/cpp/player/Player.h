//
// Created by Administrator on 2024/5/1.
//

#ifndef FFMPEGSAMPLE_PLAYER_H
#define FFMPEGSAMPLE_PLAYER_H

#include <android/native_window.h>
#include <string>
#include "VideoDecoder.h"

using namespace std;

class Player
{
public:
    Player() {};

    virtual ~Player();

    virtual void setDataSource(const string &url);

    virtual void setSurface(ANativeWindow *nativeWindow);

    virtual void prepareAsync(PrepareCallback *callback);

    virtual void start();

    virtual void pause();

    virtual void seekTo(float position) = 0;

    virtual void stop();

    virtual void release();

protected:
    Decoder *videoDecoder = nullptr;
    Decoder *audioDecoder = nullptr;
};


#endif //FFMPEGSAMPLE_PLAYER_H
