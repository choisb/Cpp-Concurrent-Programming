/*
timed_mutex�� ����Լ� ����Ʈ
- lock()	: mutex�� �ᱺ��. ���� mutex�� ��밡������ ���� ���¶�� block �� ���
- try_lock(): mutex�� lock�� �õ��Ѵ�. ���� ��밡������ ���� ���¶�� block���� �ʰ� false ��ȯ. ��밡���ϴٸ� lock ȹ��
- unlock()	: �ᱺ lock�� ��ȯ�Ѵ�.
- native_handle(): �ο췹��(�ü��)�� mutex �ڵ��� ��ȯ�Ѵ�.

- try_lock_for(): ���� �ð� ���� lock ȹ�� �õ�
- try_lock_until(): ~�ð� ���� lock ȹ�� �õ�

mutex�� ��� Ÿ��
- native_handle_type: native_handle()�� ��ȯ Ÿ��

mutex�� ����� �̵����� �ȵ�
*/
#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <mutex>
using namespace std::literals;

std::timed_mutex m;
int share_data = 0;
void foo()
{
	if (m.try_lock_for(2s))
	{
		share_data = 10;
		std::cout << "using share_data" << std::endl;
		std::this_thread::sleep_for(3s);
		m.unlock();
	}
	else
	{
		std::cout << "���ؽ� ȹ�� ����" << std::endl;
	}
}

int main()
{
	std::thread t1(foo);
	//std::this_thread::sleep_for(20ms);
	std::thread t2(foo);
	t1.join();
	t2.join();


	return 0;
}
