#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <vector>

#define n 10
#define m 50

struct School
{
    int number;
    int graduates;
    int applicants;
};

typedef struct
{
    int number;
    int area;
    char faculty[100];
    int residents;
}StudentHostelRoom;

void applicantPercentageSort(struct School *sch, int *indexArray, int size);

int main()
{
    srand(time(NULL));

    // Task 1
    printf("Task 1\n\n");
    struct School schools[n], show;
    float percentage;
    printf("The information about schools:\nSchool\tgraduates\tapplicants\n");
    for (int i = 0; i < n; i++)
    {
        schools[i].number = i + 1;
        schools[i].graduates = rand() % 1000;
        schools[i].applicants = rand() % schools[i].graduates;
        printf("№ %-2d\t   %3d\t\t   %3d\n", schools[i].number, schools[i].graduates, schools[i].applicants);
    }
    int indexArray[n];
    applicantPercentageSort(schools, indexArray, n);
    printf("\nThe information about percentage of applicants:\nSchool\tgraduates\tapplicants %%\n");
    for (int i = 0; i < n; i++)
    {
        // printf("%d ", indexArray[i]);
        show = schools[indexArray[i]];
        percentage = (float)show.applicants / show.graduates * 100;
        printf("№ %-2d\t   %3d\t\t   %3.1f%%\n", show.number, show.graduates, percentage);
    }

    // Task 2
    printf("\nTask 2\n\n");
    char faculties[5][100] = {"Математический", "Телекоммуникации", "ИВТ", "Механико-технологический", "Информационная безопасность"};
     StudentHostelRoom rooms[m];
    // Генерация массива комнат
    for (int i = 0; i < m; i++)
    {
        strcpy(rooms[i].faculty, faculties[rand() % 5]);
        rooms[i].residents = rand() % 4 + 1;
        rooms[i].area = rand() % rooms[i].residents * 12 + rooms[i].residents * 6;
        rooms[i].number = i + 101;
    }
    int k = 1;
    int found;
    for (int i = 1; i < m; i++)
    {
        found = 0;
        for (int j = i - 1; j >= 0; j--)
            if (strcmp(rooms[i].faculty, rooms[j].faculty) == 0)
                found = 1;
        if (found == 0)
        {
            k++;
        }
    }
    char foundedFaculties[k][100];
    int l = 0;
    strcpy(foundedFaculties[0], rooms[0].faculty);
    for (int i = 1; i < m; i++)
    {
        found = 0;
        for (int j = i - 1; j >= 0; j--)
            if (strcmp(rooms[i].faculty, rooms[j].faculty) == 0)
                found = 1;
        if (found == 0)
        {
            l++;
            strcpy(foundedFaculties[l], rooms[i].faculty);
        }
    }

    int studentSum, roomSum;
    float avgArea;
    printf("Информация об общежитии.\n");
    for (int i = 0; i < k; i++)
    {
        studentSum = 0, roomSum = 0, avgArea = 0.0;
        for (int j = 0; j < m; j++)
            if (strcmp(rooms[j].faculty, foundedFaculties[i]) == 0)
            {
                studentSum += rooms[j].residents;
                roomSum++;
                avgArea += rooms[j].area;
            }
        avgArea = avgArea / studentSum;
        printf("Факультет - %s Комнат: %d Студентов: %d Средняя площадь:%.1f\n", foundedFaculties[i], roomSum, studentSum, avgArea);
    }

    return 0;
}

void applicantPercentageSort(struct School *sch, int *indexArray, int size)
{
    int temp;
    for (int i = 0; i < n; i++)
        indexArray[i] = i;
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = size - 1; j > i; j--)
        {
            if ((float)sch[indexArray[j]].applicants / sch[indexArray[j]].graduates > (float)sch[indexArray[j - 1]].applicants / sch[indexArray[j - 1]].graduates)
            {
                temp = indexArray[j];
                indexArray[j] = indexArray[j - 1];
                indexArray[j - 1] = temp;
            }
        }
    }
}
