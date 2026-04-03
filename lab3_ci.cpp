#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

using namespace std;

class File
{
    char* name;
    double size;
    char date[12];
    int accessCount;

public:
    File()
    {
        name = new char[1];
        name[0] = '\0';
        size = 0.0;
        strcpy(date, "01.01.2000");
        accessCount = 0;
    }

    File(const char* n, double s, const char* d, int ac)
    {
        name = new char[strlen(n) + 1];
        strcpy(name, n);
        size = s;
        strcpy(date, d);
        accessCount = ac;
    }

    File(const File& other)
    {
        cout << "Выполняется конструктор копии" << endl;
        name = new char[strlen(other.name) + 1];
        strcpy(name, other.name);
        size = other.size;
        strcpy(date, other.date);
        accessCount = other.accessCount;
    }

    ~File()
    {
        delete[] name;
    }

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

    void setName(const char* newName)
    {
        delete[] name;
        name = new char[strlen(newName) + 1];
        strcpy(name, newName);
    }

    void setSize(double newSize) { size = newSize; }
    void setDate(const char* newDate) { strcpy(date, newDate); }
    void setAccessCount(int newCount) { accessCount = newCount; }

    void decreaseSize() { size *= 0.85; }

    double getSize() const { return size; }
    const char* getDate() const { return date; }
    const char* getName() const { return name; }
    int getAccessCount() const { return accessCount; }

    void display() const
    {
        cout << "Имя файла: " << name << endl;
        cout << "Размер: " << size << " MB" << endl;
        cout << "Дата создания: " << date << endl;
        cout << "Количество обращений: " << accessCount << endl;
    }
};

void compareDate(File f, const char* targetDate)
{
    cout << endl << "В функции compareDate:" << endl;
    if (strcmp(f.getDate(), targetDate) == 0)
    {
        cout << "Дата создания файла \"" << f.getName() << "\" совпадает с заданной датой" << endl;
    }
    else
    {
        cout << "Дата создания файла \"" << f.getName() << "\" НЕ совпадает с заданной датой" << endl;
    }
}

File createFile(const char* name, double size, const char* date, int accessCount)
{
    return File(name, size, date, accessCount);
}

int main()
{
    cout << "ЛАБОРАТОРНАЯ РАБОТА 3 (ВАРИАНТ 10)" << endl;

    // а)
    cout << endl << "а) Создание и отображение объектов:" << endl;
    File file1("document.txt", 10.5, "15.03.2024", 5);
    cout << endl << "Исходный объект file1:" << endl;
    file1.display();

    cout << endl << "Создаём file2 = file1 (вызов конструктора копирования):" << endl;
    File file2 = file1;
    cout << endl << "file2 после копирования:" << endl;
    file2.display();

    cout << endl << "Уменьшаем размер file2 на 15%:" << endl;
    file2.decreaseSize();
    cout << endl << "file2 после уменьшения размера:" << endl;
    file2.display();

    // б)
    cout << endl << "б) Сравнение даты:" << endl;
    File userFile("report.pdf", 2.3, "20.05.2024", 3);
    cout << endl << "Созданный объект:" << endl;
    userFile.display();

    const char* targetDate = "20.05.2024";
    cout << endl << "Дата для сравнения: " << targetDate << endl;
    compareDate(userFile, targetDate);

    // в)
    cout << endl << "в) Создание и возврат объекта из функции:" << endl;
    File returnedFile = createFile("photo.jpg", 5.0, "01.01.2024", 10);
    cout << endl << "Возвращённый объект:" << endl;
    returnedFile.display();

    // г)
    cout << endl << "г) Изменение имени файла:" << endl;
    File renameFile("oldname.exe", 50.0, "10.01.2024", 100);
    cout << endl << "ДО изменения имени:" << endl;
    renameFile.display();

    renameFile.setName("newname.exe");
    cout << endl << "ПОСЛЕ изменения имени:" << endl;
    renameFile.display();

    cout << endl << "ПРОГРАММА ЗАВЕРШЕНА" << endl;
    return 0;
}