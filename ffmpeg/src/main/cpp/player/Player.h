//
// Created by Administrator on 2024/5/1.
//

#ifndef FFMPEGSAMPLE_PLAYER_H
#define FFMPEGSAMPLE_PLAYER_H

#include <string>
#include "Decoder.h"

using namespace std;

class Player
{
public:
    Player() {};

    virtual ~Player() {};

    virtual void setDataSource(const string &url);

    virtual void prepareAsync() = 0;

    virtual void start() = 0;

    virtual void pause() = 0;

    virtual void seekTo(float position) = 0;

    virtual void stop() = 0;

    virtual void release();

protected:
    unique_ptr<string> mUrl = nullptr;
    Decoder *videoDecoder = nullptr;
};


#endif //FFMPEGSAMPLE_PLAYER_H
