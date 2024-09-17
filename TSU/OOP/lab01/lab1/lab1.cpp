#define _USE_MATH_DEFINES
#include <iostream>
#include <math.h>
#include <cmath>

using namespace std;
// Класс координат для облегчения инициализации
class Coordinates
{
public:
    double x;
    double y;
};
// Класс прямоугольного треугольника
class Rectangular_Triangle
{
public:
    Coordinates A;
    double a;
    double b;

    // Конструктор по умолчанию
    Rectangular_Triangle() : a(0.0), b(0.0)
    {
        A.x = 0.0;
        A.y = 0.0;
    }
    // Конструктор с параметрами для инициализации
    Rectangular_Triangle(double x, double y, double a, double b) : a(a), b(b) 
    {
        A.x = x;
        A.y = y;
    }
    // Нахождение координаты B для прямоугольного треугольника
    Coordinates B;
    Coordinates find_B_coor() 
    {
        B.x = A.x;
        B.y = A.y - a;
        return B;
    }
    // Нахождение координаты C для прямоугольного треугольника
    Coordinates C;
    Coordinates find_C_coor() 
    {
        C.x = A.x + b;
        C.y = A.y - a;
        return C;
    }
    // Функция нахождения гипотенузы прямоугольного треугольника
    double find_hypotenuse()
    {
        double c = sqrt(a * a + b * b);
        return c;
    }
    /*double c = find_hypotenuse();*/
    // Функция нахождения площади прямоугольного треугольника
    double find_square()
    {
        double s = (a * b) / 2;
        return s;
    }
    /*double s = find_square();*/
    // Функция поиска периметра прямоугольного треугольника
    double find_perimeter()
    {
        double p = a + b + find_hypotenuse();
        return p;
    }
    // Функция поиска радиуса вписанной окружности прямоугольного треугольника
    double find_inscribed_circle()
    {
        double r = (a + b - find_hypotenuse()) / 2;
        return r;
    }
    // Функция поиска радиуса описанной окружности прямоугольного треугольника
    double find_circumscribed_circle()
    {
        double R = find_hypotenuse() / 2;
        return R;
    }
    // Функция поиска высоты прямоугольного треугольника
    double find_height()
    {
        double h = 2 * find_square() / (find_hypotenuse());
        return h;
    }
    // Функция поиска наименьшего угла прямоугольного треугольника
    double find_smaller_angle()
    {
        double angle;
        if (a >= b)
        {
            angle = (asin(b / find_hypotenuse())) * 180.0 / M_PI;
        }
        else
        {
            angle = (asin(a / find_hypotenuse())) * 180.0 / M_PI;
        }
        return angle;
    }
    // Функция проверки на равнобедренность прямоугольного треугольника
    void is_isosceles_triangle()
    {
        if (a == b)
        {
            cout << "Треугольник является равнобедренным";
        }
        else
        {
            cout << "Треугольник не является равнобедренным";
        }
    }
    // Функция умножения катета на константу
    void multiplication_constant()
    {
        double k;
        cout << "Введите k: ";
        cin >> k;
        double k_a = k * a;
        double k_b = k * b;
        cout << "Катеты, умноженные на К: " << k_a << " " << k_b;
    }
    // Функция проверки 2х треугольников на подобие внутри класса треугольника
    /*void is_similar(Rectangular_Triangle& other)
    {
        if (((a / other.a) == (b / other.b)) and ((b / other.b) == (c / other.c)))
        {
            cout << "Треугольники подобны";
        }
        else
        {
            cout << "Треугольники не подобны";
        }
    }*/
    // Функция ввода значений треугольника
    void cin_triangle()
    {
        cout << "Введите координату 'x' точки A: ";
        cin >> A.x;
        cout << "\n";
        cout << "Введите координату 'y' точки A: ";
        cin >> A.y;
        cout << "\n";
        cout << "Введите длину катета a: ";
        cin >> a;
        cout << "\n";
        cout << "Введите длину катета b: ";
        cin >> b;
        cout << "\n";
    }
    // Функция вывода вводимых значений треугольника
    void cout_triangle()
    {
        cout << "Координаты точки A: x = " << A.x << " y = " << A.y << "\n";
        cout << "\n";
        cout << "Длина катета a = " << a << " Длина катета b = " << b << "\n";
    }
};
// Функция для поиска расстояния между двумя координатами
double distance(Coordinates& point1, Coordinates& point2) 
{
    double dx, dy;
    if (point1.x > point2.x)
    {
        dx = abs(point1.x - point2.x);
    }
    else
    {
        dx = abs(point2.x - point1.x);
    }
    if (point1.y > point2.y)
    {
        dy = abs(point1.y - point2.y);
    }
    else
    {
        dy = abs(point2.y - point1.y);
    }

    return sqrt(dx * dx + dy * dy);
}
// Проверка двух треугольников на равенство (параллельный перенос)
void is_equal(Rectangular_Triangle& triangle1, Rectangular_Triangle& triangle2) 
{
    triangle1.find_B_coor();
    triangle2.find_B_coor();
    triangle1.find_C_coor();
    triangle2.find_C_coor();

    double equal1 = distance(triangle1.A, triangle2.A);
    double equal2 = distance(triangle1.B, triangle2.B);
    double equal3 = distance(triangle1.C, triangle2.C);

    if ((equal1 == equal2) and (equal2 == equal3)) {
        cout << "Треугольники равны по признаку параллельного переноса" <<"\n";
    }
    else {
        cout << "Треугольники не равны по признаку параллельного переноса" << "\n";
    }
}
// Функция проверки на подобие 2х треугольников вне класса прямоугольного треугольника 
void is_similar(Rectangular_Triangle& triangle1, Rectangular_Triangle& triangle2)
{
    if (((triangle1.a / triangle2.a) == (triangle1.b / triangle2.b)) and ((triangle1.b / triangle2.b) == (triangle1.find_hypotenuse() / triangle2.find_hypotenuse())))
    {
        cout << "Треугольники подобны";
    }
    else
    {
        cout << "Треугольники не подобны";
    }
}

int main() {

    setlocale(LC_ALL, "Russian");

    //Rectangular_Triangle triangle1(0, 0, 4, 3);
    Rectangular_Triangle triangle2(5, 9, 3, 5);

    Rectangular_Triangle triangle1;
    //Rectangular_Triangle triangle2;

    cout << "Введите значения треугольника 1: " << "\n";
    triangle1.cin_triangle();
    triangle1.cout_triangle();
    /*cout << "Введите значения треугольника 2: " << "\n";
    triangle2.cin_triangle();*/
   

    cout << "Гипотенуза: " << triangle1.find_hypotenuse();
    cout << "\n";
	cout << "Площадь: " << triangle1.find_square();
    cout << "\n";
    cout << "Периметр: " << triangle1.find_perimeter();
    cout << "\n";
    cout << "Вписанная окружность: " << triangle1.find_inscribed_circle();
    cout << "\n";
    cout << "Описанная окружность: " << triangle1.find_circumscribed_circle();
    cout << "\n";
    cout << "Высота: " << triangle1.find_height();
    cout << "\n";
    cout << "Меньший угол: " << triangle1.find_smaller_angle();
    cout << "\n";
    triangle1.is_isosceles_triangle();
    cout << "\n";
    triangle1.multiplication_constant();
    cout << "\n";
    is_equal(triangle1, triangle2);
    cout << "\n";
    is_similar(triangle1, triangle2);
    cout << "\n";

    
    return 0;
}