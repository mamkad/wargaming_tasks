#pragma once

/*
	Cтатический массив
*/

#include <initializer_list>

template<typename TYPE, size_t size_> //тип и размер массива
class sArray
{
private:
	TYPE data_[size_]; //буфер
public:

	//конструкторы
	//==========================================

	 //конструктор по умочланию 

	sArray() noexcept = default;

	//конструктор копирования

	sArray(sArray const& other) noexcept
	{
		for (size_t i = 0; i < size_; ++i) //копируем данные другого объекта
			data_[i] = other.data_[i];
	}

	//перемещающий конструктор копирования

	
	sArray(sArray && other) noexcept
	{
		std::move(std::begin(other.data_), std::end(other.data_), &data_[0]); //захватываем ресурсы другого объекта
	}

	//конструктор от списка инициализации

	sArray(std::initializer_list<TYPE> lst)
	{
		if (lst.size() > size_)
			throw std::logic_error("The size of the list does not match the size of the array");

		std::copy(std::begin(lst), std::end(lst), data_); //копируем данные из списк
	}

	//операторы присваивания 
	//==========================================

	// оператор присваивания 

	sArray& operator = (sArray const& other)
	{
		if (this == &other) //защита от присваивания самому себе
			return *this;

		for (size_t i = 0; i < size_; ++i) //копируем данные другого объекта
			data_[i] = other.data_[i];

		return *this;
	}

	// перемещающий оператор присваивания

	
	sArray& operator = (sArray&& other) noexcept
	{
		if (this == &other) //защита от присваивания самому себе
			return *this;

		std::move(std::begin(other.data_), std::end(other.data_), &data_[0]); //захватываем ресурсы другого объекта

		return *this;
	}
	
	//==========================================

	//доступ по индексу 

	TYPE& operator [] (size_t i)
	{
		return data_[i];
	}

	TYPE const& operator [] (size_t i) const
	{
		return data_[i];
	}

	TYPE& At(size_t i)
	{
		if (i >= Length())
			throw std::logic_error("array is empty");

		return data_[i];
	}

	TYPE const& At(size_t i) const
	{
		if (i >= Length())
			throw std::logic_error("array is empty");

		return data_[i];
	}

	//==========================================

	//длина буфера

	size_t Length() const noexcept
	{
		return size_;
	}
};