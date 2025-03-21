#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <list>
#include <vector>
#include <algorithm> 

class Student {
private:
    std::string fullName;       // ФИО студента
    std::string group;          // Группа студента
    std::string recordBookId;   // Номер зачетной книжки
    std::array<int, 4> grades;  // Массив оценок

public:
    // Конструктор по умолчанию
    Student() = default;

    // Конструктор с параметрами
    Student(const std::string& fullName, const std::string& group, const std::string& recordBookId, const std::array<int, 4>& grades)
        : fullName(fullName), group(group), recordBookId(recordBookId), grades(grades) {}

    // Метод для чтения данных из файла
    void readFromFile(std::ifstream& input) {
        if (input.is_open()) {
            std::getline(input, fullName);           // Читаем ФИО
            std::getline(input, group);             // Читаем группу
            std::getline(input, recordBookId);      // Читаем номер зачетной книжки
            for (int& grade : grades) {             // Читаем массив оценок
                input >> grade;
            }
            input.ignore(); // Пропускаем оставшийся символ новой строки
        }
    }

    // Метод print для вывода данных о студенте
    void print(std::ostream& os = std::cout) const {
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

        os << "]" << std::endl;
    }

    // Метод для получения полного имени (используется для сортировки)
    const std::string& getFullName() const {
        return fullName;
    }
};

int main() {
    // Открываем входной файл
    std::ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл input.txt" << std::endl;
        return 1;
    }

    // Создаем контейнер list для хранения студентов
    std::list<Student> studentList;

    // Читаем данные из файла и добавляем студентов в list
    while (!inputFile.eof()) {
        Student student;
        student.readFromFile(inputFile);
        studentList.push_back(student);
    }

    inputFile.close(); // Закрываем входной файл

    // Копируем данные из list в vector
    std::vector<Student> studentVector(studentList.begin(), studentList.end());

    // Сортируем студентов по имени в алфавитном порядке
    std::sort(studentVector.begin(), studentVector.end(), [](const Student& a, const Student& b) {
        return a.getFullName() < b.getFullName();
    });

    // Открываем выходной файл
    std::ofstream outputFile("output.txt");
    if (!outputFile.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл output.txt" << std::endl;
        return 1;
    }

    // Выводим данные о студентах из vector в файл (уже отсортированные)
    for (const auto& student : studentVector) {
        student.print(outputFile);
    }

    outputFile.close(); // Закрываем выходной файл

    return 0;
}
