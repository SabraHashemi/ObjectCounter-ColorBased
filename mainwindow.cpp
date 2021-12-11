

#include "mainwindow.h"
#include "ui_mainwindow.h"

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
#include <QDirIterator>


#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>

#include<opencv2/ml.hpp>
#include "QFileDialog"
///nemidonam chejoori dirent ro injs shenasaii mikone
#include <dirent.h>

#include <QPainter>

using namespace cv::ml;
using namespace cv;
using namespace std;


#include "ColorPickerToolButton.h"

QString cam_path;
bool cameraSelected=false;
int webcam_id;
bool stop=true;
VideoCapture capture2;
Mat frame2;
Mat Frame2;
QSqlDatabase db;

QString cmid2 ;
QString cmtyp2 ;

QString resultfoldersvm2 ;
QString sideofral;
QString perecentofbrick ;
int x_0 ;
int y_0 ;



QString cam_path4;
bool cameraSelected4=false;
int webcam_id4;
bool stop4=true;
VideoCapture capture4;
Mat frame4;
Mat Frame4;


string frameName;

//https://stackoverflow.com/questions/49244008/error-using-svm-predict-function-in-opencv-when-loading-a-saved-file-with-svm-lo


static const QString path = "example.db";



int blobcount=0;



// const global variables
const cv::Scalar SCALAR_BLACK = cv::Scalar(0.0, 0.0, 0.0);
const cv::Scalar SCALAR_WHITE = cv::Scalar(255.0, 255.0, 255.0);
const cv::Scalar SCALAR_YELLOW = cv::Scalar(0.0, 255.0, 255.0);
const cv::Scalar SCALAR_GREEN = cv::Scalar(0.0, 200.0, 0.0);
const cv::Scalar SCALAR_RED = cv::Scalar(0.0, 0.0, 255.0);


// global variables
std::stringstream date;
int carCountLeft, intVerticalLinePosition, carCountRight = 0;


/* Background Subtraction Methods */
//auto algorithmsName = BGS_Factory::Instance()->GetRegisteredAlgorithmsName();


int mydelay;

std::vector<std::vector<int> > BlobsArea;
std::vector<std::vector<int> > counting_blobs;
struct detected_bricks {
    cv::Mat ax;
    int daste;
    int shomarande;
    int shomarande7;
    int shomarande8;
    int shomarande9;
    int shomarande10;

    clock_t detected_time;
};
detected_bricks mybrick;
detected_bricks getmybrick;
std::list<detected_bricks> workingset;

#include "QScreen"

int  lcd2=0;
int lcd7=0;
int lcd8=0;
int  lcd9=0;
int lcd10=0;
bool more_than_one_blob=false;
#define IMG_WIDTH	200
#define WND_NAME_RGB_CUBE	"RGB cube"
#define WND_NAME_RGB_CIE76	"RGB CIE76"
#define WND_NAME_HSV_CUBE	"HSV cube"
#define WND_NAME_HSV_CIE76	"HSV CIE76"
#define WND_NAME_RGB_KMEANS	"RGB K-means"
#define WND_NAME_HSV_KMEANS	"HSV K-means"
#define WND_NAME_RGB_CIE94	"RGB CIE94"
#define WND_NAME_HSV_CIE94	"HSV CIE94"
#include "DomColors.h"
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
cv::Scalar Compare_SCALAR_MINIMUM;
cv::Scalar Compare_SCALAR_MAXIMUM;
string code_color;

cv::Scalar getting_Compare_SCALAR_MINIMUM;
cv::Scalar getting_Compare_SCALAR_MAXIMUM;
string getting_code_color;


cv::Scalar our_SCALAR_MINIMUM;
cv::Scalar our_SCALAR_MAXIMUM;



std::vector<cv::Scalar > min_colors;
std::vector<cv::Scalar > max_colors;

bool from_up=false;
bool from_left=false;
bool from_right=false;
bool from_bottom=false;


cv::Mat origFrame_copy;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(" سیستم شمارشگر بهسان اندیش ");
    ui->lineEdit_min0->setVisible(0);
    ui->lineEdit_min1->setVisible(0);
    ui->lineEdit_min2->setVisible(0);
    ui->lineEdit_max0->setVisible(0);
    ui->lineEdit_max1->setVisible(0);
    ui->lineEdit_max2->setVisible(0);
    QObject::connect(ui->toolButton, SIGNAL(colorSelected(QColor)),
                     this, SLOT(onminColorSelected(QColor)));

    ui->groupBox_8->setHidden(true);
    //    QScreen *screen = QGuiApplication::primaryScreen();
    //    QRect screenres=screen->geometry();

    //    this->move(QPoint(screenres.x(),screenres.y()));
    //    this->resize(screenres.width(),screenres.height());
    //    this->showMaximized();

    this->setLayoutDirection(Qt::RightToLeft);
    //hide toolbar
    ui->mainToolBar->hide();
    this->setStyleSheet("MainWindow {background-image: url(:/images/wallpaper.jpg);}");
    ui->label_camera->setStyleSheet("background-color:black;");
    //ui->stackedWidget->setStyleSheet("background-color:White;");
    //ui->stackedWidget_3->setStyleSheet("background-color:White;");
    ui->label_DetectedBrick->setStyleSheet("background-color:black;");

    ui->label_DetectedBrick->setScaledContents(true);
    ui->label_camera->setScaledContents(true);


    ui->listWidget->hide();
    ui->lineEdit_2->hide();




    //ui->pushButton_power->setIcon(":/images/green-power-button-icon.png");
    // ui->pushButton_power->setStyleSheet("QPushButton{background: transparent;}");


    ui->pushButton_power->setIcon(QPixmap(":/images/green-power-button-icon.png"));

    ui->radioButton->setChecked(false);
    ui->radioButton_2->setChecked(false);
    ui->radioButton_3->setChecked(false);
    ui->radioButton_7->setChecked(false);


    const QString DRIVER("QSQLITE");

    if(!QSqlDatabase::isDriverAvailable(DRIVER))
    {             QMessageBox::information(this, "fail", "sqlite driver");

    }
    db = QSqlDatabase::addDatabase(DRIVER);
    db.setHostName("localhost");
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("ManagerDB.db");
    if (!db.open()) {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
                              qApp->tr("Unable to establish a database connection.\n"
                                       "This program needs SQLite support. Please read "
                                       "the Qt SQL driver documentation for information how "
                                       "to build it.\n\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);

    }


    if(!db.open())
        qWarning() << "ERROR1: " << db.lastError();

    QSqlQuery query1("create table Users (username nvarchar(40) primary key, firstname nvarchar(20), lastname nvarchar(20), password nvarchar(20))");
    QSqlQuery query2("insert into Users values('admin', 'Sabra', 'Hashembeygi','1234')");

    //          QSqlQuery query3;
    //          query3.exec("create table coco "
    //                    "(id nvarchar(MAX) primary key, "
    //                    "cameratype nvarchar(MAX), "
    //                    "svmpath nvarchar(MAX), "
    //                    "resultpath nvarchar(MAX))");

    QSqlQuery query3("create table coco51 (idcam integer,cameratype nvarchar(40),  resultpath nvarchar(40), side nvarchar(40), perecent integer,mdelay integer, x0 integer, y0 integer )");

    QSqlQuery query4("create table classes (class1 integer, class2 integer, class3 integer, class4 integer, class5 integer, class6 integer, class7 integer, class8 integer, class9 integer, class10 integer, class11 integer, class12 integer, class13 integer, class14 integer, class15 integer, class16 integer, class17 integer, class18 integer, class19 integer, class20 integer)");

    //QSqlQuery query3("create table coco (idcam integer,cameratype nvarchar(n), svmpath nvarchar(n), resultpath nvarchar(n))");

    if(!query1.isActive())
        qWarning() << "ERROR100: " << query1.lastError().text();
    if(!query2.isActive())
        qWarning() << "ERROR200: " << query2.lastError().text();
    if(!query3.isActive())
        qWarning() << "ERROR300: " << query3.lastError().text();
    if(!query4.isActive())
        qWarning() << "ERROR400: " << query3.lastError().text();



    //for draw rect by mouse for setting frame
    m_nInitialX =0;
    m_nInitialY = 0;
    m_nFinalX = 0;
    m_nFinalY = 0;
    m_nbMousePressed = false;
    DrawRect=false;
    finalx=0;
    finaly=0;
    finalheight=0;
    finalwidth=0;
    connect(ui->label_camera_check_2,SIGNAL(showMousePeressed(QPoint&)),this,SLOT(showMousePeressed(QPoint&)));
    connect(ui->label_camera,SIGNAL(sendMousPosition(QPoint&)),this,SLOT(showMousePosition(QPoint&)));
    connect(ui->label_camera,SIGNAL(showMousePeressed(QPoint&)),this,SLOT(showMousePeressed(QPoint&)));
    connect(ui->label_camera,SIGNAL(showMouseReleased(QPoint&)),this,SLOT(showMouseReleased(QPoint&)));

    ui->label_DetectedBrick->setHidden(true);
    ui->label_camera->setHidden(true);



    ui->label_resultsave->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}




bool in_range(Scalar color, Scalar orange_min, Scalar orange_max)
{
    bool result = false;
    std::cout <<"orange"<<color.val[0] <<endl;
    std::cout <<orange_min.val[0] <<endl;
    std::cout <<orange_max.val[0] <<endl;

    std::cout <<"orange1"<<color.val[1] <<endl;
    std::cout <<orange_min.val[1] <<endl;
    std::cout <<orange_max.val[1] <<endl;

    std::cout <<"orange2"<<color.val[2] <<endl;
    std::cout <<orange_min.val[2] <<endl;
    std::cout <<orange_max.val[2] <<endl;


    std::cout <<"orange3"<<color.val[3] <<endl;
    std::cout <<orange_min.val[3] <<endl;
    std::cout <<orange_max.val[3] <<endl;

    std::cout <<(color.val[0] >= orange_min.val[0] && color.val[0] < orange_max.val[0]+1)<<endl;
    std::cout <<(color.val[1] >= orange_min.val[1] && color.val[1] < orange_max.val[1]+1)<<endl;
    std::cout <<(color.val[2] >= orange_min.val[2] && color.val[2] < orange_max.val[2]+1)<<endl;
    std::cout <<(color.val[3] >= orange_min.val[3] && color.val[3] < orange_max.val[3]+1)<<endl;

    if ((color.val[0] >= orange_min.val[0] && color.val[0] < orange_max.val[0]+1) &&
            (color.val[1] >= orange_min.val[1] && color.val[1] < orange_max.val[1]+1) &&
            (color.val[2] >= orange_min.val[2] && color.val[2] < orange_max.val[2]+1) &&
            (color.val[3] >= orange_min.val[3] && color.val[3] < orange_max.val[3])+1)
    {
        result = true;
    }
    return result;
}
void MainWindow::on_pushButton_cameraConnect_clicked()
{

    //change background color of line edit to red and show a guide massage
    if(ui->lineEdit_2->isVisible() && ui->lineEdit_2->text()=="")
    {


        cameraSelected4=false;
    }

    else if(ui->lineEdit_2->isVisible() && ui->lineEdit_2->text()!="")
    {
        cam_path4=ui->lineEdit_2->text();

        capture4.open(cam_path4.toStdString());
        if(capture4.isOpened()){

            cameraSelected4=true;
            capture4.release();}
        else{

            cameraSelected4=false;
        }

    }
    else if(!ui->listWidget->isHidden())

    {
        webcam_id4= ui->listWidget->currentRow();
        qDebug() << webcam_id4 << "webcam_id";//if listwidget is empty or one of them not selected webcam_id will be -1
        if(webcam_id4==-1){cameraSelected4=false;
        }
        else{

            cameraSelected4=true;
        }
    }
    else if(ui->listWidget->isHidden() && ui->lineEdit_2->isHidden()){
        //guid message: "select type of camera"
        cameraSelected4=false;
    }
    if(cameraSelected4==true){

        stop4=false;
        ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex()+1);
        timer4 = new QTimer(this);
        // connect the timer to the widget and to the method that will execute
        connect(timer4, SIGNAL(timeout()), this, SLOT(displayFrame()));
        timer4 -> start(40);
        displayFrame();}
    else{
        QMessageBox msg;
        msg.setText("اتصال به دوربین برقرار نشده است.");
        msg.show();
        msg.exec();
    }

}

void MainWindow::displayFrame(){

    qDebug() <<capture4.isOpened() << "1";
    Mat Frame;

    CvCapture* capture;

    if(stop4!=true){

        qDebug() <<capture4.isOpened() << "2";
        if(!capture4.isOpened()){
            qDebug() <<capture4.isOpened()<< "3";
            if(ui->comboBox->currentIndex()==1){

                // capture = cvCaptureFromCAM(webcam_id);//("http://root:pass@192.168.197.90/axis-cgi/mjpg/video.cgi?.mjpg");
                capture4.open(webcam_id4);
            }
            else if(ui->comboBox->currentIndex()==2)
            {
                // QByteArray array =cam_path.toLocal8Bit();
                // char* buffer = array.data();
                //capture = cvCaptureFromFile(buffer);
                capture4.open(cam_path4.toStdString());


            }}
        else{

            qDebug() <<capture4.isOpened() << "5";
            qDebug() <<"dooooorbin roshan ast";
        }
        capture4 >> frame4;


        qDebug() <<capture4.isOpened() << "6";
        Frame=frame4;



        qDebug() <<capture4.isOpened() << "7";

        while(!stop4){
            capture4 >> frame4;
            capture4 >> frame4;
            if (frame4.empty()){
                cout<<"--(!)Error Connecting to Webcam\n";
                stop4=true;
                capture4.release();
                qDebug() <<capture4.isOpened() << "8";

            }
            else{
                qDebug() <<capture4.isOpened() << "9";
                QImage m=MatToQImage(frame4);
                ui->label_camera_check->setPixmap(QPixmap::fromImage(m));

                qApp->processEvents();

            }


        }
    }
    else{
        //if(stop==true) mean that we want to make camera off


        qDebug() <<capture4.isOpened() << "13";
        capture4.release();

        qDebug() <<capture4.isOpened() << "14";
        timer4->stop();
        //QImage m=MatToQImage(frame2);
        // ui->mat_Display->setPixmap(QPixmap::fromImage(m));
    }
}

