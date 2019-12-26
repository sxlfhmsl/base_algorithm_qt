#ifndef SORT_H
#define SORT_H

#include <QObject>

class Sort : public QObject
{
    Q_OBJECT
public:
    explicit Sort(QString name, QList<int> source, bool thread_enable = false, QObject *parent = nullptr);

signals:
    /**
     * @brief signal_sort_success
     * @details 排序成功，信号
     */
    void signal_sort_success(QString, QList<int>);

    void signal_sort_begin();

public slots:

protected:
    QList<int> source;
    bool thread_enable = false;
    QString name;
};

#endif // SORT_H
