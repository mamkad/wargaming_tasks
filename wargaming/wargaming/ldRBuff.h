#pragma once

/*
	����������� ����� �� ������ �������� ������
*/

#include "List.h"

template<typename TYPE>
class ldRBuff
{
private:
	List <TYPE> buff_; //����� � �������
    size_t size_; 
public:

    //����������� � ����������
    //==========================================

    ldRBuff() : size_(0) {}

    //����������� �� ������ ���������, ��������� ������ ������

	explicit ldRBuff(size_t sze) : size_(sze) {}

    //����������� �����������

    ldRBuff(ldRBuff const& other)
        : buff_(other.buff_), size_(other.size_)
    {}
    
    //������������ ����������� �����������

    ldRBuff(ldRBuff && other)
        : buff_(std::move(other.buff_)), size_(other.size_)
    {
        other.size_ = 0;
    }

    //����������� �� ������ �������������

    ldRBuff(std::initializer_list<TYPE> lst) : buff_(lst), size_(lst.size())
    {
    }

    //��������� ������������ 
    //==========================================

     // �������� ������������ 

    ldRBuff& operator = (ldRBuff const& other)
    {
        if (this == &other) //������ �� ������������ ������ ����
            return *this;

        buff_ = other.buff_; //��������� �������� ������������ 
        size_ = other.size_;
    }

    // ������������ �������� ������������

    ldRBuff& operator = (ldRBuff&& other) noexcept
    {
        if (this == &other) //������ �� ������������ ������ ����
            return *this;

        //����������� ������ ������� �������

        buff_ = std::move(other.buff_);
        size_ = other.size_;

        // ��������� ������ � ������������������ ���������
        other.size_ = 0;
    }

    //==========================================

   //�������� �������� � �����

    void Write(TYPE const& item)
    {
        if (IsFull())
            throw std::logic_error("buff is full!"); //���� ����� �����, ��������� ����������
        buff_.PushFront(item); //���������� �������� � �����
    }

    //��������� �������� �� ������

    TYPE Read()
    {
        if (IsEmpty())
            throw std::logic_error("buff is empty!"); // ���� ����� ����, ��������� ����������
        return buff_.PopBack();  //������������ �������
    }

    //����� �� ����� 

    bool IsFull()   const noexcept
    {
        return (size_ == buff_.Length());
    }

    //���� �� ����� 

    bool IsEmpty()  const noexcept
    {
        return buff_.IsEmpty();
    }

    //���������� ��������� � ������

    size_t Length() const noexcept
    {
        return buff_.Length();
    }

    //������ ������

    size_t BufferSize() const noexcept
    {
        return size_;
    }

    //������� ������

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
