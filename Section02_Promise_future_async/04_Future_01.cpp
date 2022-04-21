// std::future 멤버함수
// get(): 결과값 꺼내기
// wait(): 결과값이 준비될 때 까지 대기
// wait_for(): 주어진 시간 만큼 대기
// wait_until(): 주어진 시간 까지 대기
// share(): share_future 얻기
// valid(): 유효성 확인

#include <iostream>
#include <thread>
#include <future>
#include <chrono>
using namespace std::literals;

void add(std::promise<int>&& pm, int a, int b)
{
	std::this_thread::sleep_for(3s);
	pm.set_value(a + b);
}
int main()
{
	std::promise<int> pm;
	std::future<int> ft = pm.get_future();

	std::thread t(add, std::move(pm), 10, 20);

	//int n1 = ft.get();
	std::future_status ret = ft.wait_for(2s);

	if (ret == std::future_status::ready)	// 결과 값이 준비됨
		std::cout << "ready !" << std::endl;
	else if (ret == std::future_status::timeout) // 시간 초과
		std::cout << "timeout !" << std::endl;
	else										// 연산을 수행할 함수가 아직 시작하지 않음. async()에서 사용됨.
		std::cout << "deferred !" << std::endl;

	t.join();

	return 0;
}