#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

typedef struct
{
    string surname;
    int grades[4];
} Student;

typedef struct SinglyLinkedList
{
    Student data;
    SinglyLinkedList *next{};
} SinglyLinkedList;

typedef struct DoublyLinkedList
{
    Student data;
    DoublyLinkedList *previous, *next;
} DoublyLinkedList;

void addStudent(SinglyLinkedList **head, Student student);
void sortBySurnames(SinglyLinkedList **studentsArr, int size);
void addStudentToDoubly(DoublyLinkedList **head, Student student);

int main()
{
    srand(time(nullptr));
    // Задание 1
    SinglyLinkedList *students = nullptr;
    string surnames[] = {"Сперанский", "Калашникова", "Фридрих", "Гуляев", "Брунилин", "Шильников", "Щукин", "Аникеев", "Цибулевич", "Халиков"};
    //  Генерируем список студентов
    for (const auto &surnameBuff : surnames)
    {
        Student dataBuffer;
        for (int j = 0; j < 4; j++)
        {
            dataBuffer.grades[j] = rand() % 4 + 2;
        }
        dataBuffer.surname = surnameBuff;
        addStudent(&students, dataBuffer);
    }
    auto **indexArr = new SinglyLinkedList *[10];
    SinglyLinkedList *currentStudent = students;
    for (int i = 0; i < 10; i++)
    {
        indexArr[i] = currentStudent;
        currentStudent = (*currentStudent).next;
    }
    sortBySurnames(indexArr, 10);
    for (int i = 0; i < 10; i++)
    {
        cout << (*indexArr[i]).data.surname << "   ";
        for (int j = 0; j < 4; j++)
            cout << (*indexArr[i]).data.grades[j] << ' ';
        cout << endl;
    }
    free(indexArr);
    return 0;
}

void addStudent(SinglyLinkedList **head, Student student)
{
    auto *temp = new SinglyLinkedList;
    temp->next = *head;
    for (int i = 0; i < 4; i++)
    {
        temp->data.grades[i] = student.grades[i];
    }
    temp->data.surname = std::move(student.surname);
    *head = temp;
}

void addStudentToDoubly(DoublyLinkedList **head, Student student)
{
    auto *temp = new DoublyLinkedList;
    temp->previous = *head;
    temp->next = nullptr;
    temp->data.surname = std::move(student.surname);
    for (int i = 0; i < 4; i++)
        temp->data.grades[i] = student.grades[i];
    (*head)->next = temp;
}

void sortBySurnames(SinglyLinkedList **studentsArr, int size)
{
    SinglyLinkedList *temp;
    for (int i = 0; i < size - 1; i++)
    {
        int k = i;
        for (int j = i + 1; j < size; j++)
        {
            if ((studentsArr[j])->data.surname < (studentsArr[k])->data.surname)
            {
                k = j;
            }
        }
        temp = studentsArr[i];
        studentsArr[i] = studentsArr[k];
        studentsArr[k] = temp;
    }
}
