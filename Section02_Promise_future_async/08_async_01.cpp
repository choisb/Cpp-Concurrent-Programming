// 함수를 비동기로 실행하는 3가지 방법
// std::thread	직접 스레드 생성
// std::jthread (C++20부터)
// std::async	함수 템플릿 사용

//std::async
// - 주어진 함수를 비동기로 수행하는 함수 템플릿
// - 기존에 작성한 함수를 간단하게 비동기로 실행할 수 있다.
// - 일반적으로 스레드 풀을 활용하기 때문에 직접 스레드를 관리하는 것 보다 더 효율적
// - std::future를 반환

#include <iostream>
#include <thread>
#include <chrono>
#include <future>
using namespace std::literals;

int add(int a, int b)
{
	std::this_thread::sleep_for(2s);
	return a + b;
}
int main()
{
	// add(10, 20); // 동기 호출
	std::future<int> ft = std::async(add, 10, 20); // 비동기 호출, future를 반환함
	std::cout << "continue main" << std::endl;
	int ret = ft.get();
	std::cout << "result : " << ret << std::endl;

	return 0;
}


