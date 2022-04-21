// promise - future�� ����� �� ������
// promise ���� ���� set_value�� �ѹ��� ����� �� �ִ�.
// promise ���� future�� �ѹ��� ���� �� �ִ�.
// future ���� get()�� �ѹ��� ����� �� �ִ�.


#include <iostream>
#include <thread>
#include <future>
#include <chrono>
using namespace std::literals;

void add(std::promise<int>&& pm, int a, int b)
{
	std::this_thread::sleep_for(1s);
	pm.set_value(a + b);
	//pm.set_value(a + b + 1);
}
int main()
{
	std::promise<int> pm;
	std::future<int> ft = pm.get_future();
	// std::future<int> ft2 = pm.get_future(); //promise���� future�� �ѹ��� ���� �� �ִ�. �������� future�� �ʿ��ϴٸ� shared_future �������.
	std::thread t(add, std::move(pm), 10, 20);

	std::cout << ft.valid() << std::endl;	//future���� ���� ������ ���̱� ������ ft�� ��ȿ��
	ft.get();
	std::cout << ft.valid() << std::endl;	//future���� ���� �ѹ� ���±� ������ ft�� ��ȿ���� ����
	t.join();
	return 0;
}
