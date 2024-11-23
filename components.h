#pragma once

/*****************************************************************************
*  Changeling Game Engine Library                                            *
*  Copyright (C) 2024 Depec o Djemi  ywb3295326723@outlook.com.              *
*                                                                            *
*  This file is part of CGEL.                                                *
*                                                                            *
*  @file     components.h                                                    *
*  @brief    All components		                                             *
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

#include "extension.h"

class Component : public Object {
public:
	Component();
	virtual ~Component();
	/** @brief When added to game loop, run this function
	 */
	virtual void Awake();
	/** @brief When deleted from game loop, run this function
	 */
	virtual void Delete();
	/** @brief Run this function on every frame
	 */
	virtual void Update(float delta);
	/** @brief Handle input event
	 */
	virtual void ProcessEvent(const ExMessage& msg);
protected:
	/** @brief Invoke function
	 * @param func Invoke function
	 * @param time Delay time
	 */
	void Invoke(function<void()> func, float time);
private:
	DynamicContainer<InvokeData> m_invokes;
};
class Transform : public Component {
public:
	Transform(float x = 0, float y = 0, bool reverse = false);
	~Transform();
	/** @brief Get x
	 * 
	 * @return x
	 */
	float GetX() const;
	/** @brief Get y
	 * 
	 * @return y
	 */
	float GetY() const;
	/** @brief Set x
	 * @param x x
	 */
	void SetX(float x);
	/** @brief Set y
	 * @param y y
	 */
	void SetY(float y);
	/** @brief Get if reverse
	 * 
	 * @return Is reverse ?
	 */
	bool GetReverse() const;
	/** @brief Set if reverse
	 * @param reverse Is reverse ?
	 */
	void SetReverse(bool reverse);
	/** @brief Get position
	 * 
	 * @return position
	 */
	Vector2 GetPosition() const;
	/** @brief Set position
	 * @param pos Position
	 */
	void SetPosition(Vector2 pos);
	/** @brief Set pivot
	 * @param pivot Pivot
	 */
	void SetPivot(Vector2 pivot);
	/** @brief Get pivot
	 * 
	 * @return Pivot
	 */
	Vector2 GetPivot() const;
private:
	Vector2 m_position;
	bool m_reverse;
	Vector2 m_pivot;
};
class Animation : public Component {
public:
	Animation(float speed = 0);
	~Animation();
	/** @brief Set shadow image
	 * @param img Shadow img
	 */
	void SetShadow(shared_ptr<IMAGE> img);
	/** @brief Get current image
	 * @param reverse Is transform reverse ?
	 * 
	 * @return Current image
	 */
	IMAGE GetCurrImg(bool reverse);
	/** @brief Get left image
	 * @index index
	 * 
	 * @return Left image
	 */
	IMAGE GetLImg(int index);
	/** @brief Get right image
	 * @param index Index
	 * 
	 * @return Right image
	 */
	IMAGE GetRImg(int index);
	/** @brief Get shadow image
	 */
	IMAGE GetShadow() const;
	/** @brief Set shadow offset
	 * @param x x
	 * @param y y
	 * 
	 * @return Shadow image
	 */
	void SetShadowOffset(float x, float y);
	/** @brief Get shadow offset
	 * 
	 * @return Shadow offset
	 */
	Vector2 GetShadowOffset() const;
	/** @brief Get animation size
	 * 
	 * @return Animation size
	 */
	Vector2 GetSize(bool reverse);
	/** @brief Get animation offset
	 * 
	 * @return Animation centre
	 */
	Vector2 GetOffset(bool reverse);
	/** @brief Set animation speed
	 * @param Animation speed
	 */
	void SetAnimSpeed(float speed);
	/** @brief Get animation speed
	 * 
	 * @return Animation speed
	 */
	float GetAnimSpeed() const;
	void Update(float delta) override;
	/** @brief Set animation left images
	 * @param imgs Array of images
	 * @param count Array length
	 */
	void SetLImgs(shared_ptr<IMAGE[]> &img, int count);
	/** @brief Set animation right images
	 * @param imgs Array of images
	 * @param count Array length
	 */
	void SetRImgs(shared_ptr<IMAGE[]> &img, int count);
private:
	static shared_ptr<IMAGE> m_defaultImg;
	shared_ptr<IMAGE[]> m_LImgs;
	shared_ptr<IMAGE[]> m_RImgs;
	shared_ptr<IMAGE> m_shadow;
	int m_LImgN;
	int m_RImgN;
	int m_currL;
	int m_currR;
	float m_animationSpeed;
	float m_timeCount;
	Vector2 m_shadowOffset;
	/** @brief Get animation image
	 * @param imgs Array of images
	 * @param n Array length
	 * @param index Index
	 * 
	 * @param Target image
	 */
	IMAGE GetImg(shared_ptr<IMAGE[]>& imgs, int n, int index);
	/** @brief Set animation images
	 * @param imgs Target images of self
	 * @param flyweight Array of images
	 * @param count Target images count of self
	 * @param curr Target images curr index of self
	 * @param n Array length
	 */
	void SetImgs(shared_ptr<IMAGE[]>& imgs, shared_ptr<IMAGE[]>& flyweight, int& count, int& curr, int n);
};
class CollisionBox : public Component {
public:
	CollisionBox();
	~CollisionBox();
	/** @brief Get collision box size
	 * 
	 * @return Collision box size
	 */
	Vector2 GetSize() const;
	/** @brief Set collision box size
	 * @param size collision box size
	 */
	void SetSize(Vector2 size);
	/** @brief Get if mute
	 * 
	 * @return Is mute ?
	 */
	bool GetMute() const;
	/** @brief Set if mute
	 * @param Is mute ?
	 */
	void SetMute(bool isTrigger);
private:
	Vector2 m_size;
	bool m_mute;
};
class SimpleAnimation : public Component {
public:
	SimpleAnimation(float speed = 0);
	~SimpleAnimation();
	/** @brief Set shadow image
	 * @param img Shadow img
	 */
	void SetShadow(IMAGE img);
	/** @brief Get current image
	 * 
	 * @return Shadow image
	 */
	IMAGE GetCurrImg();
	/** @brief Get shadow image
	 * 
	 * @return Current image
	 */
	IMAGE GetShadow() const;
	/** @brief Set shadow offset
	 * @param x x
	 * @param y y
	 */
	void SetShadowOffset(float x, float y);
	/** @brief Get shadow offset
	 * 
	 * @return Shadow offset
	 */
	Vector2 GetShadowOffset() const;
	/** @brief Get animation size
	 * 
	 * @return Animation size
	 */
	Vector2 GetSize();
	/** @brief Get animation offset
	 * 
	 * @return Animation centre
	 */
	Vector2 GetOffset();
	/** @brief Set animation speed
	 * @param Animation speed
	 */
	void SetAnimSpeed(float speed);
	/** @brief Get animation speed
	 * 
	 * @return Animation speed
	 */
	float GetAnimSpeed() const;
	void Update(float delta) override;
	/** @brief Set animation images
	 * @param imgs Array of images
	 * @param count Array length
	 */
	void SetImgs(shared_ptr<IMAGE[]> &img, int count);
private:
	static shared_ptr<IMAGE> m_defaultImg;
	shared_ptr<IMAGE[]> m_Imgs;
	shared_ptr<IMAGE> m_shadow;
	int m_ImgN;
	int m_curr;
	float m_animationSpeed;
	float m_timeCount;
	Vector2 m_shadowOffset;
};
