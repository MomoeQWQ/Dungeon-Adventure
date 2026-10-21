#pragma once
template <typename T>
class DynamicArray {
public:
	DynamicArray() {};
	~DynamicArray() {};
	void push_back() {}
	void pop_back() {}
	T operator[]() {}

private:
	T m_data{};
	DynamicArray* Arrayptr{};
};

DynamicArray::push_back() {
	
}
