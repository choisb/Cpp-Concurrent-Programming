// �����带 ������ �� ������ �� �ִ� �Լ��� ����.
// thread�� �����Ҷ��� �Ϲ��Լ�, ����Լ�, �Լ���ü, ����ǥ������ ���� �� �� �ִ�.

#include <iostream>
#include <chrono> // chrono �ð� ���
#include <thread> // thread ���
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

	std::thread t1(&foo, 1, 3.4);								// �Ϲ� �Լ�
	std::thread t2(&Machine::Run, &m, 1, 3.4);					// ����Լ��� ���� �� ��� ��� �Լ��� ȣ���� ��ü�� �Բ� �����ؾ� �Ѵ�.
	std::thread t3(w, 1, 3.4);									// �Լ���ü�� �Լ� ��ü�� �Ű������� �����ϸ� �ȴ�.
	std::thread t4([](int a, double d) {std::cout << "lamda" << std::endl; }, 1, 3.4);	// ���ٵ� ���� ǥ���İ� �Ű������� �����Ѵ�.

	t1.join();
	t2.join();
	t3.join();
	t4.join();
	return 0;
}
