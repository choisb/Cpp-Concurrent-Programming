#include <iostream>
#include <future>
#include <thread>
#include <chrono>
using namespace std::literals;

void add(std::promise<int>&& p, int a, int b)
{
	int s = a + b;
	std::this_thread::sleep_for(1s);
	//p.set_value(s); // ��� ���� ����
	p.set_value_at_thread_exit(s); // �����尡 ����� �� ���� ���� 
	std::cout << "add" << std::endl;
	std::this_thread::sleep_for(1s);
}
int main()
{
	std::promise<int> pm;
	std::future<int> ft = pm.get_future(); // pm�� future�� ������.

	std::thread t(add, std::move(pm), 10, 20);

	int ret = ft.get(); // promise ��ü�� ���� ������ �� ���� block
	std::cout << ret << std::endl;
	t.join();

	return 0;
}