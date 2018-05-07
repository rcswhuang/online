#ifndef HONLINEMAINWINDOW_H
#define HONLINEMAINWINDOW_H

#include <QMainWindow>
class HOnlineTreeWidget;
namespace Ui {
class HOnlineMainWindow;
}
class HOnlineMgr;
class HOnlineView;
class HOnlineMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit HOnlineMainWindow(QWidget *parent = 0);
    ~HOnlineMainWindow();

public:
    void initOnlineMainWindow();

public slots:
    void Open(const QString&,const int);
private:
    Ui::HOnlineMainWindow *ui;
    HOnlineTreeWidget* m_pOnlineTreeWidget;
    HOnlineView* m_pOnlineView;
    HOnlineMgr* m_pOnlineMgr;
};

#endif // HONLINEMAINWINDOW_H
