#pragma once

/*
	������������ ������
*/

#include <algorithm>
#include <initializer_list>

template<typename TYPE>
class dArray
{
private:
	TYPE* data_;  //������
	size_t size_; // ������ ������ ������

public:

	//������������ � ����������
	//==========================================

	dArray() : data_(nullptr), size_(0) {}

	//����������� �� ������ ���������, ��������� ������ ������
	explicit dArray(size_t sze)  
		try : data_(new TYPE[sze]), size_(sze)
		{}
		catch(std::bad_alloc)     //���� �� ���������� �������� ������ ��� ������, ������� ����������
		{
			throw;
		}

	//����������� �����������

	dArray(dArray const & other)  
	try : data_(new TYPE[other.size_]), size_(other.size_)
	{
		for (size_t i = 0; i < size_; ++i) //�������� ������ ������� �������
			data_[i] = other.data_[i];  
	}
	catch (std::bad_alloc)  //���� �� ���������� �������� ������ ��� ������, ������� ����������
	{
		throw;
	}

	//������������ ����������� �����������

	dArray(dArray && other) noexcept  
		: data_(other.data_), size_(other.size_) //����������� ������ ������� �������
	{
		other.data_ = nullptr; //��������� ������ � ������������������ ���������
		other.size_ = 0;
	}

	//����������� �� ������ �������������

	dArray(std::initializer_list<TYPE> lst)
		try : data_(new TYPE[lst.size()]), size_(lst.size())
	{
		std::copy(std::begin(lst), std::end(lst), data_); //�������� ������ �� �����
	}
	catch (std::bad_alloc)  //���� �� ���������� �������� ������ ��� ������, ������� ����������
	{
		throw;
	}

	// ����������
	
	~dArray() 
	{
		Clear(); // ������� �����
	}

	//��������� ������������ 
	//==========================================

    //�������� ������������ 

	dArray& operator = (dArray const& other)
	{
		if (this == &other) //������ �� ������������ ������ ����
			return *this;

		Clear(); // ������� ������
		Resize(other.size_); //����� ����� ������ (������� ������ ���������� size_, ������� ����� ����������� �� �����)
		
		for (size_t i = 0; i < size_; ++i) //�������� ������ ������� �������
			data_[i] = other.data_[i];

		return *this;
	}

	//������������ �������� ������������

	dArray& operator = (dArray && other) noexcept
	{
		if (this == &other) //������ �� ������������ ������ ����
			return *this;

		Clear(); // ������� ������

		//����������� ������ ������� �������
		data_ = other.data_;
		size_ = other.size_;

		// ��������� ������ � ������������������ ���������
		other.data_ = nullptr;
		other.size_ = 0;

		return *this;
	}


	
	//==========================================

	//��������� ������� ������

	void Resize(size_t newSize)
	{
		if (size_ == newSize)   //���� ���������� ������ ��������� � �������, �������
			return;

		TYPE* newBuffer = new (std::nothrow) TYPE[newSize]; //�������� ������ �� ����� �����

		if (!newBuffer)		
			throw std::bad_alloc(); //���� �� ���������� ��������, ������� ����������

		if (data_ != nullptr) //���� ����� �� ����
		{
			// �������� ������ �� ������� ������ � �����
			size_t curSize = std::min(newSize, size_);

			for (size_t i = 0; i < curSize; ++i)
				newBuffer[i] = data_[i];

			Clear(); //������� ������� �����
		}
		
		//�����������  ����� ������ � ����� ������
		data_ = newBuffer;
		size_ = newSize;
	}

	//==========================================

	//������ �� ������� 

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

	// ���� �� �����

	bool IsEmpty()
	{
		return (size_ == 0);
	}

	//����� ������

	size_t Length() const noexcept
	{
		return size_;
	}

	//������� ������

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