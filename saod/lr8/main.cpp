#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

typedef enum{
    MALE, FEMALE
} gender;

typedef struct {
    string _name;
    string _phoneNumber;
    gender _gender;
    string _address;
} phoneEntry;

void printPhoneDict (const phoneEntry dict[], size_t size);
void printPhoneDict(const phoneEntry dict[], size_t size, const int indexArr[]);
void printPhoneDict(const phoneEntry dict[], const vector<int>& indexArr);
void SortTelephoneDictionary(const phoneEntry dict[], size_t size, int *indexArr, bool (*compare)(const phoneEntry &, const phoneEntry &));
vector<int> BSearchAllInPhoneDict (const phoneEntry dict[], const int indexArr[], size_t size, const string& key);
bool entryMore(const phoneEntry& a, const phoneEntry& b);
bool entryLess(const phoneEntry& a, const phoneEntry& b);

int main() {
    const size_t N = 5;
    phoneEntry dict[N];
    dict[0] = {"Artem", "+7-777-666-55-44", MALE, "Novosibirsk"};
    dict[1] = {"Artem", "+7-777-666-55-33", MALE, "Novosibirsk"};
    dict[2] = {"Artur", "+7-777-666-55-22", MALE, "Novosibirsk"};
    dict[3] = {"Mariya", "+7-888-666-55-22", FEMALE, "Novosibirsk"};
    dict[4] = {"Mariya", "+7-111-222-33-44", FEMALE, "Moscow"};
    int indexesInc[N], indexesDec[N];
    SortTelephoneDictionary(dict, N, indexesInc,entryLess);
    SortTelephoneDictionary(dict, N, indexesDec,entryMore);

    while (true){
        system("clear");
        cout << "Source phone directory:\n";
        printPhoneDict(dict, N);
        cout << "\nChose option:\n1 - Display the telephone directory sorted in ascending order"
                "\n2 - Display the telephone directory, sorted in descending order"
                "\n3 - Set the search key and display the found records"
                "\n0 - Exit the program\n";
        char ch;
        cin >> ch;
        system("clear");
        switch (ch) {
            case '1': {
                printPhoneDict(dict, N, indexesInc);
                getchar();
                getchar();
                break;
            }
            case '2': {
                printPhoneDict(dict, N, indexesDec);
                getchar();
                getchar();
                break;
            }
            case '3': {
                cout << "Enter the search key: ";
                string key;
                cin >> key;
                auto keyIndexes = BSearchAllInPhoneDict(dict, indexesInc, N, key);
                printPhoneDict(dict, keyIndexes);
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

bool entryLess(const phoneEntry& a, const phoneEntry& b)
{
    if (a._name < b._name)
        return true;
    if (a._name > b._name)
        return false;
    if (a._phoneNumber < b._phoneNumber)
        return true;
    return false;
}


bool entryMore(const phoneEntry& a, const phoneEntry& b)
{
    if (a._name > b._name)
        return true;
    if (a._name < b._name)
        return false;
    if (a._phoneNumber > b._phoneNumber)
        return true;
    return false;
}

void printPhoneDict (const phoneEntry dict[], size_t size)
{
    for (int i = 0; i < size; i++) {
        cout << dict[i]._name + ' ' + dict[i]._phoneNumber;
        dict[i]._gender == MALE ? cout << " Male " : cout << " Female ";
        cout << dict[i]._address << endl;
    }
}

void printPhoneDict(const phoneEntry dict[], size_t size, const int indexArr[])
{
    for (int i = 0; i < size; i++) {
        cout << dict[indexArr[i]]._name + ' ' + dict[indexArr[i]]._phoneNumber;
        dict[indexArr[i]]._gender == MALE ? cout << " Male " : cout << " Female ";
        cout << dict[indexArr[i]]._address << endl;
    }
}

void printPhoneDict(const phoneEntry dict[], const vector<int>& indexArr)
{
    for (int i : indexArr) {
        cout << dict[i]._name + ' ' + dict[i]._phoneNumber;
        dict[i]._gender == MALE ? cout << " Male " : cout << " Female ";
        cout << dict[i]._address << endl;
    }
}

vector<int> BSearchAllInPhoneDict (const phoneEntry dict[], const int indexArr[], size_t size, const string& key)
{
    std::vector<int> indexes(0);
    int L = 0, R = (int)size - 1;
    while (L < R){
        int m = floor((double)(L + R) / 2);
        if (dict[indexArr[m]]._name < key)
            L = m + 1;
        else
            R = m;
    }
    if (dict[indexArr[R]]._name == key) {
        while (R < size && dict[indexArr[R]]._name == key) {
            indexes.push_back(R);
            R++;
        }
    }
    return indexes;
}