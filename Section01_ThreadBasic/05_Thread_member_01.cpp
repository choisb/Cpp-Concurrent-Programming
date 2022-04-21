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
#include <string>
using namespace std::literals;

void foo() 
{
	std::cout << std::this_thread::get_id() << std::endl;
}
int main()
{
	int n = std::thread::hardware_concurrency(); // 하드웨어에서 지원하는 스레드의 개수를 반환
	std::cout << n << std::endl;

	std::thread t(&foo);
	std::this_thread::sleep_for(1s);

	std::thread::id tid = t.get_id();	// thread id 반환
	std::cout << "created thread id: " << tid << std::endl;
	t.join();

	return 0;
}
