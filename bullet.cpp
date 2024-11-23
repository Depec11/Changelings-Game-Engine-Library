#include "bullet.h"
#include "base/game_loop.h"

Bullet::Bullet() {
	m_targetPosition = { 0, 0 };
	m_alpha = 0;
	m_targetRadius = 0.0f;
	m_autoCollisionBox = false;
	m_autoPivot = false;
	m_collisionBox->SetSize(Vector2(RECT_RADIUS, RECT_RADIUS) * 2);
	SetName(format("BULLET {}", GetID()));
	SetSpeed(5);
}
Bullet::~Bullet() {}
void Bullet::Update(float delta) {
	Character::Update(delta);
	m_alpha += delta * m_speed;
	if (m_alpha > 360) {
		m_alpha = 0.0f;
	}
	float s = sinf(m_alpha);
	float c = cosf(m_alpha);
	m_transform->SetPosition(m_targetPosition);
	if (s >= 0 && c >= 0) {
		if (s == 0) {
			m_transform->SetY(m_targetPosition.y);
		} else {
			m_transform->SetY(m_targetPosition.y - m_targetRadius * s);
		}
		if (c == 0) {
			m_transform->SetX(m_targetPosition.x);
		} else {
			m_transform->SetX(m_targetPosition.x + m_targetRadius * c);
		}
	} else if (s >= 0 && c < 0) {
		if (s == 0) {
			m_transform->SetY(m_targetPosition.y);
		} else {
			m_transform->SetY(m_targetPosition.y - m_targetRadius * s);
		}
		m_transform->SetX(m_targetPosition.x + m_targetRadius * c);
	} else if (s < 0 && c < 0) {
		m_transform->SetX(m_targetPosition.x + m_targetRadius * c);
		m_transform->SetY(m_targetPosition.y - m_targetRadius * s);
	} else if (s < 0 && c >= 0) {
		if (c == 0) {
			m_transform->SetX(m_targetPosition.x);
		} else {
			m_transform->SetX(m_targetPosition.x + m_targetRadius * c);
		}
		m_transform->SetY(m_targetPosition.y - m_targetRadius * s);
	}
}
void Bullet::Draw() {
	setlinecolor(LINE_COLOR);
	setfillcolor(FILL_COLOR);
	fillcircle(m_transform->GetX(), m_transform->GetY(), RADIUS);
}
void Bullet::SetTargetPosition(Vector2 pos) {
	m_targetPosition = pos;
}

void Bullet::SetAlpha(float alpha) {
	m_alpha = alpha;
}
float Bullet::GetAlpha() const {
	return m_alpha;
}
void Bullet::SetTargetRadius(float targetRadius) {
	m_targetRadius = targetRadius;
}
void Bullet::CollisionBy(shared_ptr<Character> other) {
	if (other->GetTag() == "ENEMY") {
		PlayMusic("hit");
		GameLoop::DelChar(*other);
	}
}
