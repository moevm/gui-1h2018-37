#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QTimer>
#include <QDebug>
#include "toolsbar.h"

class paintScene : public QGraphicsScene
{

    Q_OBJECT

public:
    explicit paintScene(QObject *parent = 0);
    void setBrush(toolsBar *brush);
    void setBrushType(bool status);
    ~paintScene();

private:
    QPointF     previousPoint;      // Координаты предыдущей точки
    toolsBar    *myBrush;
    QBrush      *brushType;
    // Для рисования используем события мыши
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

};

#endif // PAINTSCENE_H
