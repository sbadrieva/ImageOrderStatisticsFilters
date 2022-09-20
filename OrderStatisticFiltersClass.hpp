//
//  OrderStatisticFiltersClass.hpp
//  OpenCv
//
//  Created by Shokhina Badrieva on 3/15/21.
//  Copyright © 2021 Shokhina Badrieva. All rights reserved.
//

#ifndef OrderStatisticFiltersClass_hpp
#define OrderStatisticFiltersClass_hpp

#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

double getMedian(int a[], int n);
int getMin(int arr[], int n);
int getMax(int arr[], int n);
bool medianFilter(Mat& src, Mat& dst,int kernel);
bool minFilter(Mat& src, Mat& dst,int kernel);
bool maxFilter(Mat& src, Mat& dst,int kernel);
bool midpointFilter(Mat& src, Mat& dst,int kernel);
bool alphaTrimmedFilter(Mat& src, Mat& dst,int kernel,int del);
bool multiStageMedianFilter(Mat& src, Mat& dst,int kernel);
bool weightedMedianFilter(Mat& src, Mat& dst,int kernel=5);
bool localNoiseFilterMedian(Mat& src, Mat&dst, int kernel);



#endif /* OrderStatisticFiltersClass_hpp */
