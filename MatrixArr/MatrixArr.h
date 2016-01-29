#ifndef MATRIXARR_H_201511
#define MATRIXARR_H_201511
#define _SCL_SECURE_NO_WARNINGs

class MatrixArr
{
public:
	using ValueType = double;

public:
	MatrixArr(const int rows, const int cols);
	MatrixArr(MatrixArr& rhs);
	~MatrixArr();

public:
	MatrixArr& operator=(MatrixArr& rhs);
	MatrixArr& operator=(const MatrixArr& rhs);

	ValueType * operator[](int i);
	int rows() const;
	int cols() const;

private:
	int rows_{ 0 };
	int cols_{ 0 };
	ValueType **data_{ nullptr };
};

#endif MATRIXARR_H_201511