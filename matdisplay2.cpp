#include "matdisplay2.h"
#include <QPainter>
#include <QFileDialog>
#include "mainwindow.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>   //cout
#include <QPainter>
#include <QMouseEvent>
#include <QGraphicsView>



using namespace std;
int draw2=3;
bool mPaintFlag2;

matDisplay2::matDisplay2(QWidget* parent): QLabel(parent)
{


}

matDisplay2::~matDisplay2()
{

}

void matDisplay2::mouseMoveEvent2(QMouseEvent *mouse_event)
{
    QPoint mouse_pos=mouse_event->pos();

    if( mouse_pos.x()<= this->size().width() && mouse_pos.y()<= this->size().height()){

        if(mouse_pos.x() > 0 && mouse_pos.y() > 0){
            emit sendMousPosition2(mouse_pos);

        }
    }

}

void matDisplay2::slot2(){

    draw2=10;
    mFirstClicke2=true;

}


void matDisplay2::mousePressEvent2(QMouseEvent *mouse_event)
{
    centerX2=mouse_event->pos().x();
    centerY2=mouse_event->pos().y();

    QPoint mouse_pos=mouse_event->pos();
    bool right=false;


    if( mouse_pos.x()<= this->size().width() && mouse_pos.y()<= this->size().height()){

        if(mouse_pos.x() > 0 && mouse_pos.y() > 0){
            if(mouse_event->button()== Qt::RightButton)
            {right = true;}

            emit  showMousePeressed2(mouse_pos);

        }
    }
}


void matDisplay2::mouseReleaseEvent2(QMouseEvent *mouse_event){

    QPoint mouse_pos=mouse_event->pos();

    if( mouse_pos.x()<= this->size().width() && mouse_pos.y()<= this->size().height()){

        if(mouse_pos.x() > 0 && mouse_pos.y() > 0){

            emit  showMouseReleased2(mouse_pos);

        }
    }
}

