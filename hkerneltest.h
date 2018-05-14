#ifndef HKERNELTEST_H
#define HKERNELTEST_H

#include <QDialog>
#include <QList>
namespace Ui {
class HKernelTest;
}
#include "publicdata.h"
#include "hkernelapi.h"
class HUpdateThread;
class HKernelTest : public QDialog
{
    Q_OBJECT

public:
    explicit HKernelTest(QWidget *parent = 0);
    ~HKernelTest();

    void initKernelTest();
    void initWindow();



protected:
    void contextMenuEvent(QContextMenuEvent *event);

public slots:
        void typeChanged();
        void setValue();
          void update();
public:
    QList<DIGITAL*> m_pDigitalList;
    QList<ANALOGUE*> m_pAnalogueList;
    HUpdateThread* m_pThread;
private:
    Ui::HKernelTest *ui;
    int nType;

};

#endif // HKERNELTEST_H
