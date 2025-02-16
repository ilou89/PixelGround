#include "MainWindow.h"
#include "QFileDialog"
#include "QDebug"
#include "./ui_MainWindow.h"
#include "ImageOperations.h"

void (*imgOperation[2])(QImage*, QImage*) = {NULL, gaussianBlur};

MainWindow* MainWindow::instance = nullptr;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsViewInput->setScene(scene);
    ui->graphicsViewOutput->setVisible(false);
    params.filterSize = 3;
    params.sigma      = 1.f;
    resizeEvent(nullptr);
}

void MainWindow::resizeEvent(QResizeEvent *)
{
    ui->spinBoxFilterSize->setMinimumWidth(ui->comboBoxOperation->width());
    ui->doubleSpinBoxSigma->setMinimumWidth(ui->comboBoxImplementation->width());

    ui->spinBoxFilterSize->setMaximumWidth(ui->comboBoxOperation->width());
    ui->doubleSpinBoxSigma->setMaximumWidth(ui->comboBoxImplementation->width());

    if ( inputImage.isNull() == false ) {
        ui->graphicsViewInput->fitInView(inputImage.rect(), Qt::KeepAspectRatio);
    }

}


MainWindow *MainWindow::getInstance()
{
    if ( instance == nullptr ) {
        instance = new MainWindow();
    }

    return instance;
}

const OperationParameters *MainWindow::getParams()
{
    return &(this->params);
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
            ui->graphicsViewInput->fitInView(inputImage.rect(), Qt::KeepAspectRatio);
        }

        outputImage = inputImage.copy();
    }
}


void MainWindow::on_actionShowInput_triggered(bool checked)
{
    ui->graphicsViewInput->setVisible(checked);
    resizeEvent(nullptr);
}

void MainWindow::on_actionShowOutput_triggered(bool checked)
{
    ui->graphicsViewOutput->setVisible(checked);
    resizeEvent(nullptr);
}


void MainWindow::on_comboBoxOperation_currentIndexChanged(int index)
{
    if ( index > 0 ) {
        imgOperation[index](&inputImage, &outputImage);
    }
}

void MainWindow::on_spinBoxFilterSize_valueChanged(int arg1)
{
    params.filterSize = arg1;
}


void MainWindow::on_doubleSpinBoxSigma_valueChanged(double arg1)
{
    params.sigma = (float) arg1;
}

