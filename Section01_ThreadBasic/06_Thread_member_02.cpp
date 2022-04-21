// 스레드의 멤버함수를 살펴봄. 스레드의 멤버함수 종류는 다음과 같다.
// hardware_concurrency() : 하드웨어의 개수 반환 (static)
// get_id(): 스레드의 ID 반환
// native_handle(): OS의 스레드 핸들 반환
// swap(): 스레드 object swap
// joinable(): 스레드가 join 될 수 있는지 조사
// join(): 스레드 종료 대기
// detach(): 스레드 떼어 내기


#include <iostream>
#include <chrono> // chrono 시간 사용
#include <thread> // thread 사용
#include <windows.h> // 아직 C++의 표준에 없는 기능들을 다루기 위함. (GetCurrentThread / SetThreadPriority)
#include <string>
using namespace std::literals;

void foo()
{
	auto tid = std::this_thread::get_id(); // 스레드 ID 얻기
	
	auto handle = GetCurrentThread();		// Window os의 스레드 핸들 얻기. (C++ 표준 지원 x)
	std::cout << "변경 전 우선순위: " << GetThreadPriority(handle) << std::endl;
	std::this_thread::sleep_for(200ms);
	std::cout << "변경 후 우선순위: " << GetThreadPriority(handle) << std::endl;
}
int main()
{
	std::thread t(&foo);
	std::thread::native_handle_type h = t.native_handle(); // window os의 스레드 핸들 반환

	std::cout << "ID    : " << t.get_id() << std::endl;
	std::cout << "handle: " << h          << std::endl;

	std::this_thread::sleep_for(100ms);
	SetThreadPriority(h, THREAD_PRIORITY_TIME_CRITICAL); // 스레드의 우선순위 변경. (C++ 표준 지원 x)
	t.join();

	return 0;
}
