#include <iostream>
#include <cmath>
#include <Windows.h>
using namespace std;

class Triangle {
public:
    virtual ~Triangle() {}

    virtual double area() const = 0;
    virtual double perimeter() const = 0;

    virtual double sideA() const = 0;
    virtual double sideB() const = 0;
    virtual double sideC() const = 0;

    double medianA() const {
        double a = sideA(), b = sideB(), c = sideC();
        return 0.5 * sqrt(2 * (b * b + c * c) - a * a);
    }
    double medianB() const {
        double a = sideA(), b = sideB(), c = sideC();
        return 0.5 * sqrt(2 * (a * a + c * c) - b * b);
    }
    double medianC() const {
        double a = sideA(), b = sideB(), c = sideC();
        return 0.5 * sqrt(2 * (a * a + b * b) - c * c);
    }

    double midlineA() const { return sideA() / 2.0; }
    double midlineB() const { return sideB() / 2.0; }
    double midlineC() const { return sideC() / 2.0; }
};


class TriangleByVertices : public Triangle {
    double x1, y1, x2, y2, x3, y3;

    static double dist(double x1, double y1, double x2, double y2) {
        return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    }

public:
    TriangleByVertices(double X1, double Y1,
        double X2, double Y2,
        double X3, double Y3)
        : x1(X1), y1(Y1), x2(X2), y2(Y2), x3(X3), y3(Y3)
    {
    }

    double sideA() const override { return dist(x2, y2, x3, y3); }
    double sideB() const override { return dist(x1, y1, x3, y3); }
    double sideC() const override { return dist(x1, y1, x2, y2); }

    double perimeter() const override {
        return sideA() + sideB() + sideC();
    }

    double area() const override {
        double a = sideA(), b = sideB(), c = sideC();
        double p = perimeter() / 2;
        return sqrt(p * (p - a) * (p - b) * (p - c));
    }
};

class TriangleBySides : public Triangle {
protected:
    double a, b, c;

public:
    TriangleBySides(double A, double B, double C)
        : a(A), b(B), c(C)
    {
    }

    double sideA() const override { return a; }
    double sideB() const override { return b; }
    double sideC() const override { return c; }

    double perimeter() const override {
        return a + b + c;
    }

    double area() const override {
        double p = perimeter() / 2;
        return sqrt(p * (p - a) * (p - b) * (p - c));
    }
};



class TriangleByMedians : public TriangleBySides {
private:

    static double sideFromMedians(double ma, double mb, double mc) {
        return (2.0 / 3.0) * sqrt(2 * (mb * mb + mc * mc) - ma * ma);
    }

public:
    TriangleByMedians(double ma, double mb, double mc)
        : TriangleBySides(
            sideFromMedians(ma, mb, mc),
            sideFromMedians(mb, mc, ma),
            sideFromMedians(mc, ma, mb)
        )
    {
    }
};

class RightTriangle : public TriangleBySides {
public:
    RightTriangle(double a, double b)
        : TriangleBySides(a, b, sqrt(a* a + b * b))
    {
    }

    double hypotenuse() const { return c; }

    double inradius() const {
        return (a + b - c) / 2.0;
    }
    double circumradius() const {
        return c / 2.0;
    }
};


int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    cout << "=== Поліморфізм трикутників ===\n";

    Triangle* t1 = new TriangleBySides(3, 4, 5);
    Triangle* t2 = new TriangleByVertices(0, 0, 3, 0, 0, 4);
    Triangle* t3 = new TriangleByMedians(5, 6, 7);
    Triangle* t4 = new RightTriangle(3, 4);

    Triangle* arr[] = { t1, t2, t3, t4 };

    for (Triangle* t : arr) {
        cout << "\nПлоща = " << t->area();
        cout << "\nПериметр = " << t->perimeter();
        cout << "\nМедіана до сторони a = " << t->medianA();
        cout << "\nСередня лінія паралельна стороні b = " << t->midlineB();

        if (auto rt = dynamic_cast<RightTriangle*>(t)) {
            cout << "\n>>> Вписане коло r = " << rt->inradius();
            cout << "\n>>> Описане коло R = " << rt->circumradius();
        }

        cout << "\n------------------------\n";
    }

    for (Triangle* t : arr) delete t;

    return 0;
}
