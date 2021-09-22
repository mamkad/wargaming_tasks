#include "pch.h"
#include "CppUnitTest.h"

#include "..\wargaming\IsEven.h"

#include "..\wargaming\dArray.h"
#include "..\wargaming\sArray.h"
#include "..\wargaming\List.h"
#include "..\wargaming\dRBuffer.h"
#include "..\wargaming\sRBuffer.h"
#include "..\wargaming\ldRBuff.h"
#include "..\wargaming\ldRBuff.h"

#include "..\wargaming\Sort.h"


#include <ctime>
#include <utility>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace wargamingTests
{

	//тест первого задания

	TEST_CLASS(Task1_IsEven)
	{
	public:

		// нахождение чётных чисел в диапазоне от 1 до 1000
		// сравнение результатов работы функции

		TEST_METHOD(Test1)
		{
			for (int numb = 1; numb < 1000; ++numb)
				if (!(numb % 2)) Assert::IsTrue(IsEven(numb));
				else			 Assert::IsFalse(IsEven(numb));
		}
	};

	//тесты циклических буферов
	//

	TEST_CLASS(Task2_StaticRingBuffer)
	{
		//  объект буфера на основе статического массива
		sRBuff<string, 50> sRingBuff;

		// тестирование буфера на основе статического массива

		//проверка базовых функций
		TEST_METHOD(Test1_StaticRingBuffer_Basic_Function)
		{
			Assert::IsTrue(sRingBuff.Length() == 0); //проверяем кол-во элементов
			Assert::IsTrue(sRingBuff.BufferSize() == 50); //проверяем размер буфера
			Assert::IsTrue(sRingBuff.IsEmpty() == true); //проверяем на пустоту
			Assert::IsTrue(sRingBuff.IsFull() == false); //проверяем на заполненность
		}

		// чтение/запись
		TEST_METHOD(Test2_StaticRingBuffer_ReadWrite)
		{
			//проверка базового чтения и записи
			sRingBuff.Write("Hey");
			Assert::IsTrue(sRingBuff.Read() == "Hey");

			//записываем 10 значений
			for (size_t i = 0; i < 10; ++i)
				sRingBuff.Write("str " + std::to_string(i));

			Assert::IsTrue(sRingBuff.Length() == 10); //проверяем кол-во элементов
			Assert::IsTrue(sRingBuff.IsEmpty() == false); //проверяем на пустоту
			Assert::IsTrue(sRingBuff.IsFull() == false); //проверяем на заполненность

			//записываем 40 значений
			for (size_t i = 0; i < 40; ++i)
				sRingBuff.Write("ABC " + std::to_string(i));

			Assert::IsTrue(sRingBuff.Length() == 50); //проверяем кол-во элементов
			Assert::IsTrue(sRingBuff.IsEmpty() == false); //проверяем на пустоту
			Assert::IsTrue(sRingBuff.IsFull() == true); //проверяем на заполненность

			//пробуем записать значение в заполненный буфер
			try 
			{
				sRingBuff.Write("BUFFER IS FULL");
				Assert::Fail(); 
			}
			catch (std::logic_error)
			{}

			//читаем 25 значений
			for (size_t i = 0; i < 25; ++i)
				sRingBuff.Read();

			Assert::IsTrue(sRingBuff.Length() == 25); //проверяем кол-во элементов
			Assert::IsTrue(sRingBuff.IsEmpty() == false); //проверяем на пустоту
			Assert::IsTrue(sRingBuff.IsFull() == false); //проверяем на заполненность

			//читаем оставшиеся
			while (!sRingBuff.IsEmpty())
				sRingBuff.Read();

			Assert::IsTrue(sRingBuff.Length() == 0); //проверяем кол-во элементов
			Assert::IsTrue(sRingBuff.IsEmpty() == true); //проверяем на пустоту
			Assert::IsTrue(sRingBuff.IsFull() == false); //проверяем на заполненность

			//пробуем прочитать значение из пустого буферв
			try
			{
				sRingBuff.Read();
				Assert::Fail();
			}
			catch (std::logic_error)
			{
			}
		}

		//симуляция реальной работы
		TEST_METHOD(Test3_StaticRingBuffer_RealWorks)
		{
			srand(time(NULL));

			for (size_t times = 1; times <= 100; ++times)
			{
				// случайно выбирает либо 1 либо 2.
				// если 1 - записываем значение, если 2, то читается.
				// входе работы ожидается что исключений не возникнет

				int choise = rand() % 2 + 1;  //rand () от 1 до 2
				
				switch (choise)
				{
				case 1:

					if (!sRingBuff.IsFull())
					{
						try
						{
							sRingBuff.Write("abcdefg " + std::to_string(times));
						}
						catch (std::logic_error)
						{
							Assert::Fail();
						}
					}
						
					break;

				case 2: 

					if (!sRingBuff.IsEmpty())
					{
						try
						{
							sRingBuff.Read();
						}
						catch (std::logic_error)
						{
							Assert::Fail();
						}
					}
					break;

				}

			}
		}
	};

	//тестирование структур данных, реализованных для буферов

	TEST_CLASS(DataStructTest_ArraysAndList)
	{
		dArray<double> dynamicArrayMoveS()
		{
			dArray<double> move_d = { 1, 2, 3, 4, 567, 23, 5, 23 };
			return move_d;
		}

		//тест динамического массива
		//тесты конструкторов и базовых функций
		TEST_METHOD(Test1_DynamicArray)
		{
			dArray<double> a;
			dArray<double> b(56);

			//проверяем кол-во элементов

			Assert::IsTrue(a.Length() == 0);
			Assert::IsTrue(b.Length() == 56);

			for (size_t i = 0; i < b.Length(); ++i)
				b[i] = double(i) * 2.0 / 45.0;

			//меняем размер массива a
			a.Resize(256);

			//проверяем кол-во элементов массива a 
			Assert::IsTrue(a.Length() == 256);

			//создаём массива с от b
			dArray<double> c = b; 

			// проверяем, что конструктор копирования работает правильно
			for (size_t i = 0; i < b.Length(); ++i)
				if (c[i] != b[i])
					Assert::Fail();

			c.Resize(10);

			for (size_t i = 0; i < c.Length(); ++i)
				if (c[i] != b[i])
					Assert::Fail();

			// проверка конструктора перемещения
			a = dynamicArrayMoveS();

			Assert::IsTrue(a.Length() == 8);

			//очищаем ресурсы
			a.Clear();
			Assert::IsTrue(a.Length() == 0);

			//меняем размер массива a
			a.Resize(10);

			for (size_t i = 0; i < a.Length(); ++i)
				a[i] = i * i - 1;

			//проверка оператора присваивания 
			b = a;

			for (size_t i = 0; i < a.Length(); ++i)
				if (a[i] != b[i])
					Assert::Fail();

			//выделяем слишком большой участок памяти для буфер 
			//провера на исключения
			try
			{
				c.Resize(100000000000000);
				Assert::Fail();
			}
			catch (std::bad_alloc)
			{}

			//обращаемся к массиву через неправильные индексы

			try
			{
				a.At(67) = 56;
				Assert::Fail();
			}
			catch (std::logic_error)
			{}

			c.Clear();

			try
			{
				c.At(2) = 353;
				Assert::Fail();
			}
			catch (std::logic_error)
			{}
		}

		sArray<std::pair<int, int>, 3> StaticArrayMoveS()
		{
			sArray<std::pair<int, int>, 3> t = { {4, 34}, {6,4}, {7,124} };
			return t;
		}

		//тест статического массива
		//тесты конструкторов и базовых функций

		TEST_METHOD(Test2_StaticArray)
		{
			sArray<float, 256> a;

			try
			{
				a.At(675) = 56;
				Assert::Fail();
			}
			catch (std::logic_error)
			{

			}

			for (size_t i = 0; i < a.Length(); ++i)
				a[i] = i * i * i / 100.0;

			sArray<float, 256> b = a;

			for (size_t i = 0; i < a.Length(); ++i)
				if (b[i] != a[i])
					Assert::Fail();

			sArray<float, 256> c;

			c = a;
			
			for (size_t i = 0; i < a.Length(); ++i)
				if (c[i] != a[i])
					Assert::Fail();

			sArray<float, 8> d = { 5, 3, 2, 4, 2 };

			try
			{
				sArray<float, 3> e = { 3, 5, 3, 5, 3, 2, 4 };
				Assert::Fail();
			}
			catch (std::logic_error)
			{}

			sArray<std::pair<int, int>, 3> g = { {4, 34}, {6,4}, {7,124} };
			sArray<std::pair<int, int>, 3> f = StaticArrayMoveS();
			
			Assert::IsTrue(g.Length() == f.Length());

			for (size_t i = 0; i < g.Length(); ++i)
				if ((g[i].first != f[i].first) && (g[i].second != f[i].second))
					Assert::Fail();
		}

		//тест связного списка
		//тесты конструкторов и базовых функций

		List<string> ListMoveS()
		{
			List<string> c;

			for (size_t i = 0; i < 2500; ++i)
				c.PushBack("C " + std::to_string(i));

			return c;
		}

		TEST_METHOD(Test3_List)
		{
			List<string> a;

			Assert::IsTrue(a.IsEmpty() == true);
			Assert::IsTrue(a.Length() == 0);

			try
			{
				a.PopBack();
				Assert::Fail();
			}
			catch (std::logic_error)
			{}

			for(size_t i = 0; i < 25; ++i)
				a.PushFront("A " + std::to_string(i));

			for (size_t i = 0; i < 25; ++i)
				a.PushBack("B " + std::to_string(i));

			Assert::IsTrue(a.IsEmpty() == false);
			Assert::IsTrue(a.Length() == 50);

			List<string> b = a;

			Assert::IsTrue(b.IsEmpty() == false);
			Assert::IsTrue(b.Length() == 50);

			a.Clear();

			Assert::IsTrue(a.IsEmpty() == true);
			Assert::IsTrue(a.Length() == 0);

			a = b;

			Assert::IsTrue(a.IsEmpty() == false);
			Assert::IsTrue(a.Length() == 50);

			b = ListMoveS();

			Assert::IsTrue(b.IsEmpty() == false);
			Assert::IsTrue(b.Length() == 2500);
		}


	};


	// тестирование буфера на основе динамического массива

	TEST_CLASS(Task2_DynamicRingBuffer)
	{
		//  объект буфера на основе динамического массива
		dRBuff<string> dRingBuff;

		//проверка базовых функций
		TEST_METHOD(Test1_dynamicRingBuffer_Basic_Function)
		{
			dRingBuff.Resize(256);

			Assert::IsTrue(dRingBuff.Length() == 0); //проверяем кол-во элементов
			Assert::IsTrue(dRingBuff.BufferSize() == 256); //проверяем размер буфера
			Assert::IsTrue(dRingBuff.IsEmpty() == true); //проверяем на пустоту
			Assert::IsTrue(dRingBuff.IsFull() == false); //проверяем на заполненность
		}

		// чтение/запись
		TEST_METHOD(Test2_dynamicRingBuffer_ReadWrite)
		{
			dRingBuff.Resize(50);

			//проверка базового чтения и записи
			dRingBuff.Write("Hey");
			Assert::IsTrue(dRingBuff.Read() == "Hey");

			//записываем 10 значений
			for (size_t i = 0; i < 10; ++i)
				dRingBuff.Write("str " + std::to_string(i));

			Assert::IsTrue(dRingBuff.Length() == 10); //проверяем кол-во элементов
			Assert::IsTrue(dRingBuff.IsEmpty() == false); //проверяем на пустоту
			Assert::IsTrue(dRingBuff.IsFull() == false); //проверяем на заполненность

			//записываем 40 значений
			for (size_t i = 0; i < 40; ++i)
				dRingBuff.Write("ABC " + std::to_string(i));

			Assert::IsTrue(dRingBuff.Length() == 50); //проверяем кол-во элементов
			Assert::IsTrue(dRingBuff.IsEmpty() == false); //проверяем на пустоту
			Assert::IsTrue(dRingBuff.IsFull() == true); //проверяем на заполненность

			//пробуем записать значение в заполненный буфер
			try
			{
				dRingBuff.Write("BUFFER IS FULL");
				Assert::Fail();
			}
			catch (std::logic_error)
			{
			}

			//читаем 25 значений
			for (size_t i = 0; i < 25; ++i)
				dRingBuff.Read();

			Assert::IsTrue(dRingBuff.Length() == 25); //проверяем кол-во элементов
			Assert::IsTrue(dRingBuff.IsEmpty() == false); //проверяем на пустоту
			Assert::IsTrue(dRingBuff.IsFull() == false); //проверяем на заполненность

			//читаем оставшиеся
			while (!dRingBuff.IsEmpty())
				dRingBuff.Read();

			Assert::IsTrue(dRingBuff.Length() == 0); //проверяем кол-во элементов
			Assert::IsTrue(dRingBuff.IsEmpty() == true); //проверяем на пустоту
			Assert::IsTrue(dRingBuff.IsFull() == false); //проверяем на заполненность

			//пробуем прочитать значение из пустого буферв
			try
			{
				dRingBuff.Read();
				Assert::Fail();
			}
			catch (std::logic_error)
			{
			}
			
		}

		//симуляция реальной работы
		TEST_METHOD(Test3_dynamicRingBuffer_RealWorks)
		{
			dRingBuff.Resize(123);

			srand(time(NULL));

			for (size_t times = 1; times <= 100; ++times)
			{
				// случайно выбирается число от 1 до 3
				// если 1 - записываем значение, если 2, то читается, 
				// если 3, то размер буфера меняется
				// входе работы ожидается что исключений не возникнет

				int choise = rand() % 3 + 1;  //rand () от 1 до 2

				switch (choise)
				{
				case 1:

					if (!dRingBuff.IsFull())
					{
						try
						{
							dRingBuff.Write("abcdefg " + std::to_string(times));
						}
						catch (std::logic_error)
						{
							Assert::Fail();
						}
					}

					break;

				case 2:

					if (!dRingBuff.IsEmpty())
					{
						try
						{
							dRingBuff.Read();
						}
						catch (std::logic_error)
						{
							Assert::Fail();
						}
					}
					break;

				case 3:

					dRingBuff.Resize(50 + times);
					break;
				}

			}
		}
	};

	// тестирование буфера на основе списка

	TEST_CLASS(Task2_listRingBuffer)
	{
		//  объект буфера на основе списка
		ldRBuff<string> ldRingBuff;

		//проверка базовых функций
		TEST_METHOD(Test1_listRingBuffer_Basic_Function)
		{
			ldRingBuff.Resize(256);

			Assert::IsTrue(ldRingBuff.Length() == 0); //проверяем кол-во элементов
			Assert::IsTrue(ldRingBuff.BufferSize() == 256); //проверяем размер буфера
			Assert::IsTrue(ldRingBuff.IsEmpty() == true); //проверяем на пустоту
			Assert::IsTrue(ldRingBuff.IsFull() == false); //проверяем на заполненность
		}
		// чтение/запись
		TEST_METHOD(Test2_listRingBuffer_ReadWrite)
		{
			ldRingBuff.Resize(50);

			//проверка базового чтения и записи
			ldRingBuff.Write("Hey");
			Assert::IsTrue(ldRingBuff.Read() == "Hey");

			//записываем 10 значений
			for (size_t i = 0; i < 10; ++i)
				ldRingBuff.Write("str " + std::to_string(i));

			Assert::IsTrue(ldRingBuff.Length() == 10); //проверяем кол-во элементов
			Assert::IsTrue(ldRingBuff.IsEmpty() == false); //проверяем на пустоту
			Assert::IsTrue(ldRingBuff.IsFull() == false); //проверяем на заполненность

			//записываем 40 значений
			for (size_t i = 0; i < 40; ++i)
				ldRingBuff.Write("ABC " + std::to_string(i));

			Assert::IsTrue(ldRingBuff.Length() == 50); //проверяем кол-во элементов
			Assert::IsTrue(ldRingBuff.IsEmpty() == false); //проверяем на пустоту
			Assert::IsTrue(ldRingBuff.IsFull() == true); //проверяем на заполненность

			//пробуем записать значение в заполненный буфер
			try
			{
				ldRingBuff.Write("BUFFER IS FULL");
				Assert::Fail();
			}
			catch (std::logic_error)
			{
			}

			//читаем 25 значений
			for (size_t i = 0; i < 25; ++i)
				ldRingBuff.Read();

			Assert::IsTrue(ldRingBuff.Length() == 25); //проверяем кол-во элементов
			Assert::IsTrue(ldRingBuff.IsEmpty() == false); //проверяем на пустоту
			Assert::IsTrue(ldRingBuff.IsFull() == false); //проверяем на заполненность

			//читаем оставшиеся
			while (!ldRingBuff.IsEmpty())
				ldRingBuff.Read();

			Assert::IsTrue(ldRingBuff.Length() == 0); //проверяем кол-во элементов
			Assert::IsTrue(ldRingBuff.IsEmpty() == true); //проверяем на пустоту
			Assert::IsTrue(ldRingBuff.IsFull() == false); //проверяем на заполненность

			//пробуем прочитать значение из пустого буферв
			try
			{
				ldRingBuff.Read();
				Assert::Fail();
			}
			catch (std::logic_error)
			{
			}
		}

		//симуляция реальной работы
		TEST_METHOD(Test3_listRingBuffer_RealWorks)
		{
			ldRingBuff.Resize(123);

			srand(time(NULL));

			for (size_t times = 1; times <= 100; ++times)
			{
				// случайно выбирается число от 1 до 3
				// если 1 - записываем значение, если 2, то читается, 
				// если 3, то размер буфера меняется
				// входе работы ожидается что исключений не возникнет

				int choise = rand() % 3 + 1;  //rand () от 1 до 2

				switch (choise)
				{
				case 1:

					if (!ldRingBuff.IsFull())
					{
						try
						{
							ldRingBuff.Write("abcdefg " + std::to_string(times));
						}
						catch (std::logic_error)
						{
							Assert::Fail();
						}
					}

					break;

				case 2:

					if (!ldRingBuff.IsEmpty())
					{
						try
						{
							ldRingBuff.Read();
						}
						catch (std::logic_error)
						{
							Assert::Fail();
						}
					}
					break;

				case 3:

					ldRingBuff.Resize(50 + times);
					break;
				}

			}
		}
	};

	TEST_CLASS(Task3_Sort)
	{
		TEST_METHOD(Test1_SortingOfBigArray)
		{
			int sze = 1000000;

			dArray<int> arr(sze);

			srand(time(NULL));
			for (int i = 0; i < sze; ++i)
			{
				arr[i] = rand() % 1000 + rand() % 50;

				if (!(i % 100))
					arr[i] *= -1;
			}

			QuickSort2(arr, 0, arr.Length() - 1);

			for (int i = 0; i < sze - 1; ++i)
				if(arr[i] > arr[i + 1])
					Assert::Fail();
		}
	};
};
