#ifndef ZNVECTOR_H_20150926
#define ZNVECTOR_H_20150926
#define _SCL_SECURE_NO_WARNINGS

#include <cstddef> 
#include <cstdint> 
#include <initializer_list> 
#include <memory>
#include <iostream>

class ZnVector
{
public:
	using ValueType = int32_t; 
	using IndexType = ptrdiff_t;

public:
	ZnVector() = default; 
	ZnVector(const IndexType dims); 
	ZnVector(std::initializer_list<ValueType> list); 
	
	ZnVector(const ZnVector& arr); 
	ZnVector(ZnVector&& vec); 
	~ZnVector(); 

	ZnVector& operator=(const ZnVector& vec);
	ZnVector& operator=(ZnVector&& vec); 
	
	ZnVector operator-(); 
	ZnVector& operator+=(const ZnVector& rhs); 
	ZnVector& operator+=(const ValueType rhs); 
	ZnVector& operator-=(const ZnVector& rhs); 
	ZnVector& operator-=(const ValueType rhs); 
	ZnVector& operator*=(const ValueType rhs); 
	ZnVector& operator/=(const ValueType rhs); 

	bool operator==(const ZnVector& rhs);
	bool operator!=(const ZnVector& rhs);

	ZnVector& operator++();
	ZnVector operator++(int);
	ZnVector& operator--();
	ZnVector operator--(int);
	
	std::ostream& print(std::ostream& ostrm) const;

	ValueType& operator[](const IndexType index); 
	const ValueType& operator[](const IndexType index) const; 
	ValueType* begin() { return data_; } 
	ValueType* end() { return data_ + dims_; } 
	const ValueType* cbegin() { return data_; } 
	const ValueType* cend() { return data_ + dims_; }

private:
	IndexType dims_{ 0 };
	ValueType* data_{ nullptr };
private:
	void swap(ZnVector& arr);
};

std::ostream& operator<<(std::ostream& ostrm, const ZnVector& v);
ZnVector operator+(const ZnVector& lhs, const ZnVector& rhs);
ZnVector operator-(const ZnVector& lhs, const ZnVector& rhs);
ZnVector operator*(const ZnVector& lhs, const int32_t& rhs);
ZnVector operator*(const int32_t& lhs, const ZnVector& rhs );
ZnVector operator/(const ZnVector& lhs, const int32_t& rhs);

#endif ZNVECTOR_H_20150926