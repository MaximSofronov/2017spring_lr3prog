#include "functions.h"


double bound(node a, int n, int MAX_COST, const std::vector<int> &c, const std::vector<int> &w) {
    if (a.cost >= MAX_COST) {
        return 0;
    }

    double result = a.benefit;
    int j = a.level;
    int totalWeight = a.cost;
    while ((j < n) && (totalWeight + w[j] <= MAX_COST)) {
        totalWeight += w[j];
        result += c[j];
        j++;
    }
    if (j < n) {
        result += (MAX_COST - totalWeight) * (double)c[j]/w[j];
    }
    return result;
}

void knapsack(int n, const std::vector<int> &c, const std::vector<int> &w, int MAX_COST) {
    std::queue<node> Q;
    node bestSoFar, a_node, currNode, nextAdded, nextNotAdded;
    Q.empty();

    for (int i = 0; i < n; i++) {
        nextAdded.nums.push_back(0);
        nextNotAdded.nums.push_back(0);
    }

    //best so far initialize
    bestSoFar.level = 0;
    bestSoFar.benefit = -1000000;
    bestSoFar.cost = 0;
    bestSoFar.bound = 0;
    for (int i = 0; i < n; i++) {
        bestSoFar.nums.push_back(0);
    }

    //a_node initialize
    a_node.level = 0;
    a_node.benefit = 0;
    a_node.cost = 0;
    for (int i = 0; i < n; i++) {
        a_node.nums.push_back(0);
    }

    a_node.bound = bound(bestSoFar, n, MAX_COST, c, w);

    Q.push(a_node);

    while (!Q.empty()) {
        //currNode
        currNode = Q.front();
        Q.pop();

        if (currNode.level < n and currNode.bound > bestSoFar.benefit) {
            //create a node nextAdded equal to currNode with the nextAdded item added
            nextAdded.level = currNode.level + 1;
            nextAdded.benefit = currNode.benefit + c[nextAdded.level - 1];
            nextAdded.cost = currNode.cost + w[nextAdded.level - 1];
            for (int i = 0; i < n; i++) {
                nextAdded.nums[i] = currNode.nums[i];
            }
            nextAdded.nums[nextAdded.level - 1] = 1;
            nextAdded.bound = bound(nextAdded, n, MAX_COST, c, w);

            if (nextAdded.cost <= MAX_COST) {
                if (nextAdded.benefit > bestSoFar.benefit) {
                    //set bestSoFar equal to nextAdded
                    bestSoFar.level = nextAdded.level;
                    bestSoFar.cost = nextAdded.cost;
                    bestSoFar.benefit = nextAdded.benefit;
                    for (int i = 0; i < n; i++) {
                        bestSoFar.nums[i] = nextAdded.nums[i];
                    }
                    bestSoFar.bound = nextAdded.bound;
                }

                if (nextAdded.bound > bestSoFar.benefit) {
                    //enqueue nextAdded
                    Q.push(nextAdded);
                }
            }

            //create a node nextNotAdded equal to currNode without the nextAdded item added
            nextNotAdded.level = currNode.level + 1;
            nextNotAdded.cost = currNode.cost;
            nextNotAdded.benefit = currNode.benefit;
            for (int i = 0; i < n; i++) {
                nextNotAdded.nums[i] = currNode.nums[i];
            }

            nextNotAdded.bound = bound(nextNotAdded, n, MAX_COST, c, w);

            if (nextNotAdded.bound > bestSoFar.benefit) {
                Q.push(nextNotAdded);
            }
        }
    }

    std::cout << std::endl << "Максимальная полезность = "<< bestSoFar.benefit << std::endl;

    int t=0;
    for (int i = 0; i < n; i++) {
        if (bestSoFar.nums[i]==1) {
            std::cout << "У " << t+1 << " вещи вес " << w[i] << " и полезность " << c[i] << std::endl;
            t++;
        }
    }
}

void sort(std::vector<int> &w, std::vector<int> &c, int n) {
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < n - i; j++) {
            if ((double) c[j] / w[j] < (double) c[j + 1] / w[j + 1]) {
                std::swap(c[j], c[j + 1]);
                std::swap(w[j], w[j + 1]);
            }
        }
    }
}