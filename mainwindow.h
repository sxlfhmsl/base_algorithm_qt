#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>

namespace Ui {
class MainWindow;
}
class Sort;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonRun_clicked();

    void slot_sort_success(QString name, QList<int> target);

private:
    Ui::MainWindow *ui;

    QDateTime datetime;
    Sort *sort = nullptr;

    QList<int> gen_list(int count);
};

#endif // MAINWINDOW_H
