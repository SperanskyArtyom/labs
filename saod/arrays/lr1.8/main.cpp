#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

using namespace std;

typedef struct {
    string _name;
    string _phoneNumber;
    string _district;
    string _street;
} phoneEntry;

void printPhoneDict (const phoneEntry dict[], size_t size);
void printPhoneDict(const phoneEntry dict[], size_t size, const int indexArr[]);
void printPhoneDict(const phoneEntry dict[], const vector<int>& indexArr);
void SortTelephoneDictionary(const phoneEntry dict[], size_t size, int *indexArr, bool (*compare)(const phoneEntry &, const phoneEntry &));
void FillIndex(int* IndexArr, int size);
void printMass(int* Arr, int size);


bool lessName(const phoneEntry& a, const phoneEntry& b);
bool lessStreet(const phoneEntry& a, const phoneEntry& b);

vector<int> BSearchAllName (const phoneEntry dict[], const int indexArr[], size_t size, const phoneEntry& key,
                            bool (*lessCompare)(const phoneEntry&, const phoneEntry&));

int main() {
    const size_t N = 5;
    phoneEntry dict[N] = {
            {"Banina Natalia Valerievna", "+7-111-222-33-44", "Zaelcovskiy", "Pushkina, 1"},
            {"Speransky Artem Alexandrovich",   "+7-777-666-55-44", "Oktyabrskiy", "Kirova, 4"},
            {"Safarov Arthur Victorovich", "+7-777-666-55-22", "Kalininskiy", "Kropotkina, 138"},
            {"Banina Natalia Valerievna","+7-888-666-55-22", "Kalininskiy", "Kropotkina, 138"},
            {"Speransky Artem Alexandrovich",     "+7-777-666-55-33", "Kalininskiy", "Kropotkina, 120"}
    };
    int sortedIndexesName[N], sortedIndexesStreet[N], IndexArr[N];
    FillIndex(sortedIndexesName, N);
    FillIndex(sortedIndexesStreet, N);
    FillIndex(IndexArr, N);

    cout << "Неотсортированный справочник:\n";
    printPhoneDict(dict, N);

    SortTelephoneDictionary(dict, N, sortedIndexesName, lessName);
    cout << "\nОтсортированный по ФИО справочник:\n";
    printPhoneDict(dict, N, sortedIndexesName);

    SortTelephoneDictionary(dict, N, sortedIndexesStreet, lessStreet);
    cout << "\nОтсортированный по адресу справочник:\n";
    printPhoneDict(dict, N, sortedIndexesStreet);

    cout << "\nИндексный массив до сортировки: ";
    printMass(IndexArr, N);
    cout << "Индексный массив после сортировки по имени: ";
    printMass(sortedIndexesName, N);
    cout << "Индексный массив после сортировки по адресу: ";
    printMass(sortedIndexesStreet, N);

    string field, key;
    cout << "\nПо какому полю произвести поиск: ";
    cin >> field;

    cout << "Введите ключ для сортировки: ";
    getchar();
    getline(cin, key);

    vector<int> foundedRecordsIndexes;
    if (field == "ФИО"){
        phoneEntry temp = {._name = key};
        foundedRecordsIndexes = BSearchAllName(dict, sortedIndexesName, N, temp, lessName);
    } else if (field == "адрес"){
        phoneEntry temp = {._street = key};
        foundedRecordsIndexes = BSearchAllName(dict, sortedIndexesStreet, N, temp, lessStreet);
    } else {
        cout << "\nНеверно задано поля для поиска. Ожидалось \"ФИО\" или \"адрес\"";
        return 0;
    }

    if (foundedRecordsIndexes.empty())
        cout << "\nПо заданному ключу не нашлось записей\n";
    else{
        cout << "\nНайденные записи:\n";
        printPhoneDict(dict, foundedRecordsIndexes);
    }

    return 0;
}

void SortTelephoneDictionary(const phoneEntry dict[], size_t size, int *indexArr, bool (*compare)(const phoneEntry &, const phoneEntry &))
{
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

bool lessStreet(const phoneEntry& a, const phoneEntry& b)
{
    return a._street < b._street;
}

void printPhoneDict (const phoneEntry dict[], size_t size)
{
    cout << setw(40) << left << "Name" << setw(18) << "Phone number"
         << setw(15) << "District" << "Street" << endl;
    for (int i = 0; i < size; i++) {
        cout << setw(40) << dict[i]._name << setw(18) << dict[i]._phoneNumber << setw(15) << dict[i]._district << dict[i]._street << endl;
    }
}

void printPhoneDict(const phoneEntry dict[], size_t size, const int indexArr[])
{
    cout << setw(40) << left << "Name" << setw(18) << "Phone number"
         << setw(15) << "District" << "Street" << endl;
    for (int i = 0; i < size; i++) {
        cout << setw(40) << dict[indexArr[i]]._name << setw(18) << dict[indexArr[i]]._phoneNumber << setw(15) << dict[indexArr[i]]._district << dict[indexArr[i]]._street << endl;
    }
}

void printPhoneDict(const phoneEntry dict[], const vector<int>& indexArr)
{
    cout << setw(40) << left << "Name" << setw(18) << "Phone number"
         << setw(15) << "District" << "Street" << endl;
    for (auto i : indexArr) {
        cout << setw(40) << dict[i]._name << setw(18) << dict[i]._phoneNumber << setw(15) << dict[i]._district << dict[i]._street << endl;
    }
}

vector<int> BSearchAllName (const phoneEntry dict[], const int indexArr[], size_t size, const phoneEntry& key,
                            bool (*lessCompare)(const phoneEntry&, const phoneEntry&))
{
    std::vector<int> indexes(0);
    int L = 0, R = (int)size - 1;
    while (L < R){
        int m = floor((double)(L + R) / 2);
        if (lessCompare(dict[indexArr[m]], key))
            L = m + 1;
        else
            R = m;
    }
    while (R < size && !lessCompare(dict[indexArr[R]], key) && !lessCompare(key, dict[indexArr[R]])) {
        indexes.push_back(indexArr[R]);
        R++;
    }

    return indexes;
}

void FillIndex(int* IndexArr, int size)
{
    for (int i = 0; i < size; i++)
        IndexArr[i] = i;
}

void printMass(int* Arr, int size)
{
    for (int i = 0; i < size; i++)
        cout << Arr[i] << ' ';
    cout << endl;
}