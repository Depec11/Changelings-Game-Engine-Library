#include "main_scene.h"
#include "base/game_loop.h"

#include <random>
#include <windows.h>

void GenBg(string path) {
	shared_ptr<Character> bgImg = GameLoop::AddChar();
	string bgs[1] = { path };
	shared_ptr<IMAGE[]> imgs = GetImgRes(bgs, 1);
	bgImg->InitAnimation(0, imgs, 1, imgs, 1, nullptr);
	bgImg->SetAutoPivot(false);
	bgImg->SetAutoCollisionBox(false);
	bgImg->InitCollisionBox(Vector2(0, 0), true);
	bgImg = nullptr;
}
MainScene::MainScene() {
	m_LImgs = shared_ptr<IMAGE[]>();
	m_RImgs = shared_ptr<IMAGE[]>();
	m_enemyShadow = make_shared<IMAGE>();
	m_paimon = shared_ptr<Paimon>();
	m_playingState = true;
	InitMenu();
}
MainScene::~MainScene() {
	m_paimon = nullptr;
	m_enemys.Clear();
	StopMusic("bgm");
}
void MainScene::Awake() {
	RegisterMusic("mus/bgm", "bgm");
	RegisterMusic("mus/hit", "hit");
	RegisterMusic("mus/hurt", "hurt");
}
void MainScene::Delete() {}
void MainScene::Update(float delta) {
	if (!GameLoop::GetIsPlaying()) {
		if (m_playingState) {
			PauseMusic("bgm");
		}
		m_playingState = false;
		return;
	}
	Component::Update(delta);
	if (!m_playingState) {
		ResumeMusic("bgm");
	}
	m_playingState = true;
	for (int i = 0; i < m_enemys.Count(); i++) {
		if (m_enemys[i] == nullptr) {
			m_enemys.Del(i);
		}
		m_enemys[i]->SetTarget(m_paimon->GetTransform().GetPosition());
	}
	m_enemys.ClearBin();
	m_enemys.AddToContainer();
}
void MainScene::GenPaimon() {
	m_paimon = make_shared<Paimon>(ANIM_SPEED);
	GameLoop::AddChar(m_paimon);
}
void MainScene::GenBoar() {
	shared_ptr<Boar> b = make_shared<Boar>(ANIM_SPEED);
	b->GetAnimation().SetLImgs(m_LImgs, 6);
	b->GetAnimation().SetRImgs(m_RImgs, 6);
	Direction d = Direction(RandomRange(0, 4));
	Vector2 size = GameLoop::GetSize();
	Vector2 psize = b->GetSize();
	int rx = RandomRange(0, size.x - psize.x + 1);
	int ry = RandomRange(0, size.y - psize.y + 1);
	switch (d) {
	case Direction::UP: b->InitTransform(rx, 0, false); break;
	case Direction::RIGHT: b->InitTransform(size.x - psize.x, ry, false); break;
	case Direction::DOWN: b->InitTransform(rx, size.y - psize.y, false); break;
	case Direction::LEFT: b->InitTransform(0, ry, false); break;
	default: b->InitTransform(0, 0, false); break;
	}
	GameLoop::AddChar(b);
	m_enemys.Add(b);
	b = nullptr;
}
void MainScene::StartInvokeBoar() {
	GenBoar();
	Invoke([this]() -> void { StartInvokeBoar(); }, 2 * RandomUniform());
}
void MainScene::InitMenu() {
	GenBg("menu");
	shared_ptr<Button> bgb = GenBtn("ui_start_idle", "ui_start_hovered", "ui_start_pushed", [this]() -> void { InitGame(); });
	bgb->InitTransform(544, 425, false);
	bgb->SetName("Begin Button");
	shared_ptr<Button> qgb = GenBtn("ui_quit_idle", "ui_quit_hovered", "ui_quit_pushed", []() -> void { GameLoop::Quit(); });
	qgb->InitTransform(544, 550, false);
	qgb->SetName("Quit Button");
	GameLoop::AddUI(bgb);
	GameLoop::AddUI(qgb);
	bgb = nullptr;
	qgb = nullptr;
}
void MainScene::InitGame() {
	GameLoop::ClearAllButScenes();
	PlayMusic("bgm", true);
	m_LImgs = nullptr;
	m_RImgs = nullptr;
	m_paimon = nullptr;
	string* leftImgs = GetCharImg("boar", "left", 6);
	string* rightImgs = GetCharImg("boar", "right", 6);
	m_LImgs = GetImgRes(leftImgs, 6);
	m_RImgs = GetImgRes(rightImgs, 6);
	GetImgRes(*m_enemyShadow, "shadow_enemy");
	m_paimon = make_shared<Paimon>();
	GenBg("background");
	GenPaimon();
	StartInvokeBoar();
}
shared_ptr<Button> MainScene::GenBtn(string np, string hp, string pp, function<void()> oc) {
	shared_ptr<Button> btn = make_shared<Button>();
	string* pnp = new string{ np };
	string* php = new string{ hp };
	string* ppp = new string{ pp };
	shared_ptr<IMAGE[]> ipnp = GetImgRes(pnp, 1);
	shared_ptr<IMAGE[]> iphp = GetImgRes(php, 1);
	shared_ptr<IMAGE[]> ippp = GetImgRes(ppp, 1);
	btn->InitNormalAnimation(-1, ipnp, 1);
	btn->InitHoveringAnimation(-1, iphp, 1);
	btn->InitPressedAnimation(-1, ippp, 1);
	btn->SetOnClick(oc);
	return btn;
}
