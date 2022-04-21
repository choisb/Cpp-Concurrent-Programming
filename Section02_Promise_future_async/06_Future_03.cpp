// promise - future를 사용할 때 유의점
// promise 에서 에서 set_value는 한번만 사용할 수 있다.
// promise 에서 future는 한번만 꺼낼 수 있다.
// future 에서 get()은 한번만 사용할 수 있다.


#include <iostream>
#include <thread>
#include <future>
#include <chrono>
using namespace std::literals;

void add(std::promise<int>&& pm, int a, int b)
{
	std::this_thread::sleep_for(1s);
	pm.set_value(a + b);
	//pm.set_value(a + b + 1);
}
int main()
{
	std::promise<int> pm;
	std::future<int> ft = pm.get_future();
	// std::future<int> ft2 = pm.get_future(); //promise에서 future는 한번만 꺼낼 수 있다. 여러개의 future가 필요하다면 shared_future 사용하자.
	std::thread t(add, std::move(pm), 10, 20);

	std::cout << ft.valid() << std::endl;	//future에서 값을 꺼내기 전이기 때문에 ft는 유효함
	ft.get();
	std::cout << ft.valid() << std::endl;	//future에서 값을 한번 꺼냈기 때문에 ft는 유효하지 않음
	t.join();
	return 0;
}
