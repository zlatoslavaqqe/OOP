#include "Bankomat.h"
#include <iostream>
#include <sstream>
#include <algorithm> 

using namespace std;

// Приватний метод для підрахунку суми
int Bankomat::totalMoney() const
{
    return n10 * 10 + n20 * 20 + n50 * 50 + n100 * 100 +
        n200 * 200 + n500 * 500 + n1000 * 1000;
}

// Конструктор за замовчуванням
Bankomat::Bankomat()
{
    id = 0;
    minWithdraw = 0;
    maxWithdraw = 0;
    n10 = n20 = n50 = n100 = n200 = n500 = n1000 = 0;
    cout << "[Конструктор за замовчуванням] Створено Bankomat\n";
}

// Конструктор з параметрами
Bankomat::Bankomat(int _id, int minW, int maxW)
{
    if (!Init(_id, minW, maxW))
    {
        id = 0;
        minWithdraw = 0;
        maxWithdraw = 0;
    }
    n10 = n20 = n50 = n100 = n200 = n500 = n1000 = 0;
    cout << "[Конструктор з параметрами] Створено Bankomat #" << id << "\n";
}

// Конструктор копіювання
Bankomat::Bankomat(const Bankomat& other)
{
    id = other.id;
    minWithdraw = other.minWithdraw;
    maxWithdraw = other.maxWithdraw;
    n10 = other.n10; n20 = other.n20; n50 = other.n50;
    n100 = other.n100; n200 = other.n200; n500 = other.n500;
    n1000 = other.n1000;
    cout << "[Конструктор копіювання] Копія банкомата #" << id << " створена\n";
}

// Деструктор
Bankomat::~Bankomat()
{
    cout << "[Деструктор] Bankomat #" << id << " знищено\n";
}

bool Bankomat::Init(int _id, int minW, int maxW)
{
    if (_id <= 0 || minW <= 0 || maxW <= 0 || minW > maxW)
        return false;

    id = _id;
    minWithdraw = minW;
    maxWithdraw = maxW;
    return true;
}

void Bankomat::Read()
{
    int _id, minW, maxW;
    do {
        cout << "Введіть ID банкомата: ";
        cin >> _id;
        cout << "Мінімальна сума: ";
        cin >> minW;
        cout << "Максимальна сума: ";
        cin >> maxW;
    } while (!Init(_id, minW, maxW));
}

void Bankomat::loadCash()
{
    cout << "\n--- Завантаження купюр ---\n";
    cout << "Купюр по 10:   "; cin >> n10;
    cout << "Купюр по 20:   "; cin >> n20;
    cout << "Купюр по 50:   "; cin >> n50;
    cout << "Купюр по 100:  "; cin >> n100;
    cout << "Купюр по 200:  "; cin >> n200;
    cout << "Купюр по 500:  "; cin >> n500;
    cout << "Купюр по 1000: "; cin >> n1000;
}

bool Bankomat::withdraw(int sum)
{
    if (sum < minWithdraw) {
        cout << "Сума менша за мінімальну.\n";
        return false;
    }
    if (sum > maxWithdraw) {
        cout << "Сума перевищує максимальний ліміт.\n";
        return false;
    }
    if (sum > totalMoney()) {
        cout << "У банкоматі недостатньо коштів.\n";
        return false;
    }

    int s = sum;
    // Жадібний алгоритм видачі (спрощена логіка з оригінального коду)
    int take1000 = min(n1000, s / 1000); s -= take1000 * 1000;
    int take500 = min(n500, s / 500);   s -= take500 * 500;
    int take200 = min(n200, s / 200);   s -= take200 * 200;
    int take100 = min(n100, s / 100);   s -= take100 * 100;
    int take50 = min(n50, s / 50);     s -= take50 * 50;
    int take20 = min(n20, s / 20);     s -= take20 * 20;
    int take10 = min(n10, s / 10);     s -= take10 * 10;

    if (s != 0) {
        cout << "Неможливо видати через відсутність потрібних номіналів.\n";
        return false;
    }

    // Якщо все добре, списуємо купюри
    n1000 -= take1000; n500 -= take500; n200 -= take200;
    n100 -= take100;   n50 -= take50;   n20 -= take20;
    n10 -= take10;

    cout << "Успішно видано " << sum << " грн\n";
    return true;
}

void Bankomat::Display()
{
    cout << "\n=== Інформація про банкомат ===\n";
    cout << "ID: " << id << "\n";
    cout << "Мінімум: " << minWithdraw << "\n";
    cout << "Максимум: " << maxWithdraw << "\n";
    cout << "Загальна сума: " << totalMoney() << " грн\n";
}

string Bankomat::toString()
{
    stringstream ss;
    ss << "Баланс: " << totalMoney() << " грн\n"
        << "10: " << n10 << " 20: " << n20
        << " 50: " << n50 << " 100: " << n100
        << " 200: " << n200 << " 500: " << n500
        << " 1000: " << n1000;
    return ss.str();
}
