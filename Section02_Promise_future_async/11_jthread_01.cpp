// jthread(C++20 부터)는 thread에 다음 두가지 기능이 추가됨
//	- joining thread: 소멸자에서 join 함수 호출. 별도로 join을 호출 할 필요가 없다.
//  - Cooperatively interruptible: 협력적인 인터럽트. 주 스레드에서 파생 스레드로 인터럽트를 걸 수 있다.

#include <chrono>
#include <iostream>
#include <thread>
using namespace std::literals;

void foo()
{	// stop_token이 없기 때문에 중지 시킬 방법은 없다.
	for (int i = 0; i < 10; i++)
	{
		std::this_thread::sleep_for(500ms);
		std::cout << "foo: " << i << std::endl;
	}
}

void goo(std::stop_token token)
{
	for (int i = 0; i < 10; i++)
	{
		if (token.stop_requested())	// stop_token을 활용해서 메인 스레드에서 stop을 요청했는지 확인
		{
			std::cout << "Stop goo" << std::endl;
			return;
		}
		std::this_thread::sleep_for(500ms);
		std::cout << "goo: " << i << std::endl;
	}
}

int main()
{
	std::jthread j1(foo);
	std::jthread j2(goo);
	std::this_thread::sleep_for(2s);

	j1.request_stop();	// jthread에서 추가된 함수. stop_token으로 stop을 요청함
	j2.request_stop();	
}