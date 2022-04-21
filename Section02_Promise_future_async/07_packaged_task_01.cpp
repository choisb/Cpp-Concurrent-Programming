//��Ƽ �����带 ������� �ʰ� �ۼ��� �Լ��� �񵿱�(������)�� �����Ű�� ���
#include <iostream>
#include <thread>
#include <future>

// ��Ƽ �����带 ������� �ʰ� �ۼ��� �Լ�
int add(int a, int b)
{
	std::cout << "add" << std::endl;
	return a + b;
}
int main()
{
	std::packaged_task<int(int, int)> task(add);
	std::future<int> ft = task.get_future();

	std::thread t(std::move(task), 10, 20);
	std::cout << "continue main" << std::endl;

	int ret = ft.get();
	std::cout << ret << std::endl;
	t.join();
	return 0;
}