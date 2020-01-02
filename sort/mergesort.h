#ifndef MERGESORT_H
#define MERGESORT_H

#include "sort.h"
#include <QThread>


class MergeSort : public Sort
{
    Q_OBJECT
public:
    explicit MergeSort(QList<int> source, bool thread_able, QObject *parent = nullptr);

    static void stop_threads();

signals:
    /**
     * @brief signal_pri_sort_begin
     * @details 内部调用
     */
    void signal_pri_sort_begin();

public slots:

private:
    static QThread thread_pool[8];
    static int index_thread;

private slots:
    void slot_merge_sort();
};

#endif // MERGESORT_H
