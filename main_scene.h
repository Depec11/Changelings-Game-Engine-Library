#pragma once

#include "base/characters.h"
#include "enemy.h"
#include "paimon.h"
#include "base/ui.h"

const float ANIM_SPEED = 0.15f;

string* GetCharImg(string name, string side, int n);
void GenBg(string path);
enum class Direction {
	UP = 0x1,
	RIGHT = 0x2,
	DOWN = 0x3,
	LEFT = 0x4,
};
class MainScene : public Scene {
public:
	MainScene();
	~MainScene();
	void Awake() override;
	void Delete() override;
	void Update(float delta) override;
private:
	shared_ptr<IMAGE[]> m_LImgs;
	shared_ptr<IMAGE[]> m_RImgs;
	shared_ptr<IMAGE> m_enemyShadow;
	shared_ptr<Paimon> m_paimon;
	DynamicContainer<Boar> m_enemys;
	bool m_playingState;
	void GenPaimon();
	void GenBoar();
	void StartInvokeBoar();
	void InitMenu();
	void InitGame();
	shared_ptr<Button> GenBtn(string np, string hp, string pp, function<void()> oc);
};
