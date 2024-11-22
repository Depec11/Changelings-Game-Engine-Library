#include "game_loop.h"

void GameLoop::GenerateInstance(int w, int h, bool s) {
	if (m_instance == nullptr) {
		m_instance = new GameLoop(w, h, s);
	}
}
GameLoop& GameLoop::GetInstance() {
	return *m_instance;
}
void GameLoop::DeleteInstance() {
	delete m_instance;
}
int GameLoop::GetWidth() {
	CheckReference();
	return m_instance->WIDTH;
}
int GameLoop::GetHeight() {
	CheckReference();
	return m_instance->HEIGHT;
}
Vector2 GameLoop::GetSize() {
	CheckReference();
	return Vector2(m_instance->WIDTH, m_instance->HEIGHT);
}
void GameLoop::StartAndJoin() {
	CheckReference();
	if (m_instance->SHOW_CONSOLE) {
		initgraph(m_instance->WIDTH, m_instance->HEIGHT, EX_SHOWCONSOLE);
	} else {
		initgraph(m_instance->WIDTH, m_instance->HEIGHT);
	}
	BeginBatchDraw();
	thread update(&GameLoop::Update, m_instance);
	update.join();
}
shared_ptr<Character> GameLoop::AddChar() {
	CheckReference();
	shared_ptr<Character> c = m_instance->m_chars.Add();
	return c;
}
void GameLoop::AddChar(shared_ptr<Character> c) {
	CheckReference();
	m_instance->m_chars.Add(c);
}
void GameLoop::DelChar(Character& c) {
	CheckReference();
	m_instance->m_chars.Del(c);
}
shared_ptr<Character> GameLoop::GetCharByName(string name) {
	CheckReference();
	for (int i = 0; i < m_instance->m_chars.Count(); i++) {
		auto t = m_instance->m_chars[i];
		if (t->GetName() == name) {
			return t;
		}
	}
	return shared_ptr<Character>();
}
void GameLoop::AddScene(shared_ptr<Scene> s) {
	CheckReference();
	m_instance->m_scenes.Add(s);
}
void GameLoop::DelScene(Scene& s) {
	CheckReference();
	m_instance->m_scenes.Del(s);
}
shared_ptr<Scene> GameLoop::GetSceneByName(string name) {
	CheckReference();
	for (int i = 0; i < m_instance->m_scenes.Count(); i++) {
		auto t = m_instance->m_scenes[i];
		if (t->GetName() == name) {
			return t;
		}
	}
	return shared_ptr<Scene>();
}
void GameLoop::Clear() {
	CheckReference();
	Log("CLEAR ALL THINGS");
	m_instance->m_chars.Delete();
	m_instance->m_scenes.Delete();
}
void GameLoop::SetIsPlaying(bool isPlaying) {
	CheckReference();
	m_instance->m_isPlaying = isPlaying;
}
bool GameLoop::GetIsPlaying() {
	CheckReference();
	return m_instance->m_isPlaying;
}
void GameLoop::Quit() {
	CheckReference();
	Log("QUIT GAME");
	m_instance->m_isRunning = false;
}
void GameLoop::CheckReference() {
	if (m_instance == nullptr) {
		throw null_reference("Null reference");
	}
}
void GameLoop::Log(string s) {
	Logger::Log(s);
}
GameLoop::GameLoop(int width, int height, int showCmd) : WIDTH(width), HEIGHT(height), SHOW_CONSOLE(showCmd) {
	m_isRunning = true;
	m_isPlaying = true;
	m_msg = ExMessage();
}
GameLoop::~GameLoop() {
	Clear();
}
GameLoop::GameLoop(const GameLoop& signal) {
	HEIGHT = 0;
	WIDTH = 0;
	SHOW_CONSOLE = false;
	m_isRunning = true;
	m_isPlaying = true;
	m_msg = ExMessage();
}
const GameLoop& GameLoop::operator=(const GameLoop& signal) {
	return *m_instance;
}
void GameLoop::Graphics(float delta) {
	cleardevice();
	m_chars.Iterate([this](shared_ptr<Character> i) -> void {
		i->Draw();
		if (SHOW_CONSOLE) {
			i->DrawCollisionBox();
		}
	});
	FlushBatchDraw();
}
void GameLoop::Physics() {
	if (m_chars.Count() == 0) {
		return;
	}
	vector<Vector4> rects;
	for (int i = 0; i < m_chars.Count(); i++) {
		rects.push_back(m_chars[i]->GetCollisionRect());
	}
	for (int i = 0; i < m_chars.Count() - 1; i++) {
		shared_ptr<Character> self = m_chars[i];
		Vector2 s_size = self->GetCollisionBox().GetSize();
		if (self->GetCollisionBox().GetMute() || s_size.IsZero() || rects[i].IsZero()) {
			continue;
		}
		Vector4 s_rect = rects[i];
		for (int j = i + 1; j < m_chars.Count(); j++) {
			shared_ptr<Character> other = m_chars[j];
			Vector2 o_size = other->GetCollisionBox().GetSize();
			if (other->GetCollisionBox().GetMute() || o_size.IsZero() || rects[i].IsZero()) {
				continue;
			}
			Vector4 o_rect = rects[j];
			Vector2 minBox = Vector2(s_size.x + o_size.x, s_size.y + o_size.y);
			Vector2 trueBox = Vector2(max(s_rect.z, o_rect.z) - min(s_rect.x, o_rect.x), max(s_rect.w, o_rect.w) - min(s_rect.y, o_rect.y));
			if (trueBox < minBox) {
				self->CollisionBy(other);
				other->CollisionBy(self);
			}
		}
	}
}
void GameLoop::Input() {
	while (peekmessage(&m_msg)) {
		m_chars.Iterate([this](shared_ptr<Character> i) -> void {
			i->ProcessEvent(m_msg); 
		});
		if (m_msg.message == WM_KEYDOWN) {
			switch (m_msg.vkcode) {
			case VK_ESCAPE: Quit(); break;
			case VK_F1: Clear(); break;
			case VK_SPACE: m_isPlaying = !m_isPlaying; break;
			default: break;
			}
		}
	}
}
void GameLoop::Update() {
	unsigned long long startClock = clock();
	unsigned long long endClock = startClock;
	float delta = 0;
	while (m_isRunning) {
		// lock_guard<mutex> guard(mtx);
		endClock = clock();
		delta = (endClock > startClock) ? (endClock - startClock) / 1000.0f : 0;
		startClock = endClock;
		Input();
		Graphics(delta);
		m_isRunning = m_isRunning ? IsWindow(GetHWnd()) : m_isRunning;
		m_scenes.Iterate([this, delta](shared_ptr<Scene> i) -> void {
			i->Update(delta);
		});
		m_scenes.ClearBin([](shared_ptr<Scene> i) -> void {
			i->Delete();
		});
		m_scenes.AddToContainer([](shared_ptr<Scene> i) -> void {
			i->Awake();
		});
		if (!m_isPlaying) {
			continue;
		}
		m_chars.Iterate([this, delta](shared_ptr<Character> i) -> void {
			i->Update(delta);
			i->Move(delta);
		});
		m_chars.ClearBin([](shared_ptr<Character> i) -> void {
			i->Delete();
		});
		m_chars.AddToContainer([](shared_ptr<Character> i) -> void {
			i->Awake();
		});
		Physics();
	}
}
GameLoop* GameLoop::m_instance = nullptr;
