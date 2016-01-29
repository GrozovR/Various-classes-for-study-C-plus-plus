#pragma once
#include <cstddef>
#include <iostream>
#include <iterator>
using namespace std;

class R3Vector
{
public:
	R3Vector() noexcept = default;
	R3Vector(const R3Vector&) noexcept = default;
	R3Vector(const double rX, const double rY, const double rZ);
	~R3Vector() noexcept = default;
	R3Vector& operator=(const R3Vector&) noexcept = default;

	std::ostream& print(std::ostream& ostrm) const;

	static constexpr ptrdiff_t dim() { return dimCount_; } 
	double& operator[](const ptrdiff_t i); 
	const double& operator[](const ptrdiff_t i) const; 
	
	
	R3Vector operator-(); 
	R3Vector& operator+=(const R3Vector& rhs); 	
	R3Vector& operator-=(const R3Vector& rhs); 	
	R3Vector& operator*=(const double rhs); 
	
	R3Vector& operator+=(const double rhs);
	R3Vector& operator-=(const double rhs); 
	R3Vector& operator/=(const double rhs); 
	
	
	double* begin() { return data_; }
	double* end() { return data_ + dimCount_; } 
	const double* cbegin() { return data_; } 
	const double* cend() { return data_ + dimCount_; }

	double x() const;
	double y() const;
	double z() const;
	double& rx();
	double& ry();
	double& rz();

private:
	static const ptrdiff_t dimCount_{ 3 };	
	double data_[dimCount_] = { 0.0 };
};

std::ostream& operator<<(std::ostream& ostrm, const R3Vector& v);
bool operator==(const R3Vector& lhs, const R3Vector& rhs);
bool operator!=(const R3Vector& lhs, const R3Vector& rhs);

R3Vector operator+(const R3Vector& lhs, const R3Vector& rhs); 
R3Vector operator-(const R3Vector& lhs, const R3Vector& rhs);
R3Vector operator*(const R3Vector& lhs, const double rhs); 
R3Vector operator*(const double lhs, const R3Vector& rhs); 
R3Vector operator/(const R3Vector& lhs, const double rhs);
R3Vector operator+(const R3Vector& lhs, const double rhs);
R3Vector operator-(const R3Vector& lhs, const double rhs);