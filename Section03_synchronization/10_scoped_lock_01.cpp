/*
�ΰ� �̻��� ���ؽ��� �Բ����ٺ��� ������� �߻��� �� �ִ�. �̷� ������ �ذ��ϱ� ���ؼ� scoped lock�� ����Ѵ�.
- std::lock_guard: �� ���� ���ؽ��� RAII ����� ����(C++11)
- std::scoped_lock: ���� ���� ���ؽ��� RAII ����� ����. ���������δ� std::lock�� ��� (C++17)
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

// �Ϲ� ���ؽ� Ȱ�� - ����� �߻�
//void transfer(Account& acc1, Account& acc2, int cnt)
//{
//	acc1.m.lock();
//	std::this_thread::sleep_for(10ms);
//	acc2.m.lock();	// ����� �߻�
//	acc1.money -= cnt;
//	acc2.money += cnt;
//	std::cout << "finish transfer" << std::endl;
//	acc2.m.unlock();
//	acc1.m.unlock();
//}

// std::lock ���
// std::lock(...) : ����� ȸ�Ǳ���� ���ԵǾ �������� ���ؽ��� �����ϰ� ���ɼ� ���� / ���������̱� ������ �������� ���ؽ��� ���� �� ����
// but. std::lock ���� ���� unlock�� �ؾ��ϴ� ������ ����. 
//void transfer(Account& acc1, Account& acc2, int cnt)
//{
//	std::lock(acc1.m, acc2.m);
//	acc1.money -= cnt;
//	acc2.money += cnt;
//	std::cout << "finish transfer" << std::endl;
//	acc2.m.unlock();
//	acc1.m.unlock();
//}

// std::lock�� lock guard�� �Բ� ���
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

// scoped_lock ����ϸ� �ѹ��� �ذ� 
// �������� ���ؽ��� ����� ��������� ���ؼ� ���� �� �ְ�
// �Ҹ��ڿ��� ��� unlock���� �����ϰ� �����ش�.
void transfer(Account& acc1, Account& acc2, int cnt)
{
	//std::scoped_lock<std::mutex, std::mutex> sl(acc1.m, acc2.m); // ok
	std::scoped_lock sl(acc1.m, acc2.m);	// C++17 ���� �����Ϸ��� ���ø� ���ڸ� �߷��� �� �ֱ� ������ ���ø� ���� ��� ������ ����
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