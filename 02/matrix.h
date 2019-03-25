class proxymatrix {
public:
	proxymatrix() {}
	proxymatrix(size_t cols) {
		mas = new int[cols];
		Size = cols;
	}
	~proxymatrix() {
		delete[](mas);
	}
	const int& operator[](size_t i) const
	{
		if (i >= Size)
			throw std::out_of_range("");
		return mas[i];
	}

	int& operator[](size_t i)
	{
		if (i >= Size)
			throw std::out_of_range("");
		return mas[i];
	}

private:
	size_t Size;
	int *mas;
};
class Matrix {
public:
	Matrix(size_t rows, size_t cols)
		:rows(rows), cols(cols)
	{
		mas2 = new proxymatrix[rows];
		for (int i = 0; i < rows; i++) {
			new(mas2 + i) proxymatrix(cols);
		}
	}
	~Matrix() {
		delete[](mas2);
	}
	int getRows() {
		return rows;
	}
	int getColumns() {
		return cols;
	}
	const proxymatrix& operator[](size_t i) const
	{
		if (i >= rows)
			throw std::out_of_range("");
		return mas2[i];
	}

	proxymatrix& operator[](size_t i)
	{
		if (i >= rows)
			throw std::out_of_range("");
		return mas2[i];
	}


	const Matrix &operator*=(int scalar) {
		Matrix multi(rows,cols); 

		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				multi[i][j]=mas2[i][j]*scalar; 
				mas2[i][j] = mas2[i][j] * scalar;
			}
		}

		return multi;
	}
	bool operator==(const Matrix& other) {
		if (cols != other.cols || rows != other.rows) {
			return false;
		}
		int p = 0;
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				if (mas2[i][j] != other.mas2[i][j])
					return false;
			}
		}
		return true;
	}
	bool operator!=(const Matrix& other) {

		if (mas2 == other.mas2) return false;
		else return true;
	}
private:
	size_t rows;
	size_t cols;
	proxymatrix *mas2;

};
