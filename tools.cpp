#include "tools.h"

string* GetCharImg(string name, string side, int n) {
	string* imgs = new string[n];
	for (int i = 0; i < n; i++) {
		string s = format("{}_{}_{}", name, side, i);
		imgs[i] = s;
	}
	return imgs;
}
string GetImgResPath(string path) {
	string p = format("./img/{}.png", path);
	return p;
}
void GetImgRes(IMAGE& img, string path) {
	string p = GetImgResPath(path);
	loadimage(&img, p.c_str());
}
shared_ptr<IMAGE> GetImgRes(string path) {
	IMAGE img;
	GetImgRes(img, path);
	return make_shared<IMAGE>(img);
}
shared_ptr<IMAGE[]> GetImgRes(string* path, int count) {
	shared_ptr<IMAGE[]> res = make_shared<IMAGE[]>(count);
	for (int i = 0; i < count; i++) {
		GetImgRes(((res.get())[i]), path[i]);
	}
	return res;
}
