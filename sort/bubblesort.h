#ifndef BUBBLESORT_H
#define BUBBLESORT_H

#include "sort.h"

class QThread;
class BubbleSort : public Sort
{
    Q_OBJECT
public:
    explicit BubbleSort(QList<int> source, bool thread_able, int sort_num = -1, bool order = true, QObject *parent = nullptr);
    ~BubbleSort();

signals:

public slots:


private:
    int times = 0;
    int sort_num = 0;
    bool order = true;
    QThread *thread = nullptr;
    BubbleSort *left = nullptr;
    BubbleSort *right = nullptr;

private slots:
    void slot_sort_success(QString name, QList<int> target);

    void slot_bubble_sort();
};

#endif // BUBBLESORT_H
