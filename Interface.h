#pragma once

/// <summary>
/// Абстрактный тип узла
/// </summary>
/// <typeparam name="TYPE"></typeparam>
template <typename TYPE>
class Node
{
public:
	virtual TYPE getData() const = 0;
	virtual void setData(TYPE data) = 0;
	virtual ~Node() {}
	virtual std::string toString() = 0;
};


/// <summary>
/// Базовый класс для работы со списком
/// </summary>
/// <typeparam name="TYPE"></typeparam>
template <typename TYPE>
class AList
{
public:
	virtual void add(TYPE data, size_t index) = 0;
	virtual void remove() = 0;
	virtual size_t getSize() = 0;
	virtual std::string toString() = 0;
	virtual ~AList() {}
};


template<typename TYPE>
class CustomStack : public AList<TYPE> {
public:
	virtual TYPE push() = 0;
	virtual void pull(TYPE data) = 0;
	virtual size_t getSize() = 0;
	virtual std::string toString() = 0;
};
