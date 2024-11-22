#pragma once

#include "logger.h"

#include <vector>
#include <stack>
#include <functional>
#include <algorithm>
#include <stdexcept>

template<typename T> class DynamicContainer {
public:
	DynamicContainer() {}
	~DynamicContainer() {
		Delete();
	}
	std::shared_ptr<T> Add() {
		m_toAdd.push_back(std::make_shared<T>());
		return m_toAdd.back();
	}
	void Add(std::shared_ptr<T> t) {
		m_toAdd.push_back(t);
	}
	void Del(const T& t) {
		for (int i = 0; i < m_container.size(); i++) {
			if ((*m_container[i] == t)) {
				Del(i);
				break;
			}
		}
	}
	void Del(unsigned int i) {
		m_container[i]->MarkDownDel();
		if (i >= 0 and i < m_container.size()) {
			m_bin.push_back(i);
		}
	}
	void Clear() {
		for (int i = 0; i < m_container.size(); i++) {
			Del(i);
		}
	}
	void ClearBin() {
		ClearBin([](std::shared_ptr<T> i) -> void {});
	}
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
	void AddToContainer() {
		AddToContainer(std::bind([]() -> void {}));
	}
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
	void Iterate(std::function<void(std::shared_ptr<T>)> func) {
		for (auto i = m_container.begin(); i != m_container.end(); i++) {
			func(*i);
		}
	}
	void Delete() {
		Clear();
		ClearBin();
	}
	int Count() {
		return m_container.size();
	}
	std::shared_ptr<T> operator[](size_t index) {
		if (index >= m_container.size()) {
			throw std::out_of_range("Index out of range");
		}
		return m_container[index];
	}
	const std::shared_ptr<T> operator[](size_t index) const {
		if (index >= m_container.size()) {
			throw std::out_of_range("Index out of range");
		}
		return m_container[index];
	}
	std::vector<std::shared_ptr<T>> GetAll() const {
		return m_container;
	}
private:
	std::vector<std::shared_ptr<T>> m_container;
	std::vector<std::shared_ptr<T>> m_toAdd;
	std::vector<unsigned int> m_bin;
	void Log(std::string s) {
		Logger::Log(s);
	}
	void TidyUp() {
		for (int i = 0; i < m_container.size(); i++) {
			if (m_container[i]->GetState()) {
				Del(i);
			}
		}
	}
};
