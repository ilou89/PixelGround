#include "MainWindow.h"
#include "QFileDialog"
#include "QDebug"
#include "./ui_MainWindow.h"

MainWindow* MainWindow::instance = nullptr;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsViewInput->setScene(scene);
}

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
    scene->clear();
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), nullptr, tr("Image Files (*.png *.jpg)"));
    inputImage = QImage(fileName);

    if ( inputImage.isNull() == false ) {
        QPixmap pix;
        pix = QPixmap::fromImage(inputImage);
        if(pix.isNull()==0){
            scene->addPixmap(pix);

            //TODO zoom in-out
            ui->graphicsViewInput->fitInView(pix.rect());
        }
    }
}

