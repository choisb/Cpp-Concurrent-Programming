#include <iostream>
#include <chrono> // chrono 시간 사용
#include <thread> // thread 사용
#include <string>
using namespace std::literals;

void f1() {}
void f2(int a, double b) {}
void f3(int a, int& b, std::string&& s) {b = 100; }

int main()
{
	
	int n = 0;
	std::string s = "hello";
	std::thread t1(&f1);								// 인자가 없을 경우 함수만 전달
	std::thread t2(&f2, 10, 3.4);						// 가변인자를 활용하여 인자의 타입과 개수만큼 전달
	std::thread t3(&f3, 10, std::ref(n), std::move(s)); // l-value 전달 시 std::ref() / r-value 전달시 move 사용
														// 참조로 전달하는 것은 위험할 수 있음.
														// std::ref()의 원리는 09_Reference_wrapper.cpp 예제 참고
	t1.join();
	t2.join();
	t3.join();
	

	std::cout << n << std::endl;
	std::cout << s << std::endl;

	return 0;
}