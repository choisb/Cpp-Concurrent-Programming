/*
timed_mutex의 멤버함수 리스트
- lock()	: mutex를 잠군다. 만약 mutex가 사용가능하지 않은 상태라면 block 후 대기
- try_lock(): mutex의 lock을 시도한다. 만약 사용가능하지 않은 상태라면 block하지 않고 false 반환. 사용가능하다면 lock 획득
- unlock()	: 잠군 lock을 반환한다.
- native_handle(): 로우레벨(운영체제)의 mutex 핸들을 반환한다.

- try_lock_for(): 일정 시간 동안 lock 획득 시도
- try_lock_until(): ~시간 까지 lock 획득 시도

mutex의 멤버 타입
- native_handle_type: native_handle()의 반환 타입

mutex는 복사와 이동연산 안됨
*/
#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <mutex>
using namespace std::literals;

std::timed_mutex m;
int share_data = 0;
void foo()
{
	if (m.try_lock_for(2s))
	{
		share_data = 10;
		std::cout << "using share_data" << std::endl;
		std::this_thread::sleep_for(3s);
		m.unlock();
	}
	else
	{
		std::cout << "뮤텍스 획득 실패" << std::endl;
	}
}

int main()
{
	std::thread t1(foo);
	//std::this_thread::sleep_for(20ms);
	std::thread t2(foo);
	t1.join();
	t2.join();


	return 0;
}
