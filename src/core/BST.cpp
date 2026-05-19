#include "BST.h"
#include <cmath>

//Конструктор
BST::BST() : root(nullptr) {}

//Деструктор
BST::~BST() {
    clear();
}

//==================== ВСПОМОГАТЕЛЬНЫЕ МЕТОДЫ ====================

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

//==================== ЯДРО ДЕРЕВА ====================

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

//==================== ОБХОДЫ ====================

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

//==================== ПЕЧАТЬ ====================

//Вертикальная печать (уровень + значение)
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
    res += to_string(node->data) + "\n";

    horizontalPrint(node->left, space, res);
}

//==================== ПУБЛИЧНЫЕ МЕТОДЫ ====================

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

//Найти максимум (вариант 24)
double BST::findMax() {
    if (!root) throw runtime_error("Tree is empty");
    return findMax(root)->data;
}

//Найти минимум
double BST::findMin() {
    if (!root) throw runtime_error("Tree is empty");
    return findMin(root)->data;
}

//Получить обход (обёртки)
vector<double> BST::preorder() {
    vector<double> res; preorder(root, res); return res;
}
vector<double> BST::inorder() {
    vector<double> res; inorder(root, res); return res;
}
vector<double> BST::postorder() {
    vector<double> res; postorder(root, res); return res;
}

//Получить печать (обёртки)
string BST::verticalPrint() {
    vector<pair<int, double>> res; verticalPrint(root, 0, res);
    string out;
    for (auto& p : res) out += "Level " + to_string(p.first) + ": " + to_string(p.second) + "\n";
    return out;
}
string BST::horizontalPrint() {
    string res; horizontalPrint(root, 0, res); return res;
}

//AVL балансировка (перестроение из отсортированного массива)
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
