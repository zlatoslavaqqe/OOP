#include <iostream>
#include <cmath>
#include <Windows.h>

class GeometricFigure {
protected:
    double x; //// Координата X центра фігури
    double y; // Координата Y центра фігури
    double angle; // Кут повороту в градусах
    double scale; // Масштабний фактор

public:
    GeometricFigure(double x, double y, double angle, double scale)
        : x(x), y(y), angle(angle), scale(scale) {}

    virtual void showOnScreen() const = 0; // Чисто віртуальна функція
    virtual void makeInvisible() = 0;
    void rotate(double rotationAngle) { angle += rotationAngle; }
    void translate(double dx, double dy) { x += dx; y += dy; }
};
    
class Line : public GeometricFigure {
public:
    Line(double x, double y, double angle, double scale)
        : GeometricFigure(x, y, angle, scale) {}

    void showOnScreen() const override {
        std::cout << "Пряма на екрані. Координати: (" << x << ", " << y << "), кут: " << angle << " градусів, масштаб: " << scale << std::endl;
    }

    void makeInvisible() override {
        std::cout << "Пряма прибрана з екрану." << std::endl;
    }
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Line line(0, 0, 45, 1.5);
    line.showOnScreen();

    line.rotate(30);
    line.showOnScreen();

    line.translate(2, 3);
    line.showOnScreen();

    line.makeInvisible();

    return 0;
}

