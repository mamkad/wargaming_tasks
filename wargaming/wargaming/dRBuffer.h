#pragma once

/*
    ����������� ����� �� ������ ������������� �������
    ������ ���������� � ����� dArray.h
    /�
*/

#include "dArray.h"

template<typename TYPE>
class dRBuff
{
private:
	dArray <TYPE> buff_; //����� � �������
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

    dRBuff() : readI_(0), writeI_(0), count_(0) {};

    //����������� �� ������ ���������, ��������� ������ ������

	explicit dRBuff(size_t capacity) : buff_(capacity), readI_(0), writeI_(0), count_(0) {}

    //����������� �����������

    dRBuff(dRBuff const & other) : buff_(other.buff_), readI_(other.readI_), writeI_(other.writeI_), count_(other.count_) {}

    //������������ ����������� �����������

    dRBuff(dRBuff && other) noexcept : buff_(std::move(other.buff_)), readI_(other.readI_), writeI_(other.writeI_), count_(other.count_)  //����������� ������ ������� �������
    {
        // ��������� ������ � ������������������ ���������
        other.readI_ = 0;
        other.writeI_ = 0;
        other.count_ = 0;
    }

    //����������� �� ������ �������������

    dRBuff(std::initializer_list<TYPE> lst) : buff_(lst.size()), readI_(0), writeI_(lst.size()), count_(lst.size())
    {
        size_t i = 0;
        for (TYPE const& v : lst)  //�������� ������ �� ������
            buff_[i++] = v;
    }

    //��������� ������������ 
    //==========================================

    // �������� ������������ 

    dRBuff& operator = (dRBuff const& other)
    {
        if (this == &other) //������ �� ������������ ������ ����
            return *this;

        buff_ = other.buff_;
            
        readI_ = other.readI_;
        writeI_ = other.writeI_;
        count_ = other.count_;
    }

    // ������������ �������� ������������

    dRBuff& operator = (dRBuff && other) noexcept
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

	//==========================================

    //�������� �������� � �����

    void Write(TYPE const& item)
    {
        if(IsFull())
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
        return (count_ == buff_.Length());
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
        return buff_.Length();
    }

    //������� ������

    void Clear() noexcept
    {
        readI_ = writeI_ = count_ = 0;
    }

    //==========================================

    //�������� ������ ������ 

    //��� ��������� ������� ��� ������� ������������

    void Resize(size_t newSize)
    {
        buff_.Resize(newSize);
        readI_ = writeI_ = count_ = 0;
    }
};
