#ifndef HELLOQT_H
#define HELLOQT_H

#include <QMainWindow>

namespace Ui {
class helloqt;
}

class helloqt : public QMainWindow
{
    Q_OBJECT

public:
    explicit helloqt(QWidget *parent = 0);
    ~helloqt();

private:
    Ui::helloqt *ui;
};

#endif // HELLOQT_H
