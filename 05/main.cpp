#include<iostream>
#include<thread>
#include<mutex>
#include <condition_variable>

std::condition_variable condition_;
size_t counter_ = 1;
std::mutex m;
const size_t n = 500000;

void ping()
{
	for (size_t i = 0; i < n; i++) {
		std::unique_lock<std::mutex> lock(m);
		condition_.wait(lock,[]()
		{
			return counter_ > 0;
		});
		printf("ping\n");
		--counter_;
		condition_.notify_one();
	}
}

void pong()
{
	for (size_t i = 0; i < n; i++) {
		std::unique_lock<std::mutex> lock(m);
		condition_.wait(lock,[]()
		{
			return counter_ == 0;
		});
		printf( "pong\n");
		++counter_;
		condition_.notify_one();
	}

}
int main() {
	std::thread ping_(ping);
	std::thread pong_(pong);
	ping_.join();
	pong_.join();
	return 0;
}
