#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//Напишите информационную систему "Сотрудники".
//Программа должна обеспечивать ввод данных,
//редактирование данных сотрудника, 
//удаление сотрудника, 
//поиск сотрудника по фамилии, 
//вывод информации обо всех сотрудниках указанного возраста, 
//или фамилия которых начинается на указанную букву.
//Организуйте возможность сохранения найденной информации в файл.
//Также весь список сотрудников сохраняется в файл(при выходе из программы – автоматически, в процессе исполнения программы – по команде пользователя).
//При старте программы происходит загрузка списка сотрудников из указанного пользователем файла.

struct worker {
    string surname;
    string name;
    int age;
    string zarplata;
};

void add_new_worker();

void menu();

void save();

int n;//количество сотрудников
int choise = 666;
int size_mass = 5;//общий размер массива
worker* workers = new worker[size_mass];

ifstream infile("in.txt");//на чтение
ofstream outfile("out.txt");//на запись
void main()
{
    setlocale(LC_ALL, "RU");


    cout << "Введите количество сотрудников:" << endl;
    cin >> n;


    if (!infile.is_open())//если файл не откроется
    {
        cout << "Файл не может быть открыт" << endl;
    }
    else
    {
        for (int i = 0; i < n; i++)//считываю данные
        {
            infile >> workers[i].surname >> workers[i].name >> workers[i].age >> workers[i].zarplata;
        }
        //infile.close();
    }
    menu();
    while (choise != 0)
    {
        cin >> choise;
        switch (choise)
        {
        case 0: {cout << "Всего доброго" << endl; break; }
        case 1:
        {
            n++;//увеличиваю количество сотрудников
            if (n <= size_mass)//если количество сотрудников еще не превышает размер массива
            {
                add_new_worker();
            }

            else if (n > size_mass)//если уже превышает размер массива
            {
                worker* temp = new worker[size_mass];//создаю временный массив для хранения данных
                for (int i = 0; i < n - 1; i++)//копирую данные во временный массив
                {
                    temp[i].name = workers[i].name;
                    temp[i].surname = workers[i].surname;
                    temp[i].age = workers[i].age;
                    temp[i].zarplata = workers[i].zarplata;
                }
                delete[] workers;//удаляю старый массив
                size_mass = size_mass * 2;//увеличиваю размер массива
                worker* workers = new worker[size_mass];//создаю новый увеличенный массив
                for (int i = 0; i < n - 1; i++)//копирую данные в новый увеличенный массив
                {
                    workers[i].name = temp[i].name;
                    workers[i].surname = temp[i].surname;
                    workers[i].age = temp[i].age;
                    workers[i].zarplata = temp[i].zarplata;
                }

                add_new_worker();//заполняю данные о новом сотруднике

                delete[] temp;
            }
            cout << "\nСотрудник записан, можете сохранить изменения в файле (5)\n";
            menu();
            break;
        }

        case 4:
        {
            cout << endl;
            cout << "\nВаши сотрудники:\n";
            for (int i = 0; i < n; i++)// выводить и на консоль
            {
                cout << workers[i].surname << " " << workers[i].name << " " << workers[i].age << " " << workers[i].zarplata << endl;
            }
            cout << endl;
            menu();
            break;
        }

        case 5:
        {
            save();
            menu();
            break;
        }
        default: cout << "Неправильный номер" << endl;

            break;
        }
    }
    delete[] workers;
    size_mass = size_mass * 2;
    workers = new worker[size_mass];

    system("pause");
}

void menu() {
    cout << "Для ввода нового сотрудника нажмите 1" << endl;
    cout << "Для удаления сотрудника нажмите 2" << endl;
    cout << "Для поиска сотрудника нажмите 3" << endl;
    cout << "Для вывода всех сотрудников нажмите 4" << endl;
    cout << "Для сохранения изменений в файле нажмите 5" << endl;
    cout << "Для выхода нажмите 0" << endl;
}

void add_new_worker() {
    cout << "\nВведите фамилию нового сотрудника\n";
    cin >> workers[n - 1].surname;
    cout << "\nВведите имя нового сотрудника\n";
    cin >> workers[n - 1].name;
    cout << "\nВведите возраст нового сотрудника\n";
    cin >> workers[n - 1].age;
    cout << "\nВведите заработную плату нового сотрудника\n";
    cin >> workers[n - 1].zarplata;
}

void save() {
    for (int i = 0; i < n; i++)
        outfile << workers[i].surname << " " << workers[i].name << " " << workers[i].age << " " << workers[i].zarplata << endl;
    cout << "\nСотрудники записаны в файл out.txt\n" << endl;
}