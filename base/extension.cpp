#include "extension.h"
#include <windows.h>

#pragma comment(lib, "MSIMG32.LIB")

const char* null_reference::what() const noexcept {
    return message.c_str();
}
Vector2::Vector2() {
    x = 0;
    y = 0;
}
Vector2::Vector2(float a, float b) {
    x = a;
    y = b;
}
Vector2::Vector2(int a, int b) {
    x = (float)a;
    y = (float)b;
}
Vector2 Vector2::operator+(const Vector2& other) {
    return Vector2(x + other.x, y + other.y);
}
Vector2 Vector2::operator-(const Vector2& other) {
    return Vector2(x - other.x, y - other.y);
}
Vector2 Vector2::operator/(const float& other) {
    return Vector2(x / other, y / other);
}
Vector2 Vector2::operator*(const float& other) {
    return Vector2(x * other, y * other);
}
bool Vector2::operator<(const Vector2& other) {
    return x < other.x && y < other.y;
}
bool Vector2::operator>(const Vector2& other) {
    return x > other.x && y > other.y;
}
bool Vector2::operator==(const Vector2& other) {
    return (x == other.x) && (y == other.y);
}
string Vector2::ToString() const {
    return format("<{}, {}>", x, y);
}
bool Vector2::IsZero() const {
    return x == 0 && y == 0;
}
Vector4::Vector4() {
    x = 0;
    y = 0;
    z = 0;
    w = 0;
}
Vector4::Vector4(float a, float b, float c, float d) {
    x = a;
    y = b;
    z = c;
    w = d;
}
Vector4::Vector4(Vector2 v1, Vector2 v2) {
    x = v1.x;
    y = v1.y;
    z = v2.x;
    w = v2.y;
}
string Vector4::ToString() const {
    return format("<{}, {}, {}, {}>", x, y, z, w);
}
bool Vector4::IsZero() const {
    return x == 0 && y == 0 && z == 0 && w == 0;
}
Object::Object() {
	m_id = m_number;
    m_number++;
    m_count++;
    m_name = "";
    m_isDelete = false;
    Log(format("OBJECT {} STRUCTED!", m_id));
}
Object::~Object() {
    m_count--;
    Log(format("OBJECT {} DESTRUCTED!\tLEFT: {}!", m_id, m_count));
}
void Object::SetName(string name) {
    m_name = name;
}
bool Object::operator==(const Object& obj) {
	return m_id == obj.m_id;
}
unsigned int Object::GetID() const {
    return m_id;
}
string Object::GetName() const {
    return m_name;
}
void Object::Log(string s) {
    Logger::Log(format("{}->{}", GetName(), s));
}
void Object::MarkDownDel() {
    m_isDelete = true;
}
bool Object::GetState() {
    return m_isDelete;
}
unsigned int Object::m_count = 0;
unsigned int Object::m_number = 0;
InvokeData::InvokeData() {
    func = bind([]() -> void {});
    time = 0;
    SetName(format("INVOKEDATA {}", GetID()));
}
InvokeData::InvokeData(function<void()> func, float time) : func(func), time(time) {
    SetName(format("INVOKEDATA {}", GetID()));
}
InvokeData::~InvokeData() {}
void PutImageAlpha(int x, int y, IMAGE* img) {
    int w = img->getwidth();
    int h = img->getheight();
    AlphaBlend(GetImageHDC(nullptr), x, y, w, h, GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA });
}
Vector2 Normalize(Vector2 vector) {
    float sq = vector.x * vector.x + vector.y * vector.y;
    if (sq == 0) {
        return vector;
    }
    float m = sqrt(sq);
    return Vector2(vector.x / m, vector.y / m);
}
Vector2 GetShadowPosOffset(int pw, int ph, int sw, int sh) {
    float ofsx = pw - sw;
    ofsx /= 2;
    float ofsy = ph - sh / 2.0f;
    return Vector2(ofsx, ofsy);
}

int RandomRange(int min, int max) {
    random_device rd;
    int diff = max - min;
    return min + rd() % diff;
}

float RandomUniform() {
    random_device rd;
    default_random_engine e(rd());
    uniform_real_distribution<double> u(0, 1);
    return u(e);
}
void RegisterMusic(const char* path, const char* nickname) {
    mciSendString(format("open {}.mp3 alias {}", path, nickname).c_str(), NULL, 0, NULL);
}
void PlayMusic(const char* nickname, bool isRepeat) {
    mciSendString(format("play {} {} from 0", nickname, isRepeat ? "repeat" : "").c_str(), NULL, 0, NULL);
}
void PauseMusic(const char* nickname) {
    mciSendString(format("pause {}", nickname).c_str(), NULL, 0, NULL);
}
void StopMusic(const char* nickname) {
    mciSendString(format("stop {}", nickname).c_str(), NULL, 0, NULL);
}
void ResumeMusic(const char* nickname) {
    mciSendString(format("resume {}", nickname).c_str(), NULL, 0, NULL);
}

