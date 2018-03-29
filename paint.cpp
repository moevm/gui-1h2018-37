#include "paint.h"
#include "ui_paint.h"
#include <QMessageBox>

paint::paint(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::paint)
{
    ui->setupUi(this);
    tool = new toolsBar();
    scene = new paintScene();       // Инициализируем графическую сцену
    scene->setBrush(tool);
    ui->graphicsView->setScene(scene);  // Устанавливаем графическую сцену
    ui->btnColor->setStyleSheet("background-color:black");
    timer = new QTimer();       // Инициализируем таймер
    connect(timer, &QTimer::timeout, this, &paint::slotTimer);
    timer->start(100);          // Запускаем таймер
    connect(ui->btnSetRuber, SIGNAL(clicked()), tool, SLOT(setRuber()));
    connect(ui->btnSetBrush, SIGNAL(clicked()), tool, SLOT(setBrush()));
    connect(ui->btnColor, SIGNAL(clicked()), this, SLOT(selectColor()));
    connect(ui->cmbWidth, SIGNAL(currentIndexChanged(int)), tool, SLOT(changeWidth(int)));
}

paint::~paint()
{
    delete ui;
}

void paint::slotTimer()
{
    /* Переопределяем размеры графической сцены в зависимости
     * от размеров окна
     * */
    timer->stop();
    scene->setSceneRect(0,0, ui->graphicsView->width() - 20, ui->graphicsView->height() - 20);
}

void paint::resizeEvent(QResizeEvent *event)
{
    timer->start(100);
    QWidget::resizeEvent(event);
}

void paint::selectColor()
{

    QColor selectedColor = QColorDialog::getColor();
    ui->btnColor->setStyleSheet("background-color: rgb("
                                +QString::number(selectedColor.red())+","
                                +QString::number(selectedColor.green())+","
                                +QString::number(selectedColor.blue())+");");
    tool->changeColor(selectedColor);
}

void paint:: savePic()
{
    QString fileName= QFileDialog::getSaveFileName(this, "Save image", QCoreApplication::applicationDirPath(), "BMP Files (*.bmp);;JPEG (*.JPEG);;PNG (*.png)" );
    if (!fileName.isNull())
        {
            QPixmap pixMap = this->ui->graphicsView->grab();
            pixMap.save(fileName);
        }
}

void paint::on_btnSavePic_clicked()
{
    savePic();
}

void paint::on_btnNewPic_clicked()
{
    QMessageBox msg;
       msg.setText("Новое изображение");
       msg.setInformativeText("Сохранить текущее изображение?");
       msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
       msg.setDefaultButton(QMessageBox::Yes);

       int ret = msg.exec();
       if( ret == QMessageBox::No) ui->graphicsView->scene()->clear();
       else
       {
           savePic();
           ui->graphicsView->scene()->clear();
       }
}
