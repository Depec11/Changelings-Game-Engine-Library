#pragma once

#include "base/characters.h"

class Bullet : public Character {
public:
	const static int RADIUS = 10;
	const static int RECT_RADIUS = 5;
	const static COLORREF LINE_COLOR = RGB(255, 155, 50);
	const static COLORREF FILL_COLOR = RGB(200, 75, 10);
	Bullet();
	~Bullet();
	void Update(float delta) override;
	void Draw() override;
	void SetTargetPosition(Vector2 pos);
	void SetAlpha(float alpha);
	float GetAlpha() const;
	void SetTargetRadius(float targetRadius);
	void CollisionBy(shared_ptr<Character> other) override;
private:
	float m_alpha;
	Vector2 m_targetPosition;
	float m_targetRadius;
};
