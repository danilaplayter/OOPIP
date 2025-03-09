#include <iostream>
#include <climits> 
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

class TwoDimensionalArray {
private:
    int** array;  
    int size;    
public:
    
    TwoDimensionalArray(int n) : size(n) {
        array = new int* [size];
        for (int i = 0; i < size; ++i) {
            array[i] = new int[size];
        }
    }

    ~TwoDimensionalArray() {
        for (int i = 0; i < size; ++i) {
            delete[] array[i];
        }
        delete[] array;
    }

    void fillArray() {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                array[i][j] = rand();
            }
        }
    }

    int findMinBelowDiagonal() {
        int min_val = INT_MAX;
        for (int i = 1; i < size; ++i) {
            for (int j = 0; j < i; ++j) {
                if (array[i][j] < min_val) {
                    min_val = array[i][j];
                }
            }
        }
        return min_val;
    }

    int findMaxAboveDiagonal() {
        int max_val = INT_MIN;
        for (int i = 0; i < size; ++i) {
            for (int j = i + 1; j < size; ++j) {
                if (array[i][j] > max_val) {
                    max_val = array[i][j];
                }
            }
        }
        return max_val;
    }

    void printArray() {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                cout << array[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    int n;
    cout << "Введите размер квадратного массива: ";
    cin >> n;

    TwoDimensionalArray arr(n);

    arr.fillArray();
    cout << "Массив:" << endl;
    arr.printArray();

    do {
        
        cout << "\n1. Вывести минимальный элемент ниже главной диагонали.\n2. Вывести максимальный элемент выше гланой диагонили.\n3. Закончить программу.\nВведите номер оперции: ";

        string flag;
        cin >> flag;
        if (check(flag)) {
            if (stoi(flag) == 1) {
                int min_below_diagonal = arr.findMinBelowDiagonal();
                cout << "Минимальный элемент ниже главной диагонали: " << min_below_diagonal << endl;
            }
            if(stoi(flag) == 2){
                int max_above_diagonal = arr.findMaxAboveDiagonal();
                cout << "Максимальный элемент выше главной диагонали: " << max_above_diagonal << endl;
            }
            if (stoi(flag) == 3) {
                break;
            }
        }
        else {
            cout << " Введите число, а не символы.";
        }
    } while (true);
}