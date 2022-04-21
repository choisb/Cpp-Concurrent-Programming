// std::future ����Լ�
// get(): ����� ������
// wait(): ������� �غ�� �� ���� ���
// wait_for(): �־��� �ð� ��ŭ ���
// wait_until(): �־��� �ð� ���� ���
// share(): share_future ���
// valid(): ��ȿ�� Ȯ��

#include <iostream>
#include <thread>
#include <future>
#include <chrono>
using namespace std::literals;

void add(std::promise<int>&& pm, int a, int b)
{
	std::this_thread::sleep_for(3s);
	pm.set_value(a + b);
}
int main()
{
	std::promise<int> pm;
	std::future<int> ft = pm.get_future();

	std::thread t(add, std::move(pm), 10, 20);

	//int n1 = ft.get();
	std::future_status ret = ft.wait_for(2s);

	if (ret == std::future_status::ready)	// ��� ���� �غ��
		std::cout << "ready !" << std::endl;
	else if (ret == std::future_status::timeout) // �ð� �ʰ�
		std::cout << "timeout !" << std::endl;
	else										// ������ ������ �Լ��� ���� �������� ����. async()���� ����.
		std::cout << "deferred !" << std::endl;

	t.join();

	return 0;
}