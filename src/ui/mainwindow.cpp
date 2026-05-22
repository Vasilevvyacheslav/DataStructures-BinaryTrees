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

    animationTimer = new QTimer(this);
    connect(animationTimer, &QTimer::timeout, this, &MainWindow::showNextStep);
    currentStepIndex = 0;

    isSearchAnimation = false;
}

//Деструктор
MainWindow::~MainWindow() {
    delete tree;
    delete visualizer;
    delete ui;
}

//Вставка узла
void MainWindow::onBtnInsert() {
    double value = ui->spinValue->value();

    if (tree->search(value)) {
        QMessageBox::warning(this, "Ошибка",
            QString("Элемент %1 уже существует!").arg(value, 0, 'f', 2));
        return;
    }

    tree->insert(value);
    visualizer->drawTree();

    ui->textOutput->appendPlainText(QString("Вставлено: %1").arg(value, 0, 'f', 2));
}

//Удаление узла
void MainWindow::onBtnRemove() {
    double value = ui->spinValue->value();

    if (tree->remove(value)) {
        visualizer->drawTree();
        ui->textOutput->appendPlainText(QString("Удалено: %1").arg(value, 0, 'f', 2));
    } else {
        QMessageBox::warning(this, "Ошибка",
            QString("Элемент %1 не найден!").arg(value, 0, 'f', 2));
    }
}

//Поиск узла с анимацией
void MainWindow::onBtnSearch() {
    if (tree->isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Дерево пусто!");
        return;
    }

    double value = ui->spinValue->value();
    isSearchAnimation = true; // Включаем режим поиска

    vector<TraversalStep> steps = tree->generateSearchSteps(value, searchFound);
    startAnimation(steps);
}

//Поиск максимума
void MainWindow::onBtnFindMax() {
    if (tree->isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Дерево пусто!");
        return;
    }

    double maxVal = tree->findMax();
    ui->textOutput->appendPlainText(QString("Максимум: %1").arg(maxVal, 0, 'f', 2));
    QMessageBox::information(this, "Максимум",
        QString("Максимальный элемент: %1").arg(maxVal, 0, 'f', 2));
}

// Прямой обход с анимацией
void MainWindow::onBtnPreorder() {
    if (animationTimer->isActive()) {
        // Если анимация уже идёт — останавливаем
        stopAnimation();
        ui->textOutput->appendPlainText("Анимация остановлена пользователем");
        return;
    }

    if (tree->isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Дерево пусто!");
        return;
    }
    currentTraversalType = "Прямой";
    vector<TraversalStep> steps = tree->generatePreorderSteps();
    startAnimation(steps);
}

// Симметричный обход с анимацией
void MainWindow::onBtnInorder() {
    if (animationTimer->isActive()) {
        // Если анимация уже идёт — останавливаем
        stopAnimation();
        ui->textOutput->appendPlainText("Анимация остановлена пользователем");
        return;
    }

    if (tree->isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Дерево пусто!");
        return;
    }
    currentTraversalType = "Симметричный";
    vector<TraversalStep> steps = tree->generateInorderSteps();
    startAnimation(steps);
}

// Обратный обход с анимацией
void MainWindow::onBtnPostorder() {
    if (animationTimer->isActive()) {
        // Если анимация уже идёт — останавливаем
        stopAnimation();
        ui->textOutput->appendPlainText("Анимация остановлена пользователем");
        return;
    }

    if (tree->isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Дерево пусто!");
        return;
    }
    currentTraversalType = "Обратный";
    vector<TraversalStep> steps = tree->generatePostorderSteps();
    startAnimation(steps);
}

//AVL балансировка
void MainWindow::onBtnBalance() {
    if (tree->isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Дерево пусто!");
        return;
    }

    tree->balance();
    visualizer->drawTree();

    ui->textOutput->appendPlainText("Дерево сбалансировано");
    QMessageBox::information(this, "Балансировка", "Дерево успешно сбалансировано!");
}

//Очистка дерева
void MainWindow::onBtnClear() {
    if (tree->isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Дерево уже пусто!");
        return;
    }

    tree->clear();
    visualizer->drawTree();
    ui->textOutput->appendPlainText("Дерево очищено");
    QMessageBox::information(this, "Очистка", "Все узлы удалены");
}

//Вертикальная печать
void MainWindow::onBtnVerticalPrint() {
    if (tree->isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Дерево пусто!");
        return;
    }

    QString output = QString::fromStdString(tree->verticalPrint());
    ui->textOutput->appendPlainText("=== Вертикальная печать ===");
    ui->textOutput->appendPlainText(output);
}

//Горизонтальная печать
void MainWindow::onBtnHorizontalPrint() {
    if (tree->isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Дерево пусто!");
        return;
    }

    QString output = QString::fromStdString(tree->horizontalPrint());
    ui->textOutput->appendPlainText("=== Горизонтальная печать ===");
    ui->textOutput->appendPlainText(output);
}

// Запуск анимации
void MainWindow::startAnimation(vector<TraversalStep> steps) {
    currentSteps = steps;
    currentStepIndex = 0;

    if (currentSteps.empty()) {
        QMessageBox::warning(this, "Ошибка", "Дерево пусто!");
        return;
    }

    // Показываем первый шаг
    showNextStep();

    // Запускаем таймер (1 шаг в секунду)
    animationTimer->start(1000);

    ui->textOutput->appendPlainText("Запуск анимации...");
}

// Показ следующего шага
void MainWindow::showNextStep() {
    if (currentStepIndex >= currentSteps.size()) {
        stopAnimation();
        ui->textOutput->appendPlainText("Анимация завершена!");
        return;
    }
    TraversalStep& step = currentSteps[currentStepIndex];
    // Подсвечиваем узел
    visualizer->drawTreeWithHighlight(step.currentNode, step.visited);
    // Вывод лога
    ui->textOutput->appendPlainText(
        QString("Шаг %1: %2").arg(step.stepNumber).arg(QString::fromStdString(step.logText))
    );

    currentStepIndex++;
}

// Остановка анимации
void MainWindow::stopAnimation() {
    animationTimer->stop();
    currentSteps.clear();
    // Возвращаем обычную отрисовку
    visualizer->drawTree();

    // Если это был поиск
    if (isSearchAnimation) {
        if (searchFound) {
            QMessageBox::information(this, "Поиск", "Элемент найден!");
            ui->textOutput->appendPlainText("Элемент найден в дереве.");
        } else {
            QMessageBox::warning(this, "Поиск", "Элемент не найден.");
            ui->textOutput->appendPlainText("Элемент отсутствует в дереве.");
        }
        isSearchAnimation = false; // Сбрасываем флаг
    }
    if (currentTraversalType == "Прямой") {
        printFinalResult(tree->preorder(), currentTraversalType);
    }
    else if (currentTraversalType == "Симметричный") {
        printFinalResult(tree->inorder(), currentTraversalType);
    }
    else if (currentTraversalType == "Обратный") {
        printFinalResult(tree->postorder(), currentTraversalType);
    }
    currentTraversalType = "";
    ui->textOutput->appendPlainText("Анимация завершена!");
}

// Метод для вывода строки с результатами
void MainWindow::printFinalResult(const vector<double>& res, const QString& type) {
    QString output = type + " обход: ";
    for (double val : res) {
        output += QString::number(val, 'f', 2) + " ";
    }
    ui->textOutput->appendPlainText(output);
}