cv::Rect rect_selected;
cv::Rect rectonprocessimage;
void MainWindow::displayFrameWithModel(){

    qDebug() <<capture2.isOpened() << "1";
    Mat Frame;

    CvCapture* capture;

    if(stop!=true){

        qDebug() <<capture2.isOpened() << "2";
        if(!capture2.isOpened()){
            qDebug() <<capture2.isOpened()<< "3";
            if(ui->comboBox->currentIndex()==1){

                // capture = cvCaptureFromCAM(webcam_id);//("http://root:pass@192.168.197.90/axis-cgi/mjpg/video.cgi?.mjpg");
                capture2.open(webcam_id);
            }
            else if(ui->comboBox->currentIndex()==2)
            {
                capture2.open(cam_path.toStdString());


            }}
        else{

            qDebug() <<capture2.isOpened() << "5";
            qDebug() <<"dooooorbin roshan ast";
        }
        capture2 >> frame2;


        qDebug() <<capture2.isOpened() << "6";
        Frame=frame2;
        //        if(stop4==true){
        //            stop4=false;
        //            capture4.release();
        //            timer4->stop();

        //        }


        Finalprocess();

    }
    else{


        qDebug() <<capture2.isOpened() << "133";
        capture2.release();

        qDebug() <<capture2.isOpened() << "144";
        timer->stop();
    }
}
QImage MainWindow::mymatToQImage(const cv::Mat &mat)
{
    if(mat.channels() == 1) { // if grayscale image
        return QImage((uchar*)mat.data, mat.cols, mat.rows, static_cast<int>(mat.step), QImage::Format_Grayscale8).copy();
    }
    if(mat.channels() == 3) { // if 3 channel color image
        cv::Mat rgbMat;
        cv::cvtColor(mat, rgbMat, cv::COLOR_BGR2RGB); // invert BGR to RGB
        return QImage((uchar*)rgbMat.data, mat.cols, mat.rows, static_cast<int>(mat.step), QImage::Format_RGB888).copy();
    }
    return QImage();
}
QImage MainWindow::MatToQImage( cv::Mat &mat)
{
    // 8-bits unsigned, NO. OF CHANNELS=1
    if(mat.type()==CV_8UC1)
    {
        // Set the color table (used to translate colour indexes to qRgb values)
        QVector<QRgb> colorTable;
        for (int i=0; i<256; i++)
            colorTable.push_back(qRgb(i,i,i));
        // Copy input Mat
        const uchar *qImageBuffer = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage img(qImageBuffer, mat.cols, mat.rows, mat.step, QImage::Format_Indexed8);
        img.setColorTable(colorTable);
        return img;
    }
    // 8-bits unsigned, NO. OF CHANNELS=3
    else if(mat.type()==CV_8UC3)
    {
        // Copy input Mat
        const uchar *qImageBuffer = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage img(qImageBuffer, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
        return img.rgbSwapped();
    }
    else
    {
        //qDebug() << "ERROR: Mat could not be converted to QImage.";
        return QImage();
    }
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    ui->listWidget->clear();
    ui->lineEdit_2->clear();
    //webcam type selected
    if(index==1){

        //clear errors of lineedit related to ip_camera path if there are


        ui->lineEdit_2->hide();


        //to detect webcams, we must search for "pnp" in its device name
        QString temp="pnp";

        ui->listWidget->show();


        QList<QCameraInfo> cameras = QCameraInfo::availableCameras();

        foreach (const QCameraInfo &cameraInfo, cameras) {
            QString biggerFile=cameraInfo.deviceName();
            if( (biggerFile.toStdString().find(temp.toStdString()) != std::string::npos)){
                qDebug() << cameraInfo.description();
                qDebug() << cameraInfo.deviceName();
                ui->listWidget->addItem(cameraInfo.description());}
        }
    }
    else if(index==2){
        ui->listWidget->hide();
        ui->lineEdit_2->show();
    }
    else if(index==0){
        ui->listWidget->hide();
        ui->lineEdit_2->hide();
    }
}

void MainWindow::on_pushButton_SveResult_clicked()
{
    QString directory = QFileDialog::getExistingDirectory(this,
                                                          tr("Open Directory"),
                                                          QDir::homePath(),
                                                          QFileDialog::ShowDirsOnly| QFileDialog::DontResolveSymlinks );

    if(directory==""){return;}
    ui->lineEdit->setText(directory);
}

void MainWindow::on_pushButton_loadModal_clicked()
{


    QFileDialog OlFileDialog (this);
    QString slFileName;
    OlFileDialog.setNameFilter (tr ("XML (*.xml)"));
    OlFileDialog.setFileMode (QFileDialog ::AnyFile);
    OlFileDialog.setViewMode (QFileDialog :: Detail);
    if (OlFileDialog.exec ())
        slFileName=OlFileDialog.selectedFiles().takeAt(0);
    else
        return;

    return;


}



void MainWindow::on_pushButton_Login_clicked()
{
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();

    if (db.isOpen()) {

        QSqlQuery query4("SELECT * FROM Users");
        int idName = query4.record().indexOf("username");
        while (query4.next())
        {
            QString name = query4.value(idName).toString();
            qDebug() << "===" << name;
        }
        QSqlQuery query(db);

        if (!query.exec("SELECT username,password FROM Users WHERE username ='"+ui->lineEdit_username->text()+"' AND password ='"+ui->lineEdit_password->text()+"'")) {
            qWarning() << "ERROR: " << query.lastError().text();
            QMessageBox::information(this, "پایگاه داده", "در اجرای پایگاه داده مشکلی وجود دارد. مجدد تلاش کنید.   ");

        } else {
            while (query.next()) {
                QString usernameFromDB = query.value(0).toString();
                QString passwordFromDB = query.value(1).toString();
                qDebug() << usernameFromDB << passwordFromDB;
                if (usernameFromDB == username && passwordFromDB == password){
                    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex()+1);
                    QMessageBox::information(this, "ورود", "خوش آمدید.  ");}
                else{
                    QMessageBox::information(this, "ورود", "نام کاربری یا رمز عبور به درستی وارد نشده اند.   ");}
            }
        }
    } else {
        QMessageBox::information(this, "پایگاه داده", "اتصال به پایگاه داده برقرار نشده است.    ");
    }

}

void MainWindow::on_pushButton_Register_clicked()
{
    ui->stackedWidget_3->setCurrentIndex(ui->stackedWidget_3->currentIndex()+1);

}

void MainWindow::on_pushButton_registerDone_clicked()
{
    if(ui->lineEdit_21->text()=="admin" && ui->lineEdit_22->text()=="1234"){
        if(db.isOpen()){

            try
            {

                QSqlQuery queryRegister;
                queryRegister.prepare("INSERT INTO Users(username, firstname, lastname, password) VALUES (:u, :f , :l, :p)");
                queryRegister.bindValue(":u",ui->lineEdit_25->text() );
                queryRegister.bindValue(":f",ui->lineEdit_23->text());
                queryRegister.bindValue(":l", ui->lineEdit_24->text());
                queryRegister.bindValue(":p", ui->lineEdit_26->text());

                if(queryRegister.exec())
                {
                    QMessageBox::information(this, "ثبت نام کاربر جدید", "کاربر جدید با موفقیت ثبت نام شد.   ");

                    qDebug() << "add person ok: " << queryRegister.lastError();
                }

                else
                {
                    QMessageBox::information(this, "ثبت نام کاربر جدید", "ثبت نام کاربر جدید انجام نشد. مجدد تلاش کنید. ");

                    qDebug() << "add person failed: " << queryRegister.lastError();
                }



            }catch(exception ex)
            {
                //dialog box to say that username exit before
            }

        }
        else{

            QMessageBox::information(this, "پایگاه داده", "اتصال به پایگاه داده برقرار نشده است.    ");

        }
    }
}

void MainWindow::on_pushButton_BacktoLogin_clicked()
{
    ui->stackedWidget_3->setCurrentIndex(ui->stackedWidget_3->currentIndex()-1);
}


//https://stackoverflow.com/questions/29196087/how-to-build-the-qt-sql-driver-plugin-qsqlcipher-for-sqlite-db-with-sqlcipher

void MainWindow::on_pushButton_exit_clicked()
{
    ui->stackedWidget_3->setCurrentIndex(0);
    ui->stackedWidget->setCurrentIndex(0);
    ui->comboBox->setCurrentIndex(0);
    ui->lineEdit_2->clear();
    ui->listWidget->clear();
    ui->lineEdit->clear();
    ui->lineEdit_username->clear();
    ui->lineEdit_password->clear();


}



void MainWindow::on_pushButton_saveConfigure_clicked()
{
    bool correctinputs=true;
    QString selectedcampas;

    if(ui->comboBox->currentIndex()==0 ||(ui->comboBox->currentIndex()==2 && ui->lineEdit_2->text().isEmpty()) || (ui->comboBox->currentIndex()==1 && ui->listWidget->selectedItems().isEmpty())){
        QMessageBox::information(this, "خطا", "دوربین انتخاب نشده است..");
        correctinputs=false;
    }



    if(!correctinputs){return;}

    if(db.isOpen()){

        try
        {
            if(ui->comboBox->currentIndex()==1 && !(ui->listWidget->selectedItems().takeLast()->text().isEmpty()))
            {

                selectedcampas=ui->listWidget->selectedItems().takeLast()->text();
            }else if (ui->comboBox->currentIndex()==2 && !(ui->lineEdit_2->text().isEmpty())){

                selectedcampas=ui->lineEdit_2->text();
            }




            QSqlQuery removeQuery;
            removeQuery.prepare("DELETE FROM coco51");

            if (removeQuery.exec())
            {
                qDebug() << "remove all persons succes: " << removeQuery.lastError();
            }
            else
            {
                qDebug() << "remove all persons failed: " << removeQuery.lastError();
            }

            QSqlQuery querysaveConfigure;
            querysaveConfigure.prepare("insert into coco51(idcam, cameratype, resultpath, side, perecent, mdelay,x0,y0) VALUES ( :i, :c , :r, :si, :p, :md ,:x0,:y0)");
            querysaveConfigure.bindValue(":i",ui->comboBox->currentIndex() );
            querysaveConfigure.bindValue(":c",selectedcampas );
            querysaveConfigure.bindValue(":r", ui->lineEdit->text());
            if(ui->radioButton->isChecked()){
                querysaveConfigure.bindValue(":si", "left");}
            else if(ui->radioButton_2->isChecked()){

                querysaveConfigure.bindValue(":si", "right");
            }else if(ui->radioButton_3->isChecked()){
                querysaveConfigure.bindValue(":si", "up");

            }else if(ui->radioButton_7->isChecked()){
                querysaveConfigure.bindValue(":si", "bottom");

            }
            querysaveConfigure.bindValue(":p", ui->lineEdit_27->text().toInt());

            querysaveConfigure.bindValue(":md", ui->lineEdit_5->text().toInt());
            if(from_up || from_bottom){

                querysaveConfigure.bindValue(":x0", 0);
                querysaveConfigure.bindValue(":y0", m_nInitialY);

            }
            if(from_left || from_right){
                querysaveConfigure.bindValue(":x0", m_nInitialX);
                querysaveConfigure.bindValue(":y0", 0);
            }

            querysaveConfigure.exec();
            qDebug() << "exec :" << querysaveConfigure.lastError();


            QMessageBox::information(this, "ذخیره پیکربندی", "پیکربندی ذخیره شد.");

        }catch(exception ex)
        {
            //dialog box to say that username exit before
        }

    }
    else{

        //dialog box to say that db is not open
        QMessageBox::information(this,"پایگاه داده", "ارتباط با پایگاه داده ناموفق بود.");


    }


}




void MainWindow::on_pushButton_lastConfig_clicked()
{
    ui->listWidget->clear();
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();


    if(db.isOpen()){

        try
        {


            QSqlQuery querysaveConfigure;

            querysaveConfigure.exec("SELECT * from coco51");



            if (!querysaveConfigure.exec()) {
                qWarning() << "ERROR1: " << db.lastError();

                QMessageBox::information(this, "پایگاه داده", "دریافت پیکربندی قبلی از پایگاه داده انجام نشد.   ");

            } else {
                QString cmid ;
                QString cmtyp ;
                QString selectedsvm ;
                QString resultfoldersvm ;
                QString side;
                QString Percent;
                QString filterColorSelected;
                QString x_00;
                QString y_00;
                while (querysaveConfigure.next()) {
                    cmid = querysaveConfigure.value(0).toString();
                    cmtyp = querysaveConfigure.value(1).toString();
                    resultfoldersvm = querysaveConfigure.value(2).toString();
                    side=querysaveConfigure.value(3).toString();
                    Percent=querysaveConfigure.value(4).toString();
                    x_00=querysaveConfigure.value(5).toString();
                    y_00=querysaveConfigure.value(6).toString();

                    ui->lineEdit_5->setText(querysaveConfigure.value(5).toString());
                    qDebug() << cmid << cmtyp <<selectedsvm;
                    ui->comboBox->setCurrentIndex(cmid.toInt());
                    ui->listWidget->clear();
                    if(ui->comboBox->currentIndex()==1){
                        ui->listWidget->addItem(cmtyp);
                        ui->listWidget->show();
                    }
                    if(ui->comboBox->currentIndex()==2){
                        ui->lineEdit_2->setText(cmtyp);
                        ui->lineEdit_2->show();
                    }
                    ui->lineEdit->setText(resultfoldersvm);
                    if(side=="left"){
                        ui->radioButton->setChecked(true);
                        ui->radioButton_2->setChecked(false);
                        ui->radioButton_3->setChecked(false);
                        ui->radioButton_7->setChecked(false);

                    }else if(side=="right"){
                        ui->radioButton_2->setChecked(true);
                        ui->radioButton->setChecked(false);
                        ui->radioButton_3->setChecked(false);
                        ui->radioButton_7->setChecked(false);


                    }else if(side=="up"){
                        ui->radioButton_2->setChecked(false);
                        ui->radioButton->setChecked(false);
                        ui->radioButton_3->setChecked(true);
                        ui->radioButton_7->setChecked(false);

                    }else if(side=="bottom"){
                        ui->radioButton_2->setChecked(false);
                        ui->radioButton->setChecked(false);
                        ui->radioButton_3->setChecked(false);
                        ui->radioButton_7->setChecked(true);
                    }
                    ui->lineEdit_27->setText(Percent);


                }


            }




        }catch(exception ex)
        {
            //dialog box to say that username exit before
        }

    }
    else{

        //dialog box to say that db is not open
        qWarning() << "ERROR1000: " << db.lastError();


    }


}
bool firstRun=false;
void MainWindow::on_pushButton_power_clicked()
{



    lcd2=0;
    ui->lcdNumber_2->display(0);
    lcd7=0;
    ui->lcdNumber_7->display(0);
    lcd8=0;
    ui->lcdNumber_8->display(0);
    lcd9=0;
    ui->lcdNumber_9->display(0);
    lcd10=0;
    ui->lcdNumber_10->display(0);
    carCountLeft=0;

    if(stop==true){



        if(db.isOpen()){

            try
            {


                QSqlQuery querysaveConfigure;

                querysaveConfigure.exec("SELECT * from coco51");
                if (!querysaveConfigure.exec()) {
                    qWarning() << "ERROR1: " << db.lastError();

                    QMessageBox::information(this, "خطا", "در اجرای پایگاه داده مشکلی وجود دارد.");

                } else {

                    while (querysaveConfigure.next()) {
                        cmid2 = querysaveConfigure.value(0).toString();
                        cmtyp2 = querysaveConfigure.value(1).toString();
                        resultfoldersvm2 = querysaveConfigure.value(2).toString();
                        sideofral = querysaveConfigure.value(3).toString();
                        perecentofbrick=querysaveConfigure.value(4).toString();
                        mydelay=(querysaveConfigure.value(5).toString().toInt())*1000;
                        x_0=(querysaveConfigure.value(6).toString().toInt());
                        y_0=(querysaveConfigure.value(7).toString().toInt());
                        cameraSelected=true;
                        stop=false;
                    }


                    if(cameraSelected==true && cmid2 !="" &&cmtyp2!=""   ){


                        if( capture2.isOpened()){
                            capture2.release();
                        }

                        if(cmid2.toInt()==1){
                            capture2.open(0);

                        }else{
                            capture2.open(cmtyp2.toStdString());
                        }


                        qDebug() <<capture2.isOpened() << "6";


                        qDebug() <<capture2.isOpened() << "7";
                        stop=false;
                        ui->pushButton_power->setIcon(QPixmap(":/images/red-power.png"));

                        timer = new QTimer(this);
                        if(capture2.isOpened()){
                            firstRun=true;


                       DrawRect=false;

                            }

                        // connect the timer to the widget and to the method that will execute
                        connect(timer, SIGNAL(timeout()), this, SLOT(displayFrameWithModel()));
                        timer -> start(40);
                        displayFrameWithModel();

                    }
                    else{
                        QMessageBox msg;
                        msg.setText("اتصال به دوربین برقرار نشده است.");
                        msg.show();
                        msg.exec();
                    }


                }
            }catch(exception ex)
            {
                //dialog box to say that username exit before
            }

        }
        else{

            //dialog box to say that db is not open
            qWarning() << "ERROR1000: " << db.lastError();


        }

    }else if (stop==false){

        stop=true;
        if(firstRun){ DrawRect=true;}
        capture2.release();

        ui->pushButton_power->setIcon(QPixmap(":/images/green-power-button-icon.png"));

    }


}





void MainWindow::on_pushButton_clicked()
{
    capture4.release();
    stop4=true;
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex()-1);

}






