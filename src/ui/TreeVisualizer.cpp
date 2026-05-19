#include "TreeVisualizer.h"

//Конструктор
TreeVisualizer::TreeVisualizer(QGraphicsScene* s, BST* t) : scene(s), tree(t) {}

//Отрисовка всего дерева
void TreeVisualizer::drawTree() {
    if (!scene || !tree) return;
    scene->clear();

    //Начальная позиция (центр по X, отступ сверху)
    double startX = 400;
    double startY = 50;

    //Если дерево не пустое, запускаем рекурсию
    if (tree->getRoot()) {
        drawNodeRec(tree->getRoot(), startX, startY, START_X_SPREAD);
    }
}

//Рекурсивная функция отрисовки
void TreeVisualizer::drawNodeRec(BST::Node* node, double x, double y, double offset) {
    if (!node) return;

    double nextY = y + Y_STEP;

    //1. Рисуем рёбра (линии) к детям
    if (node->left) {
        double childX = x - offset;
        scene->addLine(x, y, childX, nextY, QPen(Qt::white, 2));
        drawNodeRec(node->left, childX, nextY, offset / 2);
    }

    if (node->right) {
        double childX = x + offset;
        scene->addLine(x, y, childX, nextY, QPen(Qt::white, 2));
        drawNodeRec(node->right, childX, nextY, offset / 2);
    }

    //2. Рисуем узел (круг)
    QPen pen(Qt::white, 2);
    QBrush brush(QColor(40, 40, 40)); // Темно-серый фон
    scene->addEllipse(x - NODE_RADIUS, y - NODE_RADIUS, NODE_RADIUS * 2, NODE_RADIUS * 2, pen, brush);

    //3. Рисуем текст (значение узла)
    QGraphicsTextItem* text = scene->addText(QString::number(node->data));
    text->setFont(QFont("Arial", 12, QFont::Bold));
    text->setDefaultTextColor(Qt::white);

    //Центрирование текста
    QRectF rect = text->boundingRect();
    text->setPos(x - rect.width() / 2, y - rect.height() / 2);
}
