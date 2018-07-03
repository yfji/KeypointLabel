#ifndef QIMAGELABEL_H
#define QIMAGELABEL_H

#include <QLabel>
#include <QMouseEvent>
#include <vector>
#include <opencv2/opencv.hpp>
#include <functional>

struct Keypoint{
    cv::Point2f pos;
    int type;   //0:invisible(not labeled), 1:visible(not labeled)
};

using click_callback=std::function<void(Keypoint, int)>;

namespace Ui {
class QImageLabel;
}

class QImageLabel : public QLabel
{
    Q_OBJECT

public:
    explicit QImageLabel(QWidget *parent = 0);
    ~QImageLabel();
protected:
    void mouseReleaseEvent(QMouseEvent *e);

private:
    Keypoint currentPos;
    int labeledCount= {0};

public:
    int num_parts={0};
    char imgLoaded = {0};
    click_callback callback;

    inline int getLabeledCount(){
        return labeledCount;
    }

    inline void updatePos(const Keypoint& pt, int count){
        currentPos=pt;
        labeledCount=count;
    }

    inline Keypoint getPoint(){
        return currentPos;
    }

    inline void reset(){
        currentPos.pos.x=0;
        currentPos.pos.y=0;
        currentPos.type=0;
        labeledCount=0;
    }
};

#endif // QIMAGELABEL_H
