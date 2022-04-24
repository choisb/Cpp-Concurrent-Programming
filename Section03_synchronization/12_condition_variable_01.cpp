/*
���� �����带 ���ÿ� lock�� ȹ���ϱ� ���ؼ� �����ϰ� �ȴٸ� � �����尡 ���� lock�� ȹ���ϰ� ���� �� �� ����.
�׷���, ��Ȳ�� ���󼭴� ������ �����尡 ���� ���� ȹ���ؾ� �ϴ� ��찡 ���� �� �ִ�.
���� ��� �Ʒ��� ���� �����͸� �����ϴ� producer �����尡 �ְ� �̸� �Һ��ϴ� consumer �����尡 �ִٰ� ����.
�׸��� consumer ������� �ݵ�� producer �����尡 ���� �����ϰ� �� �ڿ� �����ؾ��Ѵٰ� ��������.

�̷� ������ �����Ҷ� Ȱ���� �� �ִ� ����� condition variable�̴�.

condition variable�� Ư¡�� ������ ����.
- condition variable�� ��ȣ ����� ����ȭ �����̴�.
- <condition_variable> ����� �ʿ��ϴ�.
- �ݵ�� unique_lock�� ����ؾ� �Ѵ�. (lock_guard ��� �Ұ�)

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
// �Һ��� �ڵ忡�� wait�Լ��� ���� ���� ���� ������ �ڵ忡�� notify_one()�� ȣ���ϴ� ��Ȳ�� �߻��� �� �ִ�.
// �׷��� �Ǹ� ���� ���� ��ȣ�� �Һ��ڴ� ��� ��ٸ��鼭 ������� ������ �ȴ�.
// �̷���� �����ڸ� ���ؼ� �����Ͱ� �غ�Ǿ����� Ȯ���ϴ� ������� ������ �ذ��� �� �ִ�.
bool data_ready = false;

void consumer()
{
	//std::lock_guard<std::mutex> lg(m); // condition variable�� �ݵ�� unique_lock�� ����ؾ���.
	std::unique_lock<std::mutex> ul(m);
	cv.wait(ul, [] {return data_ready; }); // ���������� unlock�� �� �� ��ȣ�� �ö� ���� ���. ��ȣ�� ���� �ٽ� lock�� �ɰ� ��� ����
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
	cv.notify_one();	// consumer������ ��ȣ�� ������.
}
int main()
{
	std::thread t1(producer);
	std::thread t2(consumer);
	t1.join();
	t2.join();
	return 0;
}