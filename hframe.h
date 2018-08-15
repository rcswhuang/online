#ifndef HFRAME_H
#define HFRAME_H
#include <QFrame>
class QVBoxLayout;
class HFrame : public QFrame
{
public:
    HFrame(QFrame* parent = 0);

protected:
    QVBoxLayout *frameLayout;
    QVBoxLayout *centerLayout;
};

#endif // HFRAME_H
