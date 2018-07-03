#include "qimagelabel.h"
#include "ui_mainwindow.h"

QImageLabel::QImageLabel(QWidget *parent):
    QLabel(parent)
{

}

QImageLabel::~QImageLabel(){

}

void QImageLabel::mouseReleaseEvent(QMouseEvent *e){
    if(!imgLoaded){
        return;
    }
    int buttonClass=e->button();
    float x=1.0*e->x();
    float y=1.0*e->y();
    if(Qt::LeftButton==buttonClass){
        currentPos.pos=cv::Point2f(x,y);
        currentPos.type=1;
    }
    else if(Qt::RightButton==buttonClass){
        currentPos.pos=cv::Point2f(0,0);
        currentPos.type=0;
    }
    labeledCount++;
    callback(currentPos, labeledCount);
}
