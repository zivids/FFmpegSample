//
// Created by Administrator on 2024/5/3.
//

#include "Decoder.h"

Decoder::Decoder(const string &url)
{
    mUrl = unique_ptr<string>(new string(url));
}
