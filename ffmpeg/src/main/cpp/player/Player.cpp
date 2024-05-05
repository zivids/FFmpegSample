//
// Created by Administrator on 2024/5/1.
//

#include "Player.h"
#include "LogUtils.h"

void Player::setDataSource(const string &url)
{
    mUrl = unique_ptr<string>(new string(url));
}

void Player::release()
{
    if (mUrl != nullptr)
    {
        mUrl.release();
    }
}
