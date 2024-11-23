#pragma once

#include "bullet.h"
#include "tools.h"

class Paimon : public Character  {
public:
	Paimon(float anim_speed = 0);
	~Paimon();
	void Awake();
	void Update(float delta) override;
	void ProcessEvent(const ExMessage& msg) override;
	void CollisionBy(shared_ptr<Character> other) override;
private:
	float m_radius, m_radiusMIN, m_radiusMAX, m_modSpeed;
	DynamicContainer<Bullet> m_bullets;
};
