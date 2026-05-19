#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsScene>

//Конструктор
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Создаем сцену
    QGraphicsScene* scene = new QGraphicsScene(this);

    // Устанавливаем сцену в наше поле GraphicsView (чтобы мы её видели)
    ui->graphicsTree->setScene(scene);
    //Создаём дерево и визуализатор
    tree = new BST();
    visualizer = new TreeVisualizer(scene, tree);

    //Подключаем кнопки к слотам
    connect(ui->btnInsert, &QPushButton::clicked, this, &MainWindow::onBtnInsert);
    connect(ui->btnRemove, &QPushButton::clicked, this, &MainWindow::onBtnRemove);
    connect(ui->btnSearch, &QPushButton::clicked, this, &MainWindow::onBtnSearch);
    connect(ui->btnFindMax, &QPushButton::clicked, this, &MainWindow::onBtnFindMax);

    connect(ui->btnPreorder, &QPushButton::clicked, this, &MainWindow::onBtnPreorder);
    connect(ui->btnInorder, &QPushButton::clicked, this, &MainWindow::onBtnInorder);
    connect(ui->btnPostorder, &QPushButton::clicked, this, &MainWindow::onBtnPostorder);

    connect(ui->btnBalance, &QPushButton::clicked, this, &MainWindow::onBtnBalance);
    connect(ui->btnClear, &QPushButton::clicked, this, &MainWindow::onBtnClear);

    connect(ui->btnVerticalPrint, &QPushButton::clicked, this, &MainWindow::onBtnVerticalPrint);
    connect(ui->btnHorizontalPrint, &QPushButton::clicked, this, &MainWindow::onBtnHorizontalPrint);
    //Устанавливаем фокус на поле ввода
    ui->spinValue->setFocus();
}

MainWindow::~MainWindow()
{
//Деструктор
MainWindow::~MainWindow() {
    delete tree;
    delete visualizer;
    delete ui;
}

