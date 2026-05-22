#ifndef TRAVERSALSTEPS_H
#define TRAVERSALSTEPS_H

#include <vector>
#include <string>
using namespace std;

// Шаг обхода дерева
struct TraversalStep {
    double currentNode;// Текущий узел
    vector<double> visited;// Уже посещённые узлы
    string logText;// Описание шага
    int stepNumber;// Номер шага
};

#endif // TRAVERSALSTEPS_H
