#include "MainWindow.h"
#include "QDebug"
#include "./ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}


MainWindow* MainWindow::instance = nullptr;

MainWindow *MainWindow::getInstance()
{
    if ( instance == nullptr ) {
        instance = new MainWindow();
    }

    return instance;
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    qDebug()<<"Open File";
}

