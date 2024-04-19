#pragma once
#include "Chain2.h"

template <typename TYPE>
class HIWell
{
private:
	Chain2<TYPE>* last;
public:
	HIWell() {}
	HIWell(TYPE data)
	{
		Chain2<TYPE> initializer(data);
		last = initializer;
	}
	
	void push(TYPE data) { last->getCurrent()->setData(data); last->adder.back(0); }
	TYPE pull() { TYPE res = last->getCurrent()->getData(); last->deleter.back(); return res; }

	type_t getSize() const override { return last->getSize(); }

};