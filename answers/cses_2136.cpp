// HAN MAI
// https://cses.fi/problemset/task/2136
// C++20

#include <bit>
#include <iostream>
#include <vector>
#include <string>

int main()
{
    int n, k;
    std::cin >> n >> k;

    std::vector<int> arr;
    int min = k;

    for (int i = 0; i < n; ++i)
    {
        std::string str;
        std::cin >> str;
        int num = std::stoi(str, nullptr, 2);

        for (int x : arr)
        {
            int distance = std::popcount((unsigned int)(num ^ x));

            if (distance < min)
            {
                min = distance;
            }
        }

        arr.push_back(num);
    }

    std::cout << min;
    return 0;
}
