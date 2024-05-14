//
// Created by Administrator on 2024/5/1.
//

#include "Player.h"
#include "LogUtils.h"

Player::~Player()
{
    if (videoDecoder != nullptr)
    {
        delete videoDecoder;
        videoDecoder = nullptr;
    }
}

void Player::setDataSource(const string &url)
{
    videoDecoder->setUrl(url);
}

void Player::prepareAsync(PrepareCallback *callback)
{
    videoDecoder->prepare(callback);
}

void Player::start()
{
    if (!videoDecoder->isDecoderPrepared())
    {
        return;
    }

    videoDecoder->start();
}

void Player::pause()
{
    if (!videoDecoder->isDecoderPrepared() || videoDecoder->decoderState() != STATE_DECODING)
    {
        return;
    }

    videoDecoder->pause();
}

void Player::stop()
{
    if (!videoDecoder->isDecoderPrepared() || videoDecoder->decoderState() == STATE_STOP
        || videoDecoder->decoderState() == STATE_IDLE)
    {
        return;
    }

    videoDecoder->stop();
}

void Player::release()
{
    stop();

    delete videoDecoder;
    videoDecoder = nullptr;
}