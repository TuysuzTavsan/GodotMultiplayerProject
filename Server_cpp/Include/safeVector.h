#pragma once

#include <vector>
#include <mutex>
#include <iostream>
#include <algorithm>

/*
Safe vector like container to work with multiple threads.
*/
template<typename T>
struct SafeVector {

	SafeVector() = default;
	~SafeVector() = default;

	void push_back(const T& val)
	{
		std::lock_guard lk(m_mutex);
		m_pool.push_back(val);
		std::cout << "[SafeVector] has element number# " << m_pool.size() << "\n";
	}

	void emplace_back(T&& val)
	{
		std::lock_guard lk(m_mutex);
		m_pool.emplace_back(std::move(val));
	}

	void erase(const T val)
	{
		std::lock_guard lk(m_mutex);
		m_pool.erase(
			std::remove_if(m_pool.begin(), m_pool.end(),
				[&val](T ptr) {return ptr == val; }),
			m_pool.end()
		);

		std::cout << "[SafeVector] has element number# " << m_pool.size() << "\n";
	}

private:

	std::mutex m_mutex;
	std::vector<T> m_pool; //Actual pool of objects of type T.
};