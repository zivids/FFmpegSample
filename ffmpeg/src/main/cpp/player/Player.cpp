//
// Created by Administrator on 2024/5/1.
//

#include "Player.h"
#include "LogUtils.h"

void Player::setDataSource(const string &url)
{
    if (videoDecoder == nullptr)
    {
        videoDecoder = new VideoDecoder(url);
    }
    else
    {
        videoDecoder->setUrl(url);
    }
}