#include <cstdarg>
#include <functional>
#include <iostream>
#include <string>
#include <typeinfo>

using namespace std;

class Timer {
	clock_t start_time;

public:

	void start() {
		this->start_time = clock();
	}

	void stop(string s = "ms") {
		clock_t end = clock();
		double time = (double)(end - this->start_time);
		if (s == "ms") {
			cout << time / (CLK_TCK / 1000) << endl;
		}
		if (s == "s") {
			cout << time / CLK_TCK << endl;
		}
		if (s == "m") {
			cout << time / 60 / CLK_TCK << endl;
		}
		if (s == "full") {

		}
	}

	void exec_time(int count ...) {
		va_list args;
		va_start(args, count);
		this->start();
		for (int i = 0; i < count; ++i) {
			function<void()> f = va_arg(args, function<void()>);
			f();
		}
		this->stop();
		va_end(args);
	}
};

void sort() {
	char arr[5] = { 'a','x','z','s','c' };
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5 - 1; j++) {
			if (arr[j] < arr[j - 1]) {
				int tmp = arr[j];
				arr[j] = arr[j - 1];
				arr[j - 1] = tmp;
			}
		}
	}
	for (int i = 0; i < 5; i++) {
		cout << arr[i];
	}
	cout << "\n\n" "Program execution time: ";
}

int main() {
	
	Timer timer;
	function<void()> f(sort);
	timer.exec_time(1, f);
	return 0;
}