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

#include "logger.h"

#include <vector>
#include <stack>
#include <functional>
#include <algorithm>
#include <stdexcept>

/**
 * @brief Dynamic container, T is a child of Object
 * T is a child of Object !!!
 * T is a child of Object !!!
 * T is a child of Object !!!
 */
template<typename T> class DynamicContainer {
public:
	DynamicContainer() {}
	~DynamicContainer() {
		Delete();
	}
	/**
	 * @brief Request a brand new item
	 * 
	 * @return A brand new item shared pointer
	 */
	std::shared_ptr<T> Add() {
		m_toAdd.push_back(std::make_shared<T>());
		return m_toAdd.back();
	}
	/**
	 * @brief Add a item to continer
	 * @param t A shared pointer
	 */
	void Add(std::shared_ptr<T> t) {
		m_toAdd.push_back(t);
	}
	/**
	 * @brief Delete a item
	 * @param t Item
	 */
	void Del(const T& t) {
		for (int i = 0; i < m_container.size(); i++) {
			if ((*m_container[i] == t)) {
				Del(i);
				break;
			}
		}
	}
	/**
	 * @brief Delete a item
	 * @param i Item's index in the container
	 */
	void Del(unsigned int i) {
		m_container[i]->MarkDownDel();
		if (i >= 0 and i < m_container.size()) {
			m_bin.push_back(i);
		}
	}
	/**
	 * @brief Clear container
	 */
	void Clear() {
		for (int i = 0; i < m_container.size(); i++) {
			Del(i);
		}
	}
	/**
	 * @brief Clear bin
	 */
	void ClearBin() {
		ClearBin([](std::shared_ptr<T> i) -> void {});
	}
	/**
	 * @brief Clear bin
	 * @param func To every items to delete, run the function
	 */
	void ClearBin(std::function<void(std::shared_ptr<T>)> func) {
		TidyUp();
		if (m_bin.size() > 0) {
			Log(std::format("START CLEARING BIN COUNT: {}", m_bin.size()));
		} else {
			return;
		}
		std::sort(m_bin.begin(), m_bin.end());
		std::reverse(m_bin.begin(), m_bin.end());
		m_container.erase(m_container.begin() + m_bin[0]);
		for (int i = 1; i < m_bin.size(); i++) {
			if (m_bin[i] == m_bin[i - 1]) {
				continue;
			}
			func(*(m_container.begin() + m_bin[i]));
			m_container.erase(m_container.begin() + m_bin[i]);
		}
		std::vector<unsigned int>().swap(m_bin);
		std::vector<std::shared_ptr<T>>(m_container).swap(m_container);
		if (m_bin.size() != m_bin.capacity()) {
			Log(std::format("BIN IS NOT CLEAR!\t{}<<{}!", m_bin.size(), m_bin.capacity()));
;		}
		if (m_container.size() != m_container.capacity()) {
			Log(std::format("CONTAINER IS NOT CLEAR!\t{}<<{}!", m_container.size(), m_container.capacity()));
		}
	}
	/**
	 * @brief Push items in to-add container to container
	 */
	void AddToContainer() {
		AddToContainer(std::bind([]() -> void {}));
	}
	/**
	 * @brief Push items in to-add container to container
	 * @param func To every items to push, run the function
	 */
	void AddToContainer(std::function<void(std::shared_ptr<T>)> func) {
		if (m_toAdd.size() == 0) {
			return;
		}
		Log(std::format("START ADD TO CONTAINER COUNT: {}", m_toAdd.size()));
		for (int i = 0; i < m_toAdd.size(); i++) {
			func(m_toAdd[i]);
			m_container.push_back(m_toAdd[i]);
		}
		std::vector<std::shared_ptr<T>>().swap(m_toAdd);
		return;
	}
	/**
	 * @brief Iterating the container
	 * @param func To every items in the container, run the function
	 */
	void Iterate(std::function<void(std::shared_ptr<T>)> func) {
		for (auto i = m_container.begin(); i != m_container.end(); i++) {
			func(*i);
		}
	}
	/**
	 * @brief force to delete all items
	 */
	void Delete() {
		Clear();
		ClearBin();
	}
	/**
	 * @brief Get item count
	 * 
	 * @return Item count
	 */
	int Count() {
		return m_container.size();
	}
	std::shared_ptr<T>& operator[](size_t index) {
		if (index >= m_container.size()) {
			throw std::out_of_range("Index out of range");
		}
		return m_container[index];
	}
	const std::shared_ptr<T>& operator[](size_t index) const {
		if (index >= m_container.size()) {
			throw std::out_of_range("Index out of range");
		}
		return m_container[index];
	}
private:
	std::vector<std::shared_ptr<T>> m_container;	/*!< Item container */
	std::vector<std::shared_ptr<T>> m_toAdd;		/*!< To-add container */
	std::vector<unsigned int> m_bin;				/*!< Bin */
	/**
		* @brief Log something
		* @param s Information
		*/
	void Log(std::string s) {
		Logger::Log(s);
	}
	/**
	* @brief Check items in container, if it is deleting or deleted, then push it into the bin
	 */
	void TidyUp() {
		for (int i = 0; i < m_container.size(); i++) {
			if (m_container[i]->GetState()) {
				Del(i);
			}
		}
	}
};
