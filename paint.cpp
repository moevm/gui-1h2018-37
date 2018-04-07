#include "paint.h"
#include "ui_paint.h"
#include <QMessageBox>
using namespace std;

paint::paint(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::paint)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    tool = new toolsBar();
    ui->graphicsView->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    ui->graphicsView_2->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    QGraphicsScene *leftScene = new QGraphicsScene();
    scene = new paintScene(ui->graphicsView_2->rect(), ui->graphicsView_2);
    scene->setBrush(tool);
    ui->graphicsView->setScene(leftScene);
    ui->graphicsView_2->setScene(scene);

    connect(ui->btnSetRuber, SIGNAL(clicked()), tool, SLOT(setRuber()));
    connect(ui->btnSetBrush, SIGNAL(clicked()), tool, SLOT(setBrush()));
    connect(ui->btnColor, SIGNAL(clicked()), this, SLOT(selectColor()));
    connect(ui->cmbWidth, SIGNAL(currentIndexChanged(int)), tool, SLOT(changeWidth(int)));
}

paint::~paint()
{
    delete ui;
}


void paint:: resizeEvent(QResizeEvent *)
{
    ui->graphicsView->scene()->setBackgroundBrush(
                QPixmap(ui->graphicsView->scene()->backgroundBrush().texture()).scaled(
                ui->graphicsView->geometry().width(),
                ui->graphicsView->geometry().height(), Qt::IgnoreAspectRatio));

    scene->setForegroundBrush(
                QPixmap(scene->foregroundBrush().texture()).scaled(
                ui->graphicsView_2->geometry().width(),
                ui->graphicsView_2->geometry().height(), Qt::IgnoreAspectRatio));

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
    fileName = Folder;
    fileName.append("/");
    fileName.append(QString::number(n));
    fileName.append(".png");
    QPixmap pixMap = this->ui->graphicsView_2->grab();
    pixMap.save(fileName);

}

void paint::on_btnNewPic_clicked()
{
    savePic();

    QMessageBox msg;
    msg.setText("Новый кадр анимации");
    msg.setInformativeText("Сохранить предыдущий кадр анимации в поле для рисования с возможностью редактирования?");
    msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msg.setDefaultButton(QMessageBox::Yes);

    int ret = msg.exec();
    if( ret == QMessageBox::No) ui->graphicsView_2->scene()->clear();
    ui->graphicsView->scene()->addPixmap(fileName);
    n++;
}

void paint::on_btnRepeat_clicked()
{
     ui->graphicsView_2->scene()->clear();
}

void paint::on_btnStart_clicked()
{
    Folder= QFileDialog::getSaveFileName(this, "Выберите директорию и введите название для проекта", QCoreApplication::applicationDirPath());
    QDir().mkdir(Folder);
    n=1;
    ui->stackedWidget->setCurrentIndex(1);
    this->resizeEvent(NULL);
}
