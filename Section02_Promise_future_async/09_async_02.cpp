// async를 호출할때 실행 옵션을 선택할 수 있음.


#include <iostream>
#include <thread>
#include <chrono>
#include <future>
using namespace std::literals;

int add(int a, int b)
{
	std::cout << "add: " << std::this_thread::get_id() << std::endl;
	std::this_thread::sleep_for(2s);
	return a + b;
}
int main()
{
	//std::future<int> ft = std::async(add, 10, 20);						// 바로 새로운 스레드 생성
	//std::future<int> ft = std::async(std::launch::async, add, 10, 20);	// 바로 새로운 스레드 생성
	//std::future<int> ft = std::async(std::launch::deferred, add, 10, 20);	// future가 get 하는 순간 호출한 스레드에서 실행
	std::future<int> ft = std::async(std::launch::async | std::launch::deferred, add, 10, 20);	// 시스템에 따라 다름. PC컴파일러는 일반적으로 바로 새로운 스레드 생성
	std::cout << "continue main: " << std::this_thread::get_id() << std::endl;
	std::this_thread::sleep_for(2s);

	int ret = ft.get();
	std::cout << "result : " << ret << std::endl;

	return 0;
}


