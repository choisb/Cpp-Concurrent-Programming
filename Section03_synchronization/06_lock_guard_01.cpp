/*
����ڰ� ���� lock�� unlock�� ����ϰԵ� ��� ���� �ΰ��� ������ �߻��� �� �ִ�.
- �Ǽ��� unlock�� ���� �ʴ� ���. 
- ���� �߻����� unlock ����� ������� �ʴ� ���.

�̷� ������ RAII ������� ������ lock guard�� ����ؼ� �ذ��� �� �ִ�.
*/
#include <iostream>
#include <thread>
#include <mutex>
#include <exception>

std::mutex m;
int share_data = 0;

// lock guard ������� �ʴ°��
//void goo()
//{
//	m.lock();
//	share_data = 100;
//	std::cout << "using data" << std::endl;
//	throw std::exception();	// ���ܹ߻����� m.unlock() ȣ���� �ȵ�.
//	m.unlock();
//}

// lock guard ���
void goo()
{
	std::lock_guard<std::mutex> lg(m);	// RAII ���
	share_data = 100;
	std::cout << "using data" << std::endl;
	throw std::exception(); // ���ܰ� �߻��ϴ��� stack unwinding ���� ���ؼ� lg�� �Ҹ��ڴ� �����ϰ� ȣ���
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

