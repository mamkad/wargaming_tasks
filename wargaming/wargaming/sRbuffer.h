#pragma once

/*
    ����������� ����� �� ������ ������������ �������
*/

#include "sArray.h"

template<typename TYPE, size_t size_>
class sRBuff
{
private:
    sArray<TYPE, size_> buff_; //����� � �������
    size_t readI_, writeI_;  // ������� ������ � ������
    size_t count_; //���������� ���������

    //������� ��� ����������������� ��������

    size_t Inc(size_t i) const noexcept
    {
        ++i;
        return i < buff_.Length() ? i : 0;
    }

public:
    //����������� � ����������
    //==========================================

    //����������� �� ������ ���������, ��������� ������ ������

    sRBuff() noexcept :  readI_(0), writeI_(0), count_(0) {}

    //����������� �����������

    sRBuff(sRBuff const& other) noexcept  : buff_(other.buff_), readI_(other.readI_), writeI_(other.writeI_), count_(other.count_)  {}

    //������������ ����������� �����������

    sRBuff(sRBuff&& other) noexcept  : buff_(std::move(other.buff_)), readI_(other.readI_), writeI_(other.writeI_), count_(other.count_) //����������� ������ ������� �������
    {
        // ��������� ������ � ������������������ ���������
        other.readI_ = 0;
        other.writeI_ = 0;
        other.count_ = 0;
    }

    //����������� �� ������ �������������

    sRBuff(std::initializer_list<TYPE> lst) : buff_(lst), readI_(0), writeI_(lst.size()), count_(lst.size())
    {
    }

    //��������� ������������ 
    //==========================================

    // �������� ������������ 

    sRBuff& operator = (sRBuff const& other) noexcept
    {
        if (this == &other) //������ �� ������������ ������ ����
            return *this;

        buff_ = other.buff_;

        readI_ = other.readI_;
        writeI_ = other.writeI_;
        count_ = other.count_;
    }

    // ������������ �������� ������������

    sRBuff& operator = (sRBuff&& other) noexcept
    {
        if (this == &other) //������ �� ������������ ������ ����
            return *this;

        //����������� ������ ������� �������

        buff_ = std::move(other.buff_);

        readI_ = other.readI_;
        writeI_ = other.writeI_;
        count_ = other.count_;

        // ��������� ������ � ������������������ ���������
        other.readI_ = 0;
        other.writeI_ = 0;
        other.count_ = 0;
    }

    // �������� ������������ �� ������ �������������

    sRBuff& operator = (std::initializer_list<TYPE> lst)
    {

    }

    //==========================================

    //�������� �������� � �����

    void Write(TYPE const& item)
    {
        if (IsFull())
            throw std::logic_error("buff is full!"); //���� ����� �����, ��������� ����������

        buff_[writeI_] = item; //���������� �������� � �����

        writeI_ = Inc(writeI_); //������ ������ ������
        ++count_;  //����������� �������� ���������� ���������� ��������� � ������
    }

    //��������� �������� �� ������

    TYPE Read()
    {
        if (IsEmpty())
            throw std::logic_error("buff is empty!"); // ���� ����� ����, ��������� ����������

        TYPE returnItem = std::move(buff_[readI_]);  //������������ �������

        readI_ = Inc(readI_); //������ ������ ������
        --count_;  //��������� �������� ���������� ���������� ��������� � ������

        return returnItem;
    }

    //==========================================

    //����� �� ����� 

    bool IsFull()   const noexcept
    {
        return (count_ == size_);
    }

    //���� �� ����� 

    bool IsEmpty()  const noexcept
    {
        return (count_ == 0);
    }

    //���������� ��������� � ������

    size_t Length() const noexcept
    {
        return count_;
    }

    //������ ������

    size_t BufferSize() const noexcept
    {
        return size_;
    }

    //������� ������

    void Clear() noexcept
    {
        readI_ = writeI_ = count_ = 0;
    }
};
