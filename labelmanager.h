#ifndef LABELMANAGER_H
#define LABELMANAGER_H

#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
#include <fstream>
#include <sstream>
#include <string.h>
#include <opencv2/opencv.hpp>
#include "qimagelabel.h"

class LabelManager
{
public:
    LabelManager(int num_parts);

private:
    std::vector<std::string> fileNames;
    std::vector<Keypoint> points;
    std::vector<Keypoint> originPoints;
    int num_parts = {0};
    int curIndex = {-1};
    float scale= {1.0};

private:
    void sortNames(){
        std::sort(fileNames.begin(), fileNames.end(), [this](const std::string& s1, const std::string& s2){
            const char* c1=s1.c_str();
            const char* c2=s2.c_str();
            int res=strcmp(c1, c2);
            return (res<0);
        });
    }

public:
    inline void setFileNames(const std::vector<std::string>& names){
        fileNames=names;
        sortNames();
    }

    void reset();

    void push(const Keypoint& pt);

    Keypoint pop();

    inline std::vector<Keypoint> getPoints(){
        return points;
    }
    inline std::vector<Keypoint> getOriginPoints(){
        return originPoints;
    }

    std::string getName(int index){
        return fileNames[index];
    }

    inline int getIndex(){
        return curIndex;
    }

    float adjust(const cv::Mat& oriImg, cv::Mat& newImg, cv::Size size);

    bool saveLabel(const char* fileName);
};

#endif // LABELMANAGER_H
