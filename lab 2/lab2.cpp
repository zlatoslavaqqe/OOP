#include <iostream>
#include <string>
#include <sstream>
#include <windows.h>
using namespace std;

class Bankomat
{
private:
    int id;                 // ідентифікаційний номер банкомата
    int minWithdraw;        // мінімальна сума, яку можна зняти
    int maxWithdraw;        // максимальна сума на день

    // Кількість купюр кожного номіналу
    int n10, n20, n50, n100, n200, n500, n1000;

    // Підрахунок загальної суми
    int totalMoney() const
    {
        return n10 * 10 + n20 * 20 + n50 * 50 + n100 * 100 +
            n200 * 200 + n500 * 500 + n1000 * 1000;
    }

public:
    bool Init(int _id, int minW, int maxW)
    {
        if (_id <= 0 || minW <= 0 || maxW <= 0 || minW > maxW)
            return false;

        id = _id;
        minWithdraw = minW;
        maxWithdraw = maxW;

        n10 = n20 = n50 = n100 = n200 = n500 = n1000 = 0;

        return true;
    }

    // метод Read() 
    void Read()
    {
        int _id, minW, maxW;

        do {
            cout << "Введіть ID банкомата: ";
            cin >> _id;
            cout << "Мінімальна сума для зняття: ";
            cin >> minW;
            cout << "Максимальна сума для зняття: ";
            cin >> maxW;

        } while (!Init(_id, minW, maxW));
    }

    // Завантаження купюр
    void loadCash()
    {
        cout << "\n--- Завантаження купюр у банкомат ---\n";
        cout << "Кількість купюр по 10: "; cin >> n10;
        cout << "Кількість купюр по 20: "; cin >> n20;
        cout << "Кількість купюр по 50: "; cin >> n50;
        cout << "Кількість купюр по 100: "; cin >> n100;
        cout << "Кількість купюр по 200: "; cin >> n200;
        cout << "Кількість купюр по 500: "; cin >> n500;
        cout << "Кількість купюр по 1000: "; cin >> n1000;
    }

    // Зняття грошей
    bool withdraw(int sum)
    {
        if (sum < minWithdraw)
        {
            cout << "Помилка: сума менша за мінімально дозволену.\n";
            return false;
        }
        if (sum > maxWithdraw)
        {
            cout << "Помилка: сума перевищує ліміт.\n";
            return false;
        }
        if (sum > totalMoney())
        {
            cout << "Помилка: у банкоматі недостатньо грошей.\n";
            return false;
        }

        int s = sum;

        // жадібний алгоритм видачі
        int take1000 = min(n1000, s / 1000); s -= take1000 * 1000;
        int take500 = min(n500, s / 500);  s -= take500 * 500;
        int take200 = min(n200, s / 200);  s -= take200 * 200;
        int take100 = min(n100, s / 100);  s -= take100 * 100;
        int take50 = min(n50, s / 50);   s -= take50 * 50;
        int take20 = min(n20, s / 20);   s -= take20 * 20;
        int take10 = min(n10, s / 10);   s -= take10 * 10;

        if (s != 0)
        {
            cout << "Неможливо видати таку суму через відсутність потрібних номіналів.\n";
            return false;
        }

        // оновлюємо залишок
        n1000 -= take1000;
        n500 -= take500;
        n200 -= take200;
        n100 -= take100;
        n50 -= take50;
        n20 -= take20;
        n10 -= take10;

        cout << "Успішно видано " << sum << " грн\n";
        return true;
    }

    // метод Display()
    void Display()
    {
        cout << "\n--- Інформація про банкомат ---\n";
        cout << "ID: " << id << "\n";
        cout << "Мінімальна сума: " << minWithdraw << "\n";
        cout << "Максимальна сума: " << maxWithdraw << "\n";
        cout << "Залишок у банкоматі: " << totalMoney() << " грн\n";
    }

    // метод toString()
    string toString()
    {
        stringstream ss;
        ss << "Баланс банкомата: " << totalMoney() << " грн\n"
            << "10: " << n10 << ", 20: " << n20 << ", 50: " << n50
            << ", 100: " << n100 << ", 200: " << n200
            << ", 500: " << n500 << ", 1000: " << n1000;
        return ss.str();
    }
};

int main()
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    Bankomat b;

    b.Read();
    b.loadCash();
    b.Display();

    int sum;
    cout << "\nВведіть суму для зняття: ";
    cin >> sum;
    b.withdraw(sum);

    cout << "\n" << b.toString() << endl;

    return 0;
}
