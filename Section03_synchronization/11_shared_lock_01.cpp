// shared mutex를 lock 객체로 관리하기 위해서 shared_lock을 사용할 수 있다.

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
		{
			std::lock_guard<std::shared_mutex> lg(m);
			share_data++;
			std::cout << "Writer: " << share_data << std::endl;
			std::this_thread::sleep_for(1s);
		}
		std::this_thread::sleep_for(20ms);
	}
}

void Reader(std::string name)
{
	while (1)
	{
		{
			std::shared_lock<std::shared_mutex> lg(m);
			std::cout << "Reader " << name << ": " << share_data << std::endl;
			std::this_thread::sleep_for(500ms);
		}
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