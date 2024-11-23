#pragma once

#include "Components.h"

/*****************************************************************************
*  Changeling Game Engine Library                                            *
*  Copyright (C) 2024 Depec o Djemi  ywb3295326723@outlook.com.              *
*                                                                            *
*  This file is part of CGEL.                                                *
*                                                                            *
*  @file     ui.h		                                                     *
*  @brief    All ui elements	                                             *
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

/**
 * @brief UI
 */
class UI : public Component {
public:
	UI();
	virtual ~UI();
	/**
	 * @brief Draw self to the screen
	 */
	virtual void Draw();
	virtual void ProcessEvent(const ExMessage& msg) override;
	Transform& GetTransform();
	/**
	 * @brief Initialize transform
	 * @param x x
	 * @param y y
	 * @param reverse Is reverse ?
	 */
	void InitTransform(float x, float y, bool reverse);
	/**
	 * @brief Set on-click function
	 * @param func Function
	 */
	void SetOnClick(function<void()> func);
protected:
	/**
	 * brief State interacting with mouse
	 */
	enum class State {
		NORMAL = 0x0,
		HOVERING = 0x1,
		PRESSED = 0x2,
	};
	State m_state;
	shared_ptr<Transform> m_transform;
	function<void()> m_onClick;
	virtual IMAGE GetCurrImg() = 0;
private:
	/**
	 * @brief Draw image to the screen
	 * @param img Image
	 */
	void DrawImg(IMAGE img);
	/**
	 * @brief Determine if mouse hovering on self
	 * 
	 * return Mouse hovering on self ?
	 */
	bool MouseHoving();
	/**
	 * @brief Set state to normal
	 */
	void ResetState();
};
class Button : public UI {
public:
	Button();
	virtual void Update(float delta) override;
	/** @brief Initialize normal state animation
	 * @param anim_speed Animation playing speed
	 * @param imgs Array of image 
	 * @param count Array length
	 */
	void InitNormalAnimation(float anime_speed, shared_ptr<IMAGE[]> imgs, int count);
	/** @brief Initialize hovering state animation
	 * @param anim_speed Animation playing speed
	 * @param imgs Array of image 
	 * @param count Array length
	 */
	void InitHoveringAnimation(float anime_speed, shared_ptr<IMAGE[]> imgs, int count);
	/** @brief Initialize pressed state animation
	 * @param anim_speed Animation playing speed
	 * @param imgs Array of image 
	 * @param count Array length
	 */
	void InitPressedAnimation(float anime_speed, shared_ptr<IMAGE[]> imgs, int count);
protected:
	IMAGE GetCurrImg() override;
private:
	shared_ptr<SimpleAnimation> m_normalAnimation;		/*!< Animation in normal state */
	shared_ptr<SimpleAnimation> m_hoveringAnimation;	/*!< Animation in hovering state */
	shared_ptr<SimpleAnimation> m_pressedAnimation;		/*!< Animation in pressed state */
};
