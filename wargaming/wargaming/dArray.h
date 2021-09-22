#pragma once

/*
	Динамический массив
*/

#include <algorithm>
#include <initializer_list>

template<typename TYPE>
class dArray
{
private:
	TYPE* data_;  //данные
	size_t size_; // размер буфера данных

public:

	//конструкторы и деструктор
	//==========================================

	dArray() : data_(nullptr), size_(0) {}

	//конструктор от одного аргумента, задающего размер буфера
	explicit dArray(size_t sze)  
		try : data_(new TYPE[sze]), size_(sze)
		{}
		catch(std::bad_alloc)     //если не получилось выделить память для буфера, бросаем исключение
		{
			throw;
		}

	//конструктор копирования

	dArray(dArray const & other)  
	try : data_(new TYPE[other.size_]), size_(other.size_)
	{
		for (size_t i = 0; i < size_; ++i) //копируем данные другого объекта
			data_[i] = other.data_[i];  
	}
	catch (std::bad_alloc)  //если не получилось выделить память для буфера, бросаем исключение
	{
		throw;
	}

	//перемещающий конструктор копирования

	dArray(dArray && other) noexcept  
		: data_(other.data_), size_(other.size_) //захватываем данные другого объекта
	{
		other.data_ = nullptr; //оставляем данные в синхронизированном состоянии
		other.size_ = 0;
	}

	//конструктор от списка инициализации

	dArray(std::initializer_list<TYPE> lst)
		try : data_(new TYPE[lst.size()]), size_(lst.size())
	{
		std::copy(std::begin(lst), std::end(lst), data_); //копируем данные из списк
	}
	catch (std::bad_alloc)  //если не получилось выделить память для буфера, бросаем исключение
	{
		throw;
	}

	// деструктор
	
	~dArray() 
	{
		Clear(); // очищаем буфер
	}

	//операторы присваивания 
	//==========================================

    //оператор присваивания 

	dArray& operator = (dArray const& other)
	{
		if (this == &other) //защита от присваивания самому себе
			return *this;

		Clear(); // очищаем буффер
		Resize(other.size_); //задаём новый размер (функция меняет переменную size_, поэтому здесь присваивать не нужно)
		
		for (size_t i = 0; i < size_; ++i) //копируем данные другого объекта
			data_[i] = other.data_[i];

		return *this;
	}

	//перемещающий оператор присваивания

	dArray& operator = (dArray && other) noexcept
	{
		if (this == &other) //защита от присваивания самому себе
			return *this;

		Clear(); // очищаем буффер

		//захватываем данные другого объекта
		data_ = other.data_;
		size_ = other.size_;

		// оставляем данные в синхронизированном состоянии
		other.data_ = nullptr;
		other.size_ = 0;

		return *this;
	}


	
	//==========================================

	//изменение размера буфера

	void Resize(size_t newSize)
	{
		if (size_ == newSize)   //если задаваемый размер совпадает с текущим, выходим
			return;

		TYPE* newBuffer = new (std::nothrow) TYPE[newSize]; //выделяем память на новый буфер

		if (!newBuffer)		
			throw std::bad_alloc(); //если не получилось выделить, бросаем исключение

		if (data_ != nullptr) //если буфер не пуст
		{
			// копируем данные из старого буфера в новый
			size_t curSize = std::min(newSize, size_);

			for (size_t i = 0; i < curSize; ++i)
				newBuffer[i] = data_[i];

			Clear(); //удаляем текущий буфер
		}
		
		//присваиваем  новые данные и новый размер
		data_ = newBuffer;
		size_ = newSize;
	}

	//==========================================

	//доступ по индексу 

	TYPE& operator [] (size_t i) 
	{
		return data_[i];
	}

	TYPE const & operator [] (size_t i) const 
	{
		return data_[i];
	}

	TYPE& At (size_t i)
	{
		if (IsEmpty() || i >= Length())
			throw std::logic_error("array is empty");

		return data_[i];
	}

	TYPE const& At (size_t i) const
	{
		if (IsEmpty() || i >= Length())
			throw std::logic_error("array is empty");

		return data_[i];
	}

	//==========================================

	// пуст ли буфер

	bool IsEmpty()
	{
		return (size_ == 0);
	}

	//длина буфера

	size_t Length() const noexcept
	{
		return size_;
	}

	//очистка буферв

	void Clear()
	{
		if (IsEmpty())
			return;

		delete[] data_;

		data_ = nullptr;
		size_ = 0;
	}

	//==========================================
};