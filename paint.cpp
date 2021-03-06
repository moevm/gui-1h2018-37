#include "paint.h"
#include "ui_paint.h"
#include <QMessageBox>
#include <QTime>

using namespace std;

paint::paint(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::paint)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    tool = new toolsBar();
    ui->graphicsView->setAlignment( Qt::AlignLeft | Qt::AlignTop);
    ui->graphicsView_2->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    tmr = new QTimer();

    connect(tmr, SIGNAL(timeout()), this, SLOT(updatePict()));

    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(on_btnPlay_clicked(int)));

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
    checkSave = false;
}

void paint::on_btnRepeat_clicked()
{
     ui->graphicsView_2->scene()->clear();
}

void paint::on_btnStart_clicked()
{
    Folder= QFileDialog::getSaveFileName(this, "Выберите директорию и введите название для проекта",
                                         QCoreApplication::applicationDirPath());
    QDir().mkdir(Folder);
    n=1;
    ui->stackedWidget->setCurrentIndex(1);
    this->resizeEvent(NULL);
}



void paint::on_btnGif_clicked()
{
    if (checkSave) n++;
    ui->stackedWidget->setCurrentIndex(2);
    p = new QPixmap [n];
    for(int i=1; i<n;i++)
    {
        fileName = Folder;
        fileName.append("/");
        fileName.append(QString::number(i));
        fileName.append(".png");
        p[i].load(fileName);
    }
}

void paint::updatePict()
{
    if (z>=n) z = 1;
    ui->frames->setPixmap(p[z]);
    z++;

}

void paint::on_btnPlay_clicked(int k)
{
    tmr->setInterval(k);
    tmr->start();
}

void paint::on_btnOpen_clicked()
{
    QMessageBox msg;
    msg.setText("Открыть готовый проект");
    msg.setInformativeText("Вам следует выбрать директорию, содержащую кадры анимации в формате png."
                           " Директория может быть пустой, но в ней не должно храниться посторонних файлов!");
    msg.setStandardButtons(QMessageBox::Ok);
    msg.setDefaultButton(QMessageBox::Ok);

    int ret = msg.exec();
    if( ret == QMessageBox::Ok)
    {
        Folder= QFileDialog::getExistingDirectory(this, "Выберите директорию с кадрами проекта",
                                                  QCoreApplication::applicationDirPath());
        QDir dir;
        dir = Folder;
        n=dir.count()-2;
        if (n>0)
        {
            bool check=true;
            for (int i=1; i<=n; i++)
            {
                fileName = Folder;
                fileName.append("/");
                fileName.append(QString::number(i));
                fileName.append(".png");
                if (!QDir().exists(fileName))
                    check=false;
            }
            if (check == true)
            {
                ui->stackedWidget->setCurrentIndex(1);
                fileName = Folder;
                fileName.append("/");
                fileName.append(QString::number(n));
                fileName.append(".png");
                QMessageBox msg;
                msg.setText("Отрыть готовый проект");
                msg.setInformativeText("Открыть последний кадр анимации в поле для рисования с возможностью "
                                       "редактирования?");
                msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
                msg.setDefaultButton(QMessageBox::Yes);

                int ret = msg.exec();
                if( ret == QMessageBox::Yes) ui->graphicsView_2->scene()->addPixmap(fileName);
                ui->graphicsView->scene()->addPixmap(fileName);
                n++;
            }
            else
            {
                QMessageBox msg;
                msg.setText("Посторонние файлы в директории");
                msg.setInformativeText("В директории обнаружены файлы, которые не являются кадрами анимации."
                                       " Рекомендуем вам удалить эти файлы или выбрать другую директорию.");
                msg.setStandardButtons(QMessageBox::Ok);
                msg.setDefaultButton(QMessageBox::Ok);
                int ret = msg.exec();
                if( ret == QMessageBox::Ok) return;
            }
        }
        else
        {
            ui->stackedWidget->setCurrentIndex(1);
            n=1;
        }
    }

    this->resizeEvent(NULL);
}

void paint::on_btnBack_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void paint::on_btnSave_clicked()
{
    checkSave = true;
    savePic();
}

void paint::on_btnBack_clicked()
{
    tmr->stop();
    ui->stackedWidget->setCurrentIndex(1);
}
