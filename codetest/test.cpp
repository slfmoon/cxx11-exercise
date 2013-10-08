#include <iostream>
#include <string>
#include <vector>

int main(){

	using namespace std;
	vector<int> array;
	int i;

	for( i = 0; i < 10; ++i)
		array.push_back(i);

	auto it = array.begin();
	
	while( it != array.end() ){
		cout << *it << endl;
		++it;
	}
	
	auto lambda = [] (int x, int y) -> int { return x + y;};
	auto sum = lambda(7,2);
	cout << sum << endl;

}
