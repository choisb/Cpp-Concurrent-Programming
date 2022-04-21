#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std::literals;

std::timed_mutex tm;

int main()
{
	std::unique_lock<std::timed_mutex> u1;
	std::unique_lock<std::timed_mutex> u2(tm);

	//u1 = u2; // ���� �Ұ�
	u1 = std::move(u2); // �̵� ���� ����

	std::cout << u1.owns_lock() << std::endl;	// 1

	if (u1)	// u1�� lock�� �����ߴٸ� true
		std::cout << "acquire" << std::endl;

	u1.unlock();
	std::cout << u1.owns_lock() << std::endl;	// 0

	if (u1.try_lock_for(2s)) // ������ true ��ȯ
	{
		// ...
		u1.unlock();
	}
	
	u1.release(); // ������ mutex�� ���� ����



	return 0;
}