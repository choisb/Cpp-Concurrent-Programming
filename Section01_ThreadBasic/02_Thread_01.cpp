#include <iostream>
#include <chrono> // chrono �ð� ���
#include <thread> // thread ���
using namespace std::literals; 

void foo()
{
	for (int i = 0; i < 10; i++)
	{
		std::cout << "foo: " << i << std::endl;
		std::this_thread::sleep_for(100ms);
	}
}

int main()
{
	std::thread t(foo);

	t.join(); // t �����尡 ����ɶ����� ���
	//t.detach(); // t �����带 ���� ����. (������ ������� ���������� ����. ���� �����尡 ����Ǹ� t �����嵵 ���������)
	std::cout << "end" << std::endl;

	return 0;
}