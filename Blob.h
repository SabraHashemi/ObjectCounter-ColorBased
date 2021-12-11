/*
----------------------------------------------
--- Author         : Ahmet Özlü
--- Mail           : ahmetozlu93@gmail.com
--- Date           : 1st August 2017
--- Version        : 1.0
--- OpenCV Version : 2.4.10
--- Demo Video     : https://youtu.be/3uMKK28bMuY
----------------------------------------------
*/
#ifndef MY_BLOB
#define MY_BLOB
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

class Blob {
	public:
		// member variables
        int id;
		std::vector<cv::Point> currentContour;
		cv::Rect currentBoundingRect;
		cv::RotatedRect currentRotatedRect;
		std::vector<cv::Point> centerPositions;
		double dblCurrentDiagonalSize;
		double dblCurrentAspectRatio;
        double realarea;
		bool blnCurrentMatchFoundOrNewBlob;
		bool blnStillBeingTracked;
		int intNumOfConsecutiveFramesWithoutAMatch;
		cv::Point predictedNextPosition;
        bool counted=false;

		// function prototypes
		Blob(std::vector<cv::Point> _contour);
		void predictNextPosition(void);
};

#endif    // MY_BLOB


