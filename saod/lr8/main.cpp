#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

using namespace std;

typedef enum{
    MALE, FEMALE
} gender;

typedef struct {
    string _name;
    string _surname;
    string _phoneNumber;
    gender _gender;
    string _location;
} phoneEntry;

void printPhoneDict (const phoneEntry dict[], size_t size);
void printPhoneDict(const phoneEntry dict[], size_t size, const int indexArr[]);
void printPhoneDict(const phoneEntry dict[], const vector<int>& indexArr);
void SearchByKey(const phoneEntry dict[], size_t size);
void SortByComplexKey(const phoneEntry dict[], size_t size);

int main() {
    const size_t N = 5;
    phoneEntry dict[] = {
                    {"Mariya",  "Curie",        "+7-111-222-33-44", FEMALE, "Moscow"},
                    {"Artem",   "Speranskiy",   "+7-777-666-55-44", MALE,   "Novosibirsk"},
                    {"Arthur",  "Pirozhkov",    "+7-777-666-55-22", MALE,   "Novosibirsk"},
                    {"Mariya",  "Curie",        "+7-888-666-55-22", FEMALE, "Novosibirsk"},
                    {"Artem",   "Lohmanov",     "+7-777-666-55-33", MALE,   "Novosibirsk"}
    };

    while (true){
        system("clear");
        cout << "Изначальный справочник:\n";
        printPhoneDict(dict, N);
        cout << "\nВыберите опцию:"
                "\n1 - Вывести отсортированный по ключу справочник"
                "\n2 - Найти элемент по заданному ключу"
                "\n0 - Выйти из программы\n";
        char ch;
        cin >> ch;
        system("clear");
        switch (ch) {
            case '1': {
                SortByComplexKey(dict, N);
                getchar();
                getchar();
                break;
            }
            case '2': {
                SearchByKey(dict, N);
                getchar();
                getchar();
                break;
            }
            case '0': {
                return 0;
            }
            default:
                break;
        }
    }
}

void SortTelephoneDictionary(const phoneEntry dict[], size_t size, int *indexArr, bool (*compare)(const phoneEntry &, const phoneEntry &))
{
    for (int i = 0; i < size; i++)
        indexArr[i] = i;
    for (int i = 1; i < size; i++)
    {
        auto temp = indexArr[i];
        int j = i - 1;
        while (j >= 0 && compare(dict[temp], dict[indexArr[j]]))
        {
            indexArr[j + 1] = indexArr[j];
            j--;
        }
        indexArr[j + 1] = temp;
    }
}

bool lessName(const phoneEntry& a, const phoneEntry& b)
{
    return a._name < b._name;
}

bool lessSurname(const phoneEntry& a, const phoneEntry& b)
{
    return a._surname < b._surname;
}

bool lessPhone(const phoneEntry& a, const phoneEntry& b)
{
    return a._phoneNumber < b._phoneNumber;
}

bool lessGender(const phoneEntry& a, const phoneEntry& b)
{
    return a._gender < b._gender;
}

bool lessLocation(const phoneEntry& a, const phoneEntry& b)
{
    return a._location < b._location;
}

bool lessNamePhone(const phoneEntry& a, const phoneEntry& b)
{
    if (a._name < b._name)
        return true;
    if (a._name > b._name)
        return false;
    if (a._phoneNumber < b._phoneNumber)
        return true;
    return false;
}


bool moreNamePhone(const phoneEntry& a, const phoneEntry& b)
{
    if (a._name > b._name)
        return true;
    if (a._name < b._name)
        return false;
    if (a._phoneNumber > b._phoneNumber)
        return true;
    return false;
}

bool lessNameSurname(const phoneEntry& a, const phoneEntry& b) {
    if (a._name < b._name)
        return true;
    if (a._name > b._name)
        return false;
    if (a._surname < b._surname)
        return true;
    return false;
}
    
bool moreNameSurname(const phoneEntry& a, const phoneEntry& b)
{
    if (a._name > b._name)
        return true;
    if (a._name < b._name)
        return false;
    if (a._surname > b._surname)
        return true;
    return false;
}

bool lessSurnamePhone(const phoneEntry& a, const phoneEntry& b)
{
    if (a._surname < b._surname)
        return true;
    if (a._surname > b._surname)
        return false;
    if (a._phoneNumber < b._phoneNumber)
        return true;
    return false;
}

bool moreSurnamePhone(const phoneEntry& a, const phoneEntry& b)
{
    if (a._surname > b._surname)
        return true;
    if (a._surname < b._surname)
        return false;
    if (a._phoneNumber > b._phoneNumber)
        return true;
    return false;
}

void printPhoneDict (const phoneEntry dict[], size_t size)
{
    cout << setw(12) << left << "Name" << setw(15) << "Surname" << setw(18) << "Phone number"
         << setw(8) << "Gender" << "Location" << endl;
    for (int i = 0; i < size; i++) {
        cout << setw(12) << dict[i]._name << setw(15) << dict[i]._surname << setw(18) << dict[i]._phoneNumber;
        dict[i]._gender == MALE ? cout << setw(8) << "Male" : cout << setw(8) << "Female";
        cout << dict[i]._location << endl;
    }
}

