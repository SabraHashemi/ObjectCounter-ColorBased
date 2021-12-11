#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


#include "QTimer"
#include <iostream>   //cout
#include <stdio.h>
#include <iostream>
#include <stdio.h>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <QApplication>

#include <QStringList>
#include <QDebug>

#include "QTime"
#include "QTimer"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <QBuffer>
#include <QFileDialog>
#include <QMessageBox>
#include <QCameraInfo>
#include <QListWidgetItem>
#include <QCloseEvent>



using namespace std;



#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>

#include "algorithms.h"

#include <time.h>



#include "Blob.h"
#include <fstream>
#include <string>
#include <iomanip>
#pragma warning(disable : 4996)
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>
#include<conio.h>  // remove this line if not using Windows OS
#define SHOW_STEPS // un-comment | comment this line to show steps or not



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
    void on_pushButton_cameraConnect_clicked();
    void displayFrame();
    void displayFrameWithModel();

    void on_comboBox_currentIndexChanged(int index);

    void on_pushButton_SveResult_clicked();

    void on_pushButton_loadModal_clicked();



    void on_pushButton_Login_clicked();

    void on_pushButton_Register_clicked();

    void on_pushButton_registerDone_clicked();

    void on_pushButton_BacktoLogin_clicked();

    void on_pushButton_exit_clicked();


    void on_pushButton_saveConfigure_clicked();


    void on_pushButton_lastConfig_clicked();

    void on_pushButton_power_clicked();


    void on_pushButton_clicked();

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();





    void on_pushButton_mincolor_clicked();

    void on_pushButton_savecolor_clicked();



    void onminColorSelected(QColor color);



    void on_pushButton_sample_clicked();

    void on_radioButton_5_clicked();

    void on_radioButton_6_clicked();

    void on_radioButton_4_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_deletecolor_clicked();

    void showMousePeressed(QPoint& pos);

    void on_radioButton_3_clicked();

    void on_radioButton_7_clicked();

    void on_pushButton_3_clicked();

    void on_checkBox_clicked();

    void on_checkBox_2_clicked();

    void on_radioButton_9_clicked();

    void on_radioButton_8_clicked(bool checked);

    void on_radioButton_10_clicked();

//    void on_checkBox_3_clicked();






private:
    Ui::MainWindow *ui;
    QImage MatToQImage(cv::Mat &mat);
    QTimer *timer;
    QTimer *timer4;
    QImage mymatToQImage(const cv::Mat &mat);


    void paintEvent(QPaintEvent *e);
    bool m_nbMousePressed ;
    bool DrawRect;
    int m_nInitialX ;
    int  m_nInitialY ;
    int  m_nFinalX ;
    int m_nFinalY;
    bool stopp;
    int finalx;
    int finaly;
    int finalwidth;
    int finalheight;
    QPixmap m_nPTargetPixmap;
    QPixmap r;
    QPixmap tmp2;
    bool released;

    // function prototypes
    void matchCurrentFrameBlobsToExistingBlobs(std::vector<Blob>& existingBlobs, std::vector<Blob>& currentFrameBlobs,cv::Mat& imgFrame2Copy);
    void addBlobToExistingBlobs(Blob& currentFrameBlob, std::vector<Blob>& existingBlobs, int& intIndex);
    void addNewBlob(Blob& currentFrameBlob, std::vector<Blob>& existingBlobs, cv::Mat &imgFrame2Copy);
    double distanceBetweenPoints(cv::Point point1, cv::Point point2);
    void drawAndShowContours(cv::Size imageSize, std::vector<std::vector<cv::Point> > contours, std::string strImageName);
    void drawAndShowContours(cv::Size imageSize, std::vector<Blob> blobs, std::string strImageName);
    bool checkIfBlobsCrossedTheLineRight(std::vector<Blob>& blobs, int& intHorizontalLinePosition, int& carCountRight);
    bool checkIfBlobsCrossedTheLineLeft(Blob blob, int& intHorizontalLinePositionLeft, int& carCountLeft, cv::Mat& frameresized);
    void drawBlobInfoOnImage(std::vector<Blob>& blobs, cv::Mat& imgFrame2Copy, cv::Mat& originalimage);
    void drawCarCountOnImage(int& carCountRight, cv::Mat& imgFrame2Copy);
   // int Finalprocess(const cv::VideoCapture getcapture);
    int Finalprocess();
    bool color_detection(cv::Mat& finalBrick);
    void closeEvent (QCloseEvent *event);
    int color_detection2(cv::Mat& finalBrick);
    void detect_color_based(cv::Mat& inputimage,int which_color,cv::Mat& output);
    void simple_detect(cv::Mat& inputimage,cv::Mat& output);
    int color_detection3(cv::Mat& finalBrick);
    //void detect_our_color_based(cv::Mat& inputimage,cv::Scalar our_SCALAR_MINIMUM,cv::Scalar our_SCALAR_MAXIMUM,cv::Mat& output);
    void detect_our_color_based(cv::Mat& inputimage,std::vector<cv::Scalar > min_colors,std::vector<cv::Scalar > max_colors,cv::Mat& output);
void framedifference_detect(cv::Mat& imgFrameCopy1,cv::Mat& imgFrameCopy2,cv::Mat& output);
cv::Rect enlargeROI(cv::Mat& frm, cv::Rect boundingBox, int padding);
private slots:
    void showMousePosition(QPoint &pos);
    void showMouseReleased(QPoint& pos);
    QPixmap imagewithlogo(cv::Mat &mat);
    void on_checkBox_4_clicked();
    void on_radioButton_8_clicked();
};

#endif // MAINWINDOW_H
