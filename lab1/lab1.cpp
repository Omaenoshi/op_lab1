// lab1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <windows.h>
#include <conio.h>

struct Anketa
{
    char name[30];
    unsigned int age;
    unsigned int experience;
};

DWORD Bytes;

void addAnketa()
{
    HANDLE hfile = CreateFile(L"test_lock.dat",
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        OPEN_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    Anketa anketa;
    std::cout << "Enter the name:\n";
    std::cin >> anketa.name;
    std::cout << "Enter the age:\n";
    std::cin >> anketa.age;
    std::cout << "Enter the experience:\n";
    std::cin >> anketa.experience;
    SetFilePointer(hfile, 0, 0, FILE_END);
    WriteFile(hfile, &anketa, sizeof(Anketa), &Bytes, NULL);
    CloseHandle(hfile);
}

void printAnketa(Anketa anketa)
{
    std::cout << "Name: " + std::string(anketa.name) << "\n";
    std::cout << "Age: " << anketa.age << "\n";
    std::cout << "Experience: " << anketa.experience << "\n";
}

void rewriteAnketa()
{
    Anketa anketa;

    HANDLE hfile = CreateFile(L"test_lock.dat",
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        OPEN_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    std::cout << "Enter the number of the anketa\n";
    int num;
    std::cin >> num;

    SetFilePointer(hfile, sizeof(Anketa) * (num - 1), 0, FILE_BEGIN);
    ReadFile(hfile, &anketa, sizeof(Anketa), &Bytes, NULL);

    std::cout << "The old anketa: \n";
    printAnketa(anketa);

    std::cout << "Enter the new name:\n";
    std::cin >> anketa.name;
    std::cout << "Enter the new age:\n";
    std::cin >> anketa.age;
    std::cout << "Enter the new experience:\n";
    std::cin >> anketa.experience;
    SetFilePointer(hfile, sizeof(Anketa) * (num - 1), 0, FILE_BEGIN);
    WriteFile(hfile, &anketa, sizeof(Anketa), &Bytes, NULL);
    CloseHandle(hfile);
}

void readAnketa()
{
    Anketa anketa;

    HANDLE hfile = CreateFile(L"test_lock.dat",
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        OPEN_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    std::cout << "Enter the number of the anketa\n";
    int num;
    std::cin >> num;

    SetFilePointer(hfile, sizeof(Anketa) * (num - 1), 0, FILE_BEGIN);

    ReadFile(hfile, &anketa, sizeof(Anketa), &Bytes, NULL);

    printAnketa(anketa);
    _getch();
    CloseHandle(hfile);
}

void selectOp(int num)
{
    switch (num)
    {
    case 1:
        addAnketa();
        break;
    case 2:
        readAnketa();
        break;
    case 3:
        rewriteAnketa();
        break;
    default:
        break;
    }
}

int main()
{
    while (true)
    {
        system("cls");
        std::cout << "1.Add the new anketa.\n2.Read the anketa.\n3.Rewrite the anketa.\n4.Exit.\n";
        int num;
        std::cin >> num;
        if (num == 4) break;
        system("cls");
        selectOp(num);
    }

    std::cout << "Completed\n";
    _getch();
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
