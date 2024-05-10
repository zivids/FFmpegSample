//
// Created by coocent-camera002 on 2024/5/10.
//

#ifndef FFMPEGSAMPLE_TEMPPLAYER_H
#define FFMPEGSAMPLE_TEMPPLAYER_H

#include "Player.h"
#include <string>

using namespace std;

class TempPlayer : public Player
{
    TempPlayer() {}

    ~TempPlayer();

    void prepareAsync() override;

    void start() override;

    void pause() override;

    void seekTo(float position) override;

    void stop() override;

    void release() override;
};


#endif //FFMPEGSAMPLE_TEMPPLAYER_H
