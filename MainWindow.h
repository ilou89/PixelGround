#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private:
    MainWindow(QWidget *parent = nullptr);
    static MainWindow *instance;

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
