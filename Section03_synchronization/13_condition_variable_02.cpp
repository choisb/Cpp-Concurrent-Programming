// condition variable의 조건자를 활용하면 두개의 스레드가 서로 신호를 주고받을 수도 있다.

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <condition_variable>

using namespace std::literals;

std::mutex m;
std::condition_variable cv;
int shared_data = 0;

bool data_ready = false;
bool data_process = false;

void consumer()
{
	std::unique_lock<std::mutex> ul(m);
	cv.wait(ul, [] {return data_ready; }); // 내부적으로 unlock을 한 뒤 신호가 올때 까지 대기. 신호가 오면 다시 lock을 걸고 계속 진행
	std::cout << "consumer : " << shared_data << std::endl;
	data_process = true;
	ul.unlock();
	cv.notify_one();
}

void producer()
{
	
	std::unique_lock<std::mutex> ul(m);
	shared_data = 10;
	std::cout << "producer : " << shared_data << std::endl;
	
	data_ready = true;
	cv.notify_one();	// consumer쪽으로 신호를 보낸다.
	cv.wait(ul, [] {return data_process; });
	std::cout << "producer : data processed!" << std::endl;
}
int main()
{
	std::thread t1(producer);
	std::thread t2(consumer);
	t1.join();
	t2.join();
	return 0;
}