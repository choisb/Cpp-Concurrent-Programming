// std::future �� ���� �ȵ�. ���� �̵����길 ����
// std::shared_future �� ���簡 ����

#include <iostream>
#include <thread>
#include <future>
#include <chrono>
using namespace std::literals;

void add(std::promise<int>&& pm, int a, int b)
{
	std::this_thread::sleep_for(1s);
	pm.set_value(a + b);
}
void consume(std::shared_future<int> sf)
{
	sf.get();
	std::cout << "finish foo" << std::endl;
}
int main()
{
	std::promise<int> pm;
	std::future<int> ft = pm.get_future();
	// std::future<int> ft2 = ft; // error: future�� ���� �Ұ���!

	//std::shared_future<int> sft = pm.get_future(); // promise���� �ٷ� shared_future�� ���� ���� �ִ�.
	std::shared_future<int> sft = ft.share();

	std::thread t(add, std::move(pm), 10, 20);

	std::thread t1(consume, sft); // t1�� consume �Լ��� �����Ű�� shared_future sft�� ������ ����(���簡��)
	std::thread t2(consume, sft); // t2�� consume �Լ��� �����Ű�� ���������� sft�� ������ ����(���� ����)

	t.join();
	t1.join();
	t2.join();
	return 0;
}
