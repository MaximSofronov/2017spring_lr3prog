#include "functions.h"

int main()
{
    int n, MAX_COST, wtemp, ctwmp;
    std::vector<int> w, c;
    std::cout << "Введите количество вещей" << std::endl;
    std::cin >> n;
    std::cout << "Введите максимальный вес" << std::endl;
    std::cin >> MAX_COST;

    for (int i = 0; i < n; i++)
    {
        std::cout << "Введите вес и полезность " << i+1 << " вещи" << std::endl;
        std::cin >> wtemp;
        w.push_back(wtemp);
        std::cin >> ctwmp;
        c.push_back(ctwmp);
    }

    sort(w,c,n);
    knapsack(n, c, w, MAX_COST);

    return 0;
}