void MainWindow::matchCurrentFrameBlobsToExistingBlobs(std::vector<Blob>& existingBlobs, std::vector<Blob>& currentFrameBlobs,cv::Mat& imgFrame2Copy) {
    for (auto& existingBlob : existingBlobs) {
        existingBlob.blnCurrentMatchFoundOrNewBlob = false;
        existingBlob.predictNextPosition();
    }

    for (auto& currentFrameBlob : currentFrameBlobs) {
        int intIndexOfLeastDistance = 0;
        double dblLeastDistance = 100000.0;

        for (unsigned int i = 0; i < existingBlobs.size(); i++) {

            if (existingBlobs[i].blnStillBeingTracked == true) {
                double dblDistance = distanceBetweenPoints(currentFrameBlob.centerPositions.back(), existingBlobs[i].predictedNextPosition);

                if (dblDistance < dblLeastDistance) {
                    dblLeastDistance = dblDistance;
                    intIndexOfLeastDistance = i;
                }
            }
        }
        qDebug() <<"dblLeastDistance"<<dblLeastDistance;
        qDebug() <<" currentFrameBlob.dblCurrentDiagonalSize * 0.5"<< currentFrameBlob.dblCurrentDiagonalSize * 0.5;


        if (dblLeastDistance < currentFrameBlob.dblCurrentDiagonalSize* 0.5 ) {
            // if(  currentFrameBlob.centerPositions.back().x< imgFrame2Copy.cols/2+1)
            addBlobToExistingBlobs(currentFrameBlob, existingBlobs, intIndexOfLeastDistance);
            std::cout << existingBlobs.at(intIndexOfLeastDistance).currentBoundingRect.area() << intIndexOfLeastDistance <<"     _____ex\n";
            // BlobsArea[intIndexOfLeastDistance].push_back(existingBlobs.at(intIndexOfLeastDistance).currentBoundingRect.area());

        }
        else {
            //std::max_element(std::begin(existingBlobs), std::end(existingBlobs));

            qDebug() << currentFrameBlob.dblCurrentDiagonalSize <<",,,,"<< dblLeastDistance  << "  mmmmmmmm";
            addNewBlob(currentFrameBlob, existingBlobs,imgFrame2Copy);
        }

    }

    for (auto& existingBlob : existingBlobs) {
        if (existingBlob.blnCurrentMatchFoundOrNewBlob == false) {
            existingBlob.intNumOfConsecutiveFramesWithoutAMatch++;
        }
        if (existingBlob.intNumOfConsecutiveFramesWithoutAMatch >= 5) {
            existingBlob.blnStillBeingTracked = false;
        }
    }
}


void MainWindow::addBlobToExistingBlobs(Blob& currentFrameBlob, std::vector<Blob>& existingBlobs, int& intIndex) {
    existingBlobs[intIndex].currentContour = currentFrameBlob.currentContour;
    existingBlobs[intIndex].currentBoundingRect = currentFrameBlob.currentBoundingRect;
    existingBlobs[intIndex].currentRotatedRect = currentFrameBlob.currentRotatedRect;
    existingBlobs[intIndex].centerPositions.push_back(currentFrameBlob.centerPositions.back());
    existingBlobs[intIndex].dblCurrentDiagonalSize = currentFrameBlob.dblCurrentDiagonalSize;
    existingBlobs[intIndex].dblCurrentAspectRatio = currentFrameBlob.dblCurrentAspectRatio;
    if(existingBlobs[intIndex].counted==false){
        existingBlobs[intIndex].blnStillBeingTracked = true;}
    else{existingBlobs[intIndex].blnStillBeingTracked = false;}
    existingBlobs[intIndex].blnCurrentMatchFoundOrNewBlob = true;
    existingBlobs[intIndex].id = blobcount;
}


void MainWindow::addNewBlob(Blob& currentFrameBlob, std::vector<Blob>& existingBlobs,cv::Mat& imgFrame2Copy) {
    currentFrameBlob.counted=false;
    currentFrameBlob.blnCurrentMatchFoundOrNewBlob = true;
    existingBlobs.push_back(currentFrameBlob);
}


double MainWindow::distanceBetweenPoints(cv::Point point1, cv::Point point2) {
    int intX = abs(point1.x - point2.x);
    int intY = abs(point1.y - point2.y);
    qDebug() << "intX";
    qDebug() << "intY";
    qDebug() << intX;
    qDebug() << intY;
    qDebug() << sqrt(pow(intX, 2) + pow(intY, 2));
    return(sqrt(pow(intX, 2) + pow(intY, 2)));
}


void MainWindow::drawAndShowContours(cv::Size imageSize, std::vector<std::vector<cv::Point> > contours, std::string strImageName) {
    cv::Mat image(imageSize, CV_8UC3, SCALAR_BLACK);
    cv::drawContours(image, contours, -1, SCALAR_WHITE, -1);
    cv::imshow(strImageName, image);
}


void MainWindow::drawAndShowContours(cv::Size imageSize, std::vector<Blob> blobs, std::string strImageName) {
    cv::Mat image(imageSize, CV_8UC3, SCALAR_BLACK);
    std::vector<std::vector<cv::Point> > contours;

    for (auto& blob : blobs) {
        if (blob.blnStillBeingTracked == true) {
            contours.push_back(blob.currentContour);
        }
    }

    cv::drawContours(image, contours, -1, SCALAR_WHITE, -1);
    cv::imshow(strImageName, image);
}


bool MainWindow::checkIfBlobsCrossedTheLineRight(std::vector<Blob>& blobs, int& intVerticalLinePosition, int& carCountRight) {
    bool blnAtLeastOneBlobCrossedTheLine = false;

    for (auto blob : blobs) {
        if (blob.blnStillBeingTracked == true && blob.centerPositions.size() >= 2) {
            int prevFrameIndex = (int)blob.centerPositions.size() - 2;
            int currFrameIndex = (int)blob.centerPositions.size() - 1;

            // Left way
            if (blob.centerPositions[prevFrameIndex].x > 240 && blob.centerPositions[currFrameIndex].x <= 240) {
                carCountRight++;
                blnAtLeastOneBlobCrossedTheLine = true;
            }
        }
    }

    return blnAtLeastOneBlobCrossedTheLine;
}


bool MainWindow::checkIfBlobsCrossedTheLineLeft(Blob blob, int& intVerticalLinePosition, int& carCountLeft, cv::Mat& frameresized) {
    bool blnAtLeastOneBlobCrossedTheLineLeft = false;


    if (blob.blnStillBeingTracked == true && blob.centerPositions.size() >= 2  ) {
        int prevFrameIndex = (int)blob.centerPositions.size() - 2;
        int currFrameIndex = (int)blob.centerPositions.size() - 1;

        // Left way
        //            if (blob.centerPositions[prevFrameIndex].x <= frameresized.cols / 2 && blob.centerPositions[currFrameIndex].x > frameresized.cols / 2) {
        //                carCountLeft++;
        //                blnAtLeastOneBlobCrossedTheLineLeft = true;
        //            }
        // Left way
        if(sideofral=="left"){


            qDebug() << "blob.centerPositions[prevFrameIndex].x"<<blob.centerPositions[prevFrameIndex].x;
            qDebug() << "blob.centerPositions[currFrameIndex].x"<<blob.centerPositions[currFrameIndex].x;
            qDebug() <<"frameresized.cols / 2"<< frameresized.cols / 2 ;
            int x_rate=int(640/frameresized.cols);
            if (blob.centerPositions[prevFrameIndex].x <= (x_0/x_rate) && blob.centerPositions[currFrameIndex].x > (x_0/x_rate)) {

                carCountLeft++;
                blnAtLeastOneBlobCrossedTheLineLeft = true;
                qDebug()<<"*****"<<blob.id<<blob.counted;




            }else{

                qDebug() << "sabra";

            }



        }else if(sideofral=="right"){
            int x_rate=int(640/frameresized.cols);
            if (blob.centerPositions[prevFrameIndex].x > (x_0/x_rate) && blob.centerPositions[currFrameIndex].x <= (x_0/x_rate)) {
                carCountLeft++;

                blnAtLeastOneBlobCrossedTheLineLeft = true;
            }

        }

        else if(sideofral=="up"){
            int y_rate=int(480/frameresized.rows);
            if (blob.centerPositions[prevFrameIndex].y <= (y_0/y_rate) && blob.centerPositions[currFrameIndex].y > (y_0/y_rate)) {
                carCountLeft++;

                blnAtLeastOneBlobCrossedTheLineLeft = true;
            }

        }

        else if(sideofral=="bottom"){
            int y_rate=int(480/frameresized.rows);
            if (blob.centerPositions[prevFrameIndex].y > (y_0/y_rate) && blob.centerPositions[currFrameIndex].y <= (y_0/y_rate)) {
                carCountLeft++;

                blnAtLeastOneBlobCrossedTheLineLeft = true;
            }

        }
    }


    return blnAtLeastOneBlobCrossedTheLineLeft;
}



void MainWindow::drawBlobInfoOnImage(std::vector<Blob>& blobs, cv::Mat& imgFrame2Copy, cv::Mat& originalimage) {
    for (unsigned int i = 0; i < blobs.size(); i++) {
        if (blobs[i].blnStillBeingTracked == true) {
            cv::rectangle(imgFrame2Copy, blobs[i].currentBoundingRect, SCALAR_RED, 2);
            //if overlapped
            Rect andRect_overlap = (rectonprocessimage & blobs[i].currentBoundingRect);
            Rect orRect_whole = (rectonprocessimage | blobs[i].currentBoundingRect);
            double overlap_percentOfB;
            if (orRect_whole.width != 0 && orRect_whole.height != 0)
            {
                double overlap_percentOfA = float(andRect_overlap.area()) / rectonprocessimage.area() * 100;
                 overlap_percentOfB = float(andRect_overlap.area()) / blobs[i].currentBoundingRect.area() * 100;

                cout << "overlap percent in A " << overlap_percentOfA << "%" << endl;
                cout << "overlap percent in B " << overlap_percentOfB << "%" << endl;
            }

                            if(finalheight!=0 && finalwidth!=0 && overlap_percentOfB<80.0){

                                qDebug ()<<rect_selected.x<<"-"<<rect_selected.y<<"-"<<rect_selected.height<<"-"<<rect_selected.width;

                                qDebug ()<<rectonprocessimage.x<<"-"<<rectonprocessimage.y<<"-"<<rectonprocessimage.height<<"-"<<rectonprocessimage.width;
                                cv::rectangle(imgFrame2Copy, rectonprocessimage, SCALAR_RED,1);
                                cv::rectangle(imgFrame2Copy, rectonprocessimage & blobs[i].currentBoundingRect, SCALAR_GREEN, 1);

                                imshow("roi",imgFrame2Copy);
                               // cv::waitKey(0);
                                continue;
                            }

            int intFontFace = FONT_HERSHEY_SIMPLEX;
            double dblFontScale = (imgFrame2Copy.rows * imgFrame2Copy.cols) / 300000.0;
            int intFontThickness = (int)std::round(dblFontScale * 1.0);

            cv::putText(imgFrame2Copy, std::to_string(i), blobs[i].centerPositions.back(), intFontFace, dblFontScale, SCALAR_GREEN, intFontThickness);
            cv::Mat croppedImage;
            imgFrame2Copy(blobs[i].currentBoundingRect).copyTo(croppedImage);


            // INJA barresi mikonad va blobi ke az khate markazi gozashte ra barmidarad
            bool blnAtLeastOneBlobCrossedTheLineLeft = checkIfBlobsCrossedTheLineLeft(blobs[i], intVerticalLinePosition, carCountLeft, imgFrame2Copy);

            if (blnAtLeastOneBlobCrossedTheLineLeft == true) {


                //mybrick.shomarande=(carCountLeft);
                //ui->lcdNumber_2->display(QString::number(carCountLeft/2));

                cv::RotatedRect rotatedRect = blobs[i].currentRotatedRect;
                cv::RotatedRect ScalerotatedRect = blobs[i].currentRotatedRect;



                // read points and angle
                cv::Point2f rect_points[4];
                cv::Point2f Scalesrect_points[4];
                ScalerotatedRect.points(Scalesrect_points);
                rotatedRect.points(rect_points);



                float  angle = rotatedRect.angle; // angle
                float  Scaleangle = ScalerotatedRect.angle; // angle

                // read center of rotated rect
                cv::Point2f center = rotatedRect.center; // center
                cv::Point2f Scalecenter;
                Scalecenter.x = rotatedRect.center.x * 12; // center
                Scalecenter.y = rotatedRect.center.y * 12;
                ScalerotatedRect.center = Scalecenter;
                // draw rotated rect
                for (unsigned int j = 0; j < 4; ++j)
                    cv::line(imgFrame2Copy, rect_points[j], rect_points[(j + 1) % 4], cv::Scalar(0, 255, 0));

                cv::Mat drawwednew=originalimage.clone();
                for (unsigned int j = 0; j < 4; ++j) {

                    cv::line(originalimage, (rect_points[j] * 12), (rect_points[(j + 1) % 4] * 12), cv::Scalar(0, 255, 0), 7);
                    Scalesrect_points[j] = rect_points[j] * 12;
                }
                ScalerotatedRect.points(Scalesrect_points);

                // matrices we'll use
                cv::Mat M, rotated, cropped;
                cv::Mat ScaleM, Scalerotated, Scalecropped;

                // get angle and size from the bounding box
                angle = rotatedRect.angle;



                cv::Size rect_size = rotatedRect.size;
                cv::Size Scalerect_size;
                float perecentt=perecentofbrick.toFloat()/100.0;
                Scalerect_size.width = rect_size.width * 12*perecentt;
                Scalerect_size.height = rect_size.height * 12*perecentt;


                // thanks to http://felix.abecassis.me/2011/10/opencv-rotation-deskewing/
                if (rotatedRect.angle < -45.) {
                    angle += 90.0;
                    cv::swap(rect_size.width, rect_size.height);
                    cv::swap(Scalerect_size.width, Scalerect_size.height);

                }
                // get the rotation matrix
                M = cv::getRotationMatrix2D(rotatedRect.center, angle, 1.0);
                ScaleM = cv::getRotationMatrix2D(ScalerotatedRect.center, angle, 1.0);

                // perform the affine transformation
                warpAffine(imgFrame2Copy, rotated, M, imgFrame2Copy.size(), INTER_CUBIC);
                //  warpAffine(originalimage, Scalerotated, ScaleM, originalimage.size(), INTER_CUBIC);
                warpAffine(drawwednew, Scalerotated, ScaleM, drawwednew.size(), INTER_CUBIC);


                // crop the resulting image
                getRectSubPix(Scalerotated, Scalerect_size, ScalerotatedRect.center, Scalecropped);
                getRectSubPix(rotated, rect_size, rotatedRect.center, cropped);



                cv::imshow("lll", Scalecropped);
                //QImage brick=MatToQImage(Scalecropped);

                mybrick.ax=Scalecropped.clone();
                mybrick.detected_time=clock();
                // ui->label_DetectedBrick->setPixmap(QPixmap::fromImage(brick));
                //int 1 lcd2
                //int 2 lcd7
                //int 3 lcd8
                //int4  lcd9
                //int lcd10
                more_than_one_blob=false;
                // ui->label_10->setText(QString::number(Scalecropped.cols*Scalecropped.rows));
                ui->label_8->setText(QString::number(cv::contourArea(blobs[i].currentContour)));
                if(ui->lineEdit_4->text()!="" && int((cv::contourArea(blobs[i].currentContour))/ui->lineEdit_4->text().toDouble())>=2){
                    more_than_one_blob=true;
                }
                if(!more_than_one_blob){
                    qDebug() <<"mmmmmm" <<int((Scalecropped.cols*Scalecropped.rows)/ui->lineEdit_4->text().toDouble());
                }
                if(ui->radioButton_5->isChecked() || ui->radioButton_6->isChecked() || ui->radioButton_9->isChecked()){
                    int color_is_in_rang= color_detection3(Scalecropped);

                    if(color_is_in_rang==1){
                        if(more_than_one_blob){
                            lcd2=lcd2+int((cv::contourArea(blobs[i].currentContour))/ui->lineEdit_4->text().toDouble());
                        }else
                        { lcd2++;}
                        mybrick.shomarande=(lcd2);
                    }else if(color_is_in_rang==2){
                        if(more_than_one_blob){
                            lcd7=lcd7+int((cv::contourArea(blobs[i].currentContour))/ui->lineEdit_4->text().toDouble());
                        }else
                        { lcd7++;}
                        mybrick.shomarande7=(lcd7);
                    }else if(color_is_in_rang==3){
                        if(more_than_one_blob){
                            lcd8=lcd8+int((cv::contourArea(blobs[i].currentContour))/ui->lineEdit_4->text().toDouble());
                        }else
                        { lcd8++;}
                        mybrick.shomarande8=(lcd8);
                    }else if(color_is_in_rang==4){

                        if(more_than_one_blob){
                            lcd9=lcd9+int((cv::contourArea(blobs[i].currentContour))/ui->lineEdit_4->text().toDouble());
                        }else
                        { lcd9++;}
                        mybrick.shomarande9=(lcd9);
                    }else if(color_is_in_rang==5){
                        if(more_than_one_blob){
                            lcd10=lcd10+int((cv::contourArea(blobs[i].currentContour))/ui->lineEdit_4->text().toDouble());
                        }else
                        { lcd10++;}
                        mybrick.shomarande10=(lcd10);
                    }
                }else{

                    if(more_than_one_blob){
                        lcd2=lcd2+int((cv::contourArea(blobs[i].currentContour))/ui->lineEdit_4->text().toDouble());
                    }else
                    { lcd2++;}
                    mybrick.shomarande=(lcd2);

                }

                workingset.push_back(mybrick);
                int a= int((cv::contourArea(blobs[i].currentContour))/ui->lineEdit_4->text().toDouble());
                if(resultfoldersvm2!=""){

                    cv::Rect rr=enlargeROI(drawwednew,ScalerotatedRect.boundingRect(),ui->spinBox_2->value());
                    cv::Mat img_crop222 = cv::Mat(drawwednew, rr);
                      //cv::imshow("aaa", img_crop222);
                      //cv::waitKey(0);
                    imwrite(resultfoldersvm2.toStdString()+"/" + std::to_string(i) +"_"+QString::number(a).toStdString()+ ".png", img_crop222);

                    if(ui->checkBox_4->isChecked()){
                        QImage m=MatToQImage(img_crop222);
                        ui->label_resultsave->setPixmap(QPixmap::fromImage(m));
                    }
                }
                qDebug() << int((cv::contourArea(blobs[i].currentContour))/ui->lineEdit_4->text().toDouble());
                //cv::waitKey(0);
                // imwrite("d:/resultblob/" + std::to_string(i) + "alpha.png", croppedImage);
            }

        }
    }
}

