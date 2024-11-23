#pragma once

#include "base/characters.h"

class Enemy : public Character {
public:
	Enemy();
	virtual ~Enemy();
};
class Boar : public Enemy {
public:
	Boar(float anim_speed = 0);
	~Boar();
	void Update(float delta) override;
	void SetTarget(Vector2 target);
private:
	Vector2 m_target;
};
