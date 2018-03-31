#ifndef toolsBar_H
#define toolsBar_H

#include <QWidget>

class toolsBar : public QWidget
{
    Q_OBJECT

private:
    QColor  currentColor;
    int     currentWidth;


public:
    explicit toolsBar(QWidget *parent = 0);
    void changeColor(QColor selectedColor);
    QColor getColor();
    int getWidth();
    bool getToolStatus();
    bool    isRuber;

signals:

public slots:
    void changeWidth(int index);
    void setBrush();
    void setRuber();
};

#endif // toolsBar_H
