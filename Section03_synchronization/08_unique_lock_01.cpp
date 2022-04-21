/*
lock guard는 lock / unlock을 관리하는 최소한의 기능만 제공
좀더 다양한 방법으로 뮤텍스 관리를 위해서 unique_lock 사용

lock guard는 최대한 단순한 형태로만들어 오버헤드를 줄인 설계
unique lock은 최대한 다양한 기능을 제공해주기 위한 설계
*/

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std::literals;

std::mutex m1, m2, m3;
std::timed_mutex tm1, tm2, tm3;

int main()
{
	std::unique_lock<std::mutex> u1;	// mutex를 받지 않고 unique lock만 생성
	std::unique_lock<std::mutex> u2(m1); // lock guard 처럼 mutex를 받고 lock 획득

	std::unique_lock<std::mutex> u3(m2, std::try_to_lock); // mutex를 받고 lock이 아닌 try lock 시도.
	if (u3.owns_lock())
		std::cout << "acquire lock" << std::endl;
	else
		std::cout << "fail to lock" << std::endl;

	m3.lock();
	std::unique_lock<std::mutex> u4(m3, std::adopt_lock); // 이미 lock을 획득한 뮤텍스 관리

	std::unique_lock<std::timed_mutex> u5(tm1, std::defer_lock); // 나중에 lock을 호출
	auto ret = u5.try_lock_for(2s);

	std::unique_lock<std::timed_mutex> u6(tm2, 2s); // tm2.try_lock_for() 사용
	std::unique_lock<std::timed_mutex> u7(tm3, std::chrono::steady_clock::now() + 2s); // tm3.try_lock_until() 과 동일

	return 0;
}
