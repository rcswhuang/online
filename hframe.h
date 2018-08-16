#ifndef HFRAME_H
#define HFRAME_H
#include <QFrame>
#include <QVBoxLayout>

class HFrame : public QFrame
{
public:
    HFrame(QWidget* parent = 0);

protected:
    QVBoxLayout *frameLayout;
    QVBoxLayout *centerLayout;
};

#endif // HFRAME_H
