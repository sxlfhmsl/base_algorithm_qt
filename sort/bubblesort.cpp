#include "bubblesort.h"
#include <QThread>

BubbleSort::BubbleSort(QList<int> source,  bool thread_able, int sort_num, bool order, QObject *parent) : Sort("冒泡排序", source, thread_able, parent)
{
    if (sort_num == -1)
        this->sort_num = this->source.length();
    else
        this->sort_num = sort_num;
    this->order = order;


    if (this->thread_enable)
    {
        this->thread = new QThread();
        QObject::connect(this->thread, &QThread::started, this, &BubbleSort::slot_bubble_sort);
        this->moveToThread(this->thread);
        this->thread->start();
    }
    else
    {
        QObject::connect(this, &BubbleSort::signal_sort_begin, this, &BubbleSort::slot_bubble_sort);
    }
}

BubbleSort::~BubbleSort()
{
    if (nullptr != this->thread)
    {
        this->thread->quit();
        this->thread->deleteLater();
    }
    if (nullptr != this->left)
    {
        QObject::disconnect(this->left, &BubbleSort::signal_sort_success, this, &BubbleSort::slot_sort_success);
        this->left->deleteLater();
    }
    if (nullptr != this->right)
    {
        QObject::disconnect(this->right, &BubbleSort::signal_sort_success, this, &BubbleSort::slot_sort_success);
        this->right->deleteLater();
    }
}

void BubbleSort::slot_bubble_sort()
{
    int length = this->source.length();
    if (length == this->sort_num && this->thread_enable)
    {
        this->left = new BubbleSort(this->source, true, length / 2);
        this->right = new BubbleSort(this->source, true, length - length / 2, false);
        QObject::connect(this->left, &BubbleSort::signal_sort_success, this, &BubbleSort::slot_sort_success);
        QObject::connect(this->right, &BubbleSort::signal_sort_success, this, &BubbleSort::slot_sort_success);
        return;
    }
    int temp = 0;
    if (this->sort_num == this->source.length())
        this->sort_num --;

    if (this->order)
    {
        int i_limit = length - 1;
        for (int i = 0, k = this->sort_num; i < i_limit && k > 0; i++, k--) {
            for (int j = 0; j < i_limit - i; j++) {
                if (this->source[j] > this->source[j + 1])
                {
                    temp = this->source[j];
                    this->source[j] = this->source[j + 1];
                    this->source[j + 1] = temp;
                }
            }
        }
        if (!this->thread_enable)
            this->sort_num ++;
        this->source = this->source.mid(this->source.length() - this->sort_num, this->sort_num);
        emit this->signal_sort_success(this->thread_enable ? "end" : this->name, this->source);
    }
    else
    {
        int i_limit = length -1;
        for (int i = i_limit, k = this->sort_num; i > 0 && k > 0; i--, k--) {
            for (int j = length - 1; j > i_limit - i; j--) {
                if (this->source[j] < this->source[j - 1])
                {
                    temp = this->source[j];
                    this->source[j] = this->source[j - 1];
                    this->source[j - 1] = temp;
                }
            }
        }
        if (!this->thread_enable)
            this->sort_num ++;
        this->source = this->source.mid(0, this->sort_num);
        emit this->signal_sort_success(this->thread_enable ? "begin" : this->name, this->source);
    }
}

void BubbleSort::slot_sort_success(QString name, QList<int> target)
{
    if (this->times == 0)
    {
        this->source = target;
        this->times ++;
    }
    else
    {
        if (name == "begin")
            emit this->signal_sort_success(this->name, target + this->source);
        else
            emit this->signal_sort_success(this->name, this->source + target);
    }
}
