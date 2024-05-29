//
// Created by Administrator on 2024/5/1.
//

#ifndef FFMPEGSAMPLE_PLAYER_H
#define FFMPEGSAMPLE_PLAYER_H

#include <android/native_window.h>
#include <string>
#include <thread>
#include "Decoder.h"
#include "Render.h"
#include "PrepareCallback.h"

using namespace std;

enum PlayerState
{
    STATE_IDLE,
    STATE_PREPARED,
    STATE_STARTED,
    STATE_PAUSED,
    STATE_STOPPED,
};

class Player
{
public:
    Player() {};

    virtual ~Player();

    virtual void setDataSource(const string &url);

    virtual void setSurface(ANativeWindow *nativeWindow);

    virtual void prepareAsync(PrepareCallback *callback);

    virtual void start();

    virtual void pause();

    virtual void seekTo(float position) = 0;

    virtual void stop();

    virtual void release();

protected:
    virtual void prepare(PrepareCallback *callback);

protected:
    Decoder *mVideoDecoder = nullptr;
//    Decoder *mAudioDecoder = nullptr;
    Render *mRender = nullptr;

private:
    mutex mLockMutex;
    thread *mThread = nullptr;
    condition_variable mCondition;
    volatile int mPlayerState = STATE_IDLE;
    bool mInputEOF;
    bool mOutputEOF;
};


#endif //FFMPEGSAMPLE_PLAYER_H
