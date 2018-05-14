#ifndef HUPDATETHREAD_H
#define HUPDATETHREAD_H

#include <QThread>
#include "hkerneltest.h"
class HTWork : public QObject
{
    Q_OBJECT
public:
    HTWork(HKernelTest* pParent);
public slots:
    void on_time();
public:
    HKernelTest* p_kernelTest;
    HUpdateThread *p_Thread;
};

class HUpdateThread : public QThread
{
    Q_OBJECT
public:
    HUpdateThread(HKernelTest* pParent = 0);

public:
    virtual void run();

signals:
    void update();


public:
    HKernelTest* p_kernelTest;
};

#endif // HUPDATETHREAD_H
