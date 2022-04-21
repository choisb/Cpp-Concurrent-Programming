/*
사용자가 직접 lock과 unlock을 사용하게될 경우 다음 두가지 문제가 발생할 수 있다.
- 실수로 unlock을 하지 않는 경우. 
- 예외 발생으로 unlock 명령이 실행되지 않는 경우.

이런 문제를 RAII 방식으로 구현된 lock guard를 사용해서 해결할 수 있다.
*/
#include <iostream>
#include <thread>
#include <mutex>
#include <exception>

std::mutex m;
int share_data = 0;

// lock guard 사용하지 않는경우
//void goo()
//{
//	m.lock();
//	share_data = 100;
//	std::cout << "using data" << std::endl;
//	throw std::exception();	// 예외발생으로 m.unlock() 호출이 안됨.
//	m.unlock();
//}

// lock guard 사용
void goo()
{
	std::lock_guard<std::mutex> lg(m);	// RAII 방식
	share_data = 100;
	std::cout << "using data" << std::endl;
	throw std::exception(); // 예외가 발생하더라도 stack unwinding 으로 인해서 lg의 소멸자는 안전하게 호출됨
}
void foo()
{
	try 
	{
		goo();
	}
	catch (...)
	{
		std::cout << "catch exception!" << std::endl;
	}
}

int main()
{
	std::thread t1(foo);
	std::thread t2(foo);

	t1.join();
	t2.join();
}

