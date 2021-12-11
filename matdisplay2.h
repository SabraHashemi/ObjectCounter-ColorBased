#ifndef MATDISPLAY_H
#define MATDISPLAY_H

#include <QObject>
#include <QWidget>
#include <QLabel>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>   //cout
#include <QPainter>
#include <QMouseEvent>
#include <QGraphicsView>
#include"mainwindow.h"


using namespace std;

#include <QMouseEvent>

class matDisplay2 : public QLabel
{

    Q_OBJECT
public:
    matDisplay2(QWidget* parent=0);
    ~matDisplay2();
    double centerX2;
    double centerY2;
    bool mFirstClicke2;
    int mStartX2;
    int mStartY2;
    int mEndX2 ;
    int mEndY2 ;
    MainWindow* maiobj2;

    QImage MatToQImage2( cv::Mat &mat);

public slots:
    void  slot2();

protected:
    void mouseMoveEvent2(QMouseEvent* mouse_event);
    void mousePressEvent2(QMouseEvent* mouse_event);
    void mouseReleaseEvent2(QMouseEvent *mouse_event);

signals:
    void sendMousPosition2(QPoint&);
    void showMousePeressed2(QPoint& pos);
    void showMouseReleased2(QPoint& pos);




};

#endif // MATDISPLAY_H