void printPhoneDict(const phoneEntry dict[], size_t size, const int indexArr[])
{
    cout << setw(12) << left << "Name" << setw(15) << "Surname" << setw(18) << "Phone number"
         << setw(8) << "Gender" << "Location" << endl;
    for (int i = 0; i < size; i++) {
        cout << setw(12) << dict[indexArr[i]]._name << setw(15) << dict[indexArr[i]]._surname << setw(18) << dict[indexArr[i]]._phoneNumber;
        dict[indexArr[i]]._gender == MALE ? cout << setw(8) << "Male" : cout << setw(8) << "Female";
        cout << dict[indexArr[i]]._location << endl;
    }
}

void printPhoneDict(const phoneEntry dict[], const vector<int>& indexArr)
{
    cout << setw(12) << left << "Name" << setw(15) << "Surname" << setw(18) << "Phone number"
         << setw(8) << "Gender" << "Location" << endl;
    for (int i : indexArr) {
        cout << setw(12) << dict[i]._name << setw(15) << dict[i]._surname << setw(18) << dict[i]._phoneNumber;
        dict[i]._gender == MALE ? cout << setw(8) << "Male" : cout << setw(8) << "Female";
        cout << dict[i]._location << endl;
    }
}

vector<int> BSearchAllInPhoneDict (const phoneEntry dict[], const int indexArr[], size_t size, const phoneEntry& key, bool (*compare)(const phoneEntry&, const phoneEntry&))
{
    std::vector<int> indexes(0);
    int L = 0, R = (int)size - 1;
    while (L < R){
        int m = floor((double)(L + R) / 2);
        if (compare(dict[indexArr[m]], key))
            L = m + 1;
        else
            R = m;
    }
    if (!compare(dict[indexArr[R]], key) && !compare(key, dict[indexArr[R]])) {
        while (R < size && !compare(dict[indexArr[R]], key) && !compare(key, dict[indexArr[R]])) {
            indexes.push_back(indexArr[R]);
            R++;
        }
    }
    return indexes;
}

void SearchByKey(const phoneEntry dict[], size_t size){
    phoneEntry temp;
    char keyType;
    string key;
    int sortedIndexes[size];
    vector<int> foundedRecords(0);
    cout << "Введите поле, по ключу которого будет осуществлён поиск:\n1 - Имя\n2 - Фамилия\n3 - Номер телефона\n4 - Пол\n5 - Локация\n";
    cin >> keyType;
    cout << "Введите ключ: ";
    cin >> key;
    switch (keyType) {
        case '1':{
            temp._name = key;
            SortTelephoneDictionary(dict, size, sortedIndexes, lessName);
            foundedRecords = BSearchAllInPhoneDict(dict, sortedIndexes, size, temp, lessName);
            break;
        }
        case '2':{
            temp._surname = key;
            SortTelephoneDictionary(dict, size, sortedIndexes, lessSurname);
            foundedRecords = BSearchAllInPhoneDict(dict, sortedIndexes, size, temp, lessSurname);
            break;
        }
        case '3':{
            temp._phoneNumber = key;
            SortTelephoneDictionary(dict, size, sortedIndexes, lessPhone);
            foundedRecords = BSearchAllInPhoneDict(dict, sortedIndexes, size, temp, lessPhone);
            break;
        }
        case '4':{
            if (key == "М")
                temp._gender = MALE;
            else
                temp._gender = FEMALE;
            SortTelephoneDictionary(dict, size, sortedIndexes, lessGender);
            foundedRecords = BSearchAllInPhoneDict(dict, sortedIndexes, size, temp, lessGender);
            break;
        }
        case '5':{
            temp._location = key;
            SortTelephoneDictionary(dict, size, sortedIndexes, lessLocation);
            foundedRecords = BSearchAllInPhoneDict(dict, sortedIndexes, size, temp, lessLocation);
            break;
        }
        default:{
            cout << "Неверная опция\n";
            return;
        }
    }
    cout << "Найденные записи:\n";
    printPhoneDict(dict, foundedRecords);
}

void SortByComplexKey(const phoneEntry dict[], size_t size)
{
    int sortedIndexes[size];
    bool isDecreasing = false;
    char ch;
    cout << "Выберите направление сортировки: 0 - по возрастанию, 1 - по убыванию\n";
    cin >> isDecreasing;
    cout << "\nВыберите сложный ключ для сортировки:\n1 - Имя, Фамилия\n2 - Имя Телефон\n3 - Фамилия, Телефон\n";
    cin >> ch;
    switch (ch) {
        case '1':
            isDecreasing ? SortTelephoneDictionary(dict, size, sortedIndexes, moreNameSurname):
            SortTelephoneDictionary(dict, size, sortedIndexes, lessNameSurname);
            break;
        case '2':
            isDecreasing ? SortTelephoneDictionary(dict, size, sortedIndexes, moreNamePhone):
            SortTelephoneDictionary(dict, size, sortedIndexes, lessNamePhone);
            break;
        case '3':
            isDecreasing ? SortTelephoneDictionary(dict, size, sortedIndexes, moreSurnamePhone):
            SortTelephoneDictionary(dict, size, sortedIndexes, lessSurnamePhone);
            break;
        default:
            cout << "Неверная опция\n";
            return;
    }
    cout << "\nОтсортированный справочник\n";
    printPhoneDict(dict, size, sortedIndexes);
}