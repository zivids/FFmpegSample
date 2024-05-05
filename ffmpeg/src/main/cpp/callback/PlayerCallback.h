//
// Created by Administrator on 2024/5/2.
//

#ifndef FFMPEGSAMPLE_PLAYERCALLBACK_H
#define FFMPEGSAMPLE_PLAYERCALLBACK_H

class PlayerCallback
{
public:
    virtual ~PlayerCallback() {}

    virtual void onPrepared() = 0;
};

#endif //FFMPEGSAMPLE_PLAYERCALLBACK_H
