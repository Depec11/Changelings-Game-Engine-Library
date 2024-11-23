#include "ui.h"
#include "game_loop.h"

UI::UI() {
	m_state = State::NORMAL;
	m_transform = make_shared<Transform>();
	m_onClick = bind([]() -> void{});
	SetName(format("UI {}", GetID()));
}
UI::~UI() {}
void UI::Draw() {
	DrawImg(GetCurrImg());
}
void UI::ProcessEvent(const ExMessage& msg) {
	// Log(format("{}", (int)m_state));
	bool mh = MouseHoving();
	switch (m_state) {
	case UI::State::NORMAL: {
		if (mh) {
			m_state = State::HOVERING;
		}
	} break;
	case UI::State::HOVERING: {
		if (!mh) {
			ResetState();
			return;
		}
		if (msg.message == WM_LBUTTONDOWN) {
			m_state = State::PRESSED;
		}
	} break;
	case UI::State::PRESSED: {
		if (msg.message == WM_LBUTTONUP) {
			m_state = mh ? State::HOVERING : State::NORMAL;
			if (mh) {
				m_onClick();
			}
		}
	} break;
	default:
		break;
	}
}
Transform& UI::GetTransform() {
	return *m_transform;
}
void UI::InitTransform(float x, float y, bool reverse) {
	m_transform->SetX(x);
	m_transform->SetY(y);
	m_transform->SetReverse(reverse);
}
void UI::SetOnClick(function<void()> func) {
	m_onClick = func;
}
void UI::DrawImg(IMAGE img) {
	PutImageAlpha(m_transform->GetX(), m_transform->GetY(), &img);
}
bool UI::MouseHoving() {
	IMAGE currImg = GetCurrImg();
	if (currImg.getwidth() == 0 || currImg.getheight() == 0) {
		return false;
	}
	Vector2 mousePos = GameLoop::GetMousePosition();
	Vector4 rect;
	rect.x = m_transform->GetX();
	rect.y = m_transform->GetY();
	rect.z = rect.x + currImg.getwidth();
	rect.w = rect.y + currImg.getheight();
	if (mousePos.x >= rect.x && mousePos.x <= rect.z && mousePos.y >= rect.y && mousePos.y <= rect.w) {
		return true;
	} else {
		return false;
	}
}
void UI::ResetState() {
	m_state = State::NORMAL;
}
Button::Button() {
	m_normalAnimation = make_shared<SimpleAnimation>();
	m_hoveringAnimation = make_shared<SimpleAnimation>();
	m_pressedAnimation = make_shared<SimpleAnimation>();
	SetName(format("BUTTON {}", GetID()));
}
void Button::Update(float delta) {
	Component::Update(delta);
	m_normalAnimation->Update(delta);
	m_hoveringAnimation->Update(delta);
	m_pressedAnimation->Update(delta);
}
void Button::InitNormalAnimation(float anime_speed, shared_ptr<IMAGE[]> imgs, int count) {
	m_normalAnimation->SetAnimSpeed(anime_speed);
	m_normalAnimation->SetImgs(imgs, count);
}
void Button::InitHoveringAnimation(float anime_speed, shared_ptr<IMAGE[]> imgs, int count) {
	m_hoveringAnimation->SetAnimSpeed(anime_speed);
	m_hoveringAnimation->SetImgs(imgs, count);
}
void Button::InitPressedAnimation(float anime_speed, shared_ptr<IMAGE[]> imgs, int count) {
	m_pressedAnimation->SetAnimSpeed(anime_speed);
	m_pressedAnimation->SetImgs(imgs, count);
}
IMAGE Button::GetCurrImg() {
	switch (m_state) {
	case State::NORMAL: 
		return m_normalAnimation->GetCurrImg();
	case State::HOVERING: 
		return m_hoveringAnimation->GetCurrImg();
	case State::PRESSED: 
		return m_pressedAnimation->GetCurrImg();
	default: 
		return IMAGE();
	}
}
