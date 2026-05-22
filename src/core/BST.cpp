#include "BST.h"
#include "TraversalSteps.h"
#include <cmath>
#include <stdexcept>
#include <iomanip>
//Конструктор
BST::BST() : root(nullptr) {}

//Деструктор
BST::~BST() {
    clear();
}

//Высота узла
int BST::getHeight(Node* node) {
    return node ? node->height : 0;
}

//Баланс узла (разница высот)
int BST::getBalance(Node* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

//Правый поворот (AVL)
BST::Node* BST::rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    return x;
}

//Левый поворот (AVL)
BST::Node* BST::rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    return y;
}

// Подсчёт шагов
void BST::makeStep(vector<TraversalStep>& steps, int& stepNum, double nodeVal, const string& text, const vector<double>& visited) {
    TraversalStep step;
    step.stepNumber = stepNum++; // <-- Присваиваем текущий номер и сразу увеличиваем счетчик
    step.currentNode = nodeVal;
    step.logText = text;
    step.visited = visited;
    steps.push_back(step);
}
//Рекурсивная вставка
BST::Node* BST::insert(Node* node, double value) {
    if (!node) return new Node(value);

    if (value < node->data) node->left = insert(node->left, value);
    else if (value > node->data) node->right = insert(node->right, value);
    else return node; //Дубликат не вставляем

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    return node;
}

//Рекурсивное удаление
BST::Node* BST::remove(Node* node, double value) {
    if (!node) return node;

    if (value < node->data) node->left = remove(node->left, value);
    else if (value > node->data) node->right = remove(node->right, value);
    else {
        //Узел найден
        if (!node->left) {
            Node* temp = node->right;
            delete node;
            return temp;
        } else if (!node->right) {
            Node* temp = node->left;
            delete node;
            return temp;
        }

        //Два потомка: заменяем на минимальный из правого
        Node* temp = findMin(node->right);
        node->data = temp->data;
        node->right = remove(node->right, temp->data);
    }

    if (!node) return node;
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    return node;
}

//Рекурсивный поиск
BST::Node* BST::search(Node* node, double value) {
    if (!node || node->data == value) return node;
    return value < node->data ? search(node->left, value) : search(node->right, value);
}

//Поиск минимального узла
BST::Node* BST::findMin(Node* node) {
    while (node && node->left) node = node->left;
    return node;
}

//Поиск максимального узла
BST::Node* BST::findMax(Node* node) {
    while (node && node->right) node = node->right;
    return node;
}

//Прямой обход (Корень-Левое-Правое)
void BST::preorder(Node* node, vector<double>& res) {
    if (node) {
        res.push_back(node->data);
        preorder(node->left, res);
        preorder(node->right, res);
    }
}

//Симметричный обход (Левое-Корень-Правое)
void BST::inorder(Node* node, vector<double>& res) {
    if (node) {
        inorder(node->left, res);
        res.push_back(node->data);
        inorder(node->right, res);
    }
}

//Обратный обход (Левое-Правое-Корень)
void BST::postorder(Node* node, vector<double>& res) {
    if (node) {
        postorder(node->left, res);
        postorder(node->right, res);
        res.push_back(node->data);
    }
}

//Вертикальная печать (по уровням - BFS)
void BST::verticalPrint(Node* node, int level, vector<pair<int, double>>& res) {
    if (node) {
        res.push_back({level, node->data});
        verticalPrint(node->left, level + 1, res);
        verticalPrint(node->right, level + 1, res);
    }
}

//Горизонтальная печать (повёрнутая на 90°)
void BST::horizontalPrint(Node* node, int space, string& res) {
    if (!node) return;

    space += 10;
    horizontalPrint(node->right, space, res);

    res += "\n";
    for (int i = 10; i < space; i++) res += " ";

    ostringstream oss;
    oss << fixed << setprecision(2) << node->data;
    res += oss.str();

    horizontalPrint(node->left, space, res);
}

