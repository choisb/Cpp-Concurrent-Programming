// ���̽� ����� ������ �����غ������� ����. Ƽ�� ���� �ȳ�.

#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <mutex>
using namespace std::literals;

std::mutex m;
void delay() { std::this_thread::sleep_for(1ms); }
void foo(std::string name)
{
	//int x = 0; // ���������� ������
	static int x = 0; // ���� ������ �����忡�� �������� ����.

	for (int i = 0; i < 50; ++i)
	{
		m.lock();	// �Ӱ迵���� �� �ɱ�
		x = 100; delay();
		x = x + 1; delay();
		std::cout << name << " : " << x << std::endl; delay();
		m.unlock(); // �� Ǯ��
	}
}

int main()
{
	std::thread t1(foo, " A");
	std::thread t2(foo, " B");
	t1.join();
	t2.join();
	return 0;
}