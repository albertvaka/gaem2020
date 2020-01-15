#pragma once

#include <set>
#include <cassert>

/**
 * Inheriting from this class gives you a static method getAll()
 * that returns a set with all the current instances of the class.
 */
template <typename T>
class EntS {
public:
	EntS()
	{
		getAll().push_back((T)this);
	}
	EntS(const EntS& other)
	{
		getAll().push_back((T)this);
	}
	void operator=(const EntS& other)
	{
		getAll().push_back((T)this);
	}
	~EntS()
	{
		getAll().erase(std::remove(getAll().begin(), getAll().end(), (T)this), getAll().end());
	}
	static std::vector<T>& getAll()
	{
		static std::vector<T> instancies;
		return instancies;
	}
	static void destroyAll() {
		for (typename std::vector<T>::iterator i = getAll().begin();
			i != getAll().end();
			i = getAll().begin())
		{
			delete* i;
		}
	}
};
