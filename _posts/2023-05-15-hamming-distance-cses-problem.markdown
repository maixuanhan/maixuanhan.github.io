---
layout: post
title:  "Hamming Distance [CSES Problem Set]"
date:   2023-05-15 23:00:00 +0800
categories: coding problem
--- 
The CSES Problem Set is a collection of algorithmic programming problems provided by Code Submission Evaluation System website. The following problem is randomly picked from it. You can find it [here][problem-source].

## Hamming Distance

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

The naive solution is to check every pair of strings to find out the distance between them, and then find the minimum result and print it out. The number of comparison will be around `n ⋅ n ⋅ k` which means the complexity of the solution will be O(n⋅n⋅k). This is not good enough and it's going to exceed the time limit for a worst case scenario.

(continue)

[problem-source]: https://cses.fi/problemset/task/2136
