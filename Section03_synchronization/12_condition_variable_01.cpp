/*
여러 스레드를 동시에 lock을 획득하기 위해서 경쟁하게 된다면 어떤 스레드가 먼저 lock을 획득하게 될지 알 수 없다.
그런데, 상황에 따라서는 임의의 스레드가 먼저 락을 획득해야 하는 경우가 있을 수 있다.
예를 들어 아래와 같이 데이터를 생성하는 producer 스레드가 있고 이를 소비하는 consumer 스레드가 있다고 하자.
그리고 consumer 스레드는 반드시 producer 스레드가 값을 생성하고 난 뒤에 접근해야한다고 가정하자.

이런 조건을 구현할때 활용할 수 있는 기능이 condition variable이다.

condition variable의 특징은 다음과 같다.
- condition variable은 신호 기반의 동기화 도구이다.
- <condition_variable> 헤더가 필요하다.
- 반드시 unique_lock을 사용해야 한다. (lock_guard 사용 불가)

*/
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <condition_variable>

using namespace std::literals;

std::mutex m;
std::condition_variable cv;
int shared_data = 0;
// 소비자 코드에서 wait함수가 들어가기 전에 먼저 생산자 코드에서 notify_one()을 호출하는 상황이 발생할 수 있다.
// 그렇게 되면 오지 않을 신호를 소비자는 계속 기다리면서 데드락에 빠지게 된다.
// 이런경우 조건자를 통해서 데이터가 준비되었는지 확인하는 방식으로 문제를 해결할 수 있다.
bool data_ready = false;

void consumer()
{
	//std::lock_guard<std::mutex> lg(m); // condition variable은 반드시 unique_lock을 사용해야함.
	std::unique_lock<std::mutex> ul(m);
	cv.wait(ul, [] {return data_ready; }); // 내부적으로 unlock을 한 뒤 신호가 올때 까지 대기. 신호가 오면 다시 lock을 걸고 계속 진행
	std::cout << "consumer : " << shared_data << std::endl;
}

void producer()
{
	{
		std::lock_guard<std::mutex> lg(m);
		shared_data = 10;
		std::cout << "producer : " << shared_data << std::endl;
	}
	data_ready = true;
	cv.notify_one();	// consumer쪽으로 신호를 보낸다.
}
int main()
{
	std::thread t1(producer);
	std::thread t2(consumer);
	t1.join();
	t2.join();
	return 0;
}