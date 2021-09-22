#pragma once

/*
	����������� ������
*/

#include <iostream>
using namespace std;

#include <initializer_list>

template<typename TYPE>
class List
{
private:
	//������� ������
	struct node
	{
		node(node* prev, node* next, TYPE const& item) 
			: prev_(prev), next_(next), data_(item) {} //����������� �������� ��������� ��������� �� ���������� �������, ��������� � ����� ��������
		
		node* prev_, *next_ ; //��������� �� ���������� � ��������� �������� 
		TYPE data_;  //������
	};

private:
	node* head_, *tail_; //������ � ����� ������
	size_t count_; // ���-�� ��������� ������

public:

	//������������
	//==========================================

	 //����������� �� ���������

	List() noexcept : tail_(nullptr), head_(nullptr), count_(0) {}

	//����������� �����������

	List(List const & other)
	{
		if (!other.IsEmpty()) //���� ������ ������� other �� ����
		{
			node* oHeadNode = other.head_;

			while (oHeadNode)
			{
				PushBack(oHeadNode->data_);
				oHeadNode = oHeadNode->next_;
			}
		}
		else
		{
			head_ = nullptr;
			tail_ = nullptr; 
			count_ = 0;
		}
	}

	//������������ �����������

	List(List&& other) noexcept
		: head_(other.head_), tail_(other.tail_), count_(other.count_)
	{
		other.head_ = nullptr;
		other.tail_ = nullptr;
		other.count_ = 0;
	}

	//����������� �� ������ �������������

	List(std::initializer_list<TYPE> lst)
	{
		for (auto revIt = lst.begin(); revIt != lst.end(); ++revIt)
			PushBack(*revIt);
	}

	//����������

	~List()
	{
		Clear();
	}

	//��������� ������������ 
	//==========================================

	// �������� ������������ 
	
	List& operator = (List const & other) noexcept
	{
		if (this == &other) //������ �� ������������ ������ ����
			return *this;

		Clear();

		if (!other.IsEmpty()) //���� ������ ������� other �� ����
		{
			node* oHeadNode = other.head_;

			while (oHeadNode)
			{
				PushBack(oHeadNode->data_);
				oHeadNode = oHeadNode->next_;
			}
		}
		
		return *this;
	}

	// ������������ �������� ������������

	List& operator = (List&& other) noexcept
	{
		if (this == &other) //������ �� ������������ ������ ����
			return *this;

		Clear();  //������� ��� ������

		//����������� �������

		head_ = other.head_;
		tail_ = other.tail_;
		count_ = other.count_;

		//��������� ������ � ������������������ ���������

		other.head_ = nullptr;
		other.tail_ = nullptr;
		other.count_ = 0;

		return *this;
	}

	//�������� ������� � ������ ������

	void PushFront(TYPE const& item)
	{
		node* newNode = new (std::nothrow) node(nullptr, head_, item);

		if (!newNode)
			throw std::bad_alloc();

		if (head_)
			head_->prev_ = newNode;

		if (IsEmpty())
			head_ = tail_ = newNode;
		else
			head_ = newNode;

		++count_;
	}

	void PushBack(TYPE const& item)
	{
		node* newNode = new (std::nothrow) node(tail_, nullptr, item);

		if (!newNode)
			throw std::bad_alloc();

		if (tail_)
			tail_->next_ = newNode;

		if (IsEmpty())
			head_ = tail_ = newNode;
		else
			tail_ = newNode;

		++count_;
	}

	//������� ������� �� ����� ������

	TYPE PopBack()
	{
		if (IsEmpty())
			throw std::logic_error("list is empty!");

		TYPE retItem = std::move(tail_->data_);

		if (Length() != 1)
		{
			node* delNode = tail_;
			tail_ = tail_->prev_;
			tail_->next_ = nullptr;
			delete delNode;
		}
		else
		{
			delete tail_;
			head_ = tail_ = nullptr;
		}

		--count_;

		return retItem;
	}

	//�������� ������

	void Clear()
	{
		while (!IsEmpty())
			PopBack();
	}

	//���-�� ��������� � ������

	size_t Length() const noexcept
	{
		return count_;
	}

	//���� �� ������

	bool IsEmpty()  const noexcept
	{
		return (count_ == 0);
	}
};
