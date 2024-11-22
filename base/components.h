#pragma once

#include "extension.h"

class Component : public Object {
public:
	Component();
	virtual ~Component();
	virtual void Awake();
	virtual void Delete();
	virtual void Update(float delta);
	virtual void ProcessEvent(const ExMessage& msg);
protected:
	void Invoke(function<void()> func, float time);
private:
	DynamicContainer<InvokeData> m_invokes;
};
class Transform : public Component {
public:
	Transform(float x = 0, float y = 0, bool reverse = false);
	~Transform();
	float GetX() const;
	float GetY() const;
	void SetX(float x);
	void SetY(float y);
	bool GetReverse() const;
	void SetReverse(bool reverse);
	Vector2 GetPosition() const;
	void SetPosition(Vector2 pos);
	void SetPivot(Vector2 pivot);
	Vector2 GetPivot() const;
private:
	Vector2 m_position;
	bool m_reverse;
	Vector2 m_pivot;
};
class Animation : public Component {
public:
	Animation(float speed = 0);
	~Animation();
	void SetAnimationSpeed(float animationSpeed);
	void SetLImgs(string imagePath[], int n);
	void SetRImgs(string imagePath[], int n);
	void SetShadow(string path);
	IMAGE GetCurrImg(bool reverse);
	IMAGE GetLImg(int index);
	IMAGE GetRImg(int index);
	IMAGE GetShadow() const;
	void SetShadowOffset(float x, float y);
	Vector2 GetShadowOffset() const;
	Vector2 GetSize(bool reverse);
	Vector2 GetOffset(bool reverse);
	void SetAnimSpeed(float speed);
	float GetAnimSpeed() const;
	void Update(float delta) override;
private:
	shared_ptr<IMAGE[]> m_LImgs;
	shared_ptr<IMAGE[]> m_RImgs;
	shared_ptr<IMAGE> m_defaultImg;
	shared_ptr<IMAGE> m_shadow;
	int m_LImgN;
	int m_RImgN;
	int m_currL;
	int m_currR;
	float m_animationSpeed;
	float m_timeCount;
	Vector2 m_shadowOffset;
	void SetImgs(shared_ptr<IMAGE[]>& imgs, int& count, int& curr, string imagePath[], int n) const;
	IMAGE GetImg(shared_ptr<IMAGE[]>& imgs, int n, int index);
};
class CollisionBox : public Component {
public:
	CollisionBox();
	~CollisionBox();
	Vector2 GetSize() const;
	void SetSize(Vector2 size);
	bool GetMute() const;
	void SetMute(bool isTrigger);
private:
	Vector2 m_size;
	bool m_mute;
};
