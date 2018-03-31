#ifndef paint_H
#define paint_H

#include <QWidget>
#include <QTimer>
#include <QResizeEvent>
#include <QColor>
#include <QColorDialog>
#include <QString>
#include <QFileDialog>

#include "paintscene.h"
#include "toolsbar.h"

namespace Ui {
class paint;
}

class paint : public QWidget
{
    Q_OBJECT

public:
    explicit paint(QWidget *parent = 0);
    ~paint();


private:
    /* Переопределяем событие изменения размера окна
     * для пересчёта размеров графической сцены
     * */
    void resizeEvent(QResizeEvent * event);
    Ui::paint *ui;
    QTimer *timer;      /* Определяем таймер для подготовки актуальных размеров
                         * графической сцены
                         * */
    paintScene *scene;  // Объявляем кастомную графическую сцену
    toolsBar *tool;

private slots:
    void slotTimer();
    void selectColor();
    void savePic();
    void on_btnSavePic_clicked();
    void on_btnNewPic_clicked();
    void on_btnRepeat_clicked();
};

#endif // paint_H