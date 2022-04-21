// 스레드를 생성할 때 전달할 수 있는 함수의 종류.
// thread를 생성할때는 일반함수, 멤버함수, 함수객체, 람다표현식을 전달 할 수 있다.

#include <iostream>
#include <chrono> // chrono 시간 사용
#include <thread> // thread 사용
#include <string>
using namespace std::literals;
void foo(int a, double d) {}
struct Machine 
{
	void Run(int a, double d) {}
};
struct Work
{
	void operator() (int a, double d) const {}
};

int main()
{
	Machine m;
	Work w;

	std::thread t1(&foo, 1, 3.4);								// 일반 함수
	std::thread t2(&Machine::Run, &m, 1, 3.4);					// 멤버함수를 전달 할 경우 멤버 함수를 호출할 객체도 함께 전달해야 한다.
	std::thread t3(w, 1, 3.4);									// 함수객체는 함수 객체와 매개변수만 전달하면 된다.
	std::thread t4([](int a, double d) {std::cout << "lamda" << std::endl; }, 1, 3.4);	// 람다도 람다 표현식과 매개변수만 전달한다.

	t1.join();
	t2.join();
	t3.join();
	t4.join();
	return 0;
}
