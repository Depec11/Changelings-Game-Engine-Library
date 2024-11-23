#include "enemy.h"
#include "tools.h"

Enemy::Enemy() {
	SetTag("ENEMY");
}
Enemy::~Enemy() {}
Boar::Boar(float anim_speed) {
	m_target = m_transform->GetPosition();
	Init(100);
	m_animation->SetAnimSpeed(anim_speed);
	SetAutoCollisionBox(false);
	InitCollisionBox(Vector2(65, 45), false);
}
Boar::~Boar() {}
void Boar::Update(float delta) {
	Enemy::Update(delta);
	Vector2 pos = m_transform->GetPosition();
	Vector2 diff = m_target - pos;
	m_movement = Normalize(diff);
}
void Boar::SetTarget(Vector2 target) {
	m_target = target;
}
