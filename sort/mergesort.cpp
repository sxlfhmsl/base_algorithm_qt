#include "mergesort.h"
#include <QRunnable>
#include <QVector>

int MergeSort::index_thread = 0;
QThread MergeSort::thread_pool[8];

MergeSort::MergeSort(QList<int> source, bool thread_able, QObject *parent) : Sort("归并排序", source, thread_able, parent)
{
    this->source.toVector().data();
    if (this->thread_enable)
    {
        QThread *thread = &MergeSort::thread_pool[MergeSort::index_thread ++];
        if (thread->isRunning())
        this->moveToThread(&MergeSort::thread_pool[MergeSort::index_thread ++]);
        if (MergeSort::index_thread == 8)
            MergeSort::index_thread = 0;
    }
}

void MergeSort::stop_threads()
{
    for (int var = 0; var < 8; ++var) {
        MergeSort::thread_pool[var].quit();
    }
}

void MergeSort::slot_merge_sort()
{

}
