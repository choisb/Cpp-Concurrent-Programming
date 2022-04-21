#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std::literals;

std::timed_mutex tm;

int main()
{
	std::unique_lock<std::timed_mutex> u1;
	std::unique_lock<std::timed_mutex> u2(tm);

	//u1 = u2; // 복사 불가
	u1 = std::move(u2); // 이동 연산 가능

	std::cout << u1.owns_lock() << std::endl;	// 1

	if (u1)	// u1이 lock을 소유했다면 true
		std::cout << "acquire" << std::endl;

	u1.unlock();
	std::cout << u1.owns_lock() << std::endl;	// 0

	if (u1.try_lock_for(2s)) // 성공시 true 반환
	{
		// ...
		u1.unlock();
	}
	
	u1.release(); // 소유한 mutex와 연결 해제



	return 0;
}