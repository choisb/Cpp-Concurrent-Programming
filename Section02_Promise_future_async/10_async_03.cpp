// async의 반환값 future는 소멸자에서 get을 호출한다.
// 만약 async를 반환받지 않는다면, 생성된 임시객체가 소멸될때(같은 라인) get을 호출하기 때문에 비동기로 실행되지 않음. 반드시 반환받을것!!
#include <iostream>
#include <thread>
#include <chrono>
#include <future>
using namespace std::literals;

int add(int a, int b)
{
	std::cout << "Start add" << std::endl;
	std::this_thread::sleep_for(2s);
	std::cout << "Finish add" << std::endl;

	return a + b;
}
int main()
{
	std::future<int> ft = std::async(add, 10, 20);	// future의 소멸자에는 get이 있음. 만약 코드에서 get을 생략하더라도 지역변수인 ft가 소멸될때 대기하게됨
	//std::async(add, 10, 20); // 만약 반환값 future를 받지 않는다면 임시객체가 소멸될때 get이 호출되기 때문에 비동기 실행이 안됨. 반드시 반환 받을것!!!!!!!!
	std::this_thread::sleep_for(1s);
	std::cout << "Continue main" << std::endl;
//	int ret = ft.get();

	return 0;
}


