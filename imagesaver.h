

//#include "qthread.h"
//#include "qimage.h"
//#include "common.h"
///**
//* Image saver class. Saves an image in the background.
//*/
//class ImageSaver : public QObject
//{
//    //based on: http://stackoverflow.com/questions/13878745/correct-way-of-threading-in-qt
//    Q_OBJECT
//public:
//    /**
//    * Constructor, moves itself to a background thread.
//    */
//    ImageSaver() : QObject() {
//        moveToThread(&t);
//        t.start();
//    }
//    ~ImageSaver() {
//        qDebug("Bye bye!");
//        t.quit();
//        t.wait();
//    }

//    /**
//    * Request a new image to be saved.
//    * @param image the image to save.
//    * @param absPath the absolute path of where to save the image.
//    */
//    void requestImageSave(detected_bricks mybrick, QString absPath) {
//        //thread save way to invoke the save image slot.
//        QMetaObject::invokeMethod(this, "saveImage", Q_ARG(detected_bricks, mybrick), Q_ARG(QString, absPath));
//    }


//    public slots:
//    /**
//    * Needs to be a slot to be invokable with QMetaObject.
//    * Performs the saving of the image.
//    * @param image the image to save.
//    * @param absPath the absolute path of where to save the image.
//    */
//    void saveImage(detected_bricks mybrick, QString absPath) {
//        //bool saved = image.save(absPath);

//        if(dbsql.isOpen()){


//            QImage image;



//            if(mybrick.ax.type()==CV_8UC1)
//            {
//                // Set the color table (used to translate colour indexes to qRgb values)
//                QVector<QRgb> colorTable;
//                for (int i=0; i<256; i++)
//                    colorTable.push_back(qRgb(i,i,i));
//                // Copy input Mat
//                const uchar *qImageBuffer = (const uchar*)mybrick.ax.data;
//                // Create QImage with same dimensions as input Mat
//                QImage img(qImageBuffer, mybrick.ax.cols, mybrick.ax.rows, mybrick.ax.step, QImage::Format_Indexed8);
//                img.setColorTable(colorTable);
//                 image= img;
//            }
//            // 8-bits unsigned, NO. OF CHANNELS=3
//            else if(mybrick.ax.type()==CV_8UC3)
//            {
//                // Copy input Mat
//                const uchar *qImageBuffer = (const uchar*)mybrick.ax.data;
//                // Create QImage with same dimensions as input Mat
//                QImage img(qImageBuffer, mybrick.ax.cols, mybrick.ax.rows, mybrick.ax.step, QImage::Format_RGB888);
//                image= img.rgbSwapped();
//            }
//            else
//            {
//                //qDebug() << "ERROR: Mat could not be converted to QImage.";
//                image=QImage();
//            }

//            QByteArray byteArray;
//            QBuffer buffer(&byteArray);
//            buffer.open(QIODevice::WriteOnly);
//            image.save(&buffer, "jpg");
//            //printf("insert vvvv: %.4fs\n", (double)(clock() - tStartsql) / CLOCKS_PER_SEC);

//            try
//            {

//               // imshow("saved",mybrick.ax);
//                QSqlQuery querysql(dbsql);
//                querysql.prepare("INSERT INTO MyBricks2 (Image,Date,Time,daste,shomarande,codecolor) "
//                               "VALUES (:Image,:Date,:Time,:das,:shom,:cc)");

//                querysql.bindValue(":Image", byteArray);
//                qDebug("1save -----------------------------");
//                querysql.bindValue(":Date", mybrick.day);
//                qDebug("1save -----------------------------");
//                querysql.bindValue(":Time", mybrick.hour);
//                qDebug("1save -----------------------------");
//                querysql.bindValue(":das",mybrick.daste);
//                qDebug("1save -----------------------------");
//                querysql.bindValue(":shom", mybrick.shomarande);
//                qDebug("1save -----------------------------");
//                querysql.bindValue(":cc",QString::fromStdString(mybrick.codecolor));
//                querysql.exec();
//                //printf("insert vvvv im: %.4fs\n", (double)(clock() - tStartsql) / CLOCKS_PER_SEC);

//                //qDebug("1save -----------------------------");
//            }
//            catch(exception ex)
//            {

//               qWarning() << "hhhhhhhhhhhhhhhhh: " << dbsql.lastError();


//            }


//        }
//        emit imageReady(mybrick, absPath);
//    }

//signals:
//    /**
//    * Signal to connect to after the image has been saved.
//    */
//    void imageReady(detected_bricks mybrick, QString path);

//private:
//    /**
//    * Worker thread, saves image in this thread and then ends.
//    */
//    QThread t;
//};
