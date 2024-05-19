//
// Created by xiongzw on 2024/5/10.
//

#include "TempPlayer.h"

TempPlayer::TempPlayer() : Player()
{
    mVideoDecoder = new VideoDecoder();
    mRender = new NativeVideoRender();
}

void TempPlayer::seekTo(float position)
{

}