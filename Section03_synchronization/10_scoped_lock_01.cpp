/*
두개 이상의 뮤텍스를 함께쓰다보면 데드락이 발생할 수 있다. 이런 문제를 해결하기 위해서 scoped lock을 사용한다.
- std::lock_guard: 한 개의 뮤텍스를 RAII 기술로 관리(C++11)
- std::scoped_lock: 여러 개의 뮤텍스를 RAII 기술로 관리. 내부적으로는 std::lock을 사용 (C++17)
*/
#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
using namespace std::literals;

struct Account
{
	std::mutex m;
	int money = 100;
};

// 일반 뮤텍스 활용 - 데드락 발생
//void transfer(Account& acc1, Account& acc2, int cnt)
//{
//	acc1.m.lock();
//	std::this_thread::sleep_for(10ms);
//	acc2.m.lock();	// 데드락 발생
//	acc1.money -= cnt;
//	acc2.money += cnt;
//	std::cout << "finish transfer" << std::endl;
//	acc2.m.unlock();
//	acc1.m.unlock();
//}

// std::lock 사용
// std::lock(...) : 데드락 회피기술이 도입되어서 여러개의 뮤텍스를 안전하게 락걸수 있음 / 가변인자이기 때문에 여러개의 뮤텍스를 잡을 수 있음
// but. std::lock 사용시 직접 unlock을 해야하는 문제가 있음. 
//void transfer(Account& acc1, Account& acc2, int cnt)
//{
//	std::lock(acc1.m, acc2.m);
//	acc1.money -= cnt;
//	acc2.money += cnt;
//	std::cout << "finish transfer" << std::endl;
//	acc2.m.unlock();
//	acc1.m.unlock();
//}

// std::lock과 lock guard를 함께 사용
//void transfer(Account& acc1, Account& acc2, int cnt)
//{
//	std::lock(acc1.m, acc2.m);
//	std::lock_guard<std::mutex> lg1(acc1.m, std::adopt_lock);
//	std::lock_guard<std::mutex> lg2(acc2.m, std::adopt_lock);
//	acc1.money -= cnt;
//	acc2.money += cnt;
//	std::cout << "finish transfer" << std::endl;
//
//}

// scoped_lock 사용하면 한번에 해결 
// 여러개의 뮤텍스를 데드락 방지기법을 통해서 잡을 수 있고
// 소멸자에서 모두 unlock까지 안전하게 시켜준다.
void transfer(Account& acc1, Account& acc2, int cnt)
{
	//std::scoped_lock<std::mutex, std::mutex> sl(acc1.m, acc2.m); // ok
	std::scoped_lock sl(acc1.m, acc2.m);	// C++17 부터 컴파일러가 템플릿 인자를 추론할 수 있기 때문에 템플릿 인자 모두 생략도 가능
	acc1.money -= cnt;
	acc2.money += cnt;
	std::cout << "finish transfer" << std::endl;

}

int main()
{
	Account kim, lee;
	std::thread t1(transfer, std::ref(kim), std::ref(lee), 10);
	std::thread t2(transfer, std::ref(lee), std::ref(kim), 10);
	t1.join();
	t2.join();
	return 0;
}