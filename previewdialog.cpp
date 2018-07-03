#include "previewdialog.h"
#include "ui_previewdialog.h"

PreviewDialog::PreviewDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PreviewDialog)
{
    ui->setupUi(this);
    labelW=ui->label_image->width();
    labelH=ui->label_image->height();
}

PreviewDialog::~PreviewDialog()
{
    delete ui;
}

void PreviewDialog::adjust(const cv::Mat& oriImg, cv::Mat& newImg, cv::Size size){
    int iw=oriImg.cols;
    int ih=oriImg.rows;
    int nw=size.width;
    int nh=size.height;

    float scale=MIN(1.0*nw/iw, 1.0*nh/ih);
    cv::resize(oriImg, newImg, cv::Size(), scale, scale, cv::INTER_LINEAR);
}

void PreviewDialog::paintEvent(QPaintEvent *e){
    QImage q_image = QImage((const uchar*)(image.data), image.cols, image.rows, image.cols*image.channels(), QImage::Format_RGB888);
    ui->label_image->setPixmap(QPixmap::fromImage(q_image));
}
