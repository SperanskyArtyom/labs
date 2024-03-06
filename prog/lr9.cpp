#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <utility>

using namespace std;

typedef struct StudentList
{
    string surname;
    int *grades{};
    StudentList *next{};
} StudentList;

void addStudent(StudentList **head, string surname, int *grade);
void sortBySurnames(StudentList **studentsArr, int size);

int main()
{
    srand(time(nullptr));
    // Задание 1
    StudentList *students = nullptr;
    string surnames[] = {"Сперанский", "Калашникова", "Фридрих", "Гуляев", "Брунилин", "Шильников", "Щукин", "Аникеев", "Цибулевич", "Халиков"};
    //  Генерируем список студентов
    for (const auto& surnameBuff : surnames)
    {
        int *gradeBuff = new int[4];
        for (int j = 0; j < 4; j++)
        {
            gradeBuff[j] = rand() % 4 + 2;
        }
        addStudent(&students, surnameBuff, gradeBuff);
    }
    auto **indexArr = new StudentList *[10];
    StudentList *currentStudent = students;
    for (int i = 0; i < 10; i++)
    {
        indexArr[i] = currentStudent;
        currentStudent = (*currentStudent).next;
    }
    sortBySurnames(indexArr, 10);
    for (int i = 0; i < 10; i++)
    {
        cout << (*indexArr[i]).surname << "   ";
        for (int j = 0; j < 4; j++)
            cout << (*indexArr[i]).grades[j] << ' ';
        cout << endl;
    }
    free(indexArr);
    return 0;
}

void addStudent(StudentList **head, string surname, int *grades)
{
    auto *temp = new StudentList;
    temp->next = *head;
    temp->grades = grades;
    temp->surname = std::move(surname);
    *head = temp;
}

void sortBySurnames(StudentList **studentsArr, int size)
{
    StudentList *temp;
    for (int i = 0; i < size - 1; i++)
    {
        int k = i;
        for (int j = i + 1; j < size; j++)
        {
            if ((studentsArr[j])->surname < (studentsArr[k])->surname)
            {
                k = j;
            }
        }
        temp = studentsArr[i];
        studentsArr[i] = studentsArr[k];
        studentsArr[k] = temp;
    }
}
