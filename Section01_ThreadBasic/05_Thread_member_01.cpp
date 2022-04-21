// �������� ����Լ��� ���캽. �������� ����Լ� ������ ������ ����.
// hardware_concurrency() : �ϵ������ ���� ��ȯ (static)
// get_id(): �������� ID ��ȯ
// native_handle(): OS�� ������ �ڵ� ��ȯ
// swap(): ������ object swap
// joinable(): �����尡 join �� �� �ִ��� ����
// join(): ������ ���� ���
// detach(): ������ ���� ����

#include <iostream>
#include <chrono> // chrono �ð� ���
#include <thread> // thread ���
#include <string>
using namespace std::literals;

void foo() 
{
	std::cout << std::this_thread::get_id() << std::endl;
}
int main()
{
	int n = std::thread::hardware_concurrency(); // �ϵ����� �����ϴ� �������� ������ ��ȯ
	std::cout << n << std::endl;

	std::thread t(&foo);
	std::this_thread::sleep_for(1s);

	std::thread::id tid = t.get_id();	// thread id ��ȯ
	std::cout << "created thread id: " << tid << std::endl;
	t.join();

	return 0;
}
