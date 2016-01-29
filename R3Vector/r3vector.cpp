#include "r3vector.h"

R3Vector::R3Vector(const double rX, const double rY, const double rZ)
	:data_{ rX,rY,rZ }
{}

double R3Vector::x() const
{
	return data_[0];
}
double R3Vector::y() const
{
	return data_[1];
}
double R3Vector::z() const
{
	return data_[2];
}

double& R3Vector::rx()
{
	return data_[0];
}
double& R3Vector::ry()
{
	return data_[1];
}
double& R3Vector::rz()
{
	return data_[2];
}

std::ostream& R3Vector::print(std::ostream& ostrm) const
{
	return ostrm << "(" << x() << "," << y() << "," << z() << ")";
}

double& R3Vector::operator[](const ptrdiff_t i)
{
	if ((i < 0) || (dim() <= i))
		throw out_of_range("Index out of range in R3Vector::operator[]().");
	return data_[i];
}

const double& R3Vector::operator[](const ptrdiff_t i) const
{
	if ((i < 0) || (dim() <= i))
		throw out_of_range("Index out of range in R3Vector::operator[]() const.");
	return data_[i];
}

R3Vector R3Vector::operator-()
{
	return{ -x(),-y(),-z() };
}

R3Vector& R3Vector::operator+=(const R3Vector& rhs)
{
	data_[0] += rhs.data_[0];
	data_[1] += rhs.data_[1];
	data_[2] += rhs.data_[2];
	return *this;
}
R3Vector& R3Vector::operator-=(const R3Vector& rhs)
{
	data_[0] -= rhs.data_[0];
	data_[1] -= rhs.data_[1];
	data_[2] -= rhs.data_[2];
	return *this;
}
R3Vector& R3Vector::operator*=(const double rhs)
{
	rx() *= rhs;
	ry() *= rhs;
	rz() *= rhs;
	return *this;
}

R3Vector& R3Vector::operator+=(const double rhs)
{
	for (auto& v : *this)
	{
		v += rhs;
	}
	return *this;
}
R3Vector& R3Vector::operator-=(const double rhs)
{
	for (auto iCur{ begin() }, iEnd{ end() }; iCur != iEnd; ++iCur)
	{
		*iCur -= rhs;
	}
	return *this;
}
R3Vector& R3Vector::operator/=(const double rhs)
{
	for (auto& coord : *this)
	{
		coord /= rhs;
	}
	return *this;
}

R3Vector operator+(const R3Vector& lhs, const R3Vector& rhs)
{ return R3Vector(lhs) += rhs; }
R3Vector operator-(const R3Vector& lhs, const R3Vector& rhs)
{ return R3Vector(lhs) -= rhs; }
R3Vector operator*(const R3Vector& lhs, const double rhs)
{ return R3Vector(lhs) *= rhs; }
R3Vector operator*(const double lhs, const R3Vector& rhs)
{ return R3Vector(rhs) *= lhs; }
R3Vector operator/(const R3Vector& lhs, const double rhs)
{ return R3Vector(lhs) /= rhs; }
R3Vector operator+(const R3Vector& lhs, const double rhs)
{ return R3Vector(lhs) += rhs; }
R3Vector operator-(const R3Vector& lhs, const double rhs)
{ return R3Vector(lhs) -= rhs; }

bool operator==(const R3Vector& lhs, const R3Vector& rhs)
{
	return (lhs.x() == rhs.x()) && (lhs.y() == rhs.y()) && (lhs.z() == rhs.z());
}
bool operator!=(const R3Vector& lhs, const R3Vector& rhs)
{
	return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& ostrm, const R3Vector& v)
{
	return v.print(ostrm);
}