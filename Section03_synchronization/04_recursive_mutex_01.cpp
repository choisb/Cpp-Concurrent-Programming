/*
std::mutex �� ���� �ѹ��� ������ �� �ִ�.
std::recursive_mutex �� �ϳ��� �����尡 "������" ���ؽ��� ���� ����.
*/

#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
using namespace std::literals;

class Machine
{
	std::recursive_mutex m;
	int share_data = 0;
public:
	void f1()
	{
		m.lock();
		share_data = 100;
		m.unlock();
	}
	void f2()
	{
		m.lock();
		share_data = 200;
		f1();		// ����Լ��� ���� ��ȣȣ���Ҷ� ���� recursive_mutex�� Ȱ���� �� �ִ�.
		m.unlock();
	}
};

int main()
{
	Machine m;
	std::thread t1(&Machine::f1, &m);
	std::thread t2(&Machine::f2, &m);

	t1.join();
	t2.join();

	return 0;
}