cv::Rect MainWindow::enlargeROI(cv::Mat& frm, cv::Rect boundingBox, int padding) {
    cv::Rect returnRect = cv::Rect(boundingBox.x - padding, boundingBox.y - padding, boundingBox.width + ((padding+5) * 2), boundingBox.height + (padding * 2));
    if (returnRect.x < 0)
        returnRect.x = 0;
    if (returnRect.y < 0)
        returnRect.y = 0;
    if (returnRect.x + returnRect.width >= frm.cols)
        returnRect.width = frm.cols - returnRect.x;
    if (returnRect.y + returnRect.height >= frm.rows)
        returnRect.height = frm.rows - returnRect.y;
    return returnRect;
}

void MainWindow::drawCarCountOnImage(int& carCountRight, cv::Mat& imgFrame2Copy) {
    int intFontFace = FONT_HERSHEY_SIMPLEX;
    double dblFontScale = (imgFrame2Copy.rows * imgFrame2Copy.cols) / 450000.0;
    int intFontThickness = (int)std::round(dblFontScale * 4.5);

    // Right way
    cv::Size textSize = cv::getTextSize(std::to_string(carCountRight), intFontFace, dblFontScale, intFontThickness, 0);
    cv::putText(imgFrame2Copy, "car count:" + std::to_string(carCountRight), cv::Point(568, 25), intFontFace, dblFontScale, SCALAR_RED, intFontThickness);

    // Left way
    cv::Size textSize1 = cv::getTextSize(std::to_string(carCountLeft), intFontFace, dblFontScale, intFontThickness, 0);
    cv::putText(imgFrame2Copy, "car count:" + std::to_string(carCountLeft), cv::Point(10, 25), intFontFace, dblFontScale, SCALAR_YELLOW, intFontThickness);


}




int MainWindow::Finalprocess() {


    //cv::VideoCapture capture= getcapture;
    if (!capture2.isOpened()) {
        std::cerr << "Cannot initialize web camera!" << std::endl;
        return -1;
    }

    cv::Mat img_input;
    cv::Mat imgFrame1;
    cv::Mat imgFrame2;
    cv::Mat origFrame;
    std::vector<Blob> blobs;

    cv::Point crossingLine[2];
    cv::Point crossingLineLeft[2];





    capture2.read(imgFrame1);
    capture2.read(imgFrame2);
    cv::Size size3(imgFrame1.cols / 2, imgFrame1.rows / 2);

    cv::resize(imgFrame1, imgFrame1, size3);
    cv::resize(imgFrame2, imgFrame2, size3);

    cv::Size size1(imgFrame1.cols / 6, imgFrame1.rows / 6);
    cv::resize(imgFrame1, imgFrame1, size1);


    cv::resize(imgFrame2, imgFrame2, size1);

    img_input=imgFrame2;


    //CONTROL LINE FOR CARCOUNT ~AREA1 (RIGHT WAY)
    int intHorizontalLinePosition = (int)std::round((double)imgFrame1.cols * 0.35);
    intHorizontalLinePosition = intHorizontalLinePosition * 1.40;
    intVerticalLinePosition = (int)std::round((double)imgFrame1.rows * 0.35);
    //intVerticalLinePosition = intVerticalLinePosition * 1.40;

    crossingLine[0].x = imgFrame1.cols / 2;
    crossingLine[0].y = 1;

    crossingLine[1].x = imgFrame1.cols / 2;
    crossingLine[1].y = intVerticalLinePosition;

    //CONTROL LINE FOR CARCOUNT ~AREA2 (LEFT WAY)
    crossingLineLeft[0].x = imgFrame1.cols / 2;
    crossingLineLeft[0].y = 1;

    crossingLineLeft[1].x = imgFrame1.cols / 2;
    crossingLineLeft[1].y = intVerticalLinePosition;


    char chCheckForEscKey = 0;
    bool blnFirstFrame = true;
    int frameCount = 2;


    if(finalheight!=0 && finalwidth!=0){
        if(finalheight > 0 && finalwidth < 0 ){
            finalwidth=finalwidth*-1;
            finalx=finalx-finalwidth;
        }
        if(finalheight<0 && finalwidth>0){
            finalheight=finalheight*-1;
            finaly=finaly-finalheight;
        }
        if(finalheight<0 && finalwidth <0){
            finalwidth=finalwidth*(-1);
            finalx=finalx-finalwidth;
             finalheight=finalheight*(-1);
            finaly=finaly-finalheight;
        }
        rect_selected=cv::Rect(finalx,finaly,finalwidth,finalheight);
        rectonprocessimage=cv::Rect(finalx /float(320 / float(img_input.cols)),finaly/ float(240 / float(img_input.rows)),finalwidth/float(320 / float(img_input.cols)),finalheight/ float(240 / float(img_input.rows)));
//        cv::Point2f rect_points_org[4];
//         cv::Point2f rect_points[4];
//        rect_points_org[0] = cv::Point(rect_selected.x, rect_selected.y);
//        rect_points_org[1] = cv::Point(rect_selected.x + rect_selected.width, rect_selected.y);
//        rect_points_org[2] = cv::Point(rect_selected.x + rect_selected.width, rect_selected.y + rect_selected.height);
//        rect_points_org[3] = cv::Point(rect_selected.x, rect_selected.y + rect_selected.height);
//        rect_points[0].x = rect_points_org[0].x * float(320 / float(img_input.cols));
//        rect_points[0].y = rect_points_org[0].y * float(240 / float(img_input.rows));
//        rect_points[1].x = rect_points_org[1].x * float(320 / float(img_input.cols));
//        rect_points[1].y = rect_points_org[1].y * float(240 / float(img_input.rows));
//        rect_points[2].x = rect_points_org[2].x * float(320 / float(img_input.cols));
//        rect_points[2].y = rect_points_org[2].y * float(240 / float(img_input.rows));
//        rect_points[3].x = rect_points_org[3].x * float(320 / float(img_input.cols));
//        rect_points[3].y = rect_points_org[3].y * float(240 / float(img_input.rows));
//        vector<cv::Point> prectonprocessimage(4);

//        prectonprocessimage.push_back(rect_points[0]);
//        prectonprocessimage.push_back(rect_points[1]);
//        prectonprocessimage.push_back(rect_points[2]);
//        prectonprocessimage.push_back(rect_points[3]);

//        rectonprocessimage= boundingRect(prectonprocessimage);


    }


    while (capture2.isOpened() && stop!=true) {

        if(!workingset.empty()){
            getmybrick=workingset.front();
            if( clock()-getmybrick.detected_time>=mydelay){

                workingset.pop_front();
                //ui->lcdNumber->display(getmybrick.daste);
                if(ui->checkBox->isChecked()){
                    QImage brick=MatToQImage(getmybrick.ax);
                    ui->label_DetectedBrick->setPixmap(QPixmap::fromImage(brick));}


                ui->lcdNumber_2->display(QString::number(getmybrick.shomarande));
                ui->lcdNumber_7->display(QString::number(getmybrick.shomarande7));
                ui->lcdNumber_8->display(QString::number(getmybrick.shomarande8));
                ui->lcdNumber_9->display(QString::number(getmybrick.shomarande9));
                ui->lcdNumber_10->display(QString::number(getmybrick.shomarande10));

                //cv::imshow("brick",getmybrick.ax);
                cv::waitKey(1);
            }
        }

        // Capture frame-by-frame
        capture2 >> img_input;


        cv::Mat out;
        if(img_input.empty() == true){

            break;
        }
        origFrame = img_input.clone();
        cv::resize(img_input, img_input, size3);


        if (img_input.empty()) break;


        std::vector<Blob> currentFrameBlobs;

        cv::Mat imgFrame2Copy = imgFrame2.clone();




        cv::Size size2(img_input.cols / 6, img_input.rows / 6);


        // Resize input frame for better visualization
        cv::resize(img_input, img_input, size2, 0, 0, INTER_LINEAR);



        cv::Mat imgFrameCopy1 = imgFrame1.clone();
        cv::Mat imgFrameCopy2 = img_input.clone();

        cv::Mat image1_blur,image1_hvs;
        GaussianBlur(img_input, image1_blur, Size(3,3), 0,0);

        //change colorspace from BGR(RGB) to hvs
        cvtColor(image1_blur, image1_hvs, COLOR_BGR2HSV);


        cv::Mat img_mask;
        cv::Mat img_bkgmodel;
        cv::Mat out1;




        try {

            if(ui->radioButton_4->isChecked()){

                simple_detect(img_input,out1);
                img_mask=out1;


            }
            if(ui->radioButton_5->isChecked()){

                detect_our_color_based(image1_hvs,min_colors,max_colors,out);
                //detect_color_based(image1_hvs,4,out);
                img_mask=out;

            }

            if(ui->radioButton_6->isChecked()){

                simple_detect(img_input,out1);
                detect_our_color_based(image1_hvs,min_colors,max_colors,out);

                //detect_our_color_based(image1_hvs,cv::Scalar(ui->lineEdit_min0->text().toInt(),ui->lineEdit_min1->text().toInt(),ui->lineEdit_min2->text().toInt()),cv::Scalar(ui->lineEdit_max0->text().toInt(),ui->lineEdit_max1->text().toInt(),ui->lineEdit_max2->text().toInt()),out);;
                //detect_color_based(image1_hvs,4,out);
                bitwise_or(out1,out,img_mask);

            }

            if(ui->radioButton_8->isChecked()){

                framedifference_detect(imgFrameCopy1,imgFrameCopy2,out1);
                img_mask=out1;


            }

            if(ui->radioButton_9->isChecked()){

                framedifference_detect(imgFrameCopy1,imgFrameCopy2,out1);
                detect_our_color_based(image1_hvs,min_colors,max_colors,out);

                //detect_our_color_based(image1_hvs,cv::Scalar(ui->lineEdit_min0->text().toInt(),ui->lineEdit_min1->text().toInt(),ui->lineEdit_min2->text().toInt()),cv::Scalar(ui->lineEdit_max0->text().toInt(),ui->lineEdit_max1->text().toInt(),ui->lineEdit_max2->text().toInt()),out);;
                //detect_color_based(image1_hvs,4,out);
                bitwise_or(out1,out,img_mask);


            }
            //simple_detect(img_input,out1);
            //detect_our_color_based(image1_hvs,cv::Scalar(ui->lineEdit_min0->text().toInt(),ui->lineEdit_min1->text().toInt(),ui->lineEdit_min2->text().toInt()),cv::Scalar(ui->lineEdit_max0->text().toInt(),ui->lineEdit_max1->text().toInt(),ui->lineEdit_max2->text().toInt()),out);;
            ////detect_color_based(image1_hvs,4,out);
            //bitwise_or(out1,out,img_mask);
            imshow("img_mask",img_mask);
            qDebug() << ui->lineEdit_min0->text().toInt()<<ui->lineEdit_min1->text().toInt()<<ui->lineEdit_min2->text().toInt();
            qDebug() << ui->lineEdit_max0->text().toInt()<<ui->lineEdit_max1->text().toInt()<<ui->lineEdit_max2->text().toInt();

            //cv::waitKey(0);

            cv::Mat structuringElement3x3 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
            cv::Mat structuringElement5x5 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
            cv::Mat structuringElement7x7 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(7, 7));
            cv::Mat structuringElement15x15 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(15, 15));
            //           cv::dilate(img_mask, img_mask, structuringElement3x3);
            //            cv::erode(img_mask, img_mask, structuringElement3x3);
            //            cv::erode(img_mask, img_mask, structuringElement3x3);


            cv::Mat imgThreshCopy = img_mask.clone();
            std::vector<std::vector<cv::Point> > contours;
            cv::findContours(imgThreshCopy, contours, RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

            drawAndShowContours(img_mask.size(), contours, "imgContours");

            std::vector<std::vector<cv::Point> > convexHulls(contours.size());

            for (unsigned int i = 0; i < contours.size(); i++) {
                cv::convexHull(contours[i], convexHulls[i]);
            }

            drawAndShowContours(img_mask.size(), convexHulls, "imgConvexHulls");

            for (auto& convexHull : contours) {
                Blob possibleBlob(convexHull);

                qDebug () <<"_________";
                qDebug ()<<possibleBlob.currentBoundingRect.area() << ((img_input.cols * img_input.rows) / 14 );
                qDebug () << possibleBlob.dblCurrentAspectRatio;
                qDebug () <<        0.2;
                qDebug () <<possibleBlob.dblCurrentAspectRatio ;
                qDebug () <<4.3;
                qDebug () <<possibleBlob.currentBoundingRect.width ;
                qDebug () <<img_input.cols / 3;
                qDebug () <<possibleBlob.currentBoundingRect.height;
                qDebug () <<img_input.rows / 4;
                qDebug () <<  possibleBlob.dblCurrentDiagonalSize;
                qDebug () << 50.0;
                qDebug () <<possibleBlob.dblCurrentDiagonalSize ;
                qDebug () <<135.0 ;
                qDebug () << cv::contourArea(possibleBlob.currentContour) / (double)possibleBlob.currentBoundingRect.area();
                qDebug () << 0.50;
                int minimum_area=10;
                if(ui->lineEdit_3->text()!=""){
                    minimum_area=ui->lineEdit_3->text().toInt();
                }
                //possibleBlob.currentBoundingRect.area()

qDebug ()<<"here"<<finalheight;
//if(finalheight!=0 && finalwidth!=0){

//    cv::rectangle(imgFrame2Copy, rectonprocessimage, SCALAR_RED, 2);
//    cv::rectangle(imgFrame2Copy, possibleBlob.currentBoundingRect, SCALAR_GREEN, 2);

//    imshow("roi",imgFrame2Copy);
//    cv::waitKey(0);
//}


                if (cv::contourArea(possibleBlob.currentContour) > minimum_area /*(img_input.cols * img_input.rows) / 32 &&*/

                        //                    possibleBlob.dblCurrentAspectRatio > 0.2 &&
                        //                    possibleBlob.dblCurrentAspectRatio < 4.3 &&
                        //                    possibleBlob.currentBoundingRect.width > img_input.cols / 8 &&
                        //                    possibleBlob.currentBoundingRect.height > img_input.rows / 4 &&
                        //                    possibleBlob.dblCurrentDiagonalSize >= 50.0 &&
                        //                    possibleBlob.dblCurrentDiagonalSize < 135.0 &&
                        /* (cv::contourArea(possibleBlob.currentContour) / (double)possibleBlob.currentBoundingRect.area()) > 0.50*/) {
                    currentFrameBlobs.push_back(possibleBlob);
                }
            }

            drawAndShowContours(img_mask.size(), currentFrameBlobs, "imgCurrentFrameBlobs");

            if (blnFirstFrame == true) {
                for (auto& currentFrameBlob : currentFrameBlobs) {
                    blobs.push_back(currentFrameBlob);
                }
            }
            else {
                matchCurrentFrameBlobsToExistingBlobs(blobs, currentFrameBlobs,imgFrame2Copy);
            }

            qDebug() <<"here";
            drawAndShowContours(img_mask.size(), blobs, "imgBlobs");

            imgFrame2Copy = imgFrame2.clone();	// get another copy of frame 2 since we changed the previous frame 2 copy in the processing above


            qDebug() <<"here";


            // Check the rightWay
            //bool blnAtLeastOneBlobCrossedTheLine = checkIfBlobsCrossedTheLineRight(blobs, intVerticalLinePosition, carCountRight);
            // Check the leftWay





            drawCarCountOnImage(carCountRight, imgFrame2Copy);
            qDebug() <<"here";

            cv::Mat finalbricks;
            drawBlobInfoOnImage(blobs, imgFrame2Copy, origFrame);

            qDebug() <<"here";

            cv::imshow("imgFrame2Copy", imgFrame2Copy);
            qApp->processEvents();
            //cv::waitKey(1);

            //cv::imshow("origFrame", origFrame);
            //QImage dest = QImage((uchar*)origFrame.data, origFrame.cols, origFrame.rows, origFrame.step, QImage::Format_RGB888);
            if(ui->checkBox_2->isChecked()){

                 origFrame_copy=origFrame.clone();
                cv::Size size3(320, 240);
                 cv::resize(origFrame_copy, origFrame_copy, size3);
                 if(finalwidth!=0 && finalheight!=0){ui->label_camera->setPixmap(imagewithlogo(origFrame_copy));}else{
                    ui->label_camera->setPixmap(QPixmap::fromImage(mymatToQImage(origFrame_copy)));
                 }

            }


            // now we prepare for the next iteration
            currentFrameBlobs.clear();

            imgFrame1 = imgFrame2.clone();	// move frame 1 up to where frame 2 is

            if ((capture2.isOpened()) && !imgFrame2.empty()) {
                std::cout << "here\n";
                if(ui->radioButton_8->isChecked()){
                    // capture.read(imgFrame2);
                }
                if(imgFrame2.empty() == false){
                    std::cout << "here3\n";

                    cv::resize(imgFrame2, imgFrame2, size3);

                    // cv::Size size1(380, 240);
                    cv::resize(imgFrame2, imgFrame2, size2);}
                else{
                    std::cout << "here2\n";
                }
            }
            else {
                std::cout << "end of video\n";
                cv::destroyAllWindows();
                capture2.release();
                stop=true;
                timer->stop();
                break;
            }

            blnFirstFrame = false;
            frameCount++;
            chCheckForEscKey = cv::waitKey(1);

            //  ....do something else...
        }
        catch (std::exception& e) {
            std::cout << "Exception occurred" << std::endl;
            std::cout << e.what() << std::endl;
        }

    }



    while(!workingset.empty()){
        getmybrick=workingset.front();
        if( clock()-getmybrick.detected_time>=mydelay){
            workingset.pop_front();
            //ui->lcdNumber->display(getmybrick.daste);
            if(ui->checkBox->isChecked()){
                QImage brick=MatToQImage(getmybrick.ax);
                ui->label_DetectedBrick->setPixmap(QPixmap::fromImage(brick));}

            ui->lcdNumber_2->display(QString::number(getmybrick.shomarande));
            ui->lcdNumber_7->display(QString::number(getmybrick.shomarande7));
            ui->lcdNumber_8->display(QString::number(getmybrick.shomarande8));
            ui->lcdNumber_9->display(QString::number(getmybrick.shomarande9));
            ui->lcdNumber_10->display(QString::number(getmybrick.shomarande10));


        }
    }
    //cv::destroyAllWindows();
    lcd2=0;
    ui->lcdNumber_2->display(0);
    lcd7=0;
    ui->lcdNumber_7->display(0);
    lcd8=0;
    ui->lcdNumber_8->display(0);
    lcd9=0;
    ui->lcdNumber_9->display(0);
    lcd10=0;
    ui->lcdNumber_10->display(0);
    carCountLeft=0;


    capture2.release();
    stop=true;
    timer->stop();


    return 0;


}



