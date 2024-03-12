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

typedef struct Tree
{
    Student data;
    Tree *left, *right;
} Tree;

void addStudent(SinglyLinkedList **head, Student student);
void sortBySurnames(SinglyLinkedList **studentsArr, int size);
void addStudentToDoubly(DoublyLinkedList **head, Student student);
void deleteNode(DoublyLinkedList *node);
void addStudentToTree(Tree* &node, Student data);
void printSurnamesInc (Tree* node);
void printSurnamesDec (Tree* node);
Tree *search (Tree *node, string key);

int main()
{
    srand(time(nullptr));
    // Задание 1
    SinglyLinkedList *students = nullptr;
    DoublyLinkedList *students2 = new DoublyLinkedList;
    students2->next = nullptr;
    students2->previous = nullptr;
    Tree *root = nullptr;
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
        addStudentToDoubly(&students2, dataBuffer);
        addStudentToTree(root, dataBuffer);
    }
    auto **indexArr = new SinglyLinkedList *[10];
    SinglyLinkedList *currentStudent = students;
    cout << "Изначальный список студентов:\n";
    for (int i = 0; i < 10; i++)
    {
        indexArr[i] = currentStudent;
        cout << currentStudent->data.surname;
        for (int j = 0; j < 4; j++)
            cout << ' ' << currentStudent->data.grades[j];
        cout << endl;
        currentStudent = (*currentStudent).next;
    }
    sortBySurnames(indexArr, 10);
    cout << "\nСписок студентов, отсортированный по фамилии:\n";
    for (int i = 0; i < 10; i++)
    {
        cout << (*indexArr[i]).data.surname;
        for (int j = 0; j < 4; j++)
            cout << ' ' << (*indexArr[i]).data.grades[j];
        cout << endl;
    }
    free(indexArr);
    getchar();
    // Задание 2
    auto currentStudent2 = students2;
    cout << "\nСписок студентов, сдавших сессию\n";
    while (currentStudent2->previous != nullptr)
    {
        int isDeleted = 0;
        for (int i = 0; i < 4; i++)
        {
            if (currentStudent2->data.grades[i] < 3)
            {
                currentStudent2 = currentStudent2->previous;
                deleteNode(currentStudent2->next);
                isDeleted = 1;
                break;
            }
        }
        if (isDeleted == 0)
            currentStudent2 = currentStudent2->previous;
    }

    currentStudent2 = currentStudent2->next;
    while (true)
    {
        if (currentStudent2 == nullptr)
            break;
        cout << currentStudent2->data.surname << ' ';
        for (int i = 0; i < 4; i++)
            cout << currentStudent2->data.grades[i] << ' ';
        cout << endl;
        currentStudent2 = currentStudent2->next;
    }
    getchar();
    //Задание 3
    system("clear");
    cout << "Фамилии студентов по возрастанию:\n";
    printSurnamesInc(root);
    cout << "\nФамилии студентов по убыванию:\n";
    printSurnamesDec(root);
    cout << "\nВведите фамилию для поиска информации о студенте: ";
    string key;
    cin >> key;
    Tree *foundedStudent = search(root, key);
    if (!foundedStudent)
        cout << "Студент не найден";
    else
    {
        cout << foundedStudent->data.surname;
        for (int i = 0; i < 4; i++)
            cout << ' ' << foundedStudent->data.grades[i];
    }

    return 0;
}

void addStudent(SinglyLinkedList **head, Student student)
{
    auto *temp = new SinglyLinkedList;
    temp->next = *head;
    for (int i = 0; i < 4; i++)
        temp->data.grades[i] = student.grades[i];
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
    *head = temp;
}

void deleteNode(DoublyLinkedList *node)
{
    if (node->previous != nullptr)
        node->previous->next = node->next;
    if (node->next != nullptr)
        node->next->previous = node->previous;
    delete node;
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

void addStudentToTree(Tree* &node, Student data)
{
    if (node == nullptr)
    {
        node = new Tree;
        node->data = data;
        node->left = node->right = nullptr;
        return;
    }
    if (data.surname < node->data.surname)
        addStudentToTree(node->left, data);
    else
        addStudentToTree(node->right, data);
}

void printSurnamesInc (Tree* node)
{
    if (!node)
        return;
    printSurnamesInc(node->left);
    cout << node->data.surname << endl;
    printSurnamesInc(node->right);
}

void printSurnamesDec (Tree* node)
{
    if (!node)
        return;
    printSurnamesDec(node->right);
    cout << node->data.surname << endl;
    printSurnamesDec(node->left);
}

Tree *search (Tree *node, string key)
{
    if (!node)
        return nullptr;
    if (node->data.surname == key)
        return node;
    if (key < node->data.surname)
        return search(node->left, key);
    return search(node->right, key);
}