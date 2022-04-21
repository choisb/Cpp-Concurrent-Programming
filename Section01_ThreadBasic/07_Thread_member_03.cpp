// �������� ����Լ��� ���캽. �������� ����Լ� ������ ������ ����.
// hardware_concurrency() : �ϵ������ ���� ��ȯ (static)
// get_id(): �������� ID ��ȯ
// native_handle(): OS�� ������ �ڵ� ��ȯ
// swap(): ������ object swap
// joinable(): �����尡 join �� �� �ִ��� ����
// join(): ������ ���� ���
// detach(): ������ ���� ����

#include <iostream>
#include <thread>

int main()
{
	std::thread t;
	// t.join(); //������� ���� �����带 join�� ��� ���� �߻�

	// �ʿ��� ��� join�� �������� Ȯ�� �� join�ϴ� ���� �ٶ�����.
	if (t.joinable())
	{
		t.join();
	}
	return 0;
}
