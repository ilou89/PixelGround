#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QGraphicsScene"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

struct OperationParameters{
    int filterSize;
    float sigma;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    static MainWindow *getInstance();
    const OperationParameters *getParams();

    ~MainWindow();

private slots:
    void on_actionOpen_triggered();

    void on_actionShowInput_triggered(bool checked);
    void on_actionShowOutput_triggered(bool checked);

    void on_comboBoxOperation_currentIndexChanged(int index);

    void on_spinBoxFilterSize_valueChanged(int arg1);

    void on_doubleSpinBoxSigma_valueChanged(double arg1);

private:
    MainWindow(QWidget *parent = nullptr);
    static MainWindow *instance;
    Ui::MainWindow *ui;

    QGraphicsScene *scene;
    QImage inputImage;
    QImage outputImage;
    void resizeEvent(QResizeEvent*);
    OperationParameters params;
};
#endif // MAINWINDOW_H
