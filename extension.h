#pragma once

#include "dynamic_container.h"

#include <iostream>
#include <easyx.h>
#include <exception>
#include <random>

#pragma comment(lib, "Winmm.lib")

using namespace std;

class null_reference : public exception {
public:
	null_reference(const string& msg) : message(msg) {}
	const char* what() const noexcept override;
private:
	string message;
};
struct Vector2 {
	float x;
	float y;
	Vector2();
	Vector2(float a, float b);
	Vector2 operator+(const Vector2& other);
	Vector2 operator-(const Vector2& other);
	Vector2 operator/(const float& other);
	Vector2 operator*(const float& other);
	bool operator<(const Vector2& other);
	bool operator>(const Vector2& other);
	bool operator==(const Vector2& other);
	string ToString() const;
	bool IsZero() const;
};
struct Vector4 {
	float x;
	float y;
	float z;
	float w;
	Vector4();
	Vector4(float a, float b, float c, float d);
	Vector4(Vector2 v1, Vector2 v2);
	string ToString() const;
	bool IsZero() const;
};
class Object {
public:
	Object();
	virtual ~Object();
	void SetName(string name);
	bool operator==(const Object& obj);
	unsigned int GetID() const;
	string GetName() const;
	void Log(string s);
	void MarkDownDel();
	bool GetState();
private:
	unsigned int m_id;
	string m_name;
	bool m_isDelete;
	static unsigned int m_number;
	static unsigned int m_count;
};
class InvokeData : public Object {
public:
	function<void()> func;
	float time;
	InvokeData();
	InvokeData(function<void()> func, float time);
	~InvokeData();
};
string GetImgResPath(string path);
void GetImgRes(IMAGE& img, string path);
void PutImageAlpha(int x, int y, IMAGE* img);
Vector2 Normalize(Vector2 vector);
Vector2 GetShadowPosOffset(int pw, int ph, int sw, int sh);
int RandomRange(int min, int max);
float RandomUniform();
void RegisterMusic(const char* path, const char* nickname);
void PlayMusic(const char* nickname, bool isRepeat = false);
void PauseMusic(const char* nickname);
void StopMusic(const char* nickname);
void ResumeMusic(const char* nickname);
