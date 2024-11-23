#pragma once

/*****************************************************************************
*  Changeling Game Engine Library                                            *
*  Copyright (C) 2024 Depec o Djemi  ywb3295326723@outlook.com.              *
*                                                                            *
*  This file is part of CGEL.                                                *
*                                                                            *
*  @file     characters.h                                                    *
*  @brief    All characters				                                     *
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

#include "components.h"

/**
 * @brief Character 
 */
class Character : public Component {
public:
	Character();
	virtual ~Character();
	Transform& GetTransform();
	Animation& GetAnimation();
	CollisionBox& GetCollisionBox();
	/** @brief Initialize
	 * @param speed Move speed
	 */
	void Init(float speed);
	/**
	 * @brief Initialize transform
	 * @param x x
	 * @param y y
	 * @param reverse Is reverse ?
	 */
	void InitTransform(float x, float y, bool reverse);
	/**
	 * @brief Initialize Animation
	 * @param animationSpeed Animation speed
	 * @param limgs Leftward images
	 * @param LN Leftward images count
	 * @param rimgs rightward images
	 * @param RN rightward images count
	 * @param simg Shadow image
	 * @param sx Shadow offset.x
	 * @param sy Shadow offset.y
	 */
	void InitAnimation(float animationSpeed, shared_ptr<IMAGE[]> limgs, int LN, shared_ptr<IMAGE[]> rimgs, int RN, shared_ptr<IMAGE> simg = nullptr, float sx = 0, float sy = 0);
	/**
	 * @brief Initialize collision box
	 * @param size Box size
	 * @param mute Is mute ?
	 */
	void InitCollisionBox(Vector2 size, bool mute);
	void Update(float delta) override;
	/**
	 * @brief Set speed
	 * @param speed speed
	 */
	void SetSpeed(float speed);
	/**
	 * @brief Move self
	 * @param delta Delta time
	 */
	void Move(float delta);
	/**
	 * @brief Set auto collision box
	 * @param autoCollisionBox if auto setting collision box pivot
	 */
	void SetAutoCollisionBox(bool autoCollisionBox);
	/**
	 * @brief Set auto transform pivot
	 * @param autoCollisionBox if auto setting transform pivot
	 */
	void SetAutoPivot(bool autoPivot);
	Vector2 GetSize();
	/**
	 * @brief If it's in other's collision, run this function
	 * @param other other Character
	 */
	virtual void CollisionBy(shared_ptr<Character> other);
	/**
	 * @brief Get tag
	 * 
	 * @return it's tag
	 */
	string GetTag() const;
	/**
	 * @brief Set tag
	 * @param tag tag
	 */
	void SetTag(string tag);
	/**
	 * @brief Draw self to the screen
	 */
	virtual void Draw();
	/**
	 * @brief Draw collision box covering character
	 */
	void DrawCollisionBox();
	/** @brief Get collision rect
	 * 
	 * @return Collision box rect
	 */
	Vector4 GetCollisionRect() const;
protected:
	string m_tag;
	float m_speed;
	Vector2 m_movement;
	bool m_autoCollisionBox; /*!< if it's true, collision box pivot will be calmulated as the centre of the animation image every frame */
	bool m_autoPivot; /*!< if it's true, transform pivot will be calmulated as the centre of the animation image every frame */
	shared_ptr<Transform> m_transform;
	shared_ptr<Animation> m_animation;
	shared_ptr<CollisionBox> m_collisionBox;
};
/**
 * @brief Scene 
 */
class Scene : public Component {
public:
	Scene();
	virtual ~Scene();
};
