#pragma once

/*****************************************************************************
*  Changeling Game Engine Library                                            *
*  Copyright (C) 2024 Depec o Djemi  ywb3295326723@outlook.com.              *
*                                                                            *
*  This file is part of CGEL.                                                *
*                                                                            *
*  @file     templates.h                                                     *
*  @brief    Basic template classes                                          *
*  Details.                                                                  *
*                                                                            *
*  @author   Depec o Djemi                                                   *
*  @email    ywb3295326723@putlook.com                                       *
*  @version  a.0.0.1													     *
*  @date     2024/11/23                                                      *
*  @license  NONE							                                 *
*                                                                            *
*----------------------------------------------------------------------------*
*  Remark         : Description                                              *
*----------------------------------------------------------------------------*
*  Change History :                                                          *
*  <Date>     | <Version> | <Author>       | <Description>                   *
*----------------------------------------------------------------------------*
*  2024/11/23 | a.0.0.1   | Depec o Djemi  | Create file                     *
*----------------------------------------------------------------------------*
*                                                                            *
*****************************************************************************/

#include "characters.h"
#include "ui.h"

#include <windows.h>
#include <thread>
// #include <mutex>

class SceneManager;

class GameLoop {
public:
	static void GenerateInstance(int w, int h, bool s);
	/** @brief Get instance
	 * 
	 * @return Instance
	 */
	static GameLoop& GetInstance();
	static void DeleteInstance();
	/** @brief Get width
	 * 
	 * @return Width
	 */
	static int GetWidth();
	/** @brief Get height
	 * 
	 * @return Height
	 */
	static int GetHeight();
	/** @brief Get screen size
	 * 
	 * @return Screen size
	 */
	static Vector2 GetSize();
	/** @brief Start game loop
	 */
	static void StartAndJoin();
	/** @brief Add character
	 * 
	 * @return A brand new character
	 */
	static shared_ptr<Character> AddChar();
	/** @brief Add character to container
	 * @param c Character
	 */
	static void AddChar(shared_ptr<Character> c);
	/** @brief Delete character
	 * @param c Character
	 */
	static void DelChar(Character& c);
	/** @brief Get character by name
	 * @param name Name
	 * 
	 * @return Target character
	 */
	static shared_ptr<Character> GetCharByName(string name);
	/** @brief Add scene to container
	 * @param s Scene
	 */
	static void AddScene(shared_ptr<Scene> s);
	/** @brief Delete scene
	 * @param s Scene
	 */
	static void DelScene(Scene& s);
	/** @brief Get scene by name
	 * @param name Name
	 * 
	 * @return Target scene
	 */
	static shared_ptr<Scene> GetSceneByName(string name);
	/** @brief Add ui element to container
	 * @param u UI element
	 */
	static void AddUI(shared_ptr<UI> u);
	/** @brief Delete ui element
	 * @param u UI element
	 */
	static void DelUI(UI& u);
	/** @brief Get ui by name
	 * @param name Name
	 * 
	 * @return Target ui
	 */
	static shared_ptr<UI> GetUIByName(string name);
	/** @brief Force to clear all items
	 */
	static void Clear();
	/** @brief Clear all items but scene
	 */
	static void ClearAllButScenes();
	/** @brief Set if playing
	 * @param isPlaying Is playing ?
	 */
	static void SetIsPlaying(bool isPlaying);
	/** @brief Get if playing
	 * 
	 * @return Is playing ?
	 */
	static bool GetIsPlaying();
	/** @brief Quit game
	 */
	static void Quit();
	/** @brief Check if it has no instance
	 */
	static void CheckReference();
	/** @brief Get mouse position
	 * 
	 * @return Mouse position
	 */
	static Vector2 GetMousePosition();
private:
	// const float FIXED_DELTA = 0.0167f;
	// const int FIXED_DELTA_INT = 17;
	static GameLoop* m_instance;
	int WIDTH, HEIGHT;
	bool m_isRunning, SHOW_CONSOLE;
	// mutex mtx;
	ExMessage m_msg;
	DynamicContainer<Character> m_chars;	/*!< Character container */
	DynamicContainer<Scene> m_scenes;		/*!< Scene container */
	DynamicContainer<UI> m_uis;				/*!< UI container */
	Vector2 m_mousePosition;
	bool m_isPlaying;						/*!< Not pause the game */
	/** @brief Log something
	 * @param s information
	 */
	static void Log(string s);
	GameLoop(int width, int height, int showCmd);
	~GameLoop();
	GameLoop(const GameLoop& signal);
	const GameLoop& operator=(const GameLoop& signal);
	/* @brief Draw graphics
	 * @param delta Delta time
	 */
	void Graphics(float delta);
	/* @brief Calculating collision
	 */
	void Physics();
	/* @brief Handle input message
	 */
	void Input();
	/* @brief Base frame
	 */
	void Update();
};
