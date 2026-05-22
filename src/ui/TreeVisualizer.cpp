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

    //Рисуем рёбра (линии) к детям
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

    //Рисуем узел (круг)
    QPen pen(Qt::white, 2);
    QBrush brush(QColor(40, 40, 40)); // Темно-серый фон
    scene->addEllipse(x - NODE_RADIUS, y - NODE_RADIUS, NODE_RADIUS * 2, NODE_RADIUS * 2, pen, brush);

    //Рисуем текст (значение узла)
    QGraphicsTextItem* text = scene->addText(QString::number(node->data));
    text->setFont(QFont("Arial", 12, QFont::Bold));
    text->setDefaultTextColor(Qt::white);

    //Центрирование текста
    QRectF rect = text->boundingRect();
    text->setPos(x - rect.width() / 2, y - rect.height() / 2);
}

void TreeVisualizer::drawTreeWithHighlight(double highlightNode, vector<double> visited) {
    if (!scene || !tree) return;
    scene->clear();

    double startX = 400;
    double startY = 50;

    if (tree->getRoot()) {
        drawNodeRecWithHighlight(tree->getRoot(), startX, startY, START_X_SPREAD,
                                  highlightNode, visited);
    }
}

// Рекурсивная отрисовка с подсветкой
void TreeVisualizer::drawNodeRecWithHighlight(BST::Node* node, double x, double y, double offset,
                                               double highlightNode, vector<double> visited) {
    if (!node) return;

    double nextY = y + Y_STEP;

    // Рисуем рёбра
    if (node->left) {
        double childX = x - offset;
        scene->addLine(x, y, childX, nextY, QPen(Qt::white, 2));
        drawNodeRecWithHighlight(node->left, childX, nextY, offset / 2,
                                  highlightNode, visited);
    }

    if (node->right) {
        double childX = x + offset;
        scene->addLine(x, y, childX, nextY, QPen(Qt::white, 2));
        drawNodeRecWithHighlight(node->right, childX, nextY, offset / 2,
                                  highlightNode, visited);
    }

    // Рисуем узел с цветом в зависимости от состояния
    QPen pen(Qt::white, 2);
    QBrush brush;

    if (node->data == highlightNode) {
        // Текущий узел - жёлтый
        brush = QBrush(QColor(255, 215, 0)); // Золотой
    } else if (find(visited.begin(), visited.end(), node->data) != visited.end()) {
        // Уже посещён - зелёный
        brush = QBrush(QColor(0, 150, 0)); // Тёмно-зелёный
    } else {
        // Ещё не посещён - серый
        brush = QBrush(QColor(40, 40, 40));
    }

    scene->addEllipse(x - NODE_RADIUS, y - NODE_RADIUS,
                      NODE_RADIUS * 2, NODE_RADIUS * 2, pen, brush);

    // Текст
    QGraphicsTextItem* text = scene->addText(QString::number(node->data));
    text->setFont(QFont("Arial", 12, QFont::Bold));
    text->setDefaultTextColor(Qt::white);

    QRectF rect = text->boundingRect();
    text->setPos(x - rect.width() / 2, y - rect.height() / 2);
}
