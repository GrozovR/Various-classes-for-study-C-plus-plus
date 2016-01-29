#include "MatrixArr.h"
using ValueType = double;

MatrixArr::MatrixArr(const int rows, const int cols)
	:rows_{rows}
	,cols_{cols}
{
	data_ = new ValueType*[rows_];
	for (int count{ 0 }; count < rows_; count++)
	{
		data_[count] = new ValueType[cols_];
	}
	//first initialization
	for (int i = 0; i < rows_; i++)
	{
		for (int j = 0; j < cols_; j++)
		{
			data_[i][j] = 0;
		}
	}
}
MatrixArr::MatrixArr(MatrixArr& rhs)
	:rows_{rhs.rows_}
	, cols_{rhs.cols_}
{
	data_ = new ValueType*[rows_];
	for (int count{ 0 }; count < rows_; count++)
	{
		data_[count] = new ValueType[cols_];
	}

	for (int i = 0; i < rows_; i++)
	{
		for (int j = 0; j < cols_; j++)
		{
			data_[i][j] = rhs.data_[i][j];
		}
	}
}
MatrixArr::~MatrixArr()
{
	delete[] data_;
}

MatrixArr& MatrixArr::operator=(MatrixArr& rhs) = default;
MatrixArr& MatrixArr::operator=(const MatrixArr& rhs) = default;

//made check for out of array
ValueType * MatrixArr::operator[](const int i)
{
	return data_[i];
}

int MatrixArr::rows() const
{
	return rows_;
}
int MatrixArr::cols() const
{
	return cols_;
}