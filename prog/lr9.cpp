#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

typedef struct StudentList
{
    string surname;
    int *grades;
    StudentList *next;
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
    for (int i = 0; i < 10; i++)
    {
        string surnameBuff = surnames[i];
        int *gradeBuff = new int[4];
        int randomtoken;
        for (int j = 0; j < 4; j++)
        {
            randomtoken = rand() % 4 + 2;
            gradeBuff[j] = randomtoken;
        }
        addStudent(&students, surnameBuff, gradeBuff);
    }
    StudentList **indexArr = new StudentList *[10];
    if (indexArr == nullptr)
        return 1;

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
    StudentList *temp = new StudentList;
    temp->next = *head;
    temp->grades = grades;
    temp->surname = surname;
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
