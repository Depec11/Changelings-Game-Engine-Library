#include "characters.h"

Character::Character() : Component() {
	m_movement = { 0, 0 };
	m_speed = 0;
	m_autoCollisionBox = true;
	m_autoPivot = true;
	m_transform = make_unique<Transform>();
	m_animation = make_unique<Animation>();
	m_collisionBox = make_unique<CollisionBox>();
	SetName(format("CHARACTER {}", GetID()));
	m_tag = "DEFAULT";
}
Character::~Character() {}
Transform& Character::GetTransform() {
	return *m_transform;
}
Animation& Character::GetAnimation() {
	return *m_animation;
}
CollisionBox& Character::GetCollisionBox() {
	return *m_collisionBox;
}
void Character::Init(float speed) {
	m_speed = speed;
}
void Character::InitTransform(float x, float y, bool reverse) {
	m_transform->SetX(x);
	m_transform->SetY(y);
	m_transform->SetReverse(reverse);
}
void Character::InitAnimation(float animationSpeed, shared_ptr<IMAGE[]> limgs, int LN, shared_ptr<IMAGE[]> rimgs, int RN, shared_ptr<IMAGE> simg, float sx, float sy) {
	m_animation->SetAnimSpeed(animationSpeed);
	m_animation->SetLImgs(limgs, LN);
	m_animation->SetRImgs(rimgs, RN);
	m_animation->SetShadow(simg);
	m_animation->SetShadowOffset(sx, sy);
}
void Character::InitCollisionBox(Vector2 size, bool mute) {
	m_collisionBox->SetSize(size);
	m_collisionBox->SetMute(mute);
}
void Character::Update(float delta) {
	Component::Update(delta);
	if (m_autoPivot) {
		m_transform->SetPivot(m_animation->GetSize(m_transform->GetReverse()) / 2);
	}
	if (m_autoCollisionBox) {
		m_collisionBox->SetSize(m_animation->GetSize(m_transform->GetReverse()));
	}
	m_transform->Update(delta);
	m_animation->Update(delta);
	m_collisionBox->Update(delta);
}
void Character::SetSpeed(float speed) {
	m_speed = speed;
}
void Character::Move(float delta) {
	m_transform->SetX(m_transform->GetX() + m_speed * delta * m_movement.x);
	m_transform->SetY(m_transform->GetY() + m_speed * delta * m_movement.y);
	if (m_movement.x != 0) {
		m_transform->SetReverse(m_movement.x > 0);
	}
}
void Character::SetAutoCollisionBox(bool autoCollisionBox) {
	m_autoCollisionBox = autoCollisionBox;
}
void Character::SetAutoPivot(bool autoPivot) {
	m_autoPivot = autoPivot;
}
Vector2 Character::GetSize() {
	return m_animation->GetSize(m_transform->GetReverse());
}
void Character::CollisionBy(shared_ptr<Character> other) {}
string Character::GetTag() const {
	return m_tag;
}
void Character::SetTag(string tag) {
	m_tag = tag;
}
void Character::Draw() {
	Vector2 sdof = m_animation->GetShadowOffset();
	int x = round(m_transform->GetX());
	int y = round(m_transform->GetY());
	IMAGE img = m_animation->GetCurrImg(m_transform->GetReverse());
	IMAGE shadow = m_animation->GetShadow();
	Vector2 posofs = GetShadowPosOffset(img.getwidth(), img.getheight(), shadow.getwidth(), shadow.getheight());
	PutImageAlpha(round(x + posofs.x) + sdof.x, round(y + posofs.y) + sdof.y, &shadow);
	PutImageAlpha(x, y, &img);
}
void Character::DrawCollisionBox() {
	setlinecolor(RGB(34, 177, 76));
	setfillcolor(RGB(181, 230, 29));
	Vector4 rect = GetCollisionRect();
	if (rect.x == 0 && rect.y == 0 && rect.z == 0 && rect.w == 0) {
		return;
	}
	fillrectangle(rect.x, rect.y, rect.z, rect.w);
}
Vector4 Character::GetCollisionRect() const {
	Vector2 size = m_collisionBox->GetSize();
	if (m_collisionBox->GetMute() || size.IsZero()) {
		return Vector4();
	}
	Vector2 pivot = m_transform->GetPivot();
	Vector2 position = m_transform->GetPosition();
	Vector2 top = position + pivot - size / 2;
	return Vector4(top.x, top.y, top.x + size.x, top.y + size.y);
}
Scene::Scene() {
	SetName(format("SCENE {}", GetID()));
}
Scene::~Scene() {}
