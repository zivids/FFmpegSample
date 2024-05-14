//
// Created by xiongzw on 2024/5/10.
//

#include "TempPlayer.h"

TempPlayer::TempPlayer() : Player()
{
    videoDecoder = new VideoDecoder();
}

void TempPlayer::seekTo(float position)
{

}