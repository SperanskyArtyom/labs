#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#define MAX_NAME 100
#define MAX_FILE_NAME 20

typedef struct {
    char name[MAX_NAME];
    float baggageSpace, baggageWeight;
} passenger;

int getch();
void inputPassengers(const char *filename);
void outputFile(const char* filename);
void addPassenger(const char* filename);
void removePassengers(const char* filename);
void changeBaggageWeight(const char* filename);

int main() {
    char filename[MAX_FILE_NAME];
    while (1){
        system("clear");
        printf("Введите название файла: ");
        fgets(filename, MAX_FILE_NAME, stdin);
        if (!strcmp(filename, "\n"))
            continue;
        break;
    }
    while(1){
        char stringToCleanInput[1];
        fgets(stringToCleanInput, 1, stdin);
        system("clear");
        printf("Выберите опцию:\n\t1 - создание нового файла;\n\t2 - просмотреть файл;\n\t3 - добавить запись о пассажире в конец файла;"
               "\n\t4 - найти и удалить из файла записи о пассажирах, общий вес вещей которых меньше, чем 10 кг;\n\t"
               "5 - изменить вес вещей пассажира по заданной фамилии;\n\t0 - выход из программы\n");
        char ch = (char)getch();
        switch (ch) {
            case '1':
                inputPassengers(filename);
                break;
            case '2':
                outputFile(filename);
                break;
            case '3':
                addPassenger(filename);
                break;
            case '4':
                removePassengers(filename);
                break;
            case '5':
                changeBaggageWeight(filename);
                break;
            case '0':
                return 0;
            default:
                printf("\nНеверно введена опция! Попробуйте ещё раз\n");
                system("sleep 1.5");
                break;
        }
    }
}

int getch( ) {
    struct termios oldt, newt;
    int ch;
    tcgetattr( STDIN_FILENO, &oldt );
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newt );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
    return ch;
}


void inputPassengers(const char *filename)
{
    FILE *file = fopen(filename, "wb");
    system("clear");
    char stringToCleanInput[MAX_NAME];
    printf("Введите количество пассажиров: ");
    int N;
    scanf("%d", &N);
    passenger passengerBuff;
    for (int i = 0; i < N; i++){
        system("clear");
        printf("Введите данные о пассажире №%d\n", i+1);
        printf("ФИО: ");
        fgets(stringToCleanInput, MAX_NAME, stdin);
        fgets(passengerBuff.name, MAX_NAME, stdin);
        printf("Количество занимаемых багажом мест: ");
        scanf("%f", &passengerBuff.baggageSpace);
        printf("Общий вес вещей: ");
        scanf("%f", &passengerBuff.baggageWeight);
        fwrite(&passengerBuff, sizeof(passengerBuff), 1, file);
    }
    printf("Конец записи\n");
    system("sleep 1");
    fclose(file);
    fgets(stringToCleanInput, MAX_NAME, stdin);
}

void addPassenger(const char *filename){
    FILE *file = fopen(filename, "ab");
    passenger passengerBuff;
    char stringToCleanInput[MAX_NAME];
    system("clear");
    printf("Введите данные о пассажире\n");
    printf("ФИО: ");
    fgets(passengerBuff.name, MAX_NAME, stdin);
    printf("Количество занимаемых багажом мест: ");
    scanf("%f", &passengerBuff.baggageSpace);
    printf("Общий вес вещей: ");
    scanf("%f", &passengerBuff.baggageWeight);
    fwrite(&passengerBuff, sizeof(passengerBuff), 1, file);
    fclose(file);
    fgets(stringToCleanInput, MAX_NAME, stdin);
}

void outputFile(const char* filename){
    FILE *file = fopen(filename, "rb");
    passenger passengerBuff;
    system("clear");
    int i = 1;
    while (fread(&passengerBuff, sizeof(passengerBuff), 1, file)){
        printf("Пассажир №%d\nФИО: %sКоличество занимаемых багажом мест: %.1f\nОбщий вес вещей: %.2f кг\n\n",
                i, passengerBuff.name, passengerBuff.baggageSpace, passengerBuff.baggageWeight);
        i++;
    }
    fclose(file);
    printf("Нажмите любую клавишу для возвращения в меню\n");
    getch();
}

void removePassengers(const char* filename){
    FILE *file = fopen(filename, "rb");
    FILE *newFile = fopen("temp", "wb");
    passenger passengerBuff;
    while(fread(&passengerBuff, sizeof (passenger), 1, file)){
        if (passengerBuff.baggageWeight < 10.0) {
            printf("Удалён %s", passengerBuff.name);
            continue;
        }
        fwrite(&passengerBuff, sizeof (passenger), 1, newFile);
    }
    fclose(file);
    fclose(newFile);
    remove(filename);
    rename("temp", filename);
    system("sleep 2");
}


void changeBaggageWeight(const char* filename){
    FILE *file = fopen(filename, "rb+");
    passenger passengerBuff;
    system("clear");
    char stringToCleanInput[MAX_NAME];
    char name[MAX_NAME];
    printf("Введите ФИО пассажира для изменения веса его вещей\n");
    fgets(name, MAX_NAME, stdin);
    int isFounded = 0;
    while(fread(&passengerBuff, sizeof(passenger), 1, file)){
        if(!strcmp(passengerBuff.name, name)){
            isFounded = 1;
            printf("Прежний вес: %.2f кг\nНовый вес: ", passengerBuff.baggageWeight);
            scanf("%f", &passengerBuff.baggageWeight);
            fseek(file, -1 * (long)sizeof(passengerBuff), SEEK_CUR);
            fwrite(&passengerBuff, sizeof(passenger), 1, file);
            printf("Изменение записи прошло успешно\n");
            fflush(file);
        }
    }
    if(!isFounded)
        printf("Пассажир не найден\n");
    else
        fgets(stringToCleanInput, MAX_NAME, stdin);
    fclose(file);
    system("sleep 2");
}