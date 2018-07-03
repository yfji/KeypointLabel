#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qmessagebox.h>
#include <qfiledialog.h>
#include <qdir.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ptrLabel.reset(new LabelManager(num_parts));
    saveDir="./saved_images/";
    QDir dir;
    if(!dir.exists(tr(saveDir.c_str())))
    {
        dir.mkdir(tr(saveDir.c_str()));
    }
    ui->bar->setMaximum(max_value);
    ui->bar->setValue(0);

    QFont font ("Microsoft YaHei", 14, 50);
    ui->txt_prog_image->setFont(font);
    ui->txt_prog_point->setFont(font);

    imgLabelW=ui->label_image->width();
    imgLabelH=ui->label_image->height();

    m_callback=std::bind(&MainWindow::clickImage, this, std::placeholders::_1,std::placeholders::_2);
    ui->label_image->callback=m_callback;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_open_img_clicked()
{
    QFileDialog *fileDialog = new QFileDialog(this);
    std::string title="Select an image file";

    fileDialog->setWindowTitle(tr(title.c_str()));
    fileDialog->setDirectory(".");
    fileDialog->setNameFilter(tr("Imagess(*.jpg *.jpeg *.png)"));
    fileDialog->setFileMode(QFileDialog::ExistingFiles);
    fileDialog->setViewMode(QFileDialog::Detail);
    QStringList fileName;
    if(fileDialog->exec())
    {
        ptrLabel->reset();
        fileName = fileDialog->selectedFiles();
        QString file=fileName.at(0);
        std::string strFileName=file.toStdString();

        totalFiles=1;
        imageIndex=0;
        std::stringstream ss;
        imageIndex=0;

        ss<<"0 / "<<totalFiles;
        ui->txt_prog_image->setText(tr(ss.str().c_str()));
        ss.str("");
        ss<<"0 / "<<num_parts;
        ui->txt_prog_point->setText(tr(ss.str().c_str()));

        int pos=strFileName.rfind("/");
        std::string tmp=strFileName;
        parentDir=tmp.replace(pos, strFileName.length()-pos, "");
        ptrLabel->setFileNames({strFileName.replace(0,pos+1,"")});
        imgPathValid=1;
    }
    delete fileDialog;
}

void MainWindow::on_btn_open_dir_clicked()
{
    QString file_path = QFileDialog::getExistingDirectory(this,"Select a folder",".");
    if(file_path.isEmpty())
    {
        QMessageBox::warning(this,tr("Warning"),tr("Invalid folder path, please select a new dir"),QMessageBox::Ok);
        return;
    }
    else
    {
        ptrLabel->reset();
        QDir dir(file_path);
        QStringList nameFilters;
        nameFilters << "*.jpg" << "*.jpeg"<< "*.png";
        QStringList files = dir.entryList(nameFilters, QDir::Files|QDir::Readable, QDir::Name);
        std::vector<std::string> strFileNames;
        totalFiles=files.size();

        std::stringstream ss;
        imageIndex=0;
        ss<<"0 / "<<totalFiles;
        ui->txt_prog_image->setText(tr(ss.str().c_str()));

        ss.str("");
        ss<<"0 / "<<num_parts;
        ui->txt_prog_point->setText(tr(ss.str().c_str()));
        for(auto i=0;i<files.size();++i){
            QString file=files[i];
            strFileNames.push_back(file.toStdString());
            //std::cout<<file.toStdString()<<std::endl;
        }
        parentDir=file_path.toStdString();
        ptrLabel->setFileNames(strFileNames);
        imgPathValid=1;
    }
}

void MainWindow::on_btn_open_list_clicked()
{
    //Not Implement
}

void MainWindow::on_btn_start_label_clicked()
{
    if(!imgPathValid){
        QMessageBox::warning(this,tr("Warning"),tr("Please select image/image dir/image list"),QMessageBox::Ok);
        return;
    }
    std::string cur_filename=ptrLabel->getName(imageIndex);
    std::string fullPath;
    char lastChar=parentDir[parentDir.length()-1];
    if(lastChar!='/' && lastChar!='\\'){
        parentDir=parentDir+"/";
        fullPath=parentDir+cur_filename;
    }
    else{
        fullPath=parentDir+cur_filename;
    }
    std::cout<<fullPath<<std::endl;
    ui->label_image->imgLoaded=1;
    cv::Mat tmp=cv::imread(fullPath);
    imgScale=ptrLabel->adjust(tmp, curImage, cv::Size(imgLabelW, imgLabelH));
    cv::cvtColor(curImage, curImage, cv::COLOR_BGR2RGB);
    copyImage=curImage.clone();
    this->update();
}

