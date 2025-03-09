#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

bool check(string something)
{
	for (int i = 0; i < something.size(); i++) {
		if (48 > something[i] || something[i] > 57) {
			return false;
			break;
		}
		return true;
	}
}

class Matrix {
	int rows, cols;
	int** data;

public:
	Matrix() : rows(0), cols(0), data(nullptr){}

	Matrix(int rows, int cols) : rows(rows), cols(cols) {
		data = new int* [rows];
		for (int i = 0; i < rows; i++) {
			data[i] = new int[cols];
			for (int j = 0; j < cols; j++) {
				data[i][j] = 0;
			}
		}
	}

	Matrix(const Matrix& other) : rows(other.rows), cols(other.cols) {
		data = new int* [rows];
		for (int i = 0; i < rows; i++) {
			data[i] = new int[cols];
			for (int j = 0; j < cols; j++) {
				data[i][j] = 0;
			}
		}
	}

	~Matrix() {
		for (int i = 0; i < rows; i++) {
			delete[] data[i];
		}
		delete[] data;
	}

	int get_rows() const {
		return rows;
	}

	int get_cols() const {
		return cols;
	}

	int get_data(int i, int j) const{
		return data[i][j];
	}

	void set_number(int rows, int cols, int number) {
		data[rows][cols] = number;
	}

	bool operator==(const Matrix& other) const {
		if (rows != other.rows || cols != other.cols) {
			return false;
		}

		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				if (data[i][j] != other.data[i][j]) {
					return false;
				}
			}
		}
		return true;
	}
	
	Matrix operator!() const {
		Matrix result(cols, rows);
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				result.data[j][i] = data[i][j];
			}
		}
		return result;
	}

	Matrix operator*(int number) const {
		Matrix result(rows, cols);
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				result.data[j][i] = data[i][j] * number;
			}
		}
		return result;
	}

	friend ostream& operator<<(ostream& os, const Matrix& matrix);
	friend istream& operator>>(istream& is, Matrix& matrix);

};

ostream& operator<<(ostream& os, const Matrix& matrix) {
	for (int i = 0; i < matrix.rows; ++i) {
		for (int j = 0; j < matrix.cols; ++j) {
			os << matrix.data[i][j] << " ";
		}
		os << endl;
	}
	return os;
}

istream& operator>>(istream& is, Matrix& matrix) {
	for (int i = 0; i < matrix.rows; ++i) {
		for (int j = 0; j < matrix.cols; ++j) {
			is >> matrix.data[i][j];
		}
	}
	return is;
}

int main() {

	string size;
	
	while (true) {
		cout << "Введите размерность матрицы: ";

		cin >> size;
		if (check(size)) {
			Matrix matrix(stoi(size), stoi(size));
			break;
		}
		else {
			cout << "Введите размерность матрицы, а не символы.\n";
		}
	}
	for (int i = 0; i < stoi(size); i++) {
		for (int j = 0; j < stoi(size); j++) {
			matrix.set_number(i, j, rand());
		}
	}
	cout << "Матрица: \n";
	for (int i = 0; i < stoi(size); i++) {
		for (int j = 0; j < stoi(size); j++) {
			cout << matrix.get_data(i, j) << " ";
		}
		cout << "\n";
	}
	cout << "\n";

	do {
		cout << "\n1.Вывести транспорированную матрицу\n2.Матрицу умноженную на 2.\n3.Проверить равны ли матрицы.\n4.Чтобы выйти из программы.\nВведите номер операции:";

		string flag;
		cin >> flag;
		if (check(flag)) {

			if (stoi(flag) == 1) {
				Matrix matrix_2 = !matrix;
				cout << "Транспорированная матрица:\n" << matrix_2 << endl;
			}
			if (stoi(flag) == 2) {
				Matrix matrix_3 = matrix * 2;
				cout << "Матрица умноженная на 2:\n" << matrix_3 << endl;
			}if (stoi(flag) == 3) {
				Matrix matrix_3 = matrix * 2;
				if (matrix == matrix_3) {
					cout << "Матрицы равны\n";
				}
				else {
					cout << "Матрицы не равны\n";
				}
			}
			if (stoi(flag) == 4) {
				break;
			}

		}
		else {
			cout << "Введите номер операции, а не символы.\n";
		}
	} while (true);

}