#ifndef TSTACK_H_201511
#define TSTACK_H_201511
#define _SCL_SECURE_NO_WARNINGs


template <typename T>
class tstack
{
public:
	tstack() = default;
	tstack(const tstack<T> &rhs) = default;
	tstack<T> & operator=(const tstack<T> & rhs) = default;
	~tstack();

	bool isempty();
	void push(const T v);
	T pop();
	T top();

private:
	int size{ 0 };
	T* data_{ nullptr };
	int itop{ 0 };
};

//template<typename T> tstack:<T>::tstack(const& tstack rhs);

template<typename T> tstack<T>::~tstack()
{
	delete[] data_;
}

template<typename T> void tstack<T>::push(const T v)
{
	if (size == 0)
	{
		size++;
		T* newData{ new T[size] };
		delete[] data_;
		data_ = newData;
		data_[itop] = v;
	}
	if (itop == size)
	{

		T* newData{ new T[size * 2] };
		for (int i{ 0 }; i < size; i++)
		{
			newData[i] = data_[i];
		}
		delete[] data_;
		data_ = newData;
		size *= 2;
	}
	data_[itop] = v;
	itop++;
}

template<typename T> bool tstack<T>::isempty()
{
	return 0 == itop;
}

template<typename T> T tstack<T>::pop()
{
	if (isempty())
	{
		throw std::exception("Stack is empty!");
	}
	itop--;
	return data_[itop];
}

template<typename T> T tstack<T>::top()
{
	if (isempty())
	{
		throw std::exception("Stack is empty!");
	}
	return data_[itop - 1];
}

#endif TSTACK_H_201511