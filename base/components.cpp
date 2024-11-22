#include "components.h"

Component::Component() {
	SetName(format("COMPONENT {}", GetID()));
}
Component::~Component() {
	m_invokes.Delete();
}
void Component::Awake() {}
void Component::Delete() {}
void Component::Update(float delta) {
	m_invokes.Iterate([this, delta](shared_ptr<InvokeData> i) -> void {
		i->time -= delta;
		if (i->time <= 0) {
			i->func();
			m_invokes.Del(*i);
		}
	});
	m_invokes.ClearBin();
	m_invokes.AddToContainer();
}
void Component::ProcessEvent(const ExMessage& msg) {}
void Component::Invoke(function<void()> func, float time) {
	shared_ptr<InvokeData> data =  make_shared<InvokeData>(func, time);
	m_invokes.Add(data);
	data = nullptr;
}
Transform::Transform(float x, float y, bool reverse) {
	m_position = { x,y };
	m_reverse = reverse;
	m_pivot = { 0,0 };
	SetName(format("TRANSFORM {}", GetID()));
}
Transform::~Transform() {}
float Transform::GetX() const {
	return m_position.x;
}
float Transform::GetY() const {
	return m_position.y;
}
void Transform::SetX(float x) {
	m_position.x = x;
}
void Transform::SetY(float y) {
	m_position.y = y;
}
bool Transform::GetReverse() const {
	return m_reverse;
}
void Transform::SetReverse(bool reverse) {
	m_reverse = reverse;
}
Vector2 Transform::GetPosition() const {
	return m_position;
}
void Transform::SetPosition(Vector2 pos) {
	m_position = pos;
}
void Transform::SetPivot(Vector2 pivot) {
	m_pivot = pivot;
}
Vector2 Transform::GetPivot() const {
	return m_pivot;
}
Animation::Animation(float speed) {
	m_LImgs = make_shared<IMAGE[]>(1);
	m_RImgs = make_shared<IMAGE[]>(1);
	m_shadow = make_shared<IMAGE>();
	m_defaultImg = make_shared<IMAGE>();
	m_LImgN = 0;
	m_RImgN = 0;
	m_currL = -1;
	m_currR = -1;
	m_animationSpeed = speed;
	m_timeCount = 0;
	m_shadowOffset = { 0, 0 };
	SetName(format("ANIMATION {}", GetID()));
}
Animation::~Animation() {}
void Animation::SetAnimationSpeed(float animationSpeed) {
	m_animationSpeed = animationSpeed;
}
void Animation::SetLImgs(string imagePath[], int n) {
	SetImgs(m_LImgs, m_LImgN, m_currL, imagePath, n);
}
void Animation::SetRImgs(string imagePath[], int n) {
	SetImgs(m_RImgs, m_RImgN, m_currR, imagePath, n);
}
void Animation::SetShadow(string path) {
	if (path == "") {
		return;
	}
	m_shadow.reset(new IMAGE());
	GetImgRes(*(m_shadow.get()), path);
}
IMAGE Animation::GetCurrImg(bool reverse) {
	return reverse ? GetRImg(m_currR) : GetLImg(m_currL);
}
IMAGE Animation::GetLImg(int index) {
	return GetImg(m_LImgs, m_LImgN, index);
}
IMAGE Animation::GetRImg(int index){
	return GetImg(m_RImgs, m_RImgN, index);
}
IMAGE Animation::GetShadow() const {
	return *(m_shadow.get());
}
void Animation::SetShadowOffset(float x, float y) {
	m_shadowOffset.x = x;
	m_shadowOffset.y = y;
}
Vector2 Animation::GetShadowOffset() const {
	return m_shadowOffset;
}
Vector2 Animation::GetSize(bool reverse) {
	IMAGE img = GetCurrImg(reverse);
	return Vector2(img.getwidth(), img.getheight());
}
Vector2 Animation::GetOffset(bool reverse) {
	return GetSize(reverse) / 2;
}
void Animation::SetAnimSpeed(float speed) {
	m_animationSpeed = speed;
}
float Animation::GetAnimSpeed() const {
	return m_animationSpeed;
}
void Animation::Update(float delta) {
	Component::Update(delta);
	m_timeCount += delta;
	if (m_timeCount >= m_animationSpeed) {
		m_timeCount = 0;
		if (m_currL >= 0) {
			m_currL++;
			if (m_currL >= m_LImgN) {
				m_currL = 0;
			}
		}
		if (m_currR >= 0) {
			m_currR++;
			if (m_currR >= m_RImgN) {
				m_currR = 0;
			}
		}
	}
}
void Animation::SetImgs(shared_ptr<IMAGE[]>& imgs, int& count, int& curr, string imagePath[], int n) const {
	imgs.reset(new IMAGE[n]);
	count = n;
	curr = 0;
	for (int i = 0; i < n; i++) {
		GetImgRes(((imgs.get())[i]), imagePath[i]);
	}
}
IMAGE Animation::GetImg(shared_ptr<IMAGE[]>& imgs, int n, int index) {
	if (index < 0 || index >= n) {
		return *m_defaultImg;
	}
	return imgs[index];
}
CollisionBox::CollisionBox() {
	m_size = { 0,0 };
	m_mute = false;
	SetName(format("COLLISION BOX {}", GetID()));
}
CollisionBox::~CollisionBox() {}
Vector2 CollisionBox::GetSize() const {
	return m_size;
}
void CollisionBox::SetSize(Vector2 size) {
	m_size = size;
}
bool CollisionBox::GetMute() const {
	return m_mute;
}
void CollisionBox::SetMute(bool isTrigger) {
	m_mute = isTrigger;
}
