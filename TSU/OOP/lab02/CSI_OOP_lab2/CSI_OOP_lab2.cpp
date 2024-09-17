#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class Array {
private:
    int* a; //Указатель на массив
    int n; // Число элементов в массиве
    int mem; // Память, выделенная под массив
    
    // Сдвиг влево, начиная с позиции pos + 1
    void ShiftLeft(int pos) {
        for (int i = 0; i < n - 1; i++) {
            a[i] = a[i + 1];
        }
        n--;
    }

public:
    // Конструктор с целым аргументом (м - число элементов в массиве) и по умолчанию
    // В зададнии есть разрешение на объединение этих конструкторов
    Array(int m = 1) {
        n = m;
        mem = m;
        a = new int[n];
    }
    // Конструктор с аргументом, m - число элементов в массиве b
    Array(int *b, int m) {
        n = m;
        mem = m;
        a = new int[n];
        for (int i = 0; i < n; i++) {
            a[i] = b[i];
        }
    }
    // Конструктор копирования
    Array(const Array& x) {
        n = x.n;
        mem = x.mem;
        a = new int[n];
        for (int i = 0; i < n; i++) {
            a[i] = x.a[i];
        }
    }
    // Операция присвоения
    Array& operator = (const Array& x) {
        if (this == &x) {
            return *this;
        }
        delete[] a;
        n = x.n;
        mem = x.mem;
        a = new int[n];
        for (int i = 0; i < n; i++) {
            a[i] = x.a[i];
        }
        return *this;
    }
    // Деконструктор
    ~Array() {
        delete[] a;
    }
    // Ввод массива из m чисел
    void Scan(int m) {
        n = m;
        mem = m;
        a = new int[n];
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
    }
    // Вывод массива
    void Print() {
        for (int i = 0; i < n; i++) {
            cout << a[i] << " ";
        }
    }
    // Считывание элемента по позиции
    int& operator[](int i) {
        return a[i];
    }
    // Поиск элемента key в массиве (возвращаем индекс key или -1)
    int FindKey(int key) {
        for (int i = 0; i < n; i++) {
            if (a[i] == key) {
                return i;
            }
        }
        return -1;
    }
    // Добавляем key в конец массива
    Array& operator += (int key) {
        if (n < mem) {
            a[n] = key;
            n++;
        }
        else {
            // Выделяем новую память, например, удваиваем текущий размер массива
            int newMem = mem * 2;
            int* newArray = new int[newMem];

            // Копируем существующие элементы в новый массив
            for (int i = 0; i < n; i++) {
                newArray[i] = a[i];
            }

            // Освобождаем старую память
            delete[] a;

            // Указываем на новый массив и обновляем память
            a = newArray;
            mem = newMem;

            // Добавляем новый элемент
            a[n] = key;
            n++;
        }
        return *this;
    }
    // Формирование массива b = a + key (key добавляется в конец)
    Array operator+(int key) {
        Array b(*this); // Создаем копию массива a
        if (b.n < b.mem) {
            b.a[b.n] = key; // Добавляем элемент key в конец массива b
            b.n++;
        }
        else {
            // Выделяем новую память, например, удваиваем текущий размер массива
            int newMem = b.mem * 2;
            int* newArray = new int[newMem];

            // Копируем существующие элементы из a в новый массив
            for (int i = 0; i < b.n; i++) {
                newArray[i] = b.a[i];
            }

            // Освобождаем старую память массива a
            delete[] b.a;

            // Указываем на новый массив и обновляем память и размер
            b.a = newArray;
            b.mem = newMem;

            // Добавляем новый элемент key в конец массива b
            b.a[b.n] = key;
            b.n++;
        }
        return b;
    }
    // Добавление массива в конец массива a
    Array& operator +=(Array x) {
        if (n + x.n < mem) {
            for (int i = 0; i < x.n; i++) {
                a[n + i] = x.a[i];
            }
            n += x.n;
        }
        else {
            // Плюсуем память двух массивов и создаем новый динамический
            int newMem = mem + x.mem;
            int* newArray = new int[newMem];

            // Копируем существующие элементы из a в новый массив
            for (int i = 0; i < n; i++) {
                newArray[i] = a[i];
            }
            for (int i = 0; i < x.n; i++) {
                newArray[n + i] = x.a[i];
            }

            // Освобождаем старую память массива a
            delete[] a;

            // Указываем на новый массив и обновляем память и размер
            a = newArray;
            mem = newMem;
            
            // Указываем новое количество элементов массива
            n = n + x.n;
        }
        return *this;
    }
    // Формирование массива y = a + x
    Array operator+(Array x) {
        Array y(n + x.n);
        for (int i = 0; i < n; i++) {
            y.a[i] = a[i];
        }
        for (int i = 0; i < x.n; i++) {
            y.a[n + i] = x.a[i];
        }
        y.n = n + x.n;
        return y;
    }
    // Удаление элемента key
    Array& operator -=(int key) {
        int pos = FindKey(key);
        if (pos != -1) {
            ShiftLeft(pos);
        }
        return *this;
    }
    // Формирование нового массива b = a - key
    Array operator - (int key) {
        Array b(*this);
        int pos = b.FindKey(key);
        if (pos != -1) {
            b.ShiftLeft(pos);
        }
        return *this;
    }
    // Удаление элемента с позиции pos
    Array& DelPosEq(int pos) {
        if (pos >= 0 && pos < n) {
            ShiftLeft(pos);
        }
        return *this;
    }
    // Формирование нового массива b, в котором удален элемент с позиции pos
    Array DelPosNew(int pos) {
        if (pos < 0 || pos >= n) {
            // Если заданная позиция некорректна, просто вернуть копию текущего массива
            return *this;
        }

        Array b(n - 1); // Создаем новый массив b с размером на 1 элемент меньше

        int j = 0; // Индекс для массива b

        for (int i = 0; i < n; i++) {
            if (i != pos) {
                b.a[j] = a[i];
                j++;
            }
        }

        return b;
    }

    // Проверка равенства массивов
    bool operator == (Array x) {
        if (n != x.n) {
            return false;
        }
        for (int i = 0; i < n; i++) {
            if (a[i] != x.a[i])
                return false;
        }
        return true;
    }
    // Проверка неравенства массивов
    bool operator != (Array x) {
        return !(*this == x);
    }
    // Нахождение максимума в массиве, возвращает индекс максимального элемента
    int Max() {
        int maxVal = 0;
        int maxInd = 0;
        for (int i = 0; i < n; i++) {
            if (a[i] > maxVal) {
                maxVal = a[i];
                maxInd = i;
            }
        }
        return maxInd;
    }
    // Нахождение минимума в массиве
    int Min() {
        int minVal = a[0];
        int minInd = 0;
        for (int i = 0; i < n; i++) {
            if (a[i] < minVal) {
                minVal = a[i];
                minInd = i;
            }
        }
        return minInd;
    }
    // Сортировка пузырьком
    void Sorting() {
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (a[j] > a[j + 1]) {
                    int temp = a[j];
                    a[j] = a[j + 1];
                    a[j + 1] = temp;
                }
            }
        }
    }
    //
    friend ostream& operator << (ostream& r, Array& x);
    friend istream& operator >> (istream& r, Array& x);
    };

