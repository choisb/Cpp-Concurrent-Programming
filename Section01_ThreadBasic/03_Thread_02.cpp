#include <iostream>
#include <chrono> // chrono �ð� ���
#include <thread> // thread ���
#include <string>
using namespace std::literals;

void f1() {}
void f2(int a, double b) {}
void f3(int a, int& b, std::string&& s) {b = 100; }

int main()
{
	
	int n = 0;
	std::string s = "hello";
	std::thread t1(&f1);								// ���ڰ� ���� ��� �Լ��� ����
	std::thread t2(&f2, 10, 3.4);						// �������ڸ� Ȱ���Ͽ� ������ Ÿ�԰� ������ŭ ����
	std::thread t3(&f3, 10, std::ref(n), std::move(s)); // l-value ���� �� std::ref() / r-value ���޽� move ���
														// ������ �����ϴ� ���� ������ �� ����.
														// std::ref()�� ������ 09_Reference_wrapper.cpp ���� ����
	t1.join();
	t2.join();
	t3.join();
	

	std::cout << n << std::endl;
	std::cout << s << std::endl;

	return 0;
}