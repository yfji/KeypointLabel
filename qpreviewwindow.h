#ifndef QPREVIEWWINDOW_H
#define QPREVIEWWINDOW_H

#include <QMainWindow>
#include <opencv2/opencv.hpp>

namespace Ui {
class QPreviewWindow;
}

class QPreviewWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit QPreviewWindow(QWidget *parent = 0);

    void setUpImage(cv::Mat& img){
        image=img;
        this->update();
    }

private:
    Ui::QPreviewWindow *ui;

    void paintEvent(QPaintEvent* e);

    cv::Mat image;
};

#endif // QPREVIEWWINDOW_H