int main()
{
    setlocale(LC_ALL, "Russian");

    // Тест 1
    Array mas1;
    cout << "Введите числа массива через пробел: ";
    mas1.Scan(5);
    cout << "Элементы массива 'mas1': ";
    mas1.Print();
    cout << "\n";

    // Тест 2
    Array mas2(mas1);
    cout << "Элементы массива 'mas2': ";
    mas2.Print();
    cout << "\n";

    // Тест 3
    if (mas1 == mas2) {
        cout << "Массивы mas1 и mas2 равны" << "\n";
    }
    else {
        cout << "Массивы mas1 и mas2 не равны" << "\n";
    }

    // Тест 4
    mas1 += 6;
    cout << "Элементы массива 'mas1': ";
    mas1.Print();
    cout << "\n";
    if (mas1 == mas2) {
        cout << "Массивы mas1 и mas2 равны" << "\n";
    }
    else {
        cout << "Массивы mas1 и mas2 не равны" << "\n";
    }
    // Тест 5
    Array mas3 = mas1 + 7;
    cout << "Элементы массива 'mas3': ";
    mas3.Print();
    cout << "\n";

    // Тест 6
    mas3.DelPosEq(0);
    cout << "Элементы массива 'mas3': ";
    mas3.Print();
    cout << "\n";

    // Тест 7
    Array mas4 = mas3.DelPosNew(5); 
    cout << "Элементы массива 'mas4': ";
    mas4.Print();
    cout << "\n";

    // Тест 8
    mas1.DelPosEq(1);
    if (mas1 == mas4) {
        cout << "Массивы mas1 и mas4 равны" << "\n";
    }
    else {
        cout << "Массивы mas1 и mas4 не равны" << "\n";
    }

    // Тест 9
    
    // Инициализируем генератор случайных чисел
    srand(time(0));

    int n = 10;
    int* b = new int[n];
    for (int i = 0; i < n; i++) {
        b[i] = rand() % 100;
    }
    Array mas5(b, n);
    /*cout << "Элементы массива 'mas5': ";
    mas5.Print();
    cout << "\n";*/

    // Тест 10
    cout << "Максимальный индекс = " << mas5.Max() << "; "
        << "Максимальное число = " << mas5[mas5.Max()] << "\n";
    cout << "Минимальный индекс = " << mas5.Min() << "; "
        << "Минимальное число = " << mas5[mas5.Min()]  << "\n";

    // Тест 11
    mas5.Sorting();
    cout << "Отсортированные элементы массива 'mas5': ";
    mas5.Print();
    cout << "\n";

    // Тест 12
    Array mas6 = mas1 + mas5;
    cout << "Элементы массива 'mas6': ";
    mas6.Print();
    cout << "\n";

    // Тест 13
    Array mas7(4);
    cout << "Введите числа массива через пробел: ";
    mas7.Scan(4);

    // Тест 14
    if (mas7.FindKey(1) == -1) {
        cout << "Данного элемента нет в массиве" << "\n";
    }
    else {
        cout << "Индекс элемента в массиве = " << mas7.FindKey(1) << "\n";
    }
    if (mas7.FindKey(10) == -1) {
        cout << "Данного элемента нет в массиве" << "\n";
    }
    else {
        cout << "Индекс элемента в массиве = " << mas7.FindKey(10) << "\n";
    }

    // Тест 15
    mas4 += mas7;
    cout << "Элементы изменённого массива 'mas4' (+mas7): ";
    mas4.Print();
    cout << "\n";

    // Тест 16
    mas4 = mas6;
    cout << "Присвоение mas4 = mas6: ";
    mas4.Print();
    cout << "\n";
    return 0;
}