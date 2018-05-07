#ifndef HONLINEVIEW_H
#define HONLINEVIEW_H

#include <QGraphicsView>
class HOnlineView : public QGraphicsView
{
    Q_OBJECT
public:
    HOnlineView(QWidget *parent = Q_NULLPTR);

public:
    //目前只刷新界面
    void refresh();
};

#endif // HGRAPHEDITORVIEW_H
