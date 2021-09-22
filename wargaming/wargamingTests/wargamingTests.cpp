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

	//���� ������� �������

	TEST_CLASS(Task1_IsEven)
	{
	public:

		// ���������� ������ ����� � ��������� �� 1 �� 1000
		// ��������� ����������� ������ �������

		TEST_METHOD(Test1)
		{
			for (int numb = 1; numb < 1000; ++numb)
				if (!(numb % 2)) Assert::IsTrue(IsEven(numb));
				else			 Assert::IsFalse(IsEven(numb));
		}
	};

	//����� ����������� �������
	//

	TEST_CLASS(Task2_StaticRingBuffer)
	{
		//  ������ ������ �� ������ ������������ �������
		sRBuff<string, 50> sRingBuff;

		// ������������ ������ �� ������ ������������ �������

		//�������� ������� �������
		TEST_METHOD(Test1_StaticRingBuffer_Basic_Function)
		{
			Assert::IsTrue(sRingBuff.Length() == 0); //��������� ���-�� ���������
			Assert::IsTrue(sRingBuff.BufferSize() == 50); //��������� ������ ������
			Assert::IsTrue(sRingBuff.IsEmpty() == true); //��������� �� �������
			Assert::IsTrue(sRingBuff.IsFull() == false); //��������� �� �������������
		}

		// ������/������
		TEST_METHOD(Test2_StaticRingBuffer_ReadWrite)
		{
			//�������� �������� ������ � ������
			sRingBuff.Write("Hey");
			Assert::IsTrue(sRingBuff.Read() == "Hey");

			//���������� 10 ��������
			for (size_t i = 0; i < 10; ++i)
				sRingBuff.Write("str " + std::to_string(i));

			Assert::IsTrue(sRingBuff.Length() == 10); //��������� ���-�� ���������
			Assert::IsTrue(sRingBuff.IsEmpty() == false); //��������� �� �������
			Assert::IsTrue(sRingBuff.IsFull() == false); //��������� �� �������������

			//���������� 40 ��������
			for (size_t i = 0; i < 40; ++i)
				sRingBuff.Write("ABC " + std::to_string(i));

			Assert::IsTrue(sRingBuff.Length() == 50); //��������� ���-�� ���������
			Assert::IsTrue(sRingBuff.IsEmpty() == false); //��������� �� �������
			Assert::IsTrue(sRingBuff.IsFull() == true); //��������� �� �������������

			//������� �������� �������� � ����������� �����
			try 
			{
				sRingBuff.Write("BUFFER IS FULL");
				Assert::Fail(); 
			}
			catch (std::logic_error)
			{}

			//������ 25 ��������
			for (size_t i = 0; i < 25; ++i)
				sRingBuff.Read();

			Assert::IsTrue(sRingBuff.Length() == 25); //��������� ���-�� ���������
			Assert::IsTrue(sRingBuff.IsEmpty() == false); //��������� �� �������
			Assert::IsTrue(sRingBuff.IsFull() == false); //��������� �� �������������

			//������ ����������
			while (!sRingBuff.IsEmpty())
				sRingBuff.Read();

			Assert::IsTrue(sRingBuff.Length() == 0); //��������� ���-�� ���������
			Assert::IsTrue(sRingBuff.IsEmpty() == true); //��������� �� �������
			Assert::IsTrue(sRingBuff.IsFull() == false); //��������� �� �������������

			//������� ��������� �������� �� ������� ������
			try
			{
				sRingBuff.Read();
				Assert::Fail();
			}
			catch (std::logic_error)
			{
			}
		}

		//��������� �������� ������
		TEST_METHOD(Test3_StaticRingBuffer_RealWorks)
		{
			srand(time(NULL));

			for (size_t times = 1; times <= 100; ++times)
			{
				// �������� �������� ���� 1 ���� 2.
				// ���� 1 - ���������� ��������, ���� 2, �� ��������.
				// ����� ������ ��������� ��� ���������� �� ���������

				int choise = rand() % 2 + 1;  //rand () �� 1 �� 2
				
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

	//������������ �������� ������, ������������� ��� �������

	TEST_CLASS(DataStructTest_ArraysAndList)
	{
		dArray<double> dynamicArrayMoveS()
		{
			dArray<double> move_d = { 1, 2, 3, 4, 567, 23, 5, 23 };
			return move_d;
		}

		//���� ������������� �������
		//����� ������������� � ������� �������
		TEST_METHOD(Test1_DynamicArray)
		{
			dArray<double> a;
			dArray<double> b(56);

			//��������� ���-�� ���������

			Assert::IsTrue(a.Length() == 0);
			Assert::IsTrue(b.Length() == 56);

			for (size_t i = 0; i < b.Length(); ++i)
				b[i] = double(i) * 2.0 / 45.0;

			//������ ������ ������� a
			a.Resize(256);

			//��������� ���-�� ��������� ������� a 
			Assert::IsTrue(a.Length() == 256);

			//������ ������� � �� b
			dArray<double> c = b; 

			// ���������, ��� ����������� ����������� �������� ���������
			for (size_t i = 0; i < b.Length(); ++i)
				if (c[i] != b[i])
					Assert::Fail();

			c.Resize(10);

			for (size_t i = 0; i < c.Length(); ++i)
				if (c[i] != b[i])
					Assert::Fail();

			// �������� ������������ �����������
			a = dynamicArrayMoveS();

			Assert::IsTrue(a.Length() == 8);

			//������� �������
			a.Clear();
			Assert::IsTrue(a.Length() == 0);

			//������ ������ ������� a
			a.Resize(10);

			for (size_t i = 0; i < a.Length(); ++i)
				a[i] = i * i - 1;

			//�������� ��������� ������������ 
			b = a;

			for (size_t i = 0; i < a.Length(); ++i)
				if (a[i] != b[i])
					Assert::Fail();

			//�������� ������� ������� ������� ������ ��� ����� 
			//������� �� ����������
			try
			{
				c.Resize(100000000000000);
				Assert::Fail();
			}
			catch (std::bad_alloc)
			{}

			//���������� � ������� ����� ������������ �������

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

		//���� ������������ �������
		//����� ������������� � ������� �������

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

		//���� �������� ������
		//����� ������������� � ������� �������

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


	// ������������ ������ �� ������ ������������� �������

	TEST_CLASS(Task2_DynamicRingBuffer)
	{
		//  ������ ������ �� ������ ������������� �������
		dRBuff<string> dRingBuff;

		//�������� ������� �������
		TEST_METHOD(Test1_dynamicRingBuffer_Basic_Function)
		{
			dRingBuff.Resize(256);

			Assert::IsTrue(dRingBuff.Length() == 0); //��������� ���-�� ���������
			Assert::IsTrue(dRingBuff.BufferSize() == 256); //��������� ������ ������
			Assert::IsTrue(dRingBuff.IsEmpty() == true); //��������� �� �������
			Assert::IsTrue(dRingBuff.IsFull() == false); //��������� �� �������������
		}

		// ������/������
		TEST_METHOD(Test2_dynamicRingBuffer_ReadWrite)
		{
			dRingBuff.Resize(50);

			//�������� �������� ������ � ������
			dRingBuff.Write("Hey");
			Assert::IsTrue(dRingBuff.Read() == "Hey");

			//���������� 10 ��������
			for (size_t i = 0; i < 10; ++i)
				dRingBuff.Write("str " + std::to_string(i));

			Assert::IsTrue(dRingBuff.Length() == 10); //��������� ���-�� ���������
			Assert::IsTrue(dRingBuff.IsEmpty() == false); //��������� �� �������
			Assert::IsTrue(dRingBuff.IsFull() == false); //��������� �� �������������

			//���������� 40 ��������
			for (size_t i = 0; i < 40; ++i)
				dRingBuff.Write("ABC " + std::to_string(i));

			Assert::IsTrue(dRingBuff.Length() == 50); //��������� ���-�� ���������
			Assert::IsTrue(dRingBuff.IsEmpty() == false); //��������� �� �������
			Assert::IsTrue(dRingBuff.IsFull() == true); //��������� �� �������������

			//������� �������� �������� � ����������� �����
			try
			{
				dRingBuff.Write("BUFFER IS FULL");
				Assert::Fail();
			}
			catch (std::logic_error)
			{
			}

			//������ 25 ��������
			for (size_t i = 0; i < 25; ++i)
				dRingBuff.Read();

			Assert::IsTrue(dRingBuff.Length() == 25); //��������� ���-�� ���������
			Assert::IsTrue(dRingBuff.IsEmpty() == false); //��������� �� �������
			Assert::IsTrue(dRingBuff.IsFull() == false); //��������� �� �������������

			//������ ����������
			while (!dRingBuff.IsEmpty())
				dRingBuff.Read();

			Assert::IsTrue(dRingBuff.Length() == 0); //��������� ���-�� ���������
			Assert::IsTrue(dRingBuff.IsEmpty() == true); //��������� �� �������
			Assert::IsTrue(dRingBuff.IsFull() == false); //��������� �� �������������

			//������� ��������� �������� �� ������� ������
			try
			{
				dRingBuff.Read();
				Assert::Fail();
			}
			catch (std::logic_error)
			{
			}
			
		}

		//��������� �������� ������
		TEST_METHOD(Test3_dynamicRingBuffer_RealWorks)
		{
			dRingBuff.Resize(123);

			srand(time(NULL));

			for (size_t times = 1; times <= 100; ++times)
			{
				// �������� ���������� ����� �� 1 �� 3
				// ���� 1 - ���������� ��������, ���� 2, �� ��������, 
				// ���� 3, �� ������ ������ ��������
				// ����� ������ ��������� ��� ���������� �� ���������

				int choise = rand() % 3 + 1;  //rand () �� 1 �� 2

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

	// ������������ ������ �� ������ ������

	TEST_CLASS(Task2_listRingBuffer)
	{
		//  ������ ������ �� ������ ������
		ldRBuff<string> ldRingBuff;

		//�������� ������� �������
		TEST_METHOD(Test1_listRingBuffer_Basic_Function)
		{
			ldRingBuff.Resize(256);

			Assert::IsTrue(ldRingBuff.Length() == 0); //��������� ���-�� ���������
			Assert::IsTrue(ldRingBuff.BufferSize() == 256); //��������� ������ ������
			Assert::IsTrue(ldRingBuff.IsEmpty() == true); //��������� �� �������
			Assert::IsTrue(ldRingBuff.IsFull() == false); //��������� �� �������������
		}
		// ������/������
		TEST_METHOD(Test2_listRingBuffer_ReadWrite)
		{
			ldRingBuff.Resize(50);

			//�������� �������� ������ � ������
			ldRingBuff.Write("Hey");
			Assert::IsTrue(ldRingBuff.Read() == "Hey");

			//���������� 10 ��������
			for (size_t i = 0; i < 10; ++i)
				ldRingBuff.Write("str " + std::to_string(i));

			Assert::IsTrue(ldRingBuff.Length() == 10); //��������� ���-�� ���������
			Assert::IsTrue(ldRingBuff.IsEmpty() == false); //��������� �� �������
			Assert::IsTrue(ldRingBuff.IsFull() == false); //��������� �� �������������

			//���������� 40 ��������
			for (size_t i = 0; i < 40; ++i)
				ldRingBuff.Write("ABC " + std::to_string(i));

			Assert::IsTrue(ldRingBuff.Length() == 50); //��������� ���-�� ���������
			Assert::IsTrue(ldRingBuff.IsEmpty() == false); //��������� �� �������
			Assert::IsTrue(ldRingBuff.IsFull() == true); //��������� �� �������������

			//������� �������� �������� � ����������� �����
			try
			{
				ldRingBuff.Write("BUFFER IS FULL");
				Assert::Fail();
			}
			catch (std::logic_error)
			{
			}

			//������ 25 ��������
			for (size_t i = 0; i < 25; ++i)
				ldRingBuff.Read();

			Assert::IsTrue(ldRingBuff.Length() == 25); //��������� ���-�� ���������
			Assert::IsTrue(ldRingBuff.IsEmpty() == false); //��������� �� �������
			Assert::IsTrue(ldRingBuff.IsFull() == false); //��������� �� �������������

			//������ ����������
			while (!ldRingBuff.IsEmpty())
				ldRingBuff.Read();

			Assert::IsTrue(ldRingBuff.Length() == 0); //��������� ���-�� ���������
			Assert::IsTrue(ldRingBuff.IsEmpty() == true); //��������� �� �������
			Assert::IsTrue(ldRingBuff.IsFull() == false); //��������� �� �������������

			//������� ��������� �������� �� ������� ������
			try
			{
				ldRingBuff.Read();
				Assert::Fail();
			}
			catch (std::logic_error)
			{
			}
		}

		//��������� �������� ������
		TEST_METHOD(Test3_listRingBuffer_RealWorks)
		{
			ldRingBuff.Resize(123);

			srand(time(NULL));

			for (size_t times = 1; times <= 100; ++times)
			{
				// �������� ���������� ����� �� 1 �� 3
				// ���� 1 - ���������� ��������, ���� 2, �� ��������, 
				// ���� 3, �� ������ ������ ��������
				// ����� ������ ��������� ��� ���������� �� ���������

				int choise = rand() % 3 + 1;  //rand () �� 1 �� 2

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
