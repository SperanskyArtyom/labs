#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

typedef struct SL
{
    string surname;
    int *grades;
    SL *next;
} StudentList;

typedef struct Node
{
    int value;
    struct Node *next;
} Node;

void addStudent(StudentList **head, string surname, int *grade);
void sortBySurnames(StudentList **studentsArr, int size);

int main()
{
    srand(time(NULL));
    // Задание 1
    StudentList *students = NULL;
    string surnames[] = {"Сперанский", "Калашникова", "Фридрих", "Гуляев", "Брунилин", "Шильников", "Щукин", "Аникеев", "Цибулевич", "Халиков"};
    //  Генерируем список студентов
    for (int i = 0; i < 10; i++)
    {
        string surnameBuff = surnames[i];
        int gradeBuff[4];
        for (int j = 0; j < 4; j++)
            gradeBuff[j] = rand() % 4 + 2;
        addStudent(&students, surnameBuff, gradeBuff);
    }
    StudentList **indexArr = (StudentList **)malloc(10 * sizeof(StudentList));
    if (indexArr == NULL)
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
    return 0;
}

void addStudent(StudentList **head, string surname, int *grade)
{
    StudentList *temp = (StudentList *)malloc(sizeof(StudentList));
    temp->next = *head;
    temp->grades = grade;
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
