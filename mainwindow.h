#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>
#include "labelmanager.h"
#include "qimagelabel.h"
#include "previewdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btn_open_img_clicked();

    void on_btn_open_dir_clicked();

    void on_btn_open_list_clicked();

    void on_btn_start_label_clicked();

    void on_btn_end_label_clicked();

    void on_btn_cancel_clicked();

    void on_btn_prev_clicked();

    void on_btn_next_clicked();

    void on_btn_view_clicked();

    void on_comb_radius_activated(const QString &arg1);

private:
    Ui::MainWindow *ui;

    virtual void paintEvent(QPaintEvent *e);

    void clickImage(Keypoint, int count);

    void drawImage(const std::vector<Keypoint>& points, int count);

    click_callback m_callback;

private:
    const int num_parts= {17};
    const int max_value={100};
    std::string parentDir;
    std::string saveDir;
    std::shared_ptr<LabelManager> ptrLabel;

    int totalFiles= {0};

    int imageIndex ={0};
    float imgScale = {1};
    int imgLabelW;
    int imgLabelH;
    int radius = {4};
    cv::Point2i offset;

    char imgPathValid = {0};
    cv::Mat curImage;
    cv::Mat copyImage;

};

#endif // MAINWINDOW_H