//Вставка (обёртка)
void BST::insert(double value) {
    root = insert(root, value);
}

//Удаление (обёртка)
bool BST::remove(double value) {
    if (!search(root, value)) return false;
    root = remove(root, value);
    return true;
}

//Поиск (обёртка)
bool BST::search(double value) {
    return search(root, value) != nullptr;
}

//Проверка на пустоту
bool BST::isEmpty() {
    return root == nullptr;
}

//Очистка дерева
void BST::clear() {
    vector<double> all = postorder();
    for (double val : all) remove(val);
    root = nullptr;
}

//Найти максимум
double BST::findMax() {
    if (!root) throw runtime_error("Tree is empty");
    return findMax(root)->data;
}

//Получить обход
vector<double> BST::preorder() {
    vector<double> res; preorder(root, res); return res;
}
vector<double> BST::inorder() {
    vector<double> res; inorder(root, res); return res;
}
vector<double> BST::postorder() {
    vector<double> res; postorder(root, res); return res;
}

//Получить печать
string BST::verticalPrint() {
    if (!root) return "Дерево пусто";

    string output;
    queue<pair<Node*, int>> q;
    q.push({root, 0});

    int currentLevel = 0;
    bool firstInLevel = true;

    while (!q.empty()) {
        pair<Node*, int> current = q.front();
        q.pop();

        Node* node = current.first;
        int level = current.second;

        // Если перешли на новый уровень - добавляем перенос строки
        if (level != currentLevel) {
            output += "\n";
            currentLevel = level;
            firstInLevel = true;
        }

        // Пишем заголовок уровня только один раз
        if (firstInLevel) {
            output += "Уровень " + to_string(level) + ": ";
            firstInLevel = false;
        }

        // Добавляем значение узла
        ostringstream oss;
        oss << fixed << setprecision(2) << node->data;
        output += oss.str() + "  ";

        // Добавляем детей в очередь
        if (node->left) q.push({node->left, level + 1});
        if (node->right) q.push({node->right, level + 1});
    }

    return output + "\n";
}
string BST::horizontalPrint() {
    string res; horizontalPrint(root, 0, res); return res;
}

//AVL балансировка
void BST::balance() {
    vector<double> sorted = inorder();
    clear();

    //Рекурсивное построение сбалансированного дерева
    function<void(int, int)> build = [&](int l, int r) {
        if (l > r) return;
        int mid = l + (r - l) / 2;
        insert(sorted[mid]);
        build(l, mid - 1);
        build(mid + 1, r);
    };
    build(0, sorted.size() - 1);
}

//Получить все узлы (для визуализации, обход в ширину)
vector<BST::Node*> BST::getAllNodes() {
    vector<Node*> nodes;
    queue<Node*> q;
    if (root) q.push(root);

    while (!q.empty()) {
        Node* cur = q.front(); q.pop();
        nodes.push_back(cur);
        if (cur->left) q.push(cur->left);
        if (cur->right) q.push(cur->right);
    }
    return nodes;
}

vector<TraversalStep> BST::generatePreorderSteps() {
    vector<TraversalStep> steps;
    int stepNum = 1;
    vector<double> visited;
    preorderSteps(root, steps, stepNum, visited);
    return steps;
}

vector<TraversalStep> BST::generateInorderSteps() {
    vector<TraversalStep> steps;
    int stepNum = 1;
    vector<double> visited;
    inorderSteps(root, steps, stepNum, visited);
    return steps;
}

vector<TraversalStep> BST::generatePostorderSteps() {
    vector<TraversalStep> steps;
    int stepNum = 1;
    vector<double> visited;
    postorderSteps(root, steps, stepNum, visited);
    return steps;
}

