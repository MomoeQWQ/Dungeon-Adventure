// main loop of the game
#include "./Core/DynamicArray.h"

int main() {
	DynamicArray<int> a(2);
	for (int i{ 0 };i < 5;i++) {
		a.push_back(i);
	}
	a.print();
	DynamicArray<int> b = a;
	b[0] = 1234;
	a.print();
	a = a;
	b = a;
	a.print();
}