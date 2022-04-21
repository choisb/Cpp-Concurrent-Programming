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

void foo() {}
void goo() {}
int main()
{
	std::thread t1(&foo);
	std::thread t2(&goo);

	t1.swap(t2);
	// std::thread t3 = t1; // error 스레드는 복사할 수 없다.
	std::thread t4 = std::move(t1);

	// t1.join(); // 예외 발생. t1 스레드의 내용을 t4에 이동했기 때문에 join 할 수 없다.
	t2.join();
	t4.join();

	
	return 0;
}
