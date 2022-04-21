// std::future 는 복사 안됨. 오직 이동연산만 가능
// std::shared_future 는 복사가 가능

#include <iostream>
#include <thread>
#include <future>
#include <chrono>
using namespace std::literals;

void add(std::promise<int>&& pm, int a, int b)
{
	std::this_thread::sleep_for(1s);
	pm.set_value(a + b);
}
void consume(std::shared_future<int> sf)
{
	sf.get();
	std::cout << "finish foo" << std::endl;
}
int main()
{
	std::promise<int> pm;
	std::future<int> ft = pm.get_future();
	// std::future<int> ft2 = ft; // error: future는 복사 불가능!

	//std::shared_future<int> sft = pm.get_future(); // promise에서 바로 shared_future를 꺼낼 수도 있다.
	std::shared_future<int> sft = ft.share();

	std::thread t(add, std::move(pm), 10, 20);

	std::thread t1(consume, sft); // t1에 consume 함수를 실행시키고 shared_future sft를 값으로 전달(복사가능)
	std::thread t2(consume, sft); // t2에 consume 함수를 실행시키고 마찬가지로 sft를 값으로 전달(복사 가능)

	t.join();
	t1.join();
	t2.join();
	return 0;
}