void MainWindow::on_radioButton_clicked()
{
    ui->radioButton_2->setChecked(false);
    ui->stackedWidget->setCurrentIndex(3);
    from_up=false;
    from_left=true;
    from_right=false;
    from_bottom=false;
}
void MainWindow::on_radioButton_2_clicked()
{
    ui->radioButton->setChecked(false);
    ui->stackedWidget->setCurrentIndex(3);
    from_up=false;
    from_left=false;
    from_right=true;
    from_bottom=false;

}

void MainWindow::on_radioButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    from_up=true;
    from_left=false;
    from_right=false;
    from_bottom=false;

}

void MainWindow::on_radioButton_7_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    from_up=false;
    from_left=false;
    from_right=false;
    from_bottom=true;

}


bool MainWindow::color_detection(cv::Mat& finalBrick){

    Mat Scalecropped=finalBrick;
    Mat imgFiltered, imgAdjusted, Scalecropped2, mask, Scalecroppedgray;
    //cv::imshow("lll", Scalecropped);
    cv::cvtColor(Scalecropped, Scalecroppedgray, COLOR_BGR2GRAY);
    //               Mat kernel = getStructuringElement(MORPH_ELLIPSE, Size(3, 3), Point(0, 0));

    //               morphologyEx(Scalecroppedgray, imgFiltered, MORPH_TOPHAT, kernel, Point(0, 0), 3);
    //               imgAdjusted = imgFiltered * 15;
    //               adaptiveThreshold(imgAdjusted, imgAdjusted, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY_INV, 15, 12);
    //               cv::imshow("lll2", imgAdjusted);
    adaptiveThreshold(Scalecroppedgray, Scalecropped2, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY_INV, 15, 12);
    //cv::imshow("lll3", Scalecropped2);
    Scalecropped2=(~Scalecropped2);
    bitwise_or(Scalecropped, Scalecropped, mask, Scalecropped2);
    //cv::imshow("lll4", mask);
    int count = 5;
    if (count <= 0 || count > 255) {
        printf("The color count needs to be between 1-255. You picked: %d\n", count);
        // return 1;
    }
    clock_t tStart2 = clock();

    //cv::Size size1(mask.cols / 6, mask.rows / 6);
    //cv::resize(mask, mask, size1);
    // std::vector<cv::Vec3b> colors = find_dominant_colors(mask, count);
    // cv::threshold(imgAdjusted, imgAdjusted, 0, 255.0, CV_THRESH_BINARY);

    // https://answers.opencv.org/question/109166/in-k-means-clustering-how-do-i-reconstruct-just-a-part-of-the-image/

    cv::Mat img = mask;
    cv::resize(img, img, cv::Size(IMG_WIDTH, (double)img.rows / img.cols * IMG_WIDTH));
    cv::Mat img_hsv;
    cv::cvtColor(img, img_hsv, COLOR_BGR2HSV);

    dominant_colors_graber dcg;
    cv::Vec3i cube_param_rgb = { 1, 1, 1 };
    cv::Vec3i cube_param_hsv = { 1, 2, 2 };
    cv::Vec3i cie76_param = { 25, 0, 0 };
    cv::Vec3i cie94_param = { 15, 0, 0 };

    dcg.SetParam(cube_param_rgb);
    //cv::Mat img_rgb_cube = ShowColors(img, dcg.GetDomColors(img, CS_BGR, DT_CUBE));
    //dcg.SetParam(cube_param_hsv);
    //cv::Mat img_hsv_cube = ShowColors(img_hsv, dcg.GetDomColors(img, CS_HSV, DT_CUBE));
    //imshow("img_rgb_cube",img_rgb_cube);

    dcg.SetParam(cie76_param);
    dcg.SetColorsCount(1);

    std::vector <cv::Scalar> detected_colors;


    cv::Scalar current_color;
    // detected_colors=dcg.GetDomColors(img, CS_HSV, DT_CIE76);
    detected_colors=dcg.GetDomColors(img, CS_HSV, DT_CUBE);

    //               cv::Mat innn=ShowColors(img, detected_colors, 100);
    //               qDebug() << detected_colors.size();
    //               imshow("innn",innn);
    //               cv::waitKey(0);


    for(int i=0; i < detected_colors.size(); i++){
        std::cout << "coloooooooor"<<detected_colors.at(i) << ' ';
        current_color=detected_colors.at(i);

    }

    bool xz=in_range(current_color,Compare_SCALAR_MINIMUM,Compare_SCALAR_MAXIMUM);
    return xz;
    //cv::Mat img_rgb_cie76 = ShowColors(img, dcg.GetDomColors(img, CS_BGR, DT_CIE76));
    cv::Mat img_hsv_cie76 = ShowColors(img_hsv, detected_colors);



    /*     cv::Mat img_rgb_kmeans = ShowColors(img, dcg.GetDomColors(img, CS_BGR, DT_KMEANS));
              cv::Mat img_hsv_kmeans = ShowColors(img_hsv, dcg.GetDomColors(img, CS_HSV, DT_KMEANS));

              dcg.SetParam(cie94_param);
              cv::Mat img_rgb_cie94 = ShowColors(img, dcg.GetDomColors(img, CS_BGR, DT_CIE94));
              cv::Mat img_hsv_cie94 = ShowColors(img_hsv, dcg.GetDomColors(img, CS_HSV, DT_CIE94));*/

    //cv::cvtColor(img_hsv_cube, img_hsv_cube, CV_HSV2BGR);
    cv::cvtColor(img_hsv_cie76, img_hsv_cie76, COLOR_HSV2BGR);
    //cv::cvtColor(img_hsv_kmeans, img_hsv_kmeans, CV_HSV2BGR);
    //cv::cvtColor(img_hsv_cie94, img_hsv_cie94, CV_HSV2BGR);

    //cv::imshow(WND_NAME_RGB_CUBE, img_rgb_cube);
    //cv::imshow(WND_NAME_RGB_CIE76, img_rgb_cie76);
    // cv::imshow(WND_NAME_RGB_KMEANS, img_rgb_kmeans);
    //cv::imshow(WND_NAME_RGB_CIE94, img_rgb_cie94);
    //cv::imshow(WND_NAME_HSV_CUBE, img_hsv_cube);
    cv::imshow(WND_NAME_HSV_CIE76, img_hsv_cie76);
    //cv::imshow(WND_NAME_HSV_KMEANS, img_hsv_kmeans);
    //cv::imshow(WND_NAME_HSV_CIE94, img_hsv_cie94);
    cv::waitKey(1);

    printf("color: %.4fs\n", (double)(clock() - tStart2) / CLOCKS_PER_SEC);
}


//int 1 white
//int 2 green
//int 3 red
//int4  white with blue lines
int MainWindow::color_detection2(cv::Mat& finalBrick){

    Mat Scalecropped=finalBrick;
    Mat imgFiltered, imgAdjusted, Scalecropped2, mask, Scalecroppedgray;
    //cv::imshow("lll", Scalecropped);
    cv::cvtColor(Scalecropped, Scalecroppedgray, COLOR_BGR2GRAY);
    //               Mat kernel = getStructuringElement(MORPH_ELLIPSE, Size(3, 3), Point(0, 0));

    //               morphologyEx(Scalecroppedgray, imgFiltered, MORPH_TOPHAT, kernel, Point(0, 0), 3);
    //               imgAdjusted = imgFiltered * 15;
    //               adaptiveThreshold(imgAdjusted, imgAdjusted, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY_INV, 15, 12);
    //               cv::imshow("lll2", imgAdjusted);
    adaptiveThreshold(Scalecroppedgray, Scalecropped2, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY_INV, 15, 12);
    //cv::imshow("lll3", Scalecropped2);
    Scalecropped2=(~Scalecropped2);
    bitwise_or(Scalecropped, Scalecropped, mask, Scalecropped2);
    //cv::imshow("lll4", mask);
    int count = 5;
    if (count <= 0 || count > 255) {
        printf("The color count needs to be between 1-255. You picked: %d\n", count);
        // return 1;
    }
    clock_t tStart2 = clock();

    //cv::Size size1(mask.cols / 6, mask.rows / 6);
    //cv::resize(mask, mask, size1);
    // std::vector<cv::Vec3b> colors = find_dominant_colors(mask, count);
    // cv::threshold(imgAdjusted, imgAdjusted, 0, 255.0, CV_THRESH_BINARY);

    // https://answers.opencv.org/question/109166/in-k-means-clustering-how-do-i-reconstruct-just-a-part-of-the-image/

    cv::Mat img = mask;
    cv::resize(img, img, cv::Size(IMG_WIDTH, (double)img.rows / img.cols * IMG_WIDTH));
    cv::Mat img_hsv;
    cv::cvtColor(img, img_hsv, COLOR_BGR2HSV);

    dominant_colors_graber dcg;
    cv::Vec3i cube_param_rgb = { 1, 1, 1 };
    cv::Vec3i cube_param_hsv = { 1, 2, 2 };
    cv::Vec3i cie76_param = { 25, 0, 0 };
    cv::Vec3i cie94_param = { 15, 0, 0 };

    //dcg.SetParam(cube_param_rgb);
    //cv::Mat img_rgb_cube = ShowColors(img, dcg.GetDomColors(img, CS_BGR, DT_CUBE));
    //dcg.SetParam(cube_param_hsv);
    //cv::Mat img_hsv_cube = ShowColors(img_hsv, dcg.GetDomColors(img, CS_HSV, DT_CUBE));

    dcg.SetParam(cie76_param);
    dcg.SetColorsCount(1);

    std::vector <cv::Scalar> detected_colors;


    cv::Scalar current_color;
    cv::Scalar first_color;
    cv::Scalar second_color;
    cv::Scalar third_color;
    detected_colors=dcg.GetDomColors(img, CS_HSV, DT_CUBE);
    cv::Mat innn=ShowColors(img, detected_colors, 100);
    qDebug() << detected_colors.size();
    imshow("nn",innn);
    //cv::waitKey(0);
    for(int i=0; i < detected_colors.size(); i++){
        std::cout << "coloooooooor"<<detected_colors.at(i) << ' ';
        if(i==0)
            first_color=detected_colors.at(i);
        if(i==1)
            second_color=detected_colors.at(i);
        if(i==2)
            third_color=detected_colors.at(i);

    }

    cv::Scalar red_Compare_SCALAR_MINIMUM=cv::Scalar(175,50,20,0);
    cv::Scalar red_Compare_SCALAR_MAXIMUM=cv::Scalar(180,255,255,1);
    bool xz3=in_range(first_color,red_Compare_SCALAR_MINIMUM,red_Compare_SCALAR_MAXIMUM);
    if(xz3==true){
        return 3;}
    cv::Scalar green_Compare_SCALAR_MINIMUM=cv::Scalar(40, 40,40,0);
    cv::Scalar green_Compare_SCALAR_MAXIMUM=cv::Scalar(70, 255,255,1);
    bool xz2=in_range(first_color,green_Compare_SCALAR_MINIMUM,green_Compare_SCALAR_MAXIMUM);
    if(xz2==true){
        return 2;}
    cv::Scalar white_Compare_SCALAR_MINIMUM=cv::Scalar(0, 0, 190,0);
    cv::Scalar white_Compare_SCALAR_MAXIMUM=cv::Scalar(180, 255, 255,1);
    bool xz1=in_range(first_color,white_Compare_SCALAR_MINIMUM,white_Compare_SCALAR_MAXIMUM);
    if(xz1==true){
        return 1;}
    cv::Scalar blue_Compare_SCALAR_MINIMUM=cv::Scalar(106, 127, 9,0);
    cv::Scalar blue_Compare_SCALAR_MAXIMUM=cv::Scalar( 170, 255, 209,1);
    bool xz4=in_range(first_color,blue_Compare_SCALAR_MINIMUM,blue_Compare_SCALAR_MAXIMUM);
    if(xz4==true){
        return 4;}



    else return 0;


    printf("color: %.4fs\n", (double)(clock() - tStart2) / CLOCKS_PER_SEC);
}


