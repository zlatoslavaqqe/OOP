#include <iostream>
#include <windows.h>
#include "Bankomat.h" // Підключаємо наш заголовочний файл

using namespace std;

int main()
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    // Створюємо об'єкт, використовуючи код з бібліотеки
    Bankomat atm;
    atm.Read();
    atm.loadCash();

    int choice;

    while (true)
    {
        cout << "\n МЕНЮ БАНКОМАТА (Library Version) \n";
        cout << "1 — Показати стан банкомата\n";
        cout << "2 — Завантажити нові купюри\n";
        cout << "3 — Зняти гроші\n";
        cout << "4 — Показати детальний рядок (toString)\n";
        cout << "0 — Вихід\n";
        cout << "Ваш вибір: ";
        cin >> choice;

        if (choice == 0)
        {
            cout << "\nЗавершення роботи...\n";
            break;
        }

        if (choice == 1)
        {
            atm.Display();
        }
        else if (choice == 2)
        {
            atm.loadCash();
            cout << "\nКошти успішно додані!\n";
        }
        else if (choice == 3)
        {
            int sum;
            cout << "Сума для зняття: ";
            cin >> sum;
            atm.withdraw(sum);
        }
        else if (choice == 4)
        {
            cout << atm.toString() << endl;
        }
        else
        {
            cout << "Помилка: невірний пункт меню!\n";
        }
    }

    return 0;
}
