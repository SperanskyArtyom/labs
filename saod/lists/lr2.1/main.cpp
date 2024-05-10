#include <list.h>
#include <iostream>

int main(){
    srand(time(nullptr));
    List *head = nullptr;
    std::cout << "Стек возрастающих чисел\n";
    fillInc(head, 10);
    print(head);
    std::cout << "\nКонтрольная сумма: " << CheckSum(head) << "\nКоличество серий: " << RunNumbers(head);
    std::cout << "\nСтек убывающих чисел\n";
    fillDec(head, 10);
    print(head);
    std::cout << "\nКонтрольная сумма: " << CheckSum(head) << "\nКоличество серий: " << RunNumbers(head);
    std::cout << "\nСтек случайных чисел\n";
    fillRand(head, 10);
    print(head);
    std::cout << "\nКонтрольная сумма: " << CheckSum(head) << "\nКоличество серий: " << RunNumbers(head);

    auto q = initQ();
    std::cout << "\n\nОчередь возрастающих чисел\n";
    fillInc(q, 10);
    print(q.head, true);
    std::cout << "\nКонтрольная сумма: " << CheckSum(q.head) << "\nКоличество серий: " << RunNumbers(q.head);

    std::cout << "\nОчередь убывающих чисел\n";
    fillDec(q, 10);
    print(q.head, true);
    std::cout << "\nКонтрольная сумма: " << CheckSum(q.head) << "\nКоличество серий: " << RunNumbers(q.head);

    std::cout << "\nОчередь случайных чисел\n";
    fillRand(q, 10);
    print(q.head, true);
    std::cout << "\nКонтрольная сумма: " << CheckSum(q.head) << "\nКоличество серий: : " << RunNumbers(q.head);

    return 0;
}