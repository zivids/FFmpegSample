//
// Created by Administrator on 2024/5/13.
//

#ifndef FFMPEGSAMPLE_PREPARECALLBACK_H
#define FFMPEGSAMPLE_PREPARECALLBACK_H

class PrepareCallback
{
public:
    virtual ~PrepareCallback() {}

    virtual void onPrepared() = 0;
};

#endif //FFMPEGSAMPLE_PREPARECALLBACK_H
