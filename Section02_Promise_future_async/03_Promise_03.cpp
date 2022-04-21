#include <iostream>
#include <thread>
#include <future>
#include <vector>
#include <numeric>

int main()
{
	std::vector<int> v1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	std::vector<int> v2(10);

	std::promise<void> pm1; // void로 선언할 경우 set_value시 값을 넘기지 않아도된다. 신호만 전달하는 것임.
	std::future<void> ft1 = pm1.get_future();


	std::promise<int> pm2; // void로 선언할 경우 set_value시 값을 넘기지 않아도된다. 신호만 전달하는 것임.
	std::future<int> ft2 = pm2.get_future();

	std::thread t([&] {
		std::partial_sum(v1.begin(), v1.end(), v2.begin()); // 부분합 계산 ( 계산량이 매우 많다고 상상해보자.)

		pm1.set_value(); // 첫번째 연산이 종료되었음을 메인 스레드에 알린다.

		int s = std::accumulate(v2.begin(), v2.end(), 0); // 두번째 연산. 구간의 합 계산

		pm2.set_value(s); // 두번째 연산이 종료되었음을 알리며 결과값 s를 전달한다.
		});

	ft1.get(); // 첫 번째 연산이 종료될 때 까지 대기한다. 첫 번째 연산이 종료될 경우 v2의 내용을 출력한다.
	for (auto n : v2)
		std::cout << n << ", ";
	std::cout << std::endl;


	int ret = ft2.get(); // 두 번째 연산이 종료될 때 까지 대기한다. 두 번재 연산의 결과를 받아서 출력한다.
	std::cout << ret << std::endl;



	return 0;
}