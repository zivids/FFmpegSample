//
// Created by Administrator on 2024/5/3.
//
#include "VideoDecoder.h"
#include "LogUtils.h"

VideoDecoder::~VideoDecoder()
{

}

void VideoDecoder::open()
{
    LOGD("Decoder: %s", mUrl->c_str());
}

void VideoDecoder::release()
{

}