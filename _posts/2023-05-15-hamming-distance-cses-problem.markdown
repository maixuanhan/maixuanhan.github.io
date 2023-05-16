---
layout: post
title:  "Hamming Distance [CSES Problem Set]"
date:   2023-05-15 23:00:00 +0800
categories: coding problem
--- 
The CSES Problem Set is a collection of algorithmic programming problems provided by Code Submission Evaluation System website. The following problem is randomly picked from it. You can find it [here][problem-source].

## The problem

The Hamming distance between two strings `a` and `b` of equal length is the number of positions where the strings differ.

You are given `n` bit strings, each of length `k` and your task is to calculate the minimum Hamming distance between two strings.

**Input**

The first input line has two integers `n` and `k`: the number of bit strings and their length.

Then there are `n` lines each consisting of one bit string of length `k`.

**Output**

Print the minimum Hamming distance between two strings.

**Constraints**

* 2 ≤ n ≤ 2⋅10<sup>4</sup>
* 1 ≤ k ≤ 30

**Requirements**

* Time limit: 1.00 s
* Memory limit: 512 MB

Example

Input:
```
5 6
110111
001000
100001
101000
101110
```

Output:
```
1
```

Explanation: The strings `101000` and `001000` differ only at the first position.

## Analysis

For any problem, before jumping into the coding part, let's spend some time to analyze it.

The naive solution is to check every pair of strings to find out the distance between them, and then find the minimum result and print it out. To compare a pair of strings, it will take `k` comparison for looping through the whole length of the strings. For `n` strings, the number of pairs will be `n ⋅ (n + 1) / 2`. Hence, the number of comparison will be around `k ⋅ n ⋅ (n + 1) / 2` which means the complexity of the solution will be O(n⋅n⋅k). This is not good enough and it is going to exceed the time limit for the worst case scenario. (Refer this [blog][codeforces-blog-guessing-algorithm] on how to "guess" a big O that will pass a specific data size.)

Hold on, why is the `k` surprisingly small? And those strings are not any arbitrary strings. Those are bit strings. A bit string with smaller-than-thirty length can just fit in a four byte integer. If we store the strings as integers, the Hamming distance between two strings is also the Hamming distance between two integers. The XOR operator returns value 1 if the two comparing bits are different. In other words, the Hamming distance between two integers `a` and `b` is the number of bit-1 (set bit) of the result of `a XOR b`.

Counting set bits of an integer is a constant time operation if we use the [Hamming weight][hamming-weight-alg-wiki] method. Although implementing the method is the purpose of this problem but I advise that you only read the article for the information and have some idea about the method. Some programming languages have already supported it. For example, C++20 provides `std::popcount()`; Python3 provides `int.bit_count()`. Many C/C++ compilers, such as GCC, MSVC also have built-in functions that support the method.

Back to the problem, because the distance calculation time is now constant, the complexity of the solution becomes O(n⋅n) which is acceptable.

## Solution

{% highlight cpp %}
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
{% endhighlight %}

I tried submitting this solution and luckily it passed all the tests.

[problem-source]: https://cses.fi/problemset/task/2136
[codeforces-blog-guessing-algorithm]: https://codeforces.com/blog/entry/21344
[hamming-weight-alg-wiki]: https://en.wikipedia.org/wiki/Hamming_weight
