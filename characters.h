#pragma once

#include "components.h"

class Character : public Component {
public:
	Character();
	virtual ~Character();
	Transform& GetTransform();
	Animation& GetAnimation();
	CollisionBox& GetCollisionBox();
	void Init(float speed);
	void InitTransform(float x, float y, bool reverse);
	void InitAnimation(float animationSpeed, string LImgPath[], int LN, string RImgPath[], int RN, string shadowPath = "", float sx = 0, float sy = 0);
	void InitCollisionBox(Vector2 size, bool mute);
	void Update(float delta) override;
	void SetSpeed(float speed);
	void Move(float delta);
	void SetAutoCollisionBox(bool autoCollisionBox);
	void SetAutoPivot(bool autoPivot);
	Vector2 GetSize();
	virtual void CollisionBy(shared_ptr<Character> other);
	string GetTag() const;
	void SetTag(string tag);
	virtual void Draw();
	void DrawCollisionBox();
	Vector4 GetCollisionRect() const;
protected:
	string m_tag;
	float m_speed;
	Vector2 m_movement;
	bool m_autoCollisionBox;
	bool m_autoPivot;
	shared_ptr<Transform> m_transform;
	shared_ptr<Animation> m_animation;
	shared_ptr<CollisionBox> m_collisionBox;
};
class Scene : public Component {
public:
	Scene();
	virtual ~Scene();
};
