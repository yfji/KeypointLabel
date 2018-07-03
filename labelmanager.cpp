#include "labelmanager.h"

LabelManager::LabelManager(int num_parts)
{
    this->num_parts=num_parts;
    reset();
}

void LabelManager::reset(){
    std::vector<Keypoint>().swap(points);
    std::vector<Keypoint>().swap(originPoints);
    points.clear();
    originPoints.clear();
    curIndex=-1;
    points.resize(num_parts);
    originPoints.resize(num_parts);
    for(int i=0;i<num_parts;++i){
        Keypoint& p1=points[i];
        Keypoint& p2=originPoints[i];
        p1.pos.x=0;p1.pos.y=0;
        p2.pos.x=0;p2.pos.y=0;
        p1.type=0;
        p2.type=0;
    }
}

void LabelManager::push(const Keypoint& pt){
    curIndex++;
    points[curIndex]=pt;
    cv::Point2f p=pt.pos;
    cv::Point2f originPt(p.x/scale, p.y/scale);
    originPoints[curIndex]=Keypoint{originPt, pt.type};
}

Keypoint LabelManager::pop(){
    if(curIndex>=0)
        curIndex--;
    if(curIndex>=0)
        return points[curIndex];
    return Keypoint{cv::Point2f(0,0),0};
}
float LabelManager::adjust(const cv::Mat& oriImg, cv::Mat& newImg, cv::Size size){
    int iw=oriImg.cols;
    int ih=oriImg.rows;
    int nw=size.width;
    int nh=size.height;

    //std::cout<<nw<<","<<nh<<","<<iw<<","<<ih<<std::endl;
    scale=MIN(1.0*nw/iw, 1.0*nh/ih);

    cv::resize(oriImg, newImg, cv::Size(), scale, scale, cv::INTER_LINEAR);
    return scale;
}

bool LabelManager::saveLabel(const char* fileName){
    std::ofstream out;
    out.open(fileName, std::ios::out);
    for(int i=0;i<num_parts;++i){
        Keypoint& kpt=originPoints[i];
        out<<kpt.pos.x<<' '<<kpt.pos.y<<' '<<kpt.type<<std::endl;
    }
    out.close();
    return true;
}
