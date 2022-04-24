// condition variable�� �����ڸ� Ȱ���ϸ� �ΰ��� �����尡 ���� ��ȣ�� �ְ���� ���� �ִ�.

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
	cv.wait(ul, [] {return data_ready; }); // ���������� unlock�� �� �� ��ȣ�� �ö� ���� ���. ��ȣ�� ���� �ٽ� lock�� �ɰ� ��� ����
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
	cv.notify_one();	// consumer������ ��ȣ�� ������.
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