void MainWindow::on_btn_end_label_clicked()
{
    if(!imgPathValid){
        QMessageBox::warning(this,tr("Warning"),tr("Please select image/image dir/image list"),QMessageBox::Ok);
        return;
    }
    std::string name=ptrLabel->getName(imageIndex);
    std::string tmp=name;
    std::string label_file=tmp.replace(name.find(".jpg"), 4, ".txt");
    std::stringstream ss;
    ss<<imageIndex+1<<" / "<<totalFiles;
    ui->txt_prog_image->setText(tr(ss.str().c_str()));
    int value=(int)(1.0*(imageIndex+1)/totalFiles*max_value);
    ui->bar->setValue(value);
    std::cout<<saveDir+name<<std::endl;
    //cv::imwrite(saveDir+name, curImage);
    label_file=saveDir+label_file;
    ptrLabel->saveLabel(label_file.c_str());
    ++imageIndex;

    ptrLabel->reset();
    ui->label_image->reset();

    if(imageIndex==totalFiles){
        QMessageBox::warning(this,tr("Warning"),tr("You have labeled all images"),QMessageBox::Ok);
        return;
    }
    name=ptrLabel->getName(imageIndex);
    cv::Mat tmpMat=cv::imread(parentDir+name);
    imgScale=ptrLabel->adjust(tmpMat, curImage, cv::Size(imgLabelW, imgLabelH));
    cv::cvtColor(curImage, curImage, cv::COLOR_BGR2RGB);
    copyImage=curImage.clone();
    this->update();
}

void MainWindow::on_btn_cancel_clicked()
{
    if(!imgPathValid){
        QMessageBox::warning(this,tr("Warning"),tr("Please select image/image dir/image list"),QMessageBox::Ok);
        return;
    }
    Keypoint lastPoint=ptrLabel->pop();
    int index=ptrLabel->getIndex();
    ui->label_image->updatePos(lastPoint, index+1);
    std::vector<Keypoint> points=ptrLabel->getPoints();
    drawImage(points, index+1);
    this->update();
    if(index<0){
        QMessageBox::warning(this,tr("Warning"),tr("You have cancelled all labeled points"),QMessageBox::Ok);
    }
}

void MainWindow::on_btn_prev_clicked()
{
    //Not Implement
}

void MainWindow::on_btn_next_clicked()
{
    //Not Implement
}

void MainWindow::on_btn_view_clicked()
{
    if(!imgPathValid){
        QMessageBox::warning(this,tr("Warning"),tr("Please select image/image dir/image list"),QMessageBox::Ok);
        return;
    }
    std::string name=ptrLabel->getName(imageIndex);
    cv::Mat canvas=cv::imread(parentDir+name);
    std::vector<Keypoint> points=ptrLabel->getOriginPoints();
    for(int i=0;i<num_parts;++i){
        Keypoint& kpt=points[i];
        cv::circle(canvas, kpt.pos, radius, cv::Scalar(0,0,255), -1);
    }
    cv::cvtColor(canvas, canvas, cv::COLOR_BGR2RGB);
    PreviewDialog dlg;
    dlg.setUpImage(canvas);
    dlg.exec();
}

void MainWindow::clickImage(Keypoint pos, int count){
    std::cout<<"Here is click callback: "<<count<<std::endl;
    if(count>num_parts){
        QMessageBox::warning(this,tr("Warning"),tr("You have labeled all keypoints"),QMessageBox::Ok);
        return;
    }
    ptrLabel->push(pos);
    std::vector<Keypoint> points=ptrLabel->getPoints();
    std::cout<<"Here is pushed points: "<<count<<std::endl;
    drawImage(points, count);
    this->update();
}

void MainWindow::drawImage(const std::vector<Keypoint>& points, int count){
    curImage=copyImage.clone();
    for(int i=0;i<count;++i){
        const Keypoint& kpt=points[i];
        if(kpt.type==1){
            cv::circle(curImage, kpt.pos, radius, cv::Scalar(255,0,0), -1);
        }
    }
    std::stringstream ss;
    ss<<count<<" / "<<num_parts;
    ui->txt_prog_point->setText(tr(ss.str().c_str()));
}

void MainWindow::paintEvent(QPaintEvent *e)
{
    QImage q_image = QImage((const uchar*)(curImage.data), curImage.cols, curImage.rows, curImage.cols*curImage.channels(), QImage::Format_RGB888);
    ui->label_image->setPixmap(QPixmap::fromImage(q_image));
}

void MainWindow::on_comb_radius_activated(const QString &arg1)
{
    std::string str=arg1.toStdString();
    int rad=atoi(str.c_str());
    radius=rad;
}
