#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTimer>
#include <QMainWindow>
#include <QMessageBox>
#include "BST.h"
#include "TreeVisualizer.h"
#include "TraversalSteps.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    Ui::MainWindow *ui;
    BST* tree;
    TreeVisualizer* visualizer;
    QString currentTraversalType; // Для запоминания типа обхода
    bool isSearchAnimation; // Флаг: идет ли сейчас анимация поиска
    bool searchFound; // Результат поиска (найден/не найден)
    // Для анимации
    vector<TraversalStep> currentSteps;
    int currentStepIndex;
    QTimer* animationTimer;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    // Методы анимации
    void startAnimation(vector<TraversalStep> steps);
    void stopAnimation();
    // Вывод финального списка после обхода
    void printFinalResult(const vector<double>& res, const QString& type);

private slots:
    //Основные операции
    void onBtnInsert();
    void onBtnRemove();
    void onBtnSearch();
    void onBtnFindMax();

    //Обходы
    void onBtnPreorder();
    void onBtnInorder();
    void onBtnPostorder();

    //Балансировка
    void onBtnBalance();

    //Полная очистка дерева
    void onBtnClear();

    //Печать
    void onBtnVerticalPrint();
    void onBtnHorizontalPrint();

    void showNextStep();
};

#endif // MAINWINDOW_H
