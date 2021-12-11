#ifndef MYCONNECTIONWRAPPER
#define MYCONNECTIONWRAPPER

#include "QThread"
#include "QSqlQuery"
#include "QSqlDatabase"
#include "QDebug"

#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include "QByteArray"
#include "QBuffer"
#include "QRgb"
#include "QImage"
#include "QSqlError"

class MyConnectionWrapper : public QObject
{
public:
MyConnectionWrapper(QObject *parent = 0) : QObject(parent) {}

Q_OBJECT
public slots:
void createConnection()
{
    qDebug()<<"11g";


}


void createConnection2(QSqlDatabase dbsql)
{
m_Db=dbsql;
//qDebug()<<"gggggggggggggggggggggggggggggggg";

if(m_Db.isOpen()){

    //qDebug()<<"gggggggggggggggggggggggggggggggg";
    //QSqlQuery query;
    QSqlQuery query(m_Db);
    query.exec("create table MyBricks3 (Image varbinary(max),Date DATE, Time Time(7), daste int, shomarande int, codecolor nvarchar(40))");
   // query.exec("create table Camera1 (CameraName nvarchar(200),CameraType int,URL nvarchar(MAX),Place nvarchar(300))");
    //qDebug( "Database successfully opened, now able to query" );
}
}
void executeQuery(const QString &queryString,cv::Mat ax, int daste, int shomarande, QString day,QString hour,QString codecolor)
{
//QSqlQuery query(m_Db);
//query.exec(queryString);

//qDebug()<<"cccccccccccccc"<<shomarande;



cv::Size size3(ax.cols / 2, ax.rows / 2);

cv::resize(ax, ax, size3);
    QImage image=MatToQImage(ax);

    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "jpg");

    try
    {

        //cv::imshow("saved",ax);
        QSqlQuery querysql(m_Db);
        querysql.prepare("INSERT INTO MyBricks3 (Image,Date,Time,daste,shomarande,codecolor) "
                       "VALUES (:Image,:Date,:Time,:das,:shom,:cc)");

        querysql.bindValue(":Image", byteArray);
        //qDebug("1save -----------------------------");
        querysql.bindValue(":Date", day);
        //qDebug("1save -----------------------------");
        querysql.bindValue(":Time", hour);
       // qDebug("1save -----------------------------");
        querysql.bindValue(":das",daste);
       // qDebug("1save -----------------------------");
        querysql.bindValue(":shom", shomarande);
       // qDebug("1save -----------------------------");
        querysql.bindValue(":cc",codecolor);
        querysql.exec();

        //qDebug("1save -----------------------------");
    }
    catch(std::exception ex)
    {

       qWarning() << "hhhhhhhhhhhhhhhhh: " << m_Db.lastError();


    }




}

private:
QSqlDatabase m_Db; //this is just for convenience, you can always call QSqlDatabase::database("myConnection") instead of using the member variable


QImage MatToQImage( cv::Mat &mat)
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



};


#endif // MYCONNECTIONWRAPPER

