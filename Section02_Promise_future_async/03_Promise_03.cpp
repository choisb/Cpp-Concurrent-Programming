#include <iostream>
#include <thread>
#include <future>
#include <vector>
#include <numeric>

int main()
{
	std::vector<int> v1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	std::vector<int> v2(10);

	std::promise<void> pm1; // void�� ������ ��� set_value�� ���� �ѱ��� �ʾƵ��ȴ�. ��ȣ�� �����ϴ� ����.
	std::future<void> ft1 = pm1.get_future();


	std::promise<int> pm2; // void�� ������ ��� set_value�� ���� �ѱ��� �ʾƵ��ȴ�. ��ȣ�� �����ϴ� ����.
	std::future<int> ft2 = pm2.get_future();

	std::thread t([&] {
		std::partial_sum(v1.begin(), v1.end(), v2.begin()); // �κ��� ��� ( ��귮�� �ſ� ���ٰ� ����غ���.)

		pm1.set_value(); // ù��° ������ ����Ǿ����� ���� �����忡 �˸���.

		int s = std::accumulate(v2.begin(), v2.end(), 0); // �ι�° ����. ������ �� ���

		pm2.set_value(s); // �ι�° ������ ����Ǿ����� �˸��� ����� s�� �����Ѵ�.
		});

	ft1.get(); // ù ��° ������ ����� �� ���� ����Ѵ�. ù ��° ������ ����� ��� v2�� ������ ����Ѵ�.
	for (auto n : v2)
		std::cout << n << ", ";
	std::cout << std::endl;


	int ret = ft2.get(); // �� ��° ������ ����� �� ���� ����Ѵ�. �� ���� ������ ����� �޾Ƽ� ����Ѵ�.
	std::cout << ret << std::endl;



	return 0;
}