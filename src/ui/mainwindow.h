#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "BST.h"
#include "TreeVisualizer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    Ui::MainWindow *ui;
    BST* tree;
    TreeVisualizer* visualizer;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

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
};

#endif // MAINWINDOW_H
