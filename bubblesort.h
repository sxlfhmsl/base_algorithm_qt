#ifndef BUBBLESORT_H
#define BUBBLESORT_H

#include <QObject>

class BubbleSort : public QObject
{
    Q_OBJECT
public:
    explicit BubbleSort(QObject *parent = nullptr);

signals:

public slots:
};

#endif // BUBBLESORT_H