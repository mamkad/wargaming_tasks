#pragma once

/*
	Двухсвязный список
*/

#include <iostream>
using namespace std;

#include <initializer_list>

template<typename TYPE>
class List
{
private:
	//элемент списка
	struct node
	{
		node(node* prev, node* next, TYPE const& item) 
			: prev_(prev), next_(next), data_(item) {} //конструктор элемента принимает указатель на предыдущий элемент, следующий и самое значение
		
		node* prev_, *next_ ; //указатели на предыдущий и следующий элементы 
		TYPE data_;  //данные
	};

private:
	node* head_, *tail_; //голова и хвост списка
	size_t count_; // кол-во элементов списка

public:

	//конструкторы
	//==========================================

	 //конструктор по умочланию

	List() noexcept : tail_(nullptr), head_(nullptr), count_(0) {}

	//конструктор копирования

	List(List const & other)
	{
		if (!other.IsEmpty()) //если список объекта other не пуст
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

	//перемещающий конструктор

	List(List&& other) noexcept
		: head_(other.head_), tail_(other.tail_), count_(other.count_)
	{
		other.head_ = nullptr;
		other.tail_ = nullptr;
		other.count_ = 0;
	}

	//конструктор от списка инициализации

	List(std::initializer_list<TYPE> lst)
	{
		for (auto revIt = lst.begin(); revIt != lst.end(); ++revIt)
			PushBack(*revIt);
	}

	//деструктор

	~List()
	{
		Clear();
	}

	//операторы присваивания 
	//==========================================

	// оператор присваивания 
	
	List& operator = (List const & other) noexcept
	{
		if (this == &other) //защита от присваивания самому себе
			return *this;

		Clear();

		if (!other.IsEmpty()) //если список объекта other не пуст
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

	// перемещающий оператор присваивания

	List& operator = (List&& other) noexcept
	{
		if (this == &other) //защита от присваивания самому себе
			return *this;

		Clear();  //очищаем все данные

		//захватываем ресурсы

		head_ = other.head_;
		tail_ = other.tail_;
		count_ = other.count_;

		//оставляем данные в синхронизированном состоянии

		other.head_ = nullptr;
		other.tail_ = nullptr;
		other.count_ = 0;

		return *this;
	}

	//вставить элемент в начало списка

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

	//удалить элемент из конца списка

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

	//очистить список

	void Clear()
	{
		while (!IsEmpty())
			PopBack();
	}

	//кол-во элементов в списке

	size_t Length() const noexcept
	{
		return count_;
	}

	//пуст ли список

	bool IsEmpty()  const noexcept
	{
		return (count_ == 0);
	}
};
