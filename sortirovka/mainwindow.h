#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_max_clicked();

    void on_min_clicked();

    void on_sredn_clicked();

    void on_createtable_clicked();

    void on_sortirovka_clicked();

    void on_zapolnenie_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
