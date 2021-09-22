#pragma once

/*
	Циклический буфер на основе связного списка
*/

#include "List.h"

template<typename TYPE>
class ldRBuff
{
private:
	List <TYPE> buff_; //буфер с данными
    size_t size_; 
public:

    //констукторы и деструктор
    //==========================================

    ldRBuff() : size_(0) {}

    //конструктор от одного аргумента, задающего размер буфера

	explicit ldRBuff(size_t sze) : size_(sze) {}

    //конструктор копирования

    ldRBuff(ldRBuff const& other)
        : buff_(other.buff_), size_(other.size_)
    {}
    
    //перемещающий конструктор копирования

    ldRBuff(ldRBuff && other)
        : buff_(std::move(other.buff_)), size_(other.size_)
    {
        other.size_ = 0;
    }

    //конструктор от списка инициализации

    ldRBuff(std::initializer_list<TYPE> lst) : buff_(lst), size_(lst.size())
    {
    }

    //операторы присваивания 
    //==========================================

     // оператор присваивания 

    ldRBuff& operator = (ldRBuff const& other)
    {
        if (this == &other) //защита от присваивания самому себе
            return *this;

        buff_ = other.buff_; //вызовется оператор присваивания 
        size_ = other.size_;
    }

    // перемещающий оператор присваивания

    ldRBuff& operator = (ldRBuff&& other) noexcept
    {
        if (this == &other) //защита от присваивания самому себе
            return *this;

        //захватываем данные другого объекта

        buff_ = std::move(other.buff_);
        size_ = other.size_;

        // оставляем данные в синхронизированном состоянии
        other.size_ = 0;
    }

    //==========================================

   //записать значение в буфер

    void Write(TYPE const& item)
    {
        if (IsFull())
            throw std::logic_error("buff is full!"); //если буфер полон, бросается исключение
        buff_.PushFront(item); //записываем значение в буфер
    }

    //прочитать значение из буфера

    TYPE Read()
    {
        if (IsEmpty())
            throw std::logic_error("buff is empty!"); // если буфер пуст, бросается исключение
        return buff_.PopBack();  //возвращаемый элемент
    }

    //полон ли буфер 

    bool IsFull()   const noexcept
    {
        return (size_ == buff_.Length());
    }

    //пуст ли буфер 

    bool IsEmpty()  const noexcept
    {
        return buff_.IsEmpty();
    }

    //количество элементов в буфере

    size_t Length() const noexcept
    {
        return buff_.Length();
    }

    //размер буфера

    size_t BufferSize() const noexcept
    {
        return size_;
    }

    //очистка буфера

    void Clear() noexcept
    {
        buff_.Clear();
    }

    void Resize(size_t newSize) noexcept
    {
        Clear();
        size_ = newSize;
    }
};
