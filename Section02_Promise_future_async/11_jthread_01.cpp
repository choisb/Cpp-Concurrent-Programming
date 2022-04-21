// jthread(C++20 ����)�� thread�� ���� �ΰ��� ����� �߰���
//	- joining thread: �Ҹ��ڿ��� join �Լ� ȣ��. ������ join�� ȣ�� �� �ʿ䰡 ����.
//  - Cooperatively interruptible: �������� ���ͷ�Ʈ. �� �����忡�� �Ļ� ������� ���ͷ�Ʈ�� �� �� �ִ�.

#include <chrono>
#include <iostream>
#include <thread>
using namespace std::literals;

void foo()
{	// stop_token�� ���� ������ ���� ��ų ����� ����.
	for (int i = 0; i < 10; i++)
	{
		std::this_thread::sleep_for(500ms);
		std::cout << "foo: " << i << std::endl;
	}
}

void goo(std::stop_token token)
{
	for (int i = 0; i < 10; i++)
	{
		if (token.stop_requested())	// stop_token�� Ȱ���ؼ� ���� �����忡�� stop�� ��û�ߴ��� Ȯ��
		{
			std::cout << "Stop goo" << std::endl;
			return;
		}
		std::this_thread::sleep_for(500ms);
		std::cout << "goo: " << i << std::endl;
	}
}

int main()
{
	std::jthread j1(foo);
	std::jthread j2(goo);
	std::this_thread::sleep_for(2s);

	j1.request_stop();	// jthread���� �߰��� �Լ�. stop_token���� stop�� ��û��
	j2.request_stop();	
}