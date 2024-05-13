//
// Created by Administrator on 2024/5/13.
//

#ifndef FFMPEGSAMPLE_ONPREPARECALLBACK_H
#define FFMPEGSAMPLE_ONPREPARECALLBACK_H

class OnPrepareCallback
{
public:
    virtual ~OnPrepareCallback() {}

    virtual void onPrepared() = 0;
};

#endif //FFMPEGSAMPLE_ONPREPARECALLBACK_H
