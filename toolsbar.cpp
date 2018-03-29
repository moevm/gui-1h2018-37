#include "toolsBar.h"
#include <QDebug>


toolsBar::toolsBar(QWidget *parent) : QWidget(parent)
{
    currentWidth = 1;
    isRuber = false;
    currentColor.setRgb(Qt::black);
}

void toolsBar:: changeColor(QColor selectedColor)
{
    currentColor = selectedColor;

}

void toolsBar:: changeWidth(int index)
{
    currentWidth = index+1;
}

void toolsBar:: setBrush()
{
    isRuber = false;
}

void toolsBar:: setRuber()
{
    isRuber = true;
}

QColor toolsBar:: getColor()
{
    return this->currentColor;
}

int toolsBar:: getWidth()
{
    return this->currentWidth;
}

bool toolsBar:: getToolStatus()
{
    return this->isRuber;
}


