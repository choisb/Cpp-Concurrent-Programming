#include <iostream>
#include <future>
#include <thread>
#include <chrono>
using namespace std::literals;

void add(std::promise<int>&& p, int a, int b)
{
	int s = a + b;
	std::this_thread::sleep_for(1s);
	//p.set_value(s); // 즉시 값을 설정
	p.set_value_at_thread_exit(s); // 스레드가 종료될 때 값을 설정 
	std::cout << "add" << std::endl;
	std::this_thread::sleep_for(1s);
}
int main()
{
	std::promise<int> pm;
	std::future<int> ft = pm.get_future(); // pm의 future를 꺼낸다.

	std::thread t(add, std::move(pm), 10, 20);

	int ret = ft.get(); // promise 객체에 값이 설정될 때 까지 block
	std::cout << ret << std::endl;
	t.join();

	return 0;
}