// �Լ��� �񵿱�� �����ϴ� 3���� ���
// std::thread	���� ������ ����
// std::jthread (C++20����)
// std::async	�Լ� ���ø� ���

//std::async
// - �־��� �Լ��� �񵿱�� �����ϴ� �Լ� ���ø�
// - ������ �ۼ��� �Լ��� �����ϰ� �񵿱�� ������ �� �ִ�.
// - �Ϲ������� ������ Ǯ�� Ȱ���ϱ� ������ ���� �����带 �����ϴ� �� ���� �� ȿ����
// - std::future�� ��ȯ

#include <iostream>
#include <thread>
#include <chrono>
#include <future>
using namespace std::literals;

int add(int a, int b)
{
	std::this_thread::sleep_for(2s);
	return a + b;
}
int main()
{
	// add(10, 20); // ���� ȣ��
	std::future<int> ft = std::async(add, 10, 20); // �񵿱� ȣ��, future�� ��ȯ��
	std::cout << "continue main" << std::endl;
	int ret = ft.get();
	std::cout << "result : " << ret << std::endl;

	return 0;
}


