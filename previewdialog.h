#ifndef PREVIEWDIALOG_H
#define PREVIEWDIALOG_H

#include <QDialog>
#include <opencv2/opencv.hpp>

namespace Ui {
class PreviewDialog;
}

class PreviewDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PreviewDialog(QWidget *parent = 0);
    ~PreviewDialog();

    void setUpImage(const cv::Mat& img){
        adjust(img, image, cv::Size(labelW, labelH));
        this->update();
    }

private:
    Ui::PreviewDialog *ui;

    virtual void paintEvent(QPaintEvent *e);

    void adjust(const cv::Mat& oriImg, cv::Mat& newImg, cv::Size size);

    int labelW;
    int labelH;
    cv::Mat image;
};

#endif // PREVIEWDIALOG_H
