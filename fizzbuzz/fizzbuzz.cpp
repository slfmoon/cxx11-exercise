#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>

int main(int argc, char *argv[]) {
	std::cout << "\t --- FizzBuzz Program 日本語 ---" << std::endl << std::endl;
	int num = 0;

	if(argc < 2){
		std::cout << "Input limit number : ";
		std::cin >> num;
	}else{
		std::istringstream is (argv[1]);
		is >> num; // if > 2147483647 : auto cut
	}

//	if(num < 1 || num > std::numeric_limits<int>::max()){
	if(num < 1 || num > 100000){
		std::cout << "Invalid or too big!" << std::endl;
		return -1;
	}
	std::cout << "Input number: " << num << " / Max number: " << std::numeric_limits<int>::max() << std::endl << std::endl;

	auto myfizz = [] (int x, int fb) -> bool {
		// without %
		// return (((x / fb) * fb) == x);
			return ((x % fb) == 0);
		};

	for(int i = 1; i <= num; ++i){
		if(myfizz(i, 15))
			std::cout << "FizzBuzz";
		else if(myfizz(i, 3))
			std::cout << "Fizz";
		else if(myfizz(i, 5))
			std::cout << "Buzz";
		else
			std::cout << i;

		std::cout << " ";

		if(myfizz(i, 10))
			std::cout << std::endl;
	}
	std::cout << std::endl;
}
