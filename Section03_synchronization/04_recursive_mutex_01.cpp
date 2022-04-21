/*
std::mutex 는 락을 한번만 소유할 수 있다.
std::recursive_mutex 는 하나의 스레드가 "여러번" 뮤텍스를 소유 가능.
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
		f1();		// 멤버함수들 간에 상호호출할때 많이 recursive_mutex를 활용할 수 있다.
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