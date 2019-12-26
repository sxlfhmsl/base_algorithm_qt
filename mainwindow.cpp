#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sort/bubblesort.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonRun_clicked()
{
    if (ui->checkBoxBubbleSort->isChecked())
    {
        this->sort = new BubbleSort(this->gen_list(ui->lineEditCount->text().toInt()), ui->checkBoxThread->isChecked());
    }
    this->datetime = QDateTime::currentDateTime();
    if (this->sort != nullptr)
    {
        QObject::connect(this->sort, &Sort::signal_sort_success, this, &MainWindow::slot_sort_success);
    }
    if (!ui->checkBoxThread->isChecked())
    {
        emit this->sort->signal_sort_begin();
    }
}

void MainWindow::slot_sort_success(QString name, QList<int> target)
{
    qint64 time_diff = QDateTime::currentDateTime().toMSecsSinceEpoch() - this->datetime.toMSecsSinceEpoch();
    this->sort->deleteLater();
    this->sort = nullptr;
    name = name + "-----" + QString::number(time_diff);
    if (ui->checkBoxComplex->isChecked())
    {
        name += "\n";
        for (int i = 0; i < target.length(); ++i) {
            name += (QString::number(target[i])) + ",    ";
        }
    }
    ui->textEditResult->setText(name);
}

QList<int> MainWindow::gen_list(int count)
{
    QList<int> result;
    QTime time;
    time= QTime::currentTime();
    qsrand(static_cast<uint>(time.msec() + time.second() * 1000));
    for (int var = 0; var < count; ++var) {
        result.push_back(qrand() %  count);
    }
    return result;
}
