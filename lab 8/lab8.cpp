#include <iostream>
#include <Windows.h>
using namespace std;

class Triad {
protected:
    int a, b, c;

public:
    Triad(int a = 0, int b = 0, int c = 0)
        : a(a), b(b), c(c) {
    }

    virtual ~Triad() {}

    int getA() const { return a; }
    int getB() const { return b; }
    int getC() const { return c; }

    virtual bool operator<(const Triad& other) const {
        if (a != other.a) return a < other.a;
        if (b != other.b) return b < other.b;
        return c < other.c;
    }

    virtual bool operator>(const Triad& other) const {
        return other < *this;
    }

    virtual bool operator==(const Triad& other) const {
        return a == other.a && b == other.b && c == other.c;
    }

    bool operator!=(const Triad& other) const {
        return !(*this == other);
    }

    bool operator<=(const Triad& other) const {
        return *this < other || *this == other;
    }

    bool operator>=(const Triad& other) const {
        return *this > other || *this == other;
    }

    virtual void print() const {
        cout << "(" << a << ", " << b << ", " << c << ")";
    }
};

class Time : public Triad {
public:
    Time(int h = 0, int m = 0, int s = 0)
        : Triad(h, m, s)
    {
        normalize();
    }

    void normalize() {
        if (c >= 60) { b += c / 60; c %= 60; }
        if (b >= 60) { a += b / 60; b %= 60; }
        if (a >= 24) { a %= 24; }
    }

    int hour() const { return a; }
    int minute() const { return b; }
    int second() const { return c; }

    bool operator<(const Triad& other) const override {
        const Time* t = dynamic_cast<const Time*>(&other);
        if (t) {
            if (hour() != t->hour()) return hour() < t->hour();
            if (minute() != t->minute()) return minute() < t->minute();
            return second() < t->second();
        }
        return Triad::operator<(other);
    }

    void print() const override {
        cout << hour() << ":" << minute() << ":" << second();
    }
};

Triad processTriad(const Triad& t) {
    cout << "Обробляємо Triad: ";
    t.print();
    cout << endl;

    return Triad(t.getA() + 1, t.getB() + 1, t.getC() + 1);
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Triad t1(1, 5, 9);
    Time time1(12, 59, 59);
    Time time2(13, 0, 1);

    cout << "--- Базовий клас Triad ---\n";
    t1.print();
    cout << "\n";

    cout << "--- Похідний клас Time ---\n";
    time1.print();
    cout << "\n";

    cout << "\n--- Принцип підстановки ---\n";
    Triad result = processTriad(time1); 

    cout << "Результат processTriad: ";
    result.print();
    cout << "\n\n";

    cout << "--- Порівняння часу ---\n";
    time1.print();
    cout << (time1 < time2 ? " < " : " >= ");
    time2.print();
    cout << "\n";

    return 0;
}
