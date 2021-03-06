#include <iostream> 
#include <fstream> 
#include <string.h> 
#include <string> 
#include <math.h> 
#include "numbers.dat"

int bynarysearch(int n) {
	int left = 0, right = Size - 1, middle = 0;
	while (left <= right) {
		middle = (left + right) / 2;
		if (n < Data[middle])
			right = middle - 1;
		else if (n > Data[middle])
			left = middle + 1;
		else 
			return middle;
	}
	return -1;
}
int primesearch(int t) {
	for (int j = 2; j <= sqrt((float)t); j++) {
		if (t % j == 0) 
			return 1;
		}
	return 0;
}
int counting(int lk, int rk) {
	int p = 0;
	for (int i = lk; i <= rk; i++) {
		if (Data[i] == 1 || primesearch(Data[i]) == 1)
			p++;
	}
	return p;
}
int main(int argc, char* argv[])
{
	if (argc < 3) 
		return -1;
	if ((argc + 1) % 2) 
		return -1;
	int left, right;
	for (int i = 1; i < argc; i += 2)
	{
		left = std::atoi(argv[i]);
		right = std::atoi(argv[i + 1]);
		if (left > right) {
			std::cout << '0';
			return 0;
		}
		int lk = bynarysearch(left);
		int rk = bynarysearch(right);
		while (Data[rk] == Data[rk + 1])
			rk++;
		int s = counting(lk, rk);
		int pr = rk - lk + 1 - s;
		std::cout << pr << std::endl;
	}
		return 0;
}