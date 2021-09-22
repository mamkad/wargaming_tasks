#pragma once

/*
    Циклический буфер на основе статического массива
*/

#include "sArray.h"

template<typename TYPE, size_t size_>
class sRBuff
{
private:
    sArray<TYPE, size_> buff_; //буфер с данными
    size_t readI_, writeI_;  // индексы чтения и записи
    size_t count_; //количество элементов

    //функция для инкрементирования индексов

    size_t Inc(size_t i) const noexcept
    {
        ++i;
        return i < buff_.Length() ? i : 0;
    }

public:
    //констукторы и деструктор
    //==========================================

    //конструктор от одного аргумента, задающего размер буфера

    sRBuff() noexcept :  readI_(0), writeI_(0), count_(0) {}

    //конструктор копирования

    sRBuff(sRBuff const& other) noexcept  : buff_(other.buff_), readI_(other.readI_), writeI_(other.writeI_), count_(other.count_)  {}

    //перемещающий конструктор копирования

    sRBuff(sRBuff&& other) noexcept  : buff_(std::move(other.buff_)), readI_(other.readI_), writeI_(other.writeI_), count_(other.count_) //захватываем данные другого объекта
    {
        // оставляем данные в синхронизированном состоянии
        other.readI_ = 0;
        other.writeI_ = 0;
        other.count_ = 0;
    }

    //конструктор от списка инициализации

    sRBuff(std::initializer_list<TYPE> lst) : buff_(lst), readI_(0), writeI_(lst.size()), count_(lst.size())
    {
    }

    //операторы присваивания 
    //==========================================

    // оператор присваивания 

    sRBuff& operator = (sRBuff const& other) noexcept
    {
        if (this == &other) //защита от присваивания самому себе
            return *this;

        buff_ = other.buff_;

        readI_ = other.readI_;
        writeI_ = other.writeI_;
        count_ = other.count_;
    }

    // перемещающий оператор присваивания

    sRBuff& operator = (sRBuff&& other) noexcept
    {
        if (this == &other) //защита от присваивания самому себе
            return *this;

        //захватываем данные другого объекта

        buff_ = std::move(other.buff_);

        readI_ = other.readI_;
        writeI_ = other.writeI_;
        count_ = other.count_;

        // оставляем данные в синхронизированном состоянии
        other.readI_ = 0;
        other.writeI_ = 0;
        other.count_ = 0;
    }

    // оператор присваивания от списка инициализации

    sRBuff& operator = (std::initializer_list<TYPE> lst)
    {

    }

    //==========================================

    //записать значение в буфер

    void Write(TYPE const& item)
    {
        if (IsFull())
            throw std::logic_error("buff is full!"); //если буфер полон, бросается исключение

        buff_[writeI_] = item; //записываем значение в буфер

        writeI_ = Inc(writeI_); //меняем индекс записи
        ++count_;  //увеличиваем значение переменной количества элементов в буфере
    }

    //прочитать значение из буфера

    TYPE Read()
    {
        if (IsEmpty())
            throw std::logic_error("buff is empty!"); // если буфер пуст, бросается исключение

        TYPE returnItem = std::move(buff_[readI_]);  //возвращаемый элемент

        readI_ = Inc(readI_); //меняем индекс чтения
        --count_;  //уменьшаем значение переменной количества элементов в буфере

        return returnItem;
    }

    //==========================================

    //полон ли буфер 

    bool IsFull()   const noexcept
    {
        return (count_ == size_);
    }

    //пуст ли буфер 

    bool IsEmpty()  const noexcept
    {
        return (count_ == 0);
    }

    //количество элементов в буфере

    size_t Length() const noexcept
    {
        return count_;
    }

    //размер буфера

    size_t BufferSize() const noexcept
    {
        return size_;
    }

    //очистка буфера

    void Clear() noexcept
    {
        readI_ = writeI_ = count_ = 0;
    }
};
