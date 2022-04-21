#include <iostream>
#include <chrono> // chrono 시간 사용
#include <thread> // thread 사용
using namespace std::literals; 

void foo()
{
	for (int i = 0; i < 10; i++)
	{
		std::cout << "foo: " << i << std::endl;
		std::this_thread::sleep_for(100ms);
	}
}

int main()
{
	std::thread t(foo);

	t.join(); // t 스레드가 종료될때까지 대기
	//t.detach(); // t 스레드를 떼어 낸다. (생성된 스레드는 독립적으로 실행. 메인 스레드가 종료되면 t 스레드도 강제종료됨)
	std::cout << "end" << std::endl;

	return 0;
}