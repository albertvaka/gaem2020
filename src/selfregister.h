#pragma once

#include <set>
#include <cassert>
#include <iostream>
using namespace std;

/**
 * Inheriting from this class gives you a static method getAll()
 * that returns a set with all the current instances of the class.
 */
template <typename T>
class EntS {
public:
	EntS()
	{
		getAll().push_back((T*)this);
	}
	EntS(const EntS& other)
	{
		getAll().push_back((T*)this);
	}
	void operator=(const EntS& other)
	{
		getAll().push_back((T*)this);
	}
	static std::vector<T*>& getAll()
	{
		static std::vector<T*> instancies;
		return instancies;
	}
	virtual ~EntS()
	{
		getAll().erase(std::remove(getAll().begin(), getAll().end(), (T*)this), getAll().end());
	}
	static void deleteNotAlive() {
		for (int i = getAll().size() - 1; i >= 0; i--) {
			T* e = getAll()[i];
			if (e->parent && !e->parent->alive) {
				e->parent = NULL;
			}
		}
		for (int i = getAll().size()-1; i >= 0; i--) {
			T* e = getAll()[i];
			if (!e->alive) {
				delete e;
			}
		}
	}
};
