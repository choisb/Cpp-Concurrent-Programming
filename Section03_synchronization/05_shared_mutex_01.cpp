
// 하나의 스레드가 읽기 작업을 하는동안 다른 스레드가 읽기작업을 하더라도 안전하다.
// 이런 경우 shared_mutex 사용

#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <shared_mutex> // shared_mutex를 위한 헤더
using namespace std::literals;

std::shared_mutex m;
int share_data = 0;

void Writer()
{
	while (1)
	{
		m.lock();
		share_data++;
		std::cout << "Writer: " << share_data << std::endl;
		std::this_thread::sleep_for(1s);
		m.unlock();
		std::this_thread::sleep_for(20ms);
	}
}

void Reader(std::string name)
{
	while (1)
	{
		m.lock_shared();
		std::cout << "Reader " << name << ": " << share_data << std::endl;
		std::this_thread::sleep_for(200ms);
		m.unlock_shared();
		std::this_thread::sleep_for(20ms);
	}
}

int main()
{
	std::thread t1(Writer);
	std::thread t2(Reader, "A");
	std::thread t3(Reader, "B");
	std::thread t4(Reader, "C");

	t1.join();
	t2.join();
	t3.join();
	t4.join();

	return 0;
}