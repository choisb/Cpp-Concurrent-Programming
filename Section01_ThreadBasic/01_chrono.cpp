#include <iostream>
#include <chrono>
#include <thread>
using namespace std::literals; // ����� ���� �ð� Ÿ�� ����ϱ� ����. 1s / 3ms / 10ns ��

int main()
{
	std::chrono::time_point tp1 = std::chrono::system_clock::now();

	std::chrono::hours h = std::chrono::duration_cast<std::chrono::hours>(tp1.time_since_epoch());

	std::cout << h.count() << std::endl;

	std::this_thread::sleep_for(3ms); // 3�� ���� ���
	std::this_thread::sleep_until(std::chrono::system_clock::now() + 3ms); //Ư���ð�(����ð� + 3ms)�� �ɶ� ���� ���


	return 0;
}