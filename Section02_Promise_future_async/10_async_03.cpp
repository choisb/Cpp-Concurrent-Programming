// async�� ��ȯ�� future�� �Ҹ��ڿ��� get�� ȣ���Ѵ�.
// ���� async�� ��ȯ���� �ʴ´ٸ�, ������ �ӽð�ü�� �Ҹ�ɶ�(���� ����) get�� ȣ���ϱ� ������ �񵿱�� ������� ����. �ݵ�� ��ȯ������!!
#include <iostream>
#include <thread>
#include <chrono>
#include <future>
using namespace std::literals;

int add(int a, int b)
{
	std::cout << "Start add" << std::endl;
	std::this_thread::sleep_for(2s);
	std::cout << "Finish add" << std::endl;

	return a + b;
}
int main()
{
	std::future<int> ft = std::async(add, 10, 20);	// future�� �Ҹ��ڿ��� get�� ����. ���� �ڵ忡�� get�� �����ϴ��� ���������� ft�� �Ҹ�ɶ� ����ϰԵ�
	//std::async(add, 10, 20); // ���� ��ȯ�� future�� ���� �ʴ´ٸ� �ӽð�ü�� �Ҹ�ɶ� get�� ȣ��Ǳ� ������ �񵿱� ������ �ȵ�. �ݵ�� ��ȯ ������!!!!!!!!
	std::this_thread::sleep_for(1s);
	std::cout << "Continue main" << std::endl;
//	int ret = ft.get();

	return 0;
}


