#include "paimon.h"
#include "base/game_loop.h"

Paimon::Paimon(float anim_speed) {
	string* leftImgs = GetCharImg("paimon", "left", 6);
	string* rightImgs = GetCharImg("paimon", "right", 6);
	SetSpeed(250);
	InitTransform(600, 300, false);
	InitAnimation(anim_speed, GetImgRes(leftImgs, 6), 6, GetImgRes(rightImgs, 6), 6, GetImgRes("shadow_player"));
	m_autoCollisionBox = false;
	m_collisionBox->SetSize(Vector2(45, 70));
	SetName("PAIMON");
	m_radius = 100;
	m_radiusMIN = 100;
	m_radiusMAX = 175;
	m_modSpeed = 100;
}
Paimon::~Paimon() {
	m_bullets.Clear();
}
void Paimon::Awake() {
	for (int i = 0; i < 3; i++) {
		shared_ptr<Bullet> b = make_shared<Bullet>();
		b->SetAlpha(i * 90);
		m_bullets.Add(b);
		GameLoop::AddChar(b);
	}
	m_bullets.AddToContainer();
}
void Paimon::Update(float delta) {
	Character::Update(delta);
	m_radius += m_modSpeed * delta;
	if (m_radius > m_radiusMAX) {
		m_modSpeed *= -1;
	}
	if (m_radius < m_radiusMIN) {
		m_modSpeed *= -1;
	}
	for (int i = 0; i < m_bullets.Count(); i++) {
		m_bullets[i]->SetTargetPosition(m_transform->GetPosition() + m_transform->GetPivot());
		m_bullets[i]->SetTargetRadius(m_radius);
	}
}
void Paimon::ProcessEvent(const ExMessage &msg) {
	Character::ProcessEvent(msg);
	if (msg.message == WM_KEYDOWN) {
		switch (msg.vkcode) {
		case VK_UP: m_movement.y = -1; break;
		case 87: m_movement.y = -1; break;
		case VK_DOWN: m_movement.y = 1; break;
		case 83: m_movement.y = 1; break;
		case VK_LEFT: m_movement.x = -1; break;
		case 65: m_movement.x = -1; break;
		case VK_RIGHT: m_movement.x = 1; break;
		case 68: m_movement.x = 1; break;
		default: break;
		}
	} else if (msg.message == WM_KEYUP) {
		switch (msg.vkcode) {
		case VK_UP: m_movement.y = 0; break;
		case 87: m_movement.y = 0; break;
		case VK_DOWN: m_movement.y = 0; break;
		case 83: m_movement.y = 0; break;
		case VK_LEFT: m_movement.x = 0; break;
		case 65: m_movement.x = 0; break;
		case VK_RIGHT: m_movement.x = 0; break;
		case 68: m_movement.x = 0; break;
		default: break;
		}
	}
	m_movement = Normalize(m_movement);
}
void Paimon::CollisionBy(shared_ptr<Character> other) {
	Character::CollisionBy(other);
	if (other->GetTag() == "ENEMY") {
		PlayMusic("hurt");
		GameLoop::SetIsPlaying(false);
		int res = MessageBox(NULL, "YOU LOSE!!!", "GAME OVER", MB_OK);
		if (res == IDOK) {
			GameLoop::Quit();
		}
	}
}
