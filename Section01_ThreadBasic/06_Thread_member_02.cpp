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
#include <windows.h> // ���� C++�� ǥ�ؿ� ���� ��ɵ��� �ٷ�� ����. (GetCurrentThread / SetThreadPriority)
#include <string>
using namespace std::literals;

void foo()
{
	auto tid = std::this_thread::get_id(); // ������ ID ���
	
	auto handle = GetCurrentThread();		// Window os�� ������ �ڵ� ���. (C++ ǥ�� ���� x)
	std::cout << "���� �� �켱����: " << GetThreadPriority(handle) << std::endl;
	std::this_thread::sleep_for(200ms);
	std::cout << "���� �� �켱����: " << GetThreadPriority(handle) << std::endl;
}
int main()
{
	std::thread t(&foo);
	std::thread::native_handle_type h = t.native_handle(); // window os�� ������ �ڵ� ��ȯ

	std::cout << "ID    : " << t.get_id() << std::endl;
	std::cout << "handle: " << h          << std::endl;

	std::this_thread::sleep_for(100ms);
	SetThreadPriority(h, THREAD_PRIORITY_TIME_CRITICAL); // �������� �켱���� ����. (C++ ǥ�� ���� x)
	t.join();

	return 0;
}
