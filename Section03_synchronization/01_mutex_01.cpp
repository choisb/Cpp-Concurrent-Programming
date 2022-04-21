// 레이스 컨디션 예제로 적당해보이지는 않음. 티가 많이 안남.

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
	//int x = 0; // 지역변수는 안전함
	static int x = 0; // 전역 변수는 스레드에서 안전하지 않음.

	for (int i = 0; i < 50; ++i)
	{
		m.lock();	// 임계영역에 락 걸기
		x = 100; delay();
		x = x + 1; delay();
		std::cout << name << " : " << x << std::endl; delay();
		m.unlock(); // 락 풀기
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