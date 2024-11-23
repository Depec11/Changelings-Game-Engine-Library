#pragma once

/*****************************************************************************
*  Changeling Game Engine Library                                            *
*  Copyright (C) 2024 Depec o Djemi  ywb3295326723@outlook.com.              *
*                                                                            *
*  This file is part of CGEL.                                                *
*                                                                            *
*  @file     extension.h                                                     *
*  @brief    General useful functions and classes                            *
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

#include "templates.h"

#include <iostream>
#include <easyx.h>
#include <exception>
#include <random>

#pragma comment(lib, "Winmm.lib")

using namespace std;

/**
 * @brief Null reference error 
 */
class null_reference : public exception {
public:
	null_reference(const string& msg) : message(msg) {}
	const char* what() const noexcept override;
private:
	string message;
};
/**
 * @brief Vector2
 */
struct Vector2 {
	float x;
	float y;
	Vector2();
	Vector2(float a, float b);
	Vector2(int a, int b);
	Vector2 operator+(const Vector2& other);
	Vector2 operator-(const Vector2& other);
	Vector2 operator/(const float& other);
	Vector2 operator*(const float& other);
	bool operator<(const Vector2& other);
	bool operator>(const Vector2& other);
	bool operator==(const Vector2& other);
	/**
	 * @brief Parse self to string
	 * 
	 * @return string formated like "<{x}, {y}>"
	 */
	string ToString() const;
	/**
	* @brief Determine x and y are both zeor
	* 
	* @return x and y are both zeor?
	*/
	bool IsZero() const;
};
struct Vector4 {
	float x;
	float y;
	float z;
	float w;
	Vector4();
	Vector4(float a, float b, float c, float d);
	Vector4(Vector2 v1, Vector2 v2);
	/**
	* @brief Parse self to string
	* 
	* @return string formated like "<{x}, {y}, {z}, {w}>"
	*/
	string ToString() const;
	/**
	* @brief Determine x, y, z, and w are both zeor
	* 
	* @return x, y, z, and w are both zeor?
	*/
	bool IsZero() const;
};
/**
 * @brief Basic class using in game engine
 */
class Object {
public:
	Object();
	virtual ~Object();
	/**
	 * @brief Set object's name
	 * @param name Name
	 */
	void SetName(string name);
	bool operator==(const Object& obj);
	/**
	* @brief Get object's unique id
	*/
	unsigned int GetID() const;
	/**
	* @brief Get object's name
	*/
	string GetName() const;
	/**
	* @brief Log something with object's name
	* @param s information
	*/
	void Log(string s);
	/**
	* @brief Mark object is deleting
	*/
	void MarkDownDel();
	/**
	* @brief Get object is deleted or deleting
	* 
	* @return Is deleted or deleting ?
	*/
	bool GetState();
private:
	unsigned int m_id;
	string m_name;
	bool m_isDelete;
	static unsigned int m_number; /*!< Maxmium object unique id */
	static unsigned int m_count; /*!< Object counts */
};
/**
 * @brief Invoke data for component invoking
 */
class InvokeData : public Object {
public:
	function<void()> func;
	float time;
	InvokeData();
	InvokeData(function<void()> func, float time);
	~InvokeData();
};
void PutImageAlpha(int x, int y, IMAGE* img);
Vector2 Normalize(Vector2 vector);
Vector2 GetShadowPosOffset(int pw, int ph, int sw, int sh);
int RandomRange(int min, int max);
float RandomUniform();
void RegisterMusic(const char* path, const char* nickname);
void PlayMusic(const char* nickname, bool isRepeat = false);
void PauseMusic(const char* nickname);
void StopMusic(const char* nickname);
void ResumeMusic(const char* nickname);
