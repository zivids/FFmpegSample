//
// Created by xiongzw on 2024/5/10.
//

#include "FFmpegPlayer.h"

FFmpegPlayer::FFmpegPlayer() : Player()
{
    mVideoDecoder = new VideoDecoder();
    mRender = new NativeVideoRender();
}

void FFmpegPlayer::seekTo(float position)
{

}