// Рекурсивная генерация прямого обхода
void BST::preorderSteps(Node* node, vector<TraversalStep>& steps, int& stepNum, vector<double> visited) {
    if (!node) return;

    // Посещаем узел
    visited.push_back(node->data);
    makeStep(steps, stepNum, node->data, "Посещаем узел: " + to_string(node->data), visited);

    // Переход влево
    if (node->left) {
        makeStep(steps, stepNum, node->left->data, "Переход влево к " + to_string(node->left->data), visited);
    }
    preorderSteps(node->left, steps, stepNum, visited);

    // Переход вправо
    if (node->right) {
        makeStep(steps, stepNum, node->right->data, "Переход вправо к " + to_string(node->right->data), visited);
    }
    preorderSteps(node->right, steps, stepNum, visited);
}

// Рекурсивная генерация симметричного обхода
void BST::inorderSteps(Node* node, vector<TraversalStep>& steps, int& stepNum, vector<double> visited) {
    if (!node) return;

    // Переход влево
    if (node->left) {
        makeStep(steps, stepNum, node->left->data, "Спускаемся влево к " + to_string(node->left->data), visited);
    }
    inorderSteps(node->left, steps, stepNum, visited);

    // Посещаем узел
    visited.push_back(node->data);
    makeStep(steps, stepNum, node->data, "Посещаем узел: " + to_string(node->data), visited);

    // Переход вправо
    if (node->right) {
        makeStep(steps, stepNum, node->right->data, "Переход вправо к " + to_string(node->right->data), visited);
    }
    inorderSteps(node->right, steps, stepNum, visited);
}

// Рекурсивная генерация обратного обхода
void BST::postorderSteps(Node* node, vector<TraversalStep>& steps, int& stepNum, vector<double> visited) {
    if (!node) return;

    // Переход влево
    if (node->left) {
        makeStep(steps, stepNum, node->left->data, "Спускаемся влево к " + to_string(node->left->data), visited);
    }
    postorderSteps(node->left, steps, stepNum, visited);

    // Переход вправо
    if (node->right) {
        makeStep(steps, stepNum, node->right->data, "Переход вправо к " + to_string(node->right->data), visited);
    }
    postorderSteps(node->right, steps, stepNum, visited);

    // Посещаем узел
    visited.push_back(node->data);
    makeStep(steps, stepNum, node->data, "Посещаем узел: " + to_string(node->data), visited);
}

// Генерация шагов поиска
vector<TraversalStep> BST::generateSearchSteps(double value, bool& found) {
    vector<TraversalStep> steps;
    int stepNum = 1;
    found = false; // Сбрасываем флаг перед стартом

    searchSteps(root, value, steps, stepNum, found);

    // Если элемент не найден, добавим финальный шаг "Не найдено"
    if (!found) {
        TraversalStep step;
        step.stepNumber = stepNum++;
        step.currentNode = value; // Подсвечиваем искомое значение
        step.logText = "Элемент " + to_string(value) + " не найден!";
        steps.push_back(step);
    }
    // Если найден, последний узел уже добавлен в список visited внутри searchSteps,
    // поэтому он подсветится зеленым.

    return steps;
}

void BST::searchSteps(Node* node, double value, vector<TraversalStep>& steps, int& stepNum, bool& found) {
    if (!node) return;

    TraversalStep step;
    step.stepNumber = stepNum++;
    step.currentNode = node->data;

    // Проверка на совпадение
    if (value == node->data) {
        found = true;
        step.logText = "Проверяем " + to_string(node->data) + " -> НАЙДЕНО!";
        step.visited.push_back(node->data); // Добавляем в visited, чтобы стал зеленым
        steps.push_back(step);
        return; // Заканчиваем поиск
    }

    // Если не совпало, узел все равно становится частью "пройденного пути" (зеленым)
    step.visited.push_back(node->data);

    if (value < node->data) {
        step.logText = "Проверяем " + to_string(node->data) + " -> Идем влево";
        steps.push_back(step);
        searchSteps(node->left, value, steps, stepNum, found);
    } else {
        step.logText = "Проверяем " + to_string(node->data) + " -> Идем вправо";
        steps.push_back(step);
        searchSteps(node->right, value, steps, stepNum, found);
    }
}
