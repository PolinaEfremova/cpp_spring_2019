class proxymatrix {

public:
	proxymatrix() {}
	void alloc(int number) {
		mas = new int[number];
		Size = number;
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
	proxymatrix(proxymatrix &obj) {
		Size = obj.Size;
		mas = new int[Size];
		for (int i = 0; i < Size; i++) {
			mas[i] = obj.mas[i];
		}

	}
	void copy(proxymatrix &obj) {
		mas = new int[obj.Size];
		for (int i = 0; i < obj.Size; i++) {
			mas[i] = obj.mas[i];
		}
		Size = obj.Size;
	}

private:
	int Size;
	int *mas;
};
class Matrix {
public:
	Matrix(int rows, int cols) :rows(rows), cols(cols) {
		mas2 = new proxymatrix[rows];
		for (int i = 0; i < rows; i++) {
			mas2[i].alloc(cols);
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
	Matrix(Matrix& obj) {
		rows = obj.rows;
		mas2 = new proxymatrix[obj.rows];
		for (int i = 0; i < obj.rows; i++) {
			mas2[i].copy(obj.mas2[i]);
		}

	}

	Matrix operator*=(int num) {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				//multi[i][j] = mas2[i][j] * num;
				mas2[i][j] = mas2[i][j] * num;
			}
		}
		Matrix multi(*this);
		return multi;
	}
	const bool operator==(const Matrix& other) {
		if ((cols != other.cols) || (rows != other.rows)) {
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
	const bool operator!=(const Matrix& other) {
		if ((cols != other.cols) || (rows != other.rows)) {
			return true;
		}
		int p = 0;
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				if (mas2[i][j] != other.mas2[i][j])
					return true;
			}
		}
		return false;
	}
private:
	int rows;
	int cols;
	proxymatrix *mas2;

};