//int 1 lcd2
//int 2 lcd7
//int 3 lcd8
//int4  lcd9
//int5 lcd10
int MainWindow::color_detection3(cv::Mat& finalBrick){

    Mat Scalecropped=finalBrick;
    Mat imgFiltered, imgAdjusted, Scalecropped2, mask, Scalecroppedgray;
    cv::cvtColor(Scalecropped, Scalecroppedgray, COLOR_BGR2GRAY);
    adaptiveThreshold(Scalecroppedgray, Scalecropped2, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY_INV, 15, 12);
    //cv::imshow("lll3", Scalecropped2);
    Scalecropped2=(~Scalecropped2);
    bitwise_or(Scalecropped, Scalecropped, mask, Scalecropped2);
    cv::imshow("lll4", mask);
    int count = 5;
    if (count <= 0 || count > 255) {
        printf("The color count needs to be between 1-255. You picked: %d\n", count);
        // return 1;
    }
    clock_t tStart2 = clock();
    cv::Mat img = mask;
    cv::resize(img, img, cv::Size(IMG_WIDTH, (double)img.rows / img.cols * IMG_WIDTH));
    cv::Mat img_hsv;
    cv::cvtColor(img, img_hsv, COLOR_BGR2HSV);

    dominant_colors_graber dcg;
    cv::Vec3i cube_param_rgb = { 1, 1, 1 };
    cv::Vec3i cube_param_hsv = { 1, 2, 2 };
    cv::Vec3i cie76_param = { 25, 0, 0 };
    cv::Vec3i cie94_param = { 15, 0, 0 };


    dcg.SetParam(cie76_param);
    dcg.SetColorsCount(3);

    std::vector <cv::Scalar> detected_colors;


    cv::Scalar current_color;
    cv::Scalar first_color;
    cv::Scalar second_color;
    cv::Scalar third_color;
    detected_colors=dcg.GetDomColors(img, CS_HSV, DT_CUBE);
    cv::Mat innn=ShowColors(img, detected_colors, 100);
    qDebug() << detected_colors.size();
    imshow("nn",innn);
    //cv::waitKey(0);
    for(int i=0; i < detected_colors.size(); i++){
        std::cout << "coloooooooor"<<detected_colors.at(i) << ' ';
        if(i==0)
            first_color=detected_colors.at(i);
        if(i==1)
            second_color=detected_colors.at(i);
        if(i==2)
            third_color=detected_colors.at(i);

    }

    //to do: if object is bigesr in area means include 2 blob then we must compare second color and third color
    //for area diviation and add counter---> better to set countour area to add up lcd
    //if area not filled then what?
    //each lcd count based on its color
    if(min_colors.size()>=1){
        cv::Scalar first_Compare_SCALAR_MINIMUM=cv::Scalar(min_colors[0][0],min_colors[0][1],min_colors[0][2],0);
        cv::Scalar first_Compare_SCALAR_MAXIMUM=cv::Scalar(max_colors[0][0],max_colors[0][1],max_colors[0][2],1);
        bool xz3=in_range(first_color,first_Compare_SCALAR_MINIMUM,first_Compare_SCALAR_MAXIMUM);
        if(xz3==true){
            return 1;}}
    if(min_colors.size()>=2){
        cv::Scalar second_Compare_SCALAR_MINIMUM=cv::Scalar(min_colors[1][0],min_colors[1][1],min_colors[1][2],0);
        cv::Scalar second_Compare_SCALAR_MAXIMUM=cv::Scalar(max_colors[1][0],max_colors[1][1],max_colors[1][2],1);
        bool xz2=in_range(first_color,second_Compare_SCALAR_MINIMUM,second_Compare_SCALAR_MAXIMUM);
        if(xz2==true){
            return 2;}}
    if(min_colors.size()>=3){
        cv::Scalar third_Compare_SCALAR_MINIMUM=cv::Scalar(min_colors[2][0],min_colors[2][1],min_colors[2][2],0);
        cv::Scalar third_Compare_SCALAR_MAXIMUM=cv::Scalar(max_colors[2][0],max_colors[2][1],max_colors[2][2],1);
        bool xz1=in_range(first_color,third_Compare_SCALAR_MINIMUM,third_Compare_SCALAR_MAXIMUM);
        if(xz1==true){
            return 3;}}
    if(min_colors.size()>=4){
        cv::Scalar fourth_Compare_SCALAR_MINIMUM=cv::Scalar(min_colors[3][0],min_colors[3][1],min_colors[3][2],0);
        cv::Scalar fourth_Compare_SCALAR_MAXIMUM=cv::Scalar(max_colors[3][0],max_colors[3][1],max_colors[3][2],1);
        bool xz4=in_range(first_color,fourth_Compare_SCALAR_MINIMUM,fourth_Compare_SCALAR_MAXIMUM);
        if(xz4==true){
            return 4;}
    }
    if(min_colors.size()>=5){
        cv::Scalar fifth_Compare_SCALAR_MINIMUM=cv::Scalar(min_colors[3][0],min_colors[3][1],min_colors[3][2],0);
        cv::Scalar fifth_Compare_SCALAR_MAXIMUM=cv::Scalar(max_colors[3][0],max_colors[3][1],max_colors[3][2],1);
        bool xz5=in_range(first_color,fifth_Compare_SCALAR_MINIMUM,fifth_Compare_SCALAR_MAXIMUM);
        if(xz5==true){
            return 5;}}



    //second dominate color

    if(min_colors.size()>=1){
        cv::Scalar first_Compare_SCALAR_MINIMUM=cv::Scalar(min_colors[0][0],min_colors[0][1],min_colors[0][2],0);
        cv::Scalar first_Compare_SCALAR_MAXIMUM=cv::Scalar(max_colors[0][0],max_colors[0][1],max_colors[0][2],1);
        bool xz3=in_range(second_color,first_Compare_SCALAR_MINIMUM,first_Compare_SCALAR_MAXIMUM);
        if(xz3==true){
            return 1;}}
    if(min_colors.size()>=2){
        cv::Scalar second_Compare_SCALAR_MINIMUM=cv::Scalar(min_colors[1][0],min_colors[1][1],min_colors[1][2],0);
        cv::Scalar second_Compare_SCALAR_MAXIMUM=cv::Scalar(max_colors[1][0],max_colors[1][1],max_colors[1][2],1);
        bool xz2=in_range(second_color,second_Compare_SCALAR_MINIMUM,second_Compare_SCALAR_MAXIMUM);
        if(xz2==true){
            return 2;}}
    if(min_colors.size()>=3){
        cv::Scalar third_Compare_SCALAR_MINIMUM=cv::Scalar(min_colors[2][0],min_colors[2][1],min_colors[2][2],0);
        cv::Scalar third_Compare_SCALAR_MAXIMUM=cv::Scalar(max_colors[2][0],max_colors[2][1],max_colors[2][2],1);
        bool xz1=in_range(second_color,third_Compare_SCALAR_MINIMUM,third_Compare_SCALAR_MAXIMUM);
        if(xz1==true){
            return 3;}}
    if(min_colors.size()>=4){
        cv::Scalar fourth_Compare_SCALAR_MINIMUM=cv::Scalar(min_colors[3][0],min_colors[3][1],min_colors[3][2],0);
        cv::Scalar fourth_Compare_SCALAR_MAXIMUM=cv::Scalar(max_colors[3][0],max_colors[3][1],max_colors[3][2],1);
        bool xz4=in_range(second_color,fourth_Compare_SCALAR_MINIMUM,fourth_Compare_SCALAR_MAXIMUM);
        if(xz4==true){
            return 4;}
    }
    if(min_colors.size()>=5){
        cv::Scalar fifth_Compare_SCALAR_MINIMUM=cv::Scalar(min_colors[3][0],min_colors[3][1],min_colors[3][2],0);
        cv::Scalar fifth_Compare_SCALAR_MAXIMUM=cv::Scalar(max_colors[3][0],max_colors[3][1],max_colors[3][2],1);
        bool xz5=in_range(second_color,fifth_Compare_SCALAR_MINIMUM,fifth_Compare_SCALAR_MAXIMUM);
        if(xz5==true){
            return 5;}}

    //third dominate color

    if(min_colors.size()>=1){
        cv::Scalar first_Compare_SCALAR_MINIMUM=cv::Scalar(min_colors[0][0],min_colors[0][1],min_colors[0][2],0);
        cv::Scalar first_Compare_SCALAR_MAXIMUM=cv::Scalar(max_colors[0][0],max_colors[0][1],max_colors[0][2],1);
        bool xz3=in_range(third_color,first_Compare_SCALAR_MINIMUM,first_Compare_SCALAR_MAXIMUM);
        if(xz3==true){
            return 1;}}
    if(min_colors.size()>=2){
        cv::Scalar second_Compare_SCALAR_MINIMUM=cv::Scalar(min_colors[1][0],min_colors[1][1],min_colors[1][2],0);
        cv::Scalar second_Compare_SCALAR_MAXIMUM=cv::Scalar(max_colors[1][0],max_colors[1][1],max_colors[1][2],1);
        bool xz2=in_range(third_color,second_Compare_SCALAR_MINIMUM,second_Compare_SCALAR_MAXIMUM);
        if(xz2==true){
            return 2;}}
    if(min_colors.size()>=3){
        cv::Scalar third_Compare_SCALAR_MINIMUM=cv::Scalar(min_colors[2][0],min_colors[2][1],min_colors[2][2],0);
        cv::Scalar third_Compare_SCALAR_MAXIMUM=cv::Scalar(max_colors[2][0],max_colors[2][1],max_colors[2][2],1);
        bool xz1=in_range(third_color,third_Compare_SCALAR_MINIMUM,third_Compare_SCALAR_MAXIMUM);
        if(xz1==true){
            return 3;}}
    if(min_colors.size()>=4){
        cv::Scalar fourth_Compare_SCALAR_MINIMUM=cv::Scalar(min_colors[3][0],min_colors[3][1],min_colors[3][2],0);
        cv::Scalar fourth_Compare_SCALAR_MAXIMUM=cv::Scalar(max_colors[3][0],max_colors[3][1],max_colors[3][2],1);
        bool xz4=in_range(third_color,fourth_Compare_SCALAR_MINIMUM,fourth_Compare_SCALAR_MAXIMUM);
        if(xz4==true){
            return 4;}
    }
    if(min_colors.size()>=5){
        cv::Scalar fifth_Compare_SCALAR_MINIMUM=cv::Scalar(min_colors[3][0],min_colors[3][1],min_colors[3][2],0);
        cv::Scalar fifth_Compare_SCALAR_MAXIMUM=cv::Scalar(max_colors[3][0],max_colors[3][1],max_colors[3][2],1);
        bool xz5=in_range(third_color,fifth_Compare_SCALAR_MINIMUM,fifth_Compare_SCALAR_MAXIMUM);
        if(xz5==true){
            return 5;}}
    else return 0;


    printf("color: %.4fs\n", (double)(clock() - tStart2) / CLOCKS_PER_SEC);
}


void MainWindow::closeEvent (QCloseEvent *event)
{
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "سیستم شمارشگر بهسان اندیش",
                                                                tr("خروج از برنامه\n"),
                                                                QMessageBox::Cancel | QMessageBox::Yes,
                                                                QMessageBox::Yes);
    if (resBtn != QMessageBox::Yes) {
        event->ignore();


    } else {
        stop=true;
        stop4=true;
        if(capture2.isOpened()){
            capture2.release();
        }
        if(capture4.isOpened()){
            capture4.release();
        }
        //        capture.release();
        //        capture4.release();
        destroyAllWindows();
        event->accept();
    }
}

//hameye rang ha=0;
//red=1;
//green=2
//yellow=3
//blue=4
//brown
//
void MainWindow::detect_color_based(cv::Mat& inputimage,int which_color,cv::Mat& output){
    Mat image1_blur,image1,image1_hvs;

    image1_hvs=inputimage.clone();


    if (which_color == 1) {

        //set up threshold
        Mat red_lower = (Mat_<double>(1, 3) <<
                         0, 170, 25);
        Mat red_upper = (Mat_<double>(1, 3) <<
                         6, 255, 255);
        Mat red_lower_180 = (Mat_<double>(1, 3) <<
                             174, 170, 25);
        Mat red_upper_180 = (Mat_<double>(1, 3) <<
                             180, 255, 255);

        //detect red color
        Mat red_color_detection1, red_color_detection2, red_color_detection;
        inRange(image1_hvs, red_lower, red_upper, red_color_detection1);
        inRange(image1_hvs, red_lower_180, red_upper_180, red_color_detection2);
        addWeighted(red_color_detection1, 1, red_color_detection2, 1, 0, red_color_detection);

        //filter out the noise;
        erode(red_color_detection, red_color_detection, 0, Point(-1, -1), 2);
        dilate(red_color_detection, red_color_detection, 0, Point(-1, -1), 2);

        //display image
        namedWindow("Red color detection", WINDOW_NORMAL);
        imshow("Red color detection", red_color_detection);
        output=red_color_detection;

        //find contours
        std::vector<std::vector<Point>> contours;
        findContours(red_color_detection, contours, RETR_LIST, CHAIN_APPROX_NONE);

        //draw contours
        Scalar color(0, 0, 255);// red
        drawContours(image1, contours, -1, color, FILLED);

        //display contours on original image
        namedWindow("result", WINDOW_NORMAL);
        imshow("result", image1);
        waitKey(0);
    }
    else if (which_color ==2) {

        //set up threshold
        Mat green_lower = (Mat_<double>(1, 3) <<
                           23, 40, 100);
        Mat green_upper = (Mat_<double>(1, 3) <<
                           65, 255, 255);

        //detect green color
        Mat green_color_detection;
        inRange(image1_hvs, green_lower, green_upper, green_color_detection);

        //filter out the noise;
        erode(green_color_detection, green_color_detection, 0, Point(-1, -1), 2);
        dilate(green_color_detection, green_color_detection, 0, Point(-1, -1), 2);

        //display image
        namedWindow("Green color detection", WINDOW_NORMAL);
        imshow("Green color detection", green_color_detection);
        output=green_color_detection;

        //find contours
        std::vector<std::vector<Point>> contours;
        findContours(green_color_detection, contours, RETR_LIST, CHAIN_APPROX_NONE);

        //drow contours
        Scalar color(0, 255, 0);//green
        drawContours(image1, contours, -1, color, FILLED);

        //display contours on original image
        namedWindow("result", WINDOW_NORMAL);
        imshow("result", image1);
        waitKey(0);
    }
    else if (which_color == 4) {

        //set up threshold
        Mat blue_lower = (Mat_<double>(1, 3) <<
                          106, 127, 9);
        Mat blue_upper = (Mat_<double>(1, 3) <<
                          170, 255, 209);//170, 255, 159

        //detect red color
        Mat blue_color_detection;
        inRange(image1_hvs, blue_lower, blue_upper, blue_color_detection);

        //filter out the noise;
        erode(blue_color_detection, blue_color_detection,cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3)));
        dilate(blue_color_detection, blue_color_detection,cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3)));


        //display image
        namedWindow("Blue color detection", WINDOW_NORMAL);
        imshow("Blue color detection", blue_color_detection);
        output=blue_color_detection;
        //find contours
        std::vector<std::vector<Point>> contours;
        findContours(blue_color_detection, contours, RETR_LIST, CHAIN_APPROX_NONE);

        //draw contours
        Scalar color(255, 0, 0);//blue
        drawContours(image1, contours, -1, color, FILLED);
    }


}


