// �������� ����Լ��� ���캽. �������� ����Լ� ������ ������ ����.
// hardware_concurrency() : �ϵ������ ���� ��ȯ (static)
// get_id(): �������� ID ��ȯ
// native_handle(): OS�� ������ �ڵ� ��ȯ
// swap(): ������ object swap
// joinable(): �����尡 join �� �� �ִ��� ����
// join(): ������ ���� ���
// detach(): ������ ���� ����

#include <iostream>
#include <thread>

void foo() {}
void goo() {}
int main()
{
	std::thread t1(&foo);
	std::thread t2(&goo);

	t1.swap(t2);
	// std::thread t3 = t1; // error ������� ������ �� ����.
	std::thread t4 = std::move(t1);

	// t1.join(); // ���� �߻�. t1 �������� ������ t4�� �̵��߱� ������ join �� �� ����.
	t2.join();
	t4.join();

	
	return 0;
}
