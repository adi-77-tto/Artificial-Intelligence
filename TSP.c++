#include <bits/stdc++.h>
using namespace std;

const int N = 4;                 
const int POP_SIZE = 6;
const int GENERATIONS = 100;
const double MUTATION_RATE = 0.1;

int dist[N][N] = {
    {0, 10, 15, 20},
    {10, 0, 35, 25},
    {15, 35, 0, 30},
    {20, 25, 30, 0}
};

int calculateDistance(vector<int> route) {
    int cost = 0;
    for (int i = 0; i < N - 1; i++) {
        cost += dist[route[i]][route[i + 1]];
    }
    cost += dist[route[N - 1]][route[0]];
    return cost;
}

double fitness(vector<int> route) {
    return 1.0 / calculateDistance(route);
}

// 🔹 Generate random chromosome
vector<int> randomRoute() {
    vector<int> route;
    for (int i = 0; i < N; i++) route.push_back(i);
    random_shuffle(route.begin() + 1, route.end()); 
    return route;
}

vector<int> selectParent(vector<vector<int>> &population) {
    vector<double> fit;
    double total = 0;

    for (auto &ind : population) {
        double f = fitness(ind);
        fit.push_back(f);
        total += f;
    }

    double r = ((double)rand() / RAND_MAX) * total;
    double sum = 0;

    for (int i = 0; i < population.size(); i++) {
        sum += fit[i];
        if (sum >= r) return population[i];
    }

    return population.back();
}

vector<int> crossover(vector<int> p1, vector<int> p2) {
    vector<int> child(N, -1);

    int start = rand() % N;
    int end = rand() % N;
    if (start > end) swap(start, end);

    for (int i = start; i <= end; i++) {
        child[i] = p1[i];
    }

    int j = 0;
    for (int i = 0; i < N; i++) {
        if (child[i] == -1) {
            while (find(child.begin(), child.end(), p2[j]) != child.end()) {
                j++;
            }
            child[i] = p2[j++];
        }
    }

    return child;
}

void mutate(vector<int> &route) {
    if ((double)rand() / RAND_MAX < MUTATION_RATE) {
        int i = rand() % N;
        int j = rand() % N;
        swap(route[i], route[j]);
    }
}

void printRoute(vector<int> route) {
    for (int i : route) cout << char('A' + i) << " ";
    cout << char('A' + route[0]); 
}

int main() {
    srand(time(0));

    vector<vector<int>> population;

    for (int i = 0; i < POP_SIZE; i++) {
        population.push_back(randomRoute());
    }

    vector<int> bestRoute;
    int bestCost = INT_MAX;

    for (int gen = 0; gen < GENERATIONS; gen++) {
        vector<vector<int>> newPop;

        for (int i = 0; i < POP_SIZE; i++) {
            vector<int> p1 = selectParent(population);
            vector<int> p2 = selectParent(population);

            vector<int> child = crossover(p1, p2);
            mutate(child);

            newPop.push_back(child);

            int cost = calculateDistance(child);
            if (cost < bestCost) {
                bestCost = cost;
                bestRoute = child;
            }
        }

        population = newPop;
    }

    cout << "Best Route: ";
    printRoute(bestRoute);
    cout << "\nMinimum Cost: " << bestCost << endl;
    return 0;
}