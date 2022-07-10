#include <locale.h>
#include <iostream>
#include <string>

using namespace std;

class Matrix {
private:
    int** vals;
    int size;
    string name;
public:
    Matrix() { // конструктор по умолчанию
        this->size = 0;
        this->vals = NULL;
    }
    
    Matrix(int n) { // конструктор с аргументом
        this->size = n;
        this->vals = new int* [n];
        for (int i = 0; i < n; ++i) {
            this->vals[i] = new int[n];
        }
    }
    
    Matrix(int n, int** vals) : Matrix(n) { // делегирующий конструктор с заданной матрицей
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                this->vals[i][j] = vals[i][j];
            }
        }
    }
    
    Matrix(int n, int** vals, string name) : Matrix(n, vals) {
        this->name = name;
    }
    Matrix(string name) : Matrix() { this->name = name; }
    Matrix(const Matrix& A) : Matrix(A.size, A.vals) {} // конструктор копирования
    Matrix(const Matrix& A, string name) : Matrix(A) { this->name = name; }
    
    ~Matrix() { // деструктор класса
        if (vals != NULL) {
            for (int i = 0; i < size; ++i) {
                delete vals[i];
            }
        }
    }
    void print() { // печатаем матрицу
        if (this->vals != NULL) {
            for (int i = 0; i < this->size; ++i) {
                for (int j = 0; j < this->size; ++j) {
                    cout << this->vals[i][j] << " ";
                }
                cout << endl;
            }
        }
        else { cout << "Матрицы нет" << endl; }
    }

    void printData() { // печатаем  все данные по объекту 
        cout << "матрица " << this->name << "; размер: " << this->size << endl;
        this->print();
    }

    void set(int n, int** vals, string name) { // установка (замена) всех значений
        this->setVals(n, vals);        
        this->setName(name);
    }
    void setName(string name) { this->name = name; }  // установка названия
    void setVals(int n, int** vals) { // установка матрицы и размера 
        this->size = n;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                this->vals[i][j] = vals[i][j];
            }
        }
    }
    void clear() { // очищаем данные класса
        for (int i = 0; i < size; ++i) {
            delete vals[i];
        }
        vals = NULL;
        size = 0;
        name = "";
    }

    friend Matrix operator / (const Matrix& A, const int b); // дрежуственный перегруженный оператор деления на целочисленное значения
    Matrix operator = (Matrix &A) { // перегруженный оператор присваивания       
        
        if (this->vals != NULL) {
            for (int i = 0; i < size; ++i) {
                delete vals[i];
            }
        }
        size = A.size;
        name = A.name;
        vals = new int* [size];
        for (int i = 0; i < size; ++i) {
            vals[i] = new int[size];
        }
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                vals[i][j] = A.vals[i][j];
            }
        }

        return *this;
    }
};

Matrix operator / (const Matrix& A, const int b) { // сама дружественная функция
    int ** vals = new int* [A.size];
    for (int i = 0; i < A.size; ++i) {
        vals[i] = new int[A.size];
    }

    for (int i = 0; i < A.size; ++i) {
        for (int j = 0; j < A.size; ++j) {
            vals[i][j] = A.vals[i][j] / b;
        }
    }
    Matrix *C = new Matrix(A.size, vals, "new C");
    return *C;
}

int main()
{
    setlocale(0, "rus");
    srand(time(0));
    int b, optEnter, n = 0;
    cout << "Какова размерность матрицы?   ";
    cin >> n;
    if (n > 0) {
        int** vals = new int* [n];
        for (int i = 0; i < n; ++i) {
            vals[i] = new int[n];
        }
        cout << "Введете матрицу A вручную (1) или сгенерируете (2)?   ";
        cin >> optEnter;

        switch (optEnter)
        {
        case 1:
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    cin >> vals[i][j];
                }
            }
            break;
        case 2:
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    vals[i][j] = rand() % 50;
                }
            }
            break;
        default:
            cout << "Этого действия не предполагалось, пока!";
            return 0;
        }
        cout << "Вот что получилось: " << endl;
        Matrix A(n, vals, "A");
        A.printData();
        cout << "На какое целочисленное значение поделим матрицу?  ";
        cin >> b;
        cout << "Время разделить маааатрицу!.." << endl;
        Matrix C = (A / b);
        C.printData();
    }
    return 0;
}

