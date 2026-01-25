#include <iostream>
#include <cmath>
#include <stdexcept>
#include <string>
#include <Windows.h>
using namespace std;

struct Complex {
    double x, y;
};

struct Polar {
    double radius;
    double angle;
};


class EmptyException {};

class ParamException {
public:
    double x, y;
    ParamException(double _x, double _y) : x(_x), y(_y) {}
};

class ComplexException : public std::exception {
    string msg;
public:
    ComplexException(string m) : msg(std::move(m)) {}
    const char* what() const noexcept override {
        return msg.c_str();
    }
};

Polar toPolar1(const Complex& z)
{
    if (isnan(z.x) || isnan(z.y))
        throw invalid_argument("Параметри не є числами!");

    if (z.x == 0 && z.y == 0)
        throw ComplexException("Радіус = 0, кут не визначено!");

    Polar p;
    p.radius = sqrt(z.x * z.x + z.y * z.y);
    p.angle = atan2(z.y, z.x);
    return p;
}

Polar toPolar2(const Complex& z) throw()
{
    Polar p{ -1, -1 };

    if (z.x == 0 && z.y == 0)
        return p;

    p.radius = sqrt(z.x * z.x + z.y * z.y);
    p.angle = atan2(z.y, z.x);
    return p;
}

Polar toPolar3(const Complex& z) throw(std::invalid_argument)
{
    if (z.x == 0 && z.y == 0)
        throw invalid_argument("Комплексне число не може бути 0+0i");

    Polar p;
    p.radius = sqrt(z.x * z.x + z.y * z.y);
    p.angle = atan2(z.y, z.x);
    return p;
}

Polar toPolar4(const Complex& z) throw(ParamException)
{
    if (z.x == 0 && z.y == 0)
        throw ParamException(z.x, z.y);

    Polar p;
    p.radius = sqrt(z.x * z.x + z.y * z.y);
    p.angle = atan2(z.y, z.x);
    return p;
}

int main()
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    Complex z;
    cout << "Введіть x: ";
    cin >> z.x;
    cout << "Введіть y: ";
    cin >> z.y;

    cout << "\n--- Тестуємо функції ---\n";

    try {
        Polar p1 = toPolar1(z);
        cout << "toPolar1: R=" << p1.radius << " angle=" << p1.angle << endl;
    }
    catch (const ComplexException& e) {
        cout << "[toPolar1] ComplexException: " << e.what() << endl;
    }
    catch (const invalid_argument& e) {
        cout << "[toPolar1] invalid_argument: " << e.what() << endl;
    }

    Polar p2 = toPolar2(z);
    if (p2.radius < 0)
        cout << "[toPolar2] ПОМИЛКА (cannot throw exceptions)" << endl;
    else
        cout << "toPolar2: R=" << p2.radius << " angle=" << p2.angle << endl;

    try {
        Polar p3 = toPolar3(z);
        cout << "toPolar3: R=" << p3.radius << " angle=" << p3.angle << endl;
    }
    catch (const invalid_argument& e) {
        cout << "[toPolar3] invalid_argument: " << e.what() << endl;
    }

    try {
        Polar p4 = toPolar4(z);
        cout << "toPolar4: R=" << p4.radius << " angle=" << p4.angle << endl;
    }
    catch (const ParamException& e) {
        cout << "[toPolar4] ParamException: (" << e.x << ", " << e.y << ")" << endl;
    }

    return 0;
}
