// 스레드의 멤버함수를 살펴봄. 스레드의 멤버함수 종류는 다음과 같다.
// hardware_concurrency() : 하드웨어의 개수 반환 (static)
// get_id(): 스레드의 ID 반환
// native_handle(): OS의 스레드 핸들 반환
// swap(): 스레드 object swap
// joinable(): 스레드가 join 될 수 있는지 조사
// join(): 스레드 종료 대기
// detach(): 스레드 떼어 내기

#include <iostream>
#include <thread>

int main()
{
	std::thread t;
	// t.join(); //실행되지 않은 스레드를 join할 경우 예외 발생

	// 필요할 경우 join이 가능한지 확인 후 join하는 것이 바람직함.
	if (t.joinable())
	{
		t.join();
	}
	return 0;
}
