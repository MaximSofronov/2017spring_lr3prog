#ifndef INC_3_FUNCTIONS_H
#define INC_3_FUNCTIONS_H

#endif

#include <queue>
#include <iostream>

struct node
{
    int level;
    std::vector<int> nums; //set of items selected
    int benefit;
    int cost;
    int bound;
};

double bound(node u, int n, int MAX_COST, const std::vector<int>& c, const std::vector<int>& w);

void knapsack(int n, const std::vector<int>& c, const std::vector<int>& w, int MAX_COST);

void sort(std::vector<int>& w, std::vector<int>& c,int n);