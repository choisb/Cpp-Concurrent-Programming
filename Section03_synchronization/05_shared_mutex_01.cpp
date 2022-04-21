
// �ϳ��� �����尡 �б� �۾��� �ϴµ��� �ٸ� �����尡 �б��۾��� �ϴ��� �����ϴ�.
// �̷� ��� shared_mutex ���

#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <shared_mutex> // shared_mutex�� ���� ���
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