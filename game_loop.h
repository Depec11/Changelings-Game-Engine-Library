#pragma once

#include "characters.h"

#include <windows.h>
#include <thread>
// #include <mutex>

class SceneManager;

class GameLoop {
public:
	static void GenerateInstance(int w, int h, bool s);
	static GameLoop& GetInstance();
	static void DeleteInstance();
	static int GetWidth();
	static int GetHeight();
	static Vector2 GetSize();
	static void StartAndJoin();
	static shared_ptr<Character> AddChar();
	static void AddChar(shared_ptr<Character> c);
	static void DelChar(Character& c);
	static shared_ptr<Character> GetCharByName(string name);
	static void AddScene(shared_ptr<Scene> s);
	static void DelScene(Scene& s);
	static shared_ptr<Scene> GetSceneByName(string name);
	static void Clear();
	static void SetIsPlaying(bool isPlaying);
	static bool GetIsPlaying();
	static void Quit();
	static void CheckReference();
private:
	// const float FIXED_DELTA = 0.0167f;
	// const int FIXED_DELTA_INT = 17;
	static GameLoop* m_instance;
	int WIDTH, HEIGHT;
	bool m_isRunning, SHOW_CONSOLE;
	// mutex mtx;
	ExMessage m_msg;
	DynamicContainer<Character> m_chars;
	DynamicContainer<Scene> m_scenes;
	bool m_isPlaying;
	static void Log(string s);
	GameLoop(int width, int height, int showCmd);
	~GameLoop();
	GameLoop(const GameLoop& signal);
	const GameLoop& operator=(const GameLoop& signal);
	void Graphics(float delta);
	void Physics();
	void Input();
	void Update();
};