void MainWindow::framedifference_detect(cv::Mat& imgFrameCopy1,cv::Mat& imgFrameCopy2,cv::Mat& output){
    cv::Mat imgDifference;
    cv::Mat imgThresh;
    cv::cvtColor(imgFrameCopy1, imgFrameCopy1, COLOR_BGR2GRAY);
    cv::cvtColor(imgFrameCopy2, imgFrameCopy2, COLOR_BGR2GRAY);
    cv::GaussianBlur(imgFrameCopy1, imgFrameCopy1, cv::Size(5, 5), 0);
    cv::GaussianBlur(imgFrameCopy2, imgFrameCopy2, cv::Size(5, 5), 0);
    cv::absdiff(imgFrameCopy1, imgFrameCopy2, imgDifference);
    cv::threshold(imgDifference, imgThresh, 70, 255.0, THRESH_BINARY);
    cv::imshow("imgThresh", imgThresh);
    cv::Mat structuringElement3x3 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
    cv::Mat structuringElement5x5 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
    cv::Mat structuringElement7x7 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(7, 7));
    cv::Mat structuringElement15x15 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(15, 15));

    //           for (unsigned int i = 0; i < 2; i++) {
    //               cv::dilate(imgThresh, imgThresh, structuringElement5x5);
    //               cv::dilate(imgThresh, imgThresh, structuringElement5x5);
    //               cv::erode(imgThresh, imgThresh, structuringElement5x5);
    //           }

    cv::Mat imgThreshCopy = imgThresh.clone();
    imshow("absdifference",imgThreshCopy);
    //  cv::waitKey(0);
    output=imgThreshCopy;

}

void MainWindow::simple_detect(cv::Mat& inputimage,cv::Mat& output){

    cv::Mat img_mask;
    cv::Mat imgFrame2Copy=inputimage;
    cv::cvtColor(imgFrame2Copy, imgFrame2Copy, COLOR_BGR2GRAY);
    cv::GaussianBlur(imgFrame2Copy, imgFrame2Copy, cv::Size(5, 5), 0);


    cv::Mat structuringElement3x3 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
    cv::Mat structuringElement5x5 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
    cv::Mat structuringElement7x7 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(7, 7));
    cv::Mat structuringElement15x15 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(15, 15));



    // line detection
    Mat dst, cdst, canny;
    Canny(imgFrame2Copy, canny, 0, 250, 3);
    //            cv::dilate(canny, canny, structuringElement5x5);
    //            cv::erode(canny, canny, structuringElement3x3);

    img_mask = imgFrame2Copy;


    int thresh=ui->spinBox->value();
    cv::threshold(img_mask, img_mask, thresh, 255.0, THRESH_BINARY);


    //ezafe shod
    // cv::morphologyEx(img_mask,img_mask, MORPH_CLOSE, structuringElement3x3);


    output=img_mask;

    imshow("simpledetect",img_mask);
    //cv::waitKey(0);
}



//void MainWindow::set_mincolor_lable(int min0,int min1,int min2)
//{
//    ui->label_mincolor->setAutoFillBackground(true);// This is important!!
//   QString  values = QString::number(min0)+","+QString::number(min1)+","+QString::number(min2)   ;                                      min1,

//     ui->label_mincolor->setStyleSheet("QLabel { background-color: rgb("+values+"); }");

//}





void MainWindow::detect_our_color_based(cv::Mat& inputimage,std::vector<cv::Scalar > min_colors,std::vector<cv::Scalar > max_colors,cv::Mat& output){

    int count_of_color=min_colors.size();
    if(count_of_color==1){

        qDebug()<< min_colors[0][0];
        Mat image1_blur,image1,image1_hvs,output1;

        image1_hvs=inputimage.clone();

        //set up threshold
        Mat red_lower = (Mat_<double>(1, 3) <<
                         min_colors[0][0], min_colors[0][1], min_colors[0][2]);
        Mat red_upper = (Mat_<double>(1, 3) <<
                         max_colors[0][0], max_colors[0][1], max_colors[0][2]);


        //detect red color
        Mat red_color_detection1, red_color_detection2, red_color_detection;
        inRange(image1_hvs, red_lower, red_upper, red_color_detection);
        // addWeighted(red_color_detection1, 1, red_color_detection2, 1, 0, red_color_detection);

        //filter out the noise;
        erode(red_color_detection, red_color_detection, 0, Point(-1, -1), 2);
        dilate(red_color_detection, red_color_detection, 0, Point(-1, -1), 2);

        //display image
        namedWindow("Red color detection", WINDOW_NORMAL);
        imshow("Red color detection", red_color_detection);
        //cv::waitKey(0);
        output=red_color_detection;



    }
    else if(count_of_color==2){

        std::cout << "hi"<<std::endl;
        Mat image1_blur,image1,image1_hvs,output0,output1;

        image1_hvs=inputimage.clone();
        for(int i=0;i<2;i++){

            //set up threshold
            Mat red_lower = (Mat_<double>(1, 3) <<
                             min_colors[i][0], min_colors[i][1], min_colors[i][2]);
            Mat red_upper = (Mat_<double>(1, 3) <<
                             max_colors[i][0], max_colors[i][1], max_colors[i][2]);


            //detect red color
            Mat red_color_detection1, red_color_detection2, red_color_detection;
            inRange(image1_hvs, red_lower, red_upper, red_color_detection);
            std::cout << "hi1"<<std::endl;
            // addWeighted(red_color_detection1, 1, red_color_detection2, 1, 0, red_color_detection);

            //filter out the noise;
            erode(red_color_detection, red_color_detection, 0, Point(-1, -1), 2);
            dilate(red_color_detection, red_color_detection, 0, Point(-1, -1), 2);
            std::cout << "hi2"<<std::endl;
            //display image
            imshow("Red color detection", red_color_detection);
            std::cout << "hi3"<<std::endl;
            if(i==0)
                output0=red_color_detection;
            if(i==1)
                output1=red_color_detection;

        }


        imshow("Red color detection0", output0);

        imshow("Red color detection1", output1);

        bitwise_or(output0,output1,output);

    }
    else if(count_of_color==3){
        Mat image1_blur,image1,image1_hvs,output0,output1,output2;

        image1_hvs=inputimage.clone();
        for(int i=0;i<=2;i++){

            //set up threshold
            Mat red_lower = (Mat_<double>(1, 3) <<
                             min_colors[i][0], min_colors[i][1], min_colors[i][2]);
            Mat red_upper = (Mat_<double>(1, 3) <<
                             max_colors[i][0], max_colors[i][1], max_colors[i][2]);


            //detect red color
            Mat red_color_detection1, red_color_detection2, red_color_detection;
            inRange(image1_hvs, red_lower, red_upper, red_color_detection);
            // addWeighted(red_color_detection1, 1, red_color_detection2, 1, 0, red_color_detection);

            //filter out the noise;
            erode(red_color_detection, red_color_detection, 0, Point(-1, -1), 2);
            dilate(red_color_detection, red_color_detection, 0, Point(-1, -1), 2);

            //display image
            namedWindow("Red color detection", WINDOW_NORMAL);
            imshow("Red color detection", red_color_detection);
            if(i==0)
                output0=red_color_detection;
            if(i==1)
                output1=red_color_detection;
            if(i==2)
                output2=red_color_detection;

        }

        bitwise_or(output0,output1,output);
        bitwise_or(output,output2,output);


    }
    else if(count_of_color==4){
        Mat image1_blur,image1,image1_hvs,output0,output1,output2,output3;

        image1_hvs=inputimage.clone();
        for(int i=0;i<=3;i++){

            //set up threshold
            Mat red_lower = (Mat_<double>(1, 3) <<
                             min_colors[i][0], min_colors[i][1], min_colors[i][2]);
            Mat red_upper = (Mat_<double>(1, 3) <<
                             max_colors[i][0], max_colors[i][1], max_colors[i][2]);


            //detect red color
            Mat red_color_detection1, red_color_detection2, red_color_detection;
            inRange(image1_hvs, red_lower, red_upper, red_color_detection);
            //addWeighted(red_color_detection1, 1, red_color_detection2, 1, 0, red_color_detection);

            //filter out the noise;
            erode(red_color_detection, red_color_detection, 0, Point(-1, -1), 2);
            dilate(red_color_detection, red_color_detection, 0, Point(-1, -1), 2);

            //display image
            namedWindow("Red color detection", WINDOW_NORMAL);
            imshow("Red color detection", red_color_detection);
            if(i==0)
                output0=red_color_detection;
            if(i==1)
                output1=red_color_detection;
            if(i==2)
                output2=red_color_detection;
            if(i==3)
                output3=red_color_detection;

        }

        bitwise_or(output0,output1,output);
        bitwise_or(output,output2,output);
        bitwise_or(output,output3,output);


    }
    else if(count_of_color==5){
        Mat image1_blur,image1,image1_hvs,output0,output1,output2,output3,output4;

        image1_hvs=inputimage.clone();
        for(int i=0;i<=3;i++){

            //set up threshold
            Mat red_lower = (Mat_<double>(1, 3) <<
                             min_colors[i][0], min_colors[i][1], min_colors[i][2]);
            Mat red_upper = (Mat_<double>(1, 3) <<
                             max_colors[i][0], max_colors[i][1], max_colors[i][2]);


            //detect red color
            Mat red_color_detection1, red_color_detection2, red_color_detection;
            inRange(image1_hvs, red_lower, red_upper, red_color_detection);
            // addWeighted(red_color_detection1, 1, red_color_detection2, 1, 0, red_color_detection);

            //filter out the noise;
            erode(red_color_detection, red_color_detection, 0, Point(-1, -1), 2);
            dilate(red_color_detection, red_color_detection, 0, Point(-1, -1), 2);

            //display image
            namedWindow("Red color detection", WINDOW_NORMAL);
            imshow("Red color detection", red_color_detection);
            if(i==0)
                output0=red_color_detection;
            if(i==1)
                output1=red_color_detection;
            if(i==2)
                output2=red_color_detection;
            if(i==3)
                output3=red_color_detection;
            if(i==4)
                output4=red_color_detection;

        }
        bitwise_or(output0,output1,output);
        bitwise_or(output,output2,output);
        bitwise_or(output,output3,output);
        bitwise_or(output,output4,output);

    }
    //    Mat bgr_red = Mat(1, 1, CV_8UC3, our_SCALAR_MINIMUM);
    //    Mat hsv_red=bgr_red;
    //    Vec3b MIN_pixel_HSV= hsv_red.at<Vec3b>(0, 0);

    //     bgr_red = Mat(1, 1, CV_8UC3, our_SCALAR_MAXIMUM);
    //     Mat hsv_red2=bgr_red;
    //    Vec3b MAX_pixel_HSV= hsv_red2.at<Vec3b>(0, 0);

    //    Mat image1_blur,image1,image1_hvs;

    //    image1_hvs=inputimage.clone();
    //                    //set up threshold
    //                    Mat green_lower = (Mat_<double>(1, 3) <<
    //                        MIN_pixel_HSV[0], MIN_pixel_HSV[1], MIN_pixel_HSV[2]);
    //                    Mat green_upper = (Mat_<double>(1, 3) <<
    //                        MAX_pixel_HSV[0], MAX_pixel_HSV[1], MAX_pixel_HSV[2]);



    //                    qDebug() << "min"<<MIN_pixel_HSV[0]<<MIN_pixel_HSV[1]<<MIN_pixel_HSV[2];
    //                    qDebug() <<"max" <<MAX_pixel_HSV[0]<<MAX_pixel_HSV[1]<<MAX_pixel_HSV[2];

    //                    //detect green color
    //                    Mat green_color_detection;
    //                    inRange(image1_hvs, green_lower, green_upper, green_color_detection);

    //                    //filter out the noise;
    //                    erode(green_color_detection, green_color_detection, 0, Point(-1, -1), 2);
    //                    dilate(green_color_detection, green_color_detection, 0, Point(-1, -1), 2);

    //                    //display image
    //                    namedWindow("Green color detection", WINDOW_NORMAL);
    //                    imshow("Green color detection", green_color_detection);
    //   output=green_color_detection;

    ////                    //find contours
    ////                    std::vector<std::vector<Point>> contours;
    ////                    findContours(green_color_detection, contours, RETR_LIST, CHAIN_APPROX_NONE);

    ////                    //drow contours
    ////                    Scalar color(0, 255, 0);//green
    ////                    drawContours(image1, contours, -1, color, FILLED);

    ////                    //display contours on original image
    ////                    namedWindow("result", WINDOW_NORMAL);
    ////                    imshow("result", image1);
    ////                    waitKey(0);


}

void MainWindow::on_pushButton_mincolor_clicked()
{

}
cv::Scalar qcolor2scalarrgb(QColor color)
{
    int r,g,b;
    color.getRgb(&r, &g, &b);
    return cv::Scalar(r,g,b); // swap RGB-->BGR
}
cv::Scalar qcolor2scalarhsv(QColor color)
{

    int h,s,v;
    color.getHsv(&h, &s, &v);
    return cv::Scalar(h,s,v); // swap RGB-->BGR
}
QColor scalar2qcolor(cv::Scalar color)
{
    return QColor(color[2],color[1],color[0]); // swap RGB-->BGR
}

cv::Scalar vec3toscalar(const Vec3b & v){

    return Scalar(v.val[0],v.val[1],v.val[2]);
}

QColor  color_selected_lcd_text;
vector<QString> stylsOfLeds;
void MainWindow::on_pushButton_savecolor_clicked()

{
    if( ui->lineEdit_min0->text()!="" &&ui->lineEdit_min1->text()!="" && ui->lineEdit_min2->text()!="" && ui->lineEdit_max0->text()!="" && ui->lineEdit_max1->text()!="" && ui->lineEdit_max2->text()!=""){

    }else{

        QMessageBox::information(this, "رنگ", "بازه ی رنگی انتخاب نشده است");
        return;
    }
    if(min_colors.size()<5 ){

        min_colors.push_back(cv::Scalar (ui->lineEdit_min0->text().toInt(),ui->lineEdit_min1->text().toInt(),ui->lineEdit_min2->text().toInt()));
        max_colors.push_back(cv::Scalar (ui->lineEdit_max0->text().toInt(),ui->lineEdit_max1->text().toInt(),ui->lineEdit_max2->text().toInt()));
        cv::Mat hsv(100, 100, CV_32FC3, cv::Scalar (ui->lineEdit_min0->text().toInt(),ui->lineEdit_min1->text().toInt(),ui->lineEdit_min2->text().toInt())); // same in cv::Mat hsv(10, 10, CV_32F);
        cv::Mat rgb(hsv.size(), hsv.type());
        cv::cvtColor(hsv, rgb, cv::COLOR_HSV2BGR);

        if(min_colors.size()==1){

            QColor mycolor = color_selected_lcd_text;
            QString style = "color: rgb(%1, %2, %3);";
            style = style.arg(mycolor.red()).arg(mycolor.green()).arg(mycolor.blue());
            ui->lcdNumber_2->setStyleSheet(style);
            stylsOfLeds.push_back(style);

        }
        if(min_colors.size()==2){

            QColor mycolor = color_selected_lcd_text;
            QString style = "color: rgb(%1, %2, %3);";
            style = style.arg(mycolor.red()).arg(mycolor.green()).arg(mycolor.blue());
            ui->lcdNumber_7->setStyleSheet(style);
            stylsOfLeds.push_back(style);

        }
        if(min_colors.size()==3){

            QColor mycolor = color_selected_lcd_text;
            QString style = "color: rgb(%1, %2, %3);";
            style = style.arg(mycolor.red()).arg(mycolor.green()).arg(mycolor.blue());
            ui->lcdNumber_8->setStyleSheet(style);
            stylsOfLeds.push_back(style);

        }
        if(min_colors.size()==4){

            QColor mycolor = color_selected_lcd_text;
            QString style = "color: rgb(%1, %2, %3);";
            style = style.arg(mycolor.red()).arg(mycolor.green()).arg(mycolor.blue());
            ui->lcdNumber_9->setStyleSheet(style);
            stylsOfLeds.push_back(style);

        }
        if(min_colors.size()==5){

            QColor mycolor = color_selected_lcd_text;
            QString style = "color: rgb(%1, %2, %3);";
            style = style.arg(mycolor.red()).arg(mycolor.green()).arg(mycolor.blue());
            ui->lcdNumber_10->setStyleSheet(style);
            stylsOfLeds.push_back(style);

        }

        QMessageBox::information(this, "رنگ", "ذخیره شد.");
        onminColorSelected(QColor(0,0,0));
        ui->lineEdit_min0->setText("");
        ui->lineEdit_min1->setText("");
        ui->lineEdit_min2->setText("");
        ui->lineEdit_max0->setText("");
        ui->lineEdit_max1->setText("");
        ui->lineEdit_max2->setText("");
        cv::Mat ik;
        QImage finalq=MatToQImage(ik);
        ui->label_13->setPixmap(QPixmap::fromImage(finalq));


    }else{
        QMessageBox::information(this, "رنگ", "تمام رنگ ها انتخاب شده است");


    }
}



