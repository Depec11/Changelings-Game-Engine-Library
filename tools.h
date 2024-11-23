#pragma once

#include "base/extension.h"

string* GetCharImg(string name, string side, int n);
string GetImgResPath(string path);
void GetImgRes(IMAGE& img, string path);
shared_ptr<IMAGE> GetImgRes(string path);
shared_ptr<IMAGE[]> GetImgRes(string* path, int count);
