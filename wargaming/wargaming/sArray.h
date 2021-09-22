#pragma once

/*
	C���������� ������
*/

#include <initializer_list>

template<typename TYPE, size_t size_> //��� � ������ �������
class sArray
{
private:
	TYPE data_[size_]; //�����
public:

	//������������
	//==========================================

	 //����������� �� ��������� 

	sArray() noexcept = default;

	//����������� �����������

	sArray(sArray const& other) noexcept
	{
		for (size_t i = 0; i < size_; ++i) //�������� ������ ������� �������
			data_[i] = other.data_[i];
	}

	//������������ ����������� �����������

	
	sArray(sArray && other) noexcept
	{
		std::move(std::begin(other.data_), std::end(other.data_), &data_[0]); //����������� ������� ������� �������
	}

	//����������� �� ������ �������������

	sArray(std::initializer_list<TYPE> lst)
	{
		if (lst.size() > size_)
			throw std::logic_error("The size of the list does not match the size of the array");

		std::copy(std::begin(lst), std::end(lst), data_); //�������� ������ �� �����
	}

	//��������� ������������ 
	//==========================================

	// �������� ������������ 

	sArray& operator = (sArray const& other)
	{
		if (this == &other) //������ �� ������������ ������ ����
			return *this;

		for (size_t i = 0; i < size_; ++i) //�������� ������ ������� �������
			data_[i] = other.data_[i];

		return *this;
	}

	// ������������ �������� ������������

	
	sArray& operator = (sArray&& other) noexcept
	{
		if (this == &other) //������ �� ������������ ������ ����
			return *this;

		std::move(std::begin(other.data_), std::end(other.data_), &data_[0]); //����������� ������� ������� �������

		return *this;
	}
	
	//==========================================

	//������ �� ������� 

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

	//����� ������

	size_t Length() const noexcept
	{
		return size_;
	}
};