void MainWindow::onminColorSelected(QColor color)
{
    qDebug() <<color;;
    color_selected_lcd_text=color;

    QColor mycolor = color_selected_lcd_text;
    qDebug()<<"bbbbbb"<<mycolor;
    QString style = "background-color: rgb(%1, %2, %3);";
    style = style.arg(mycolor.red()).arg(mycolor.green()).arg(mycolor.blue());
    ui->label_selected_text_color->setStyleSheet(style);


    // ui->textEdit->setTextColor(color);
}



void MainWindow::on_pushButton_sample_clicked()
{
    QString image_path= QFileDialog::getOpenFileName(this,tr("Open Image"), "/home/jana", tr("Image Files (*.png *.jpg *.bmp)"));
    //// 1. Create mask settings UI with default HSV range to detect blue color
    if(image_path==""){return;}
    auto const MASK_WINDOW = "Mask Settings";
    cv::namedWindow(MASK_WINDOW, WINDOW_AUTOSIZE);

    // HSV range to detect blue color
    int minHue = 90, maxHue = 140;
    int minSat = 74, maxSat = 255;
    int minVal =  0, maxVal = 255;

    // Create trackbars of mask settings window

    cv::createTrackbar("Min Hue", MASK_WINDOW, &minHue, 179);
    cv::createTrackbar("Max Hue", MASK_WINDOW, &maxHue, 179);
    cv::createTrackbar("Min Sat", MASK_WINDOW, &minSat, 255);
    cv::createTrackbar("Max Sat", MASK_WINDOW, &maxSat, 255);
    cv::createTrackbar("Min Val", MASK_WINDOW, &minVal, 255);
    cv::createTrackbar("Max Val", MASK_WINDOW, &maxVal, 255);
    cv::Mat final;
    while (true) {
        //// 2. Read and convert image to HSV color space
        cv::Mat inputImage { cv::imread(image_path.toStdString(), cv::IMREAD_COLOR) };
        cv::Mat inputImageHSV;
        cv::cvtColor(inputImage, inputImageHSV, cv::COLOR_BGR2HSV);

        //// 3. Create mask and result (masked) image
        cv::Mat mask;
        // params: input array, lower boundary array, upper boundary array, output array
        cv::inRange(
                    inputImageHSV,
                    cv::Scalar(minHue, minSat, minVal),
                    cv::Scalar(maxHue, maxSat, maxVal),
                    mask
                    );
        ui->lineEdit_min0->setText(QString::number(minHue));
        ui->lineEdit_min1->setText(QString::number(minSat));
        ui->lineEdit_min2->setText(QString::number(minVal));
        ui->lineEdit_max0->setText(QString::number(maxHue));
        ui->lineEdit_max1->setText(QString::number(maxSat));
        ui->lineEdit_max2->setText(QString::number(maxVal));
        cv::Mat resultImage;
        // params: src1	array, src2 array, output array, mask
        cv::bitwise_and(inputImage, inputImage, resultImage, mask);

        //// 4. Show images
        //cv::imshow("Mask Settings1", inputImage);
        //cv::imshow("Mask Settings2", resultImage);
        // imshow("Mask", mask);

        Mat im1 = inputImage;
        Mat im2 = resultImage;
        cv::resize(im1, im1,Size(640,480));
        cv::resize(im2, im2,Size(640,480));
        Size sz1 = im1.size();
        Size sz2 = im2.size();

        Mat im3(sz1.height, sz1.width+sz2.width, CV_8UC3);
        // Move right boundary to the left.
        im3.adjustROI(0, 0, 0, -sz2.width);
        im1.copyTo(im3);
        // Move the left boundary to the right, right boundary to the right.
        im3.adjustROI(0, 0, -sz1.width, sz2.width);
        im2.copyTo(im3);
        // restore original ROI.
        im3.adjustROI(0, 0, sz1.width, 0);
        //imshow("im3", im3);
        cv::imshow("Mask Settings", im3);
        final=im2;
        //// Wait for 'esc' (27) key press for 30ms. If pressed, end program.
        if (cv::waitKey(30) == 27 || cv::getWindowProperty("Mask Settings",cv::WND_PROP_VISIBLE)<1) {

            break;

        }

    }
    QImage finalq=MatToQImage(final);
    ui->label_13->setPixmap(QPixmap::fromImage(finalq));
    cv::destroyWindow("Mask Settings");

}

void MainWindow::on_radioButton_5_clicked()
{
    if(ui->radioButton_5->isChecked()){

        ui->stackedWidget_2->setCurrentIndex(0);
    }else{


    }
}

void MainWindow::on_radioButton_6_clicked()
{
    if(ui->radioButton_6->isChecked()){

        ui->stackedWidget_2->setCurrentIndex(0);
    }else{


    }
}

void MainWindow::on_radioButton_4_clicked()
{
    if(ui->radioButton_4->isChecked()){


        ui->stackedWidget_2->setCurrentIndex(1);
        ui->spinBox->setVisible(true);
        ui->label_9->setVisible(true);
    }else{
        ui->spinBox->setVisible(false);
        ui->label_9->setVisible(false);

    }
}

void MainWindow::on_pushButton_2_clicked()
{
    min_colors.clear();
    max_colors.clear();

    QString style = "color: rgb(0, 0, 0);";

    ui->lcdNumber_2->setStyleSheet(style);

    ui->lcdNumber_7->setStyleSheet(style);

    ui->lcdNumber_8->setStyleSheet(style);

    ui->lcdNumber_9->setStyleSheet(style);

    ui->lcdNumber_10->setStyleSheet(style);
}

//delete color
void MainWindow::on_pushButton_deletecolor_clicked()
{

    if(ui->comboBox_2->currentIndex()!=0){
        if(min_colors.size()!=0 && min_colors.size() > (ui->comboBox_2->currentIndex()-1)){
            min_colors.erase (min_colors.begin()+ ui->comboBox_2->currentIndex()-1);
            max_colors.erase (max_colors.begin()+ ui->comboBox_2->currentIndex()-1);
            stylsOfLeds.erase (stylsOfLeds.begin()+ ui->comboBox_2->currentIndex()-1);


            if(stylsOfLeds.size()==0){
                ui->lcdNumber_2->setStyleSheet("color: rgb(0, 0, 0);");
                ui->lcdNumber_7->setStyleSheet("color: rgb(0, 0, 0);");
                ui->lcdNumber_8->setStyleSheet("color: rgb(0, 0, 0);");
                ui->lcdNumber_9->setStyleSheet("color: rgb(0, 0, 0);");
                ui->lcdNumber_10->setStyleSheet("color: rgb(0, 0, 0);");
            }
            if(stylsOfLeds.size()==1){
                ui->lcdNumber_2->setStyleSheet(stylsOfLeds[0]);
                ui->lcdNumber_7->setStyleSheet("color: rgb(0, 0, 0);");
                ui->lcdNumber_8->setStyleSheet("color: rgb(0, 0, 0);");
                ui->lcdNumber_9->setStyleSheet("color: rgb(0, 0, 0);");
                ui->lcdNumber_10->setStyleSheet("color: rgb(0, 0, 0);");
            }
            if(stylsOfLeds.size()==2){
                ui->lcdNumber_2->setStyleSheet(stylsOfLeds[0]);
                ui->lcdNumber_7->setStyleSheet(stylsOfLeds[1]);
                ui->lcdNumber_8->setStyleSheet("color: rgb(0, 0, 0);");
                ui->lcdNumber_9->setStyleSheet("color: rgb(0, 0, 0);");
                ui->lcdNumber_10->setStyleSheet("color: rgb(0, 0, 0);");
            }
            if(stylsOfLeds.size()==3){
                ui->lcdNumber_2->setStyleSheet(stylsOfLeds[0]);
                ui->lcdNumber_7->setStyleSheet(stylsOfLeds[1]);
                ui->lcdNumber_8->setStyleSheet(stylsOfLeds[2]);

                ui->lcdNumber_9->setStyleSheet("color: rgb(0, 0, 0);");
                ui->lcdNumber_10->setStyleSheet("color: rgb(0, 0, 0);");
            }
            if(stylsOfLeds.size()==4){
                ui->lcdNumber_2->setStyleSheet(stylsOfLeds[0]);
                ui->lcdNumber_7->setStyleSheet(stylsOfLeds[1]);
                ui->lcdNumber_8->setStyleSheet(stylsOfLeds[2]);
                ui->lcdNumber_9->setStyleSheet(stylsOfLeds[3]);
                ui->lcdNumber_10->setStyleSheet("color: rgb(0, 0, 0);");

            }

        }

    }

}



void MainWindow::showMousePeressed(QPoint& pos){

    //    if( DrawRect==true  ){

    //        QImage img=MatToQImage(image_frame);
    //        QPixmap n=QPixmap::fromImage(img);
    //        ui->label->setPixmap(n);
    //        m_nPTargetPixmap=n;//new
    //        r =n;//new
    //        tmp2= r;//new
    m_nbMousePressed = true;
    m_nInitialX = pos.x();
    m_nInitialY = pos.y();
    qDebug() <<"preesed x"<<QString::number(m_nInitialX);
    qDebug() <<QString::number(m_nInitialY);


    int h = ui->label_camera_check_2->height();
    int w = ui->label_camera_check_2->width();
    QPixmap pix(w, h);
    QPainter paint(&pix);
    pix.fill( Qt::black);
    paint.setPen(QColor(255, 0, 0, 255));
    if(from_up || from_bottom){
        paint.drawLine(0,m_nInitialY,w,m_nInitialY);

    }
    if(from_left || from_right){
        paint.drawLine(m_nInitialX,0,m_nInitialX,h);

    }

    ui->label_camera_check_2->setPixmap(pix);

    if( DrawRect==true  ){
        QImage img=MatToQImage(origFrame_copy);
        QPixmap n=QPixmap::fromImage(img);
        ui->label->setPixmap(n);
        m_nPTargetPixmap=n;//new
        r =n;//new
        tmp2= r;//new
        m_nbMousePressed = true;
        m_nInitialX = pos.x();
        m_nInitialY = pos.y();
        qDebug() <<"preesed x"<<QString::number(m_nInitialX);
        qDebug() <<QString::number(m_nInitialY);
    }

    //    }
}


void MainWindow::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_checkBox_clicked()
{
    if(ui->checkBox->isChecked()){
        ui->label_DetectedBrick->setHidden(false);}else{

        ui->label_DetectedBrick->setHidden(true);
    }

}

void MainWindow::on_checkBox_2_clicked()
{
    if(ui->checkBox_2->isChecked()){
        ui->label_camera->setHidden(false);}else{

        ui->label_camera->setHidden(true);
    }
}

void MainWindow::on_radioButton_9_clicked()
{
    if(ui->radioButton_9->isChecked()){

        ui->stackedWidget_2->setCurrentIndex(0);
    }else{


    }
}

void MainWindow::on_radioButton_8_clicked(bool checked)
{
    if(ui->radioButton_8->isChecked()){

        ui->stackedWidget_2->setCurrentIndex(1);
    }else{


    }
}

void MainWindow::on_radioButton_10_clicked()
{
    if(ui->radioButton_10->isChecked()){

        ui->groupBox_8->setHidden(false);
    }else{
        ui->groupBox_8->setHidden(true);


    }

}


void MainWindow::paintEvent(QPaintEvent *e)
{
    if(!released && DrawRect && m_nbMousePressed)
    {
        QImage img=MatToQImage(origFrame_copy);
        QPixmap n=QPixmap::fromImage(img);
        r =n;
        tmp2= r;
        QPainter PixmapPainter(&tmp2);
        if(DrawRect){
            QPen pen2(Qt::green);
            PixmapPainter.setPen(pen2);
            PixmapPainter.drawRect(QRect(m_nInitialX, m_nInitialY,m_nFinalX-m_nInitialX ,m_nFinalY-m_nInitialY));
            finalx=m_nInitialX;
            finaly=m_nInitialY;
            finalwidth=m_nFinalX-m_nInitialX;
            finalheight= m_nFinalY-m_nInitialY;
        }}
    if(released && DrawRect )
    {
        QImage img=MatToQImage(origFrame_copy);
        QPixmap n=QPixmap::fromImage(img);
        r =n;
        tmp2= r;
        QPainter PixmapPainter(&tmp2);
        if(DrawRect){
            QPen pen2(Qt::green);
            PixmapPainter.setPen(pen2);
            PixmapPainter.drawRect(QRect(m_nInitialX, m_nInitialY,m_nFinalX-m_nInitialX ,m_nFinalY-m_nInitialY));
            finalx=m_nInitialX;
            finaly=m_nInitialY;
            finalwidth=m_nFinalX-m_nInitialX;
            finalheight= m_nFinalY-m_nInitialY;
        }}
    //draw rect zade shode va dge hichi nashode
    if( DrawRect && !released && !m_nbMousePressed )
    {
        QImage img=MatToQImage(origFrame_copy);
        QPixmap n=QPixmap::fromImage(img);
        // m_nPTargetPixmap=n;//new
        r =n;//new
        // tmp2= r;
        tmp2= r;
        ui->label_camera->setPixmap(tmp2);
    }
    if(DrawRect){
        ui->label_camera->setPixmap(tmp2);
    }
    if(!m_nbMousePressed && !DrawRect )
    {
        r = tmp2;
    }
}
void MainWindow::showMousePosition(QPoint &pos)
{
    if( DrawRect ){
        m_nFinalX = pos.x();
        m_nFinalY= pos.y();
        if(m_nbMousePressed)
            m_nFinalX = pos.x();
        m_nFinalY=pos.y();}
}
void MainWindow::showMouseReleased(QPoint &pos)
{
    if(m_nbMousePressed==true){
        released=true;}
    if(DrawRect){
        m_nbMousePressed = false;
        m_nFinalX = pos.x();
        m_nFinalY = pos.y();
        qDebug()<<"x was released: " <<QString::number(pos.x()) <<"y was Released: " <<QString::number(pos.y());
        // update();}
    }
}

//void MainWindow::on_checkBox_3_clicked()
//{
//if(ui->checkBox_3->isChecked()){


////    if(stop==false){
////    stop=true;
////    DrawRect=true;}
////    else{
////        stop=false;
////        DrawRect=false;
////        timer = new QTimer(this);
////        // connect the timer to the widget and to the method that will execute
////        connect(timer, SIGNAL(timeout()), this, SLOT(displayFrameWithModel()));
////        timer -> start(40);
////        displayFrameWithModel();
////    }
//}
//}

QPixmap MainWindow::imagewithlogo(cv::Mat &mat){
    QImage qq=MatToQImage(mat);
    QPixmap BackGround=QPixmap::fromImage(qq);
    QPixmap result(BackGround.width(), BackGround.height());
    QPainter painter(&result);
    painter.drawPixmap(0, 0, BackGround);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(Qt::white, 4, Qt::DashDotLine, Qt::RoundCap));
    //painter.setBrush(QBrush(Qt::green, Qt::SolidPattern));
    painter.fillRect(QRect(finalx,finaly,  finalwidth,finalheight),QBrush(QColor(128, 128, 255, 128)));
           // painter.fillRect(r, QBrush(Qt::yellow, Qt::SolidPattern));
    painter.drawRect(finalx,finaly,  finalwidth,finalheight);
return result;
}

void MainWindow::on_checkBox_4_clicked()
{
if(ui->checkBox_4->isChecked()){
    ui->label_resultsave->setVisible(true);

}else{
    ui->label_resultsave->setVisible(false);
}
}

void MainWindow::on_radioButton_8_clicked()
{
    if(ui->radioButton_8->isChecked()){
        ui->spinBox->setVisible(false);
        ui->label_9->setVisible(false);
    }
}
