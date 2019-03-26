class proxymatrix {
public:
	proxymatrix() {}
	proxymatrix(size_t cols)
		:Size(cols)
	{
		array = new int[cols];
	}
	~proxymatrix() {
		delete[](array);
	}
	const int& operator[](size_t i) const
	{
		if (i >= Size)
			throw std::out_of_range("");
		return array[i];
	}

	int& operator[](size_t i)
	{
		if (i >= Size)
			throw std::out_of_range("");
		return array[i];
	}

private:
	size_t Size;
	int *array = nullptr;
};

class Matrix {
public:
	Matrix(size_t rows, size_t cols)
		:rows(rows), cols(cols)
	{
		 array2d = static_cast<proxymatrix*>(operator new[](rows * sizeof(proxymatrix)));
		for (size_t i = 0; i < rows; i++) {
			new (array2d + i) proxymatrix(cols);
		}
	}
	~Matrix() {
		for (int i = 0; i < rows; i++)
		{
			array2d[i].~proxymatrix();
		}
		operator delete[](array2d);
	}
	size_t getRows() {
		return rows;
	}
	size_t getColumns() {
		return cols;
	}
	const proxymatrix& operator[](size_t i) const
	{
		if (i >= rows)
			throw std::out_of_range("");
		return array2d[i];
	}

	proxymatrix& operator[](size_t i)
	{
		if (i >= rows)
			throw std::out_of_range("");
		return array2d[i];
	}
	 Matrix &operator*=(int scalar) {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				array2d[i][j] = array2d[i][j] * scalar;
			}
		}
		return *this;
	}
	bool operator==(const Matrix& other) {
		if (cols != other.cols || rows != other.rows) {
			return false;
		}
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				if (array2d[i][j] != other.array2d[i][j])
					return false;
			}
		}
		return true;
	}
	bool operator!=(const Matrix& other) {
		return !(array2d == other.array2d);
	}
private:
	size_t rows;
	size_t cols;
	proxymatrix *array2d = nullptr;

};
