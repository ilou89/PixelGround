#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QGraphicsScene"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    static MainWindow *getInstance();

    ~MainWindow();

private slots:
    void on_actionOpen_triggered();

    void on_actionShowInput_triggered(bool checked);
    void on_actionShowOutput_triggered(bool checked);

private:
    MainWindow(QWidget *parent = nullptr);
    static MainWindow *instance;
    Ui::MainWindow *ui;

    QGraphicsScene *scene;
    QImage inputImage;
    void resizeEvent(QResizeEvent*);
};
#endif // MAINWINDOW_H
