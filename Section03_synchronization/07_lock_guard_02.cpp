/*
lock guard의 생성자는 두 종류가 있다.

1. mutex만 전달 받고 생성자에서 lock을 거는 생성자

	explicit lock_guard(_Mutex& _Mtx) : _MyMutex(_Mtx) { // construct and lock
		_MyMutex.lock();
	}
2. mutex와 adopt_lock_t 를 전달 받고 생성자에서는 lock을 걸지 않는 생서자. 이미 lock이 걸린 mutex를 전달받을 때 사용할 수 있다.
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
	std::lock_guard<std::mutex> lg(m, std::adopt_lock); // 이미 lock을 건 mutex를 adopt_lock과 함께 전달
	std::cout << "using share data" << std::endl;
}

int main()
{
	std::thread t1(foo);
	std::thread t2(foo);

	t1.join();
	t2.join();
}

