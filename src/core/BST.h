#ifndef BST_H
#define BST_H

#include <vector>
#include <string>
#include <queue>
#include <functional>
#include "TraversalSteps.h"
using namespace std;

class BST {
protected:
    //Узел дерева
    struct Node {
        double data;
        Node* left;
        Node* right;
        int height; //Для AVL

        Node(double value) : data(value), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root;

private:
    //Вспомогательные методы
    Node* insert(Node* node, double value);
    Node* remove(Node* node, double value);
    Node* search(Node* node, double value);
    Node* findMin(Node* node);
    Node* findMax(Node* node);
    int getHeight(Node* node);
    int getBalance(Node* node);
    Node* rotateRight(Node* y);
    Node* rotateLeft(Node* x);

    //Обходы
    void preorder(Node* node, vector<double>& res);
    void inorder(Node* node, vector<double>& res);
    void postorder(Node* node, vector<double>& res);

    //Печать
    void verticalPrint(Node* node, int level, vector<pair<int, double>>& res);
    void horizontalPrint(Node* node, int space, string& res);

    // Рекурсивные методы для генерации шагов
    void preorderSteps(Node* node, vector<TraversalStep>& steps, int& stepNum, vector<double> visited);
    void inorderSteps(Node* node, vector<TraversalStep>& steps, int& stepNum, vector<double> visited);
    void postorderSteps(Node* node, vector<TraversalStep>& steps, int& stepNum, vector<double> visited);
    void searchSteps(Node* node, double value, vector<TraversalStep>& steps, int& stepNum, bool& found);
    // Метод отвечающий за подсчёт шагов анимации
    void makeStep(vector<TraversalStep>& steps, int& stepNum, double nodeVal, const string& text, const vector<double>& visited);
public:
    BST();
    ~BST();

    //Основные операции
    void insert(double value);
    bool remove(double value);
    bool search(double value);
    bool isEmpty();
    void clear();

    //Поиск максимального узла
    double findMax();

    //Обходы
    vector<double> preorder();
    vector<double> inorder();
    vector<double> postorder();

    //Печать
    string verticalPrint();
    string horizontalPrint();

    //AVL балансировка
    void balance();

    //Для визуализации
    Node* getRoot() { return root; }
    vector<Node*> getAllNodes();
    friend class TreeVisualizer;

    // Генерация шагов для анимации
    vector<TraversalStep> generatePreorderSteps();
    vector<TraversalStep> generateInorderSteps();
    vector<TraversalStep> generatePostorderSteps();
    vector<TraversalStep> generateSearchSteps(double value, bool& found);
};

#endif // BST_H
