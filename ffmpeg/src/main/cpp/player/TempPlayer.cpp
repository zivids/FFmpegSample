//
// Created by coocent-camera002 on 2024/5/10.
//

#include "TempPlayer.h"

TempPlayer::~TempPlayer()
{

}

void TempPlayer::prepareAsync()
{
    if (videoDecoder == nullptr)
    {
        return;
    }

    videoDecoder->prepare();
}

void TempPlayer::start()
{

}

void TempPlayer::pause()
{

}

void TempPlayer::seekTo(float position)
{

}

void TempPlayer::stop()
{

}

void TempPlayer::release()
{

}