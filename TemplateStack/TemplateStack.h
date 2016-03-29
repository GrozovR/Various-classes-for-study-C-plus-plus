#ifndef T_STACK_H_2016
#define T_SHTCK_H_2016

template <typename T>
class tStack
{
public:
	tStack() = default;
	~tStack();

	//tStack(const tStack<T>& rhs);
	//tStack<T>& operator=(const tStack<T>& rhs);


	bool isEmpty();
	void push(const T v);
	void pop();
	T top() const;

private:
	int size{ 0 };
	T* data_{ nullptr };
	int itop{ 0 };
};

template<typename T>
inline tStack<T>::~tStack()
{
	delete[] data_;
}

template<typename T>
inline bool tStack<T>::isEmpty()
{
	return 0 == size;
}

template<typename T> void tStack<T>::push(const T v)
{
	if (isEmpty())
	{
		size++;
		data_ = new T[size];
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

template<typename T>
inline void tStack<T>::pop()
{
	if (isEmpty())
	{
		throw std::exception("Stack is empty");
	}
	itop--;
}

template<typename T>
inline T tStack<T>::top() const
{
	if (isEmpty())
	{
		throw std::exception("Stack is empty");
	}
	return data_[itop - 1];
}



#endif T_STACK_H_2016