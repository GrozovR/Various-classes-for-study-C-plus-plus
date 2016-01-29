#include "znvector.h"

#include <cassert>
#include <algorithm>
#include <stdexcept>


using namespace std;

ZnVector::ZnVector(const IndexType dims)
	:dims_{ dims }
{
	data_ = new ValueType[dims_];
}

ZnVector::ZnVector(std::initializer_list<ValueType> vals)
	: dims_{ static_cast<IndexType>(vals.size()) }
	, data_{ new ValueType[dims_] }
{
	std::uninitialized_copy(vals.begin(), vals.end(), data_);
}

ZnVector::ZnVector(ZnVector&& vec)
	: dims_{ vec.dims_ }
	, data_{ vec.data_ }
{
	vec.dims_ = 0;
	vec.data_ = nullptr;
}

ZnVector::ZnVector(const ZnVector& vec)
	: dims_{ vec.dims_ }
	, data_{ new ValueType[dims_] }
{
	std::uninitialized_copy(vec.data_, vec.data_ + vec.dims_, data_);
}

ZnVector::~ZnVector()
{
	delete[] data_;
}

ZnVector& ZnVector::operator=(const ZnVector& arr)
{
	if (this != &arr)
	{
		swap(ZnVector(arr));
	}
	return *this;
}
ZnVector& ZnVector::operator=(ZnVector&& arr)
{
	if (this != &arr)
	{
		swap(arr);
	}
	return *this;
}

std::ostream& ZnVector::print(std::ostream& ostrm) const
{	
	ostrm << "(";
	for (IndexType i{ 0 }; i < dims_ - 1; i += 1)
	{
		ostrm << data_[i];
		ostrm << ",";
	}
	ostrm << data_[dims_ - 1];
	ostrm << ")";

	return ostrm;
}

std::ostream& operator<<(std::ostream& ostrm, const ZnVector& v)
{
	return v.print(ostrm);
}

ZnVector::ValueType& ZnVector::operator[](const IndexType index)
{
	assert(index <= 0);
	assert(index < dims_);
	if ((index < 0) || (dims_ <= index))
	{
		throw out_of_range("index out of range in ZnVector::operator[]");
	}
	return data_[index];
}

const ZnVector::ValueType& ZnVector::operator[](const IndexType index) const
{
	assert(index <= 0);
	assert(index < dims_);
	if ((index < 0) || (dims_ <= index))
	{
		throw out_of_range("index out of range in ZnVector::operator[]");
	}
	return data_[index];
}

void ZnVector::swap(ZnVector& arr)
{
	IndexType dims{ arr.dims_ };
	arr.dims_ = dims_;
	dims_ = dims;
	ValueType* data{ arr.data_ };
	arr.data_ = data_;
	data_ = data;
}

ZnVector ZnVector::operator-()
{
	ZnVector res(dims_);
	for (IndexType i{ 0 }; i < dims_; i += 1)
	{
		res.data_[i] = -data_[i];
	}
	return res;
}
ZnVector& ZnVector::operator+=(const ZnVector& rhs)
{
	if (dims_ == rhs.dims_)
	{
		for (IndexType i{ 0 }; i < dims_; i += 1)
		{
			data_[i] += rhs.data_[i];
		}
	}
	else
	{
		throw exception("Vectors have different dimmension");
	}
	return *this;
}
ZnVector& ZnVector::operator+=(const ValueType rhs)
{
	for_each(data_, data_ + dims_, [rhs](ValueType& v) { v += rhs; });
	return *this;
}
ZnVector& ZnVector::operator-=(const ZnVector& rhs)
{
	
	if (dims_ == rhs.dims_)
	{
		for (IndexType i{ 0 }; i != dims_; ++i)
		{
			data_[i] -= rhs.data_[i];
		}
	}
	else
	{
		throw exception("Vectors have different dimmension");
	}
	return *this;
}
ZnVector& ZnVector::operator-=(const ValueType rhs)
{
	for (IndexType i{ 0 }; i != dims_; ++i)
	{
		data_[i] -= rhs;
	}
	return *this;
}
ZnVector& ZnVector::operator*=(const ValueType rhs)
{
	for (ValueType* i{ data_ }, *iEnd{ data_ + dims_ }; i != iEnd; ++i)
	{
		*i *= rhs;
	}
	return *this;
}
ZnVector& ZnVector::operator/=(const ValueType rhs)
{
	for (ValueType* i{ data_ }, *iEnd{ data_ + dims_ }; i != iEnd; ++i)
	{
		*i /= rhs;
	}
	
	return *this;
}

bool ZnVector::operator==(const ZnVector& rhs)
{
	bool tmp{ false };
	if (dims_ == rhs.dims_)
	{
		tmp = true;
		for (IndexType i{ 0 }; i != dims_; ++i)
		{
			if (data_[i] != rhs.data_[i]) tmp = false;
		}
	}
	return tmp;
}
bool ZnVector::operator!=(const ZnVector& rhs)
{
	bool tmp = (*this == rhs);
	return !tmp;
}

ZnVector& ZnVector::operator++()
{
	for (IndexType i{ 0 }; i < dims_; i++)
	{
		++data_[i];
	}
	return *this;
}
ZnVector ZnVector::operator++(int)
{
	ZnVector tmp(*this);
	operator++();
	return tmp;
}
ZnVector& ZnVector::operator--()
{
	for (IndexType i{ 0 }; i < dims_; i++)
	{
		--data_[i];
	}
	return *this;
}
ZnVector ZnVector::operator--(int)
{
	ZnVector tmp(*this);
	operator--();
	return tmp;
}

ZnVector operator+(const ZnVector& lhs,const ZnVector& rhs)
{
	return ZnVector(lhs) += rhs;
}
ZnVector operator-(const ZnVector& lhs,const  ZnVector& rhs)
{
	return ZnVector(lhs) -= rhs;
}
ZnVector operator*(const ZnVector& lhs, const int32_t rhs)
{
	ZnVector tmp(lhs);
	tmp *= rhs;
	return tmp;
}
ZnVector operator*(const int32_t lhs,const ZnVector& rhs)
{
	ZnVector tmp(rhs);
	tmp *= lhs;
	return tmp;
}
ZnVector operator/(const ZnVector& lhs, const int32_t  rhs)
{
	ZnVector tmp(lhs);
	tmp /= rhs;
	return tmp;
}