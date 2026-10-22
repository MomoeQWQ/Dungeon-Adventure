#pragma once
#include <cassert>
#include <iostream>//for test

template <typename T>
class DynamicArray {
public:
	explicit DynamicArray(int capacity)
		: m_capacity{ capacity }
	{
		assert(capacity > 0 && "Incorrect DynamicArray Size");//In case minus or zero input
		arrayptr = new T[m_capacity];
	}

	~DynamicArray() {
		delete[] arrayptr;
	}

	//copy constructor
	DynamicArray(const DynamicArray& source) 
	{ 
		deepCopy(source); 
	}
	
	//operator= overloading
	DynamicArray& operator=(const DynamicArray& source) {
		//self-assignment guard
		if (this != &source)
		{
			deepCopy(source);
		}

		return *this;
	}

	//operator[] overloading
	T& operator[](int index) {
		assert(index >= 0 && index < m_size && "invalid array index input");
		return arrayptr[index];
	}

	//const version of operator[]
	const T& operator[](int index) const {
		assert(index >= 0 && index < m_size && "invalid array index input");
		return arrayptr[index];
	}

	//get size 
	int getSize() const{
		return m_size;
	}

	void push_back(const T&);
	T pop_back();

	//only for test
	void print() const{
		for (int i{ 0 };i < m_size;i++) {
			std::cout << arrayptr[i] << "\t";
		}
		std::cout << std::endl;
	}

private:
	T* arrayptr{};
	int m_size{};
	int m_capacity{};
	void expansion();//Helper function expasion(update memory size)
	void deepCopy(const DynamicArray& source);//Helper function DeepCopy(as we allocate memory by ourselves)
};

//Implement Helper function of copy constructor
template <typename T>
void DynamicArray<T>::deepCopy(const DynamicArray& source) {
	delete[] arrayptr;//safe to delete nullptr if constructed by default
	m_size = source.m_size;
	m_capacity = source.m_capacity;
	if (source.arrayptr) //non-null source array pointer
	{
		arrayptr = new T[m_capacity];
		
		//copy
		for (int i{ 0 };i < m_size;i++)
			arrayptr[i] = source.arrayptr[i];
	}
	else
		arrayptr = nullptr;
}

//Implement expansion
template <typename T>
void DynamicArray<T>::expansion() {
	T* temp_ptr{ new T[m_capacity * 2] };//step1. allocate a larger memory
	for (int i{ 0 };i < m_size;i++)
	{
		temp_ptr[i] = arrayptr[i];
	}//step2. copy initial data
	delete[] arrayptr;//step3. release old memory
	arrayptr = temp_ptr;
	m_capacity *= 2;//step4. re-bind arrayptr,update parameters
}

//Implement push_back
template <typename T>
void DynamicArray<T>::push_back(const T& value) {
	if (m_size == m_capacity)
		expansion();
	arrayptr[m_size] = value;
	m_size++;
}

//Implement pop_back
template <typename T>
T DynamicArray<T>::pop_back() {
	assert(m_size > 0 && "invalid visiting an empty DynamicArray");
	T out{ (*this)[m_size - 1] };//visit memory by [] which includes a boundary check,instead of using arrayptr
	m_size--;
	return out;
}