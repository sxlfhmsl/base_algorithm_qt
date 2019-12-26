#include "sort.h"

Sort::Sort(QString name, QList<int> source, bool thread_enable, QObject *parent) : QObject(parent)
{
    this->source = source;
    this->thread_enable = thread_enable;
    if (this->thread_enable)
        this->name = name + "-多线程";
    else
        this->name = name;
}
