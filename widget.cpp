#include "opencv2/opencv.hpp"
#include "widget.h"
#include "ui_widget.h"
#include <QString>
using namespace cv;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    cam = new gestionCam();
    ui->setupUi(this);
    time = new QTimer(this);
    timeAnimation=new QTimer(this);
    connect(timeAnimation,SIGNAL(timeout()),this,SLOT(animation()));
    connect( time, SIGNAL(timeout()), this, SLOT(video()) );
    timeAnimation->start(20);
    time->start(20);
}

void Widget::keyPressEvent(QKeyEvent *event){
    switch(event->key())    {
        // Sortie de l'application
        case Qt::Key_Escape: {
            close();
            break;
        }
        case Qt::Key_Left: {
            cv::Point p;
            p.x=-1;
            //ui->widgetJeu->setPos(p);
            break;
        }
        case Qt::Key_Right: {
            cv::Point p ;
            p.x=1;
            //ui->widgetJeu->setPos(p);
            break;
        }
        // Cas par défaut
        default: {
            event->ignore();
            return;
        }
    }
    // Acceptation de l'évènement et mise a jour de la scene
    event->accept();
}


Widget::~Widget(){
    delete ui;
}

void Widget::animation(){
    ui->widgetJeu->getJeuCasseBrique()->animation((float)cam->getVect().x , (float)cam->getVect().x);
}

void Widget::video(){

    frame = cam->imageVideo();
    this->setVect(cam->getVect());
    QImage img= QImage((const unsigned char*)(frame.data),frame.cols,frame.rows,QImage::Format_RGB888);

    ui->widgetJeu->setPos(cam->getVect());
    ui->widgetJeu->update();

    // Display on label
    ui->imageLabel_->setPixmap(QPixmap::fromImage(img));
    // Resize the label to fit the image
    ui->imageLabel_->resize(ui->imageLabel_->pixmap()->size());
}
