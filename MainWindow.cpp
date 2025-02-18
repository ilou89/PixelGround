#include "MainWindow.h"
#include <QFileDialog>
#include <QDebug>
#include "./ui_MainWindow.h"
#include "ImageOperations.h"

void (*imgOperation[2])(QImage*, QImage*, QProgressDialog*) = {NULL, gaussianBlur};

MainWindow* MainWindow::instance = nullptr;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    inputScene = new QGraphicsScene(this);
    ui->graphicsViewInput->setScene(inputScene);
    outputScene = new QGraphicsScene(this);
    ui->graphicsViewOutput->setScene(outputScene);

    ui->graphicsViewOutput->setVisible(false);
    ui->label->setVisible(false);
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

    if ( outputImage.isNull() == false ) {
        ui->graphicsViewOutput->fitInView(outputImage.rect(), Qt::KeepAspectRatio);
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
    inputScene->clear();
    outputScene->clear();
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), nullptr, tr("Image Files (*.png *.jpg)"));
    inputImage = QImage(fileName);

    if ( inputImage.isNull() == false ) {
        QPixmap pix = QPixmap::fromImage(inputImage);
        if(pix.isNull()==0){
            inputScene->addPixmap(pix);

            //TODO zoom in-out
            ui->graphicsViewInput->fitInView(inputImage.rect(), Qt::KeepAspectRatio);
        }

        outputImage = inputImage.copy();

        QString res =  QString::number(inputImage.width()) + "x" + QString::number(inputImage.height());
        ui->statusbar->showMessage(res);
    }
}


void MainWindow::on_actionShowInput_triggered(bool checked)
{
    ui->graphicsViewInput->setVisible(checked);
    ui->label_2->setVisible(checked);
    resizeEvent(nullptr);
}

void MainWindow::on_actionShowOutput_triggered(bool checked)
{
    ui->graphicsViewOutput->setVisible(checked);
    ui->label->setVisible(checked);
    resizeEvent(nullptr);
}


void MainWindow::on_comboBoxOperation_currentIndexChanged(int index)
{
    if ( index > 0 ) {
        outputScene->clear();
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


void MainWindow::on_pushButton_released()
{
    int operationIdx = ui->comboBoxOperation->currentIndex();

    if ( operationIdx > 0 ) {
        outputImage = inputImage.copy();

        QProgressDialog progress("Operation in progress.", "Cancel", 0, 100, this->centralWidget());
        progress.setVisible(true);
        progress.setWindowModality(Qt::WindowModal);
        progress.setValue(0);
        qApp->processEvents(QEventLoop::AllEvents);

        imgOperation[operationIdx](&inputImage, &outputImage, &progress);
        outputScene->clear();

        //Invalidate output image
        if ( progress.wasCanceled() == true ) {
            outputImage = QImage();
        }

        if ( outputImage.isNull() == false ) {
            QPixmap pix = QPixmap::fromImage(outputImage);
            outputScene->addPixmap(pix);
            ui->graphicsViewOutput->fitInView(outputImage.rect(), Qt::KeepAspectRatio);
        }

        progress.reset();
    }
}
