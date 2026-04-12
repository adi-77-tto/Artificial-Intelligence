#include <bits/stdc++.h>
using namespace std;

const int N = 8;
const int POP_SIZE = 6;
const double MUTATION_RATE = 0.1;

string randomChromosome() {
    string s = "";
    for (int i = 0; i < N; i++) {
        s += char('1' + rand() % 8);
    }
    return s;
}

int fitness(string s) {
    int conflicts = 0;

    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            int r1 = s[i] - '0';
            int r2 = s[j] - '0';

            if (r1 == r2 || abs(r1 - r2) == abs(i - j)) {
                conflicts++;
            }
        }
    }

    int totalPairs = 28;
    return totalPairs - conflicts;
}

string selectParent(vector<string>& pop) {
    vector<int> fit;
    int total = 0;

    for (auto &ind : pop) {
        int f = fitness(ind);
        fit.push_back(f);
        total += f;
    }

    int r = rand() % total;
    int sum = 0;

    for (int i = 0; i < pop.size(); i++) {
        sum += fit[i];
        if (sum > r) return pop[i];
    }

    return pop.back();
}

string crossover(string p1, string p2) {
    int point = rand() % N;
    return p1.substr(0, point) + p2.substr(point);
}

void mutate(string &child) {
    for (int i = 0; i < N; i++) {
        if ((double)rand() / RAND_MAX < MUTATION_RATE) {
            child[i] = char('1' + rand() % 8);
        }
    }
}

void printBoard(string s) {
    cout << "Board:\n";
    for (int i = 0; i < N; i++) {
        for (int j = 1; j <= N; j++) {
            if (s[i] - '0' == j) cout << "Q ";
            else cout << ". ";
        }
        cout << endl;
    }
}

int main() {
    srand(time(0));

    vector<string> population;

    for (int i = 0; i < POP_SIZE; i++) {
        population.push_back(randomChromosome());
    }

    int generation = 0;

    while (true) {
        cout << "\nGeneration " << generation << ":\n";

        for (auto &ind : population) {
            cout << ind << " Fitness: " << fitness(ind) << endl;
        }

        for (auto &ind : population) {
            if (fitness(ind) == 28) {
                cout << "\nSolution Found: " << ind << endl;
                printBoard(ind);
                return 0;
            }
        }

        vector<string> newPop;

        for (int i = 0; i < POP_SIZE; i++) {
            string p1 = selectParent(population);
            string p2 = selectParent(population);

            string child = crossover(p1, p2);
            mutate(child);

            newPop.push_back(child);
        }

        population = newPop;
        generation++;
    }

}