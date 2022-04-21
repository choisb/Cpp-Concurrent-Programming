/*
lock guard�� �����ڴ� �� ������ �ִ�.

1. mutex�� ���� �ް� �����ڿ��� lock�� �Ŵ� ������

	explicit lock_guard(_Mutex& _Mtx) : _MyMutex(_Mtx) { // construct and lock
		_MyMutex.lock();
	}
2. mutex�� adopt_lock_t �� ���� �ް� �����ڿ����� lock�� ���� �ʴ� ������. �̹� lock�� �ɸ� mutex�� ���޹��� �� ����� �� �ִ�.
	lock_guard(_Mutex& _Mtx, adopt_lock_t) : _MyMutex(_Mtx) {} // construct but don't lock

*/
#include <iostream>
#include <thread>
#include <mutex>
#include <exception>

std::mutex m;
int share_data = 0;

void foo()
{
	m.lock();
	std::lock_guard<std::mutex> lg(m, std::adopt_lock); // �̹� lock�� �� mutex�� adopt_lock�� �Բ� ����
	std::cout << "using share data" << std::endl;
}

int main()
{
	std::thread t1(foo);
	std::thread t2(foo);

	t1.join();
	t2.join();
}

