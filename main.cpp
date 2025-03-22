#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <list>
#include <vector>
#include <algorithm>
using namespace std;


/*В приложении организовать контейнер объектов своего класса (использовать
шаблоны std::list, std::vector или std::deque в зависимости от варианта, элементы
контейнера - объекты класса, не указатели!!!!). Варианты заданий заданы в ячейках
таблицы 1. Параметры приложений указаны в заголовках строк и столбцов таблицы 1.
Класс должен иметь необходимые конструкторы, конструктор копирования и
перемещения при необходимости (обосновать отсутствие или наличие необходимости),
перегруженные операции присваивания с копированием и перемещением. При
необходимости (обосновать отсутствие или наличие необходимости), перегруженную
операцию вставки в поток <<.
Обеспечить копирование одного контейнера в другой с помощью алгоритма
std::copy. А также сортировку объектов в исходном контейнере, для шаблона list при
сортировке использовать метод list::sort без параметров, для шаблона vector или deque
при сортировке использовать алгоритм std::sort с двумя параметрами: итератор на начало
и итератор на конец контейнера.
Исходные данные прочитать из текстового файла input.txt. Вывести в выходной
файл output.txt исходный контейнер, контейнер после сортировки, использовать при этом
перегруженную операцию вставки в поток, также вывести в выходной файл контейнер, в
который скопирован исходный контейнер.

Объект- студент(поля: ФИО, Группа, Номер зачетной книжки, Массив 4-х оценок за сессию).
Сортировка по ФИО.
*/

class Student {
private:
     string fullName;       // ФИО студента
     string group;          // Группа студента
     string recordBookId;   // Номер зачетной книжки
     array<int, 4> grades;  // Массив оценок

public:
    // Конструктор по умолчанию
    Student() = default;

    // Конструктор с параметрами
    Student(const  string& fullName, const  string& group, const  string& recordBookId, const  array<int, 4>& grades)
        : fullName(fullName), group(group), recordBookId(recordBookId), grades(grades) {}

    // Метод для чтения данных из файла
    void readFromFile( ifstream& input) {
        if (input.is_open()) {
             getline(input, fullName);           // Читаем ФИО
             getline(input, group);             // Читаем группу
             getline(input, recordBookId);      // Читаем номер зачетной книжки
            for (int& grade : grades) {             // Читаем массив оценок
                input >> grade;
            }
            input.ignore(); // Пропускаем оставшийся символ новой строки
        }
    }

    // Метод print для вывода данных о студенте
    void print( ostream& os =  cout) const {
        os << "ФИО: " << fullName
           << ", Группа: " << group
           << ", Зачетная книжка: " << recordBookId
           << ", Оценки: [";

        for (size_t i = 0; i < grades.size(); ++i) {
            os << grades[i];
            if (i < grades.size() - 1) {
                os << ", "; // Добавляем запятую между оценками
            }
        }

        os << "]" <<  endl;
    }

    // Метод для получения полного имени (используется для сортировки)
    const  string& getFullName() const {
        return fullName;
    }
};

int main() {
    // Открываем входной файл
     ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
         cerr << "Ошибка: не удалось открыть файл input.txt" <<  endl;
        return 1;
    }

    // Создаем контейнер list для хранения студентов
     list<Student> studentList;

    // Читаем данные из файла и добавляем студентов в list
    while (!inputFile.eof()) {
        Student student;
        student.readFromFile(inputFile);
        studentList.push_back(student);
    }

    inputFile.close(); // Закрываем входной файл

    // Копируем данные из list в vector
     vector<Student> studentVector(studentList.begin(), studentList.end());

    // Сортируем студентов по имени в алфавитном порядке
     sort(studentVector.begin(), studentVector.end(), [](const Student& a, const Student& b) {
        return a.getFullName() < b.getFullName();
    });

    // Открываем выходной файл
     ofstream outputFile("output.txt");
    if (!outputFile.is_open()) {
         cerr << "Ошибка: не удалось открыть файл output.txt" <<  endl;
        return 1;
    }

    // Выводим данные о студентах из vector в файл (уже отсортированные)
    for (const auto& student : studentVector) {
        student.print(outputFile);
    }

    outputFile.close(); // Закрываем выходной файл

    return 0;
}
