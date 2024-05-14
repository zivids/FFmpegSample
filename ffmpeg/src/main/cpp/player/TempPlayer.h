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
public:
    TempPlayer();

    ~TempPlayer() {};

    void seekTo(float position) override;
};


#endif //FFMPEGSAMPLE_TEMPPLAYER_H
