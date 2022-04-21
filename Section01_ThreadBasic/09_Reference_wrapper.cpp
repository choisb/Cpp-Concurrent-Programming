// 03_Thread_02.cpp �������� ����� std::ref() �� ������ �����ϱ� ���� ��Ʈ

#include <iostream>
#include <functional>

namespace my
{
	template<typename T>struct reference_wrapper 
	{
		T* obj;
	public:
		reference_wrapper(T& t) : obj(&t) {}
		operator T& () { return *obj; }	// ���� ��ȯ ������.
	};

	// reference_wrapper ��ü�� ���� ��ȯ�ϴ� �Լ�
	template<typename T> reference_wrapper<T> ref(T& obj)	
	{
		return reference_wrapper<T>(obj);
	}
}

void foo(int& a) { a = 200; }
template<typename T> void call_foo(T arg)
{
	foo(arg);
}

int main()
{
	int n1 = 0;
	int n2 = 0;
	int n3 = 0;
	int n4 = 0;
	int n5 = 0;

	foo(n1);				// ���� ����
	call_foo(n2);			// �� ����
	call_foo(std::ref(n3));	// ���� ����
	call_foo(my::reference_wrapper(n4));	// ���� ����
	call_foo(my::ref(n5));					// ���� ����

	std::cout << n1 << std::endl;	// 200
	std::cout << n2 << std::endl;	// 0
	std::cout << n3 << std::endl;	// 200
	std::cout << n4 << std::endl;
	std::cout << n5 << std::endl;

	return 0;
}