#include <iostream>
#include <chrono>
#include <thread>
using namespace std::literals; // 사용자 정의 시간 타입 사용하기 위함. 1s / 3ms / 10ns 등

int main()
{
	std::chrono::time_point tp1 = std::chrono::system_clock::now();

	std::chrono::hours h = std::chrono::duration_cast<std::chrono::hours>(tp1.time_since_epoch());

	std::cout << h.count() << std::endl;

	std::this_thread::sleep_for(3ms); // 3초 동안 대기
	std::this_thread::sleep_until(std::chrono::system_clock::now() + 3ms); //특정시간(현재시간 + 3ms)이 될때 까지 대기


	return 0;
}