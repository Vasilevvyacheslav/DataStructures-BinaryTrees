#ifndef TREEVISUALIZER_H
#define TREEVISUALIZER_H

#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include <QPen>
#include <QBrush>
#include <QFont>
#include <QColor>
#include <QString>
#include <algorithm>
#include <cmath>
#include "BST.h"
using namespace std;


class TreeVisualizer
{
private:
    QGraphicsScene* scene;
    BST* tree;

    //Параметры отрисовки
    const double Y_STEP = 80;
    const double START_X_SPREAD = 250;
    const double NODE_RADIUS = 25;

    //Рекурсивная отрисовка
    void drawNodeRec(BST::Node* node, double x, double y, double offset);
    // Рекурсивная отрисовка с подсветкой
    void drawNodeRecWithHighlight(BST::Node* node, double x, double y, double offset,
                                  double highlightNode, vector<double> visited);

public:
    TreeVisualizer(QGraphicsScene* s, BST* t);

    //Метод для отрисовки всего дерева
    void drawTree();

    // Отрисовка с подсветкой
    void drawTreeWithHighlight(double highlightNode = -1, vector<double> visited = {});
};

#endif // TREEVISUALIZER_H
