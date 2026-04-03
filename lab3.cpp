#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

using namespace std;

class File
{
    char* name;          // Имя файла
    double size;         // Размер файла
    char date[12];       // Дата создания (ДД.ММ.ГГГГ)
    int accessCount;     // Количество обращений

public:
    // Конструктор по умолчанию
    File()
    {
        name = new char[1];
        name[0] = '\0';
        size = 0.0;
        strcpy(date, "01.01.2000");
        accessCount = 0;
    }

    // Конструктор с параметрами
    File(const char* n, double s, const char* d, int ac)
    {
        name = new char[strlen(n) + 1];
        strcpy(name, n);
        size = s;
        strcpy(date, d);
        accessCount = ac;
    }

    // Конструктор копирования
    File(const File& other)
    {
        cout << "Выполняется конструктор копии" << endl;
        name = new char[strlen(other.name) + 1];
        strcpy(name, other.name);
        size = other.size;
        strcpy(date, other.date);
        accessCount = other.accessCount;
    }

    // Деструктор
    ~File()
    {
        delete[] name;
    }

    // Перегрузка оператора присваивания
    File& operator=(const File& other)
    {
        if (this != &other)
        {
            delete[] name;
            name = new char[strlen(other.name) + 1];
            strcpy(name, other.name);
            size = other.size;
            strcpy(date, other.date);
            accessCount = other.accessCount;
        }
        return *this;
    }

    // Методы set
    void setName(const char* newName)
    {
        delete[] name;
        name = new char[strlen(newName) + 1];
        strcpy(name, newName);
    }

    void setSize(double newSize)
    {
        size = newSize;
    }

    void setDate(const char* newDate)
    {
        strcpy(date, newDate);
    }

    void setAccessCount(int newCount)
    {
        accessCount = newCount;
    }

    // Метод для уменьшения размера на 15%
    void decreaseSize()
    {
        size *= 0.85;
    }

    // Методы get
    double getSize() const
    {
        return size;
    }

    const char* getDate() const
    {
        return date;
    }

    const char* getName() const
    {
        return name;
    }

    int getAccessCount() const
    {
        return accessCount;
    }

    // Метод отображения
    void display() const
    {
        cout << "Имя файла: " << name << endl;
        cout << "Размер: " << size << " MB" << endl;
        cout << "Дата создания: " << date << endl;
        cout << "Количество обращений: " << accessCount << endl;
    }
};

// Функция сравнения даты (принимает объект по значению)
void compareDate(File f, const char* targetDate)
{
    cout << "\n--- В функции compareDate ---" << endl;
    if (strcmp(f.getDate(), targetDate) == 0)
    {
        cout << "Дата создания файла \"" << f.getName() << "\" совпадает с заданной датой" << endl;
    }
    else
    {
        cout << "Дата создания файла \"" << f.getName() << "\" НЕ совпадает с заданной датой" << endl;
    }
}

// Функция создания файла с вводом пользователя (возвращает объект)
File createFile()
{
    char name[100];
    double size;
    char date[12];
    int accessCount;

    cout << "\nВведите имя файла: ";
    cin >> name;
    cout << "Введите размер (MB): ";
    cin >> size;
    cout << "Введите дату создания (ДД.ММ.ГГГГ): ";
    cin >> date;
    cout << "Введите количество обращений: ";
    cin >> accessCount;

    return File(name, size, date, accessCount);
}

// Функция для пункта а) - демонстрация конструктора копирования и уменьшения размера
void demoCopyAndDecrease()
{
    cout << "\nПункт а) Создание объекта, копирование, уменьшение размера на 15%" << endl;
    
    File file1("document.txt", 10.5, "15.03.2024", 5);
    
    cout << "\nИсходный объект file1:" << endl;
    file1.display();
    
    cout << "\nСоздаём file2 = file1 (вызов конструктора копирования):" << endl;
    File file2 = file1;
    
    cout << "\nfile2 после копирования:" << endl;
    file2.display();
    
    cout << "\nУменьшаем размер file2 на 15%:" << endl;
    file2.decreaseSize();
    
    cout << "\nfile2 после уменьшения размера:" << endl;
    file2.display();
}

// Функция для пункта б) - сравнение даты
void demoCompareDate()
{
    cout << "\nПункт б) Сравнение даты создания файла" << endl;
    
    cout << "\nСоздаём объект с данными от пользователя:" << endl;
    File userFile = createFile();
    
    cout << "\nСозданный объект:" << endl;
    userFile.display();
    
    char targetDate[12];
    cout << "\nВведите дату для сравнения (ДД.ММ.ГГГГ): ";
    cin >> targetDate;
    
    compareDate(userFile, targetDate);
}

// Функция для пункта в) - возврат объекта из функции
void demoReturnObject()
{
    cout << "\nПункт в) Создание и возврат объекта из функции" << endl;
    
    cout << "\nВызываем функцию createFile(), которая возвращает объект:" << endl;
    File returnedFile = createFile();
    
    cout << "\nВозвращённый объект:" << endl;
    returnedFile.display();
}

// Функция для пункта г) - изменение имени файла
void demoChangeName()
{
    cout << "\nПункт г) Изменение имени файла" << endl;
    
    File renameFile("oldname.exe", 50.0, "10.01.2024", 100);
    
    cout << "\nДО изменения имени:" << endl;
    renameFile.display();
    
    renameFile.setName("newname.exe");
    
    cout << "\nПОСЛЕ изменения имени:" << endl;
    renameFile.display();
}

void showMenu()
{
    cout << "\nМЕНЮ (Вариант 10 - класс File):" << endl;
    cout << "1. Создать объект, скопировать, уменьшить размер на 15%" << endl;
    cout << "2. Сравнить дату создания файла с заданной" << endl;
    cout << "3. Создать объект и вернуть его из функции" << endl;
    cout << "4. Изменить имя файла (до/после)" << endl;
    cout << "5. Выход" << endl;
    cout << "Ваш выбор: ";
}

int main()
{   
    int choice;
    do {
        showMenu();
        cin >> choice;
        
        switch (choice)
        {
        case 1:
            demoCopyAndDecrease();
            break;
        case 2:
            demoCompareDate();
            break;
        case 3:
            demoReturnObject();
            break;
        case 4:
            demoChangeName();
            break;
        case 5:
            cout << "\nВыход из программы..." << endl;
            break;
        default:
            cout << "\nОшибка! Введите число от 1 до 5." << endl;
        }
    } while (choice != 5);
    
    system("pause");
    return 0;
}