#pragma once
#include <cassert>

//DynamicArray, a simple implementation of dynamic array, similar to std::vector
template <typename T>
class DynamicArray {
public:
	explicit DynamicArray(int capacity = 8)//default capacity is 8
		: m_capacity{ capacity }
	{
		assert(capacity > 0 && "Incorrect DynamicArray Size");//In case minus or zero input
		m_arrayptr = new T[m_capacity];
	}

	~DynamicArray() {
		delete[] m_arrayptr;
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
		return m_arrayptr[index];
	}

	//const version of operator[]
	const T& operator[](int index) const {
		assert(index >= 0 && index < m_size && "invalid array index input");
		return m_arrayptr[index];
	}

	//get size 
	int getSize() const{
		return m_size;
	}
	
	//push and pop
	void push_back(const T&);
	T pop_back();

	//additional, designed for World::clear
	//clear, not release, next push_back will overwrite
	void clear() 
	{
		m_size = 0;
	}

private:
	T* m_arrayptr{};
	int m_size{};
	int m_capacity{};
	void expansion();//Helper function expasion(update memory size)
	void deepCopy(const DynamicArray& source);//Helper function DeepCopy(as we allocate memory by ourselves)
};

//Implement Helper function of copy constructor
template <typename T>
void DynamicArray<T>::deepCopy(const DynamicArray& source) {
	assert(m_size <= m_capacity);
	delete[] m_arrayptr;//safe to delete nullptr if constructed by default
	m_size = source.m_size;
	m_capacity = source.m_capacity;
	if (source.m_arrayptr) //non-null source array pointer
	{
		m_arrayptr = new T[m_capacity];
		
		//copy
		for (int i{ 0 };i < m_size;i++)
			m_arrayptr[i] = source.m_arrayptr[i];
	}
	else
		m_arrayptr = nullptr;
}

//Implement helper function expansion
template <typename T>
void DynamicArray<T>::expansion() {
	T* temp_ptr{ new T[m_capacity * 2] };//step1. allocate a larger memory
	for (int i{ 0 };i < m_size;i++)
	{
		temp_ptr[i] = m_arrayptr[i];
	}//step2. copy initial data
	delete[] m_arrayptr;//step3. release old memory
	m_arrayptr = temp_ptr;
	m_capacity *= 2;//step4. re-bind arrayptr,update parameters
}

//Implement push_back
template <typename T>
void DynamicArray<T>::push_back(const T& value) {
	if (m_size == m_capacity)
		expansion();
	m_arrayptr[m_size] = value;
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