#ifndef HOPERORDERWINDOW_H
#define HOPERORDERWINDOW_H

#include "hframe.h"

/*
 * 操作票预演窗口：两部分
 * 1.左边是编辑窗口
 * 2.右边是viewer窗口
*/

class HRehearsalFrame : public HFrame
{
    Q_OBJECT

public:
    explicit HRehearsalFrame(HFrame *parent = 0);
    ~HRehearsalFrame();

private:
};

#endif // HOPERORDERWINDOW_H
