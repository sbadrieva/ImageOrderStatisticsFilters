//
//  OrderStatisticFiltersClass.cpp
//  OpenCv
//
//  Created by Shokhina Badrieva on 3/15/21.
//  Copyright © 2021 Shokhina Badrieva. All rights reserved.
//

#include "OrderStatisticFiltersClass.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;



double getMedian(int a[], int n)
{
    // First we sort the array
    sort(a, a + n);
    
    // check for even case
    if (n % 2 != 0)
        return (double)a[n / 2];
    
    return (double)(a[(n - 1) / 2] + a[n / 2]) / 2.0;
}

int getMin(int arr[], int n)
{
    int res = arr[0];
    for (int i = 1; i < n; i++)
        res = min(res, arr[i]);
    return res;
}

int getMax(int arr[], int n)
{
    int res = arr[0];
    for (int i = 1; i < n; i++)
        res = max(res, arr[i]);
    return res;
}



bool medianFilter(Mat& src, Mat& dst,int kernel)
{
    if(src.type()!=CV_8UC1){
        cout<<"Image is not grayscale!"<<endl;
        return false;
    }
    else if(kernel%2!=1){
        cout<<"Kernel is not uneven!"<<endl;
        return false;
    }
    else if(kernel<1){
        cout<<"Kernel must be of size greater than 1!"<<endl;
        return false;
    }
    
    //border size
    int padding = (kernel - 1) / 2;
    
    int median = 0.0;
    int final = 0;
    int imgRows, imgCols;
    cv::Mat img_temp;
    int medianArr[kernel*kernel];
    
    imgRows = src.size().height;
    imgCols = src.size().width;
    
    //make a border around image with border size
    copyMakeBorder(src, img_temp, padding, padding, padding, padding, BORDER_CONSTANT, 0);
    
    //output image will be grayscale
    dst = Mat::zeros(imgRows, imgCols, CV_8UC1);
    
    // loop over whole image and find median of neighborhood of pixel
    for (unsigned int i = padding; i<imgRows + padding; i++){
        for (unsigned int j = padding; j<imgCols + padding; j++){
            median = 0.0;
            // loop over neighborhood
            int index=0;
            for (int x = -padding; x <= padding; x++){
                for (int y = -padding; y <= padding; y++){
                    //int val=img_temp.at<uchar>(i+x,j+y);
                    //cout<<"Value in imgtemp: "<<val<<endl;
                    medianArr[index]=(img_temp.at<uchar>(i+x,j+y));
                    index++;
                }
            }
            
            /*cout<<"Median Array"<<endl;
             for(int i=0;i<kernel*kernel;i++){
             cout<<medianArr[i]<<" ";
             }
             cout<<endl;
             */
            int median=getMedian(medianArr, kernel*kernel);
            //cout<<"Median is: "<<median<<endl;
            
            final = round(median);
            // cast result to uchar and set pixel in output image
            dst.at<uchar>(i - padding, j - padding) = (uchar)final;
            double finalVal=dst.at<uchar>(i - padding, j - padding);
            //cout<<"Final val: "<<finalVal<<endl;
        }
    }
    /*
     imshow("final img: ",dst);
     waitKey(0);
     destroyAllWindows();
     */
    return true;
}


//works for a kernel of five
bool weightedMedianFilter(Mat& src, Mat& dst,int kernel)
{
    
    int weights[5][5]={{1,2,2,2,1},{2,2,3,2,2},{2,3,3,3,2},{2,2,3,2,2},{1,2,2,2,1}};
    /*
     for(int i=0;i<kernel;i++){
     for(int j=0;j<kernel;j++){
     cout<<weights[i][j]<<" ";
     }
     cout<<endl;
     }
     */
    
    if(src.type()!=CV_8UC1){
        cout<<"Image is not grayscale!"<<endl;
        return false;
    }
    else if(kernel%2!=1){
        cout<<"Kernel is not uneven!"<<endl;
        return false;
    }
    else if(kernel<1){
        cout<<"Kernel must be of size greater than 1!"<<endl;
        return false;
    }
    
    //border size
    int padding = (kernel - 1) / 2;
    
    int median = 0.0;
    int final = 0;
    int imgRows, imgCols;
    cv::Mat img_temp;
    int medianArr[51];
    
    imgRows = src.size().height;
    imgCols = src.size().width;
    
    //make a border around image with border size
    copyMakeBorder(src, img_temp, padding, padding, padding, padding, BORDER_CONSTANT, 0);
    
    //output image will be grayscale
    dst = Mat::zeros(imgRows, imgCols, CV_8UC1);
    
    // loop over whole image and find mean of neighborhood of pixel
    for (unsigned int i = padding; i<imgRows + padding; i++){
        for (unsigned int j = padding; j<imgCols + padding; j++){
            median = 0.0;
            // loop over neighborhood
            int index=0;
            int count=0;
            int numOfWeight=0;
            for (int x = -padding; x <= padding; x++){
                for (int y = -padding; y <= padding; y++){
                    //int val=img_temp.at<uchar>(i+x,j+y);
                    //cout<<"Value in imgtemp: "<<val<<endl;
                    numOfWeight=weights[x+padding][y+padding];
                    //cout<<"Weight number "<<numOfWeight<<endl;
                    while(numOfWeight!=0){
                        int val=(img_temp.at<uchar>(i+x,j+y));
                        //cout<<"Value in img temp is: "<<val<<endl;
                        
                        medianArr[index]=(img_temp.at<uchar>(i+x,j+y));
                        //cout<<"Value is madian array at index "<<index<<" is: "<<medianArr[index]<<endl;
                        index++;
                        count++;
                        numOfWeight--;
                        //cout<<"index: "<<index<<endl;
                        //cout<<"count: "<<count<<endl;
                    }
                }
            }
            /*
             cout<<"Median Array"<<endl;
             for(int arrayEl=0;arrayEl<count;arrayEl++){
             cout<<medianArr[arrayEl]<<" ";
             }
             cout<<endl;
             */
            int median=getMedian(medianArr, count);
            //cout<<"Median is: "<<median<<endl;
            
            final = round(median);
            // cast result to uchar and set pixel in output image
            dst.at<uchar>(i - padding, j - padding) = (uchar)final;
            //double finalVal=dst.at<uchar>(i - padding, j - padding);
            //cout<<"Final val: "<<finalVal<<endl;
        }
    }
    /*
     imshow("final img: ",dst);
     waitKey(0);
     destroyAllWindows();
     */
    return true;
}


bool minFilter(Mat& src, Mat& dst,int kernel)
{
    if(src.type()!=CV_8UC1){
        cout<<"Image is not grayscale!"<<endl;
        return false;
    }
    else if(kernel%2!=1){
        cout<<"Kernel is not uneven!"<<endl;
        return false;
    }
    else if(kernel<1){
        cout<<"Kernel must be of size greater than 1!"<<endl;
        return false;
    }
    
    //border size
    int padding = (kernel - 1) / 2;
    
    int median = 0.0;
    int final = 0;
    int imgRows, imgCols;
    cv::Mat img_temp;
    int medianArr[kernel*kernel];
    
    imgRows = src.size().height;
    imgCols = src.size().width;
    
    //make a border around image with border size
    copyMakeBorder(src, img_temp, padding, padding, padding, padding, BORDER_CONSTANT, 0);
    
    //output image will be grayscale
    dst = Mat::zeros(imgRows, imgCols, CV_8UC1);
    
    // loop over whole image and find mean of neighborhood of pixel
    for (unsigned int i = padding; i<imgRows + padding; i++){
        for (unsigned int j = padding; j<imgCols + padding; j++){
            median = 0.0;
            // loop over neighborhood
            int index=0;
            for (int x = -padding; x <= padding; x++){
                for (int y = -padding; y <= padding; y++){
                    //int val=img_temp.at<uchar>(i+x,j+y);
                    //cout<<"Value in imgtemp: "<<val<<endl;
                    medianArr[index]=(img_temp.at<uchar>(i+x,j+y));
                    index++;
                }
            }
            
            /*cout<<"Median Array"<<endl;
             for(int i=0;i<kernel*kernel;i++){
             cout<<medianArr[i]<<" ";
             }
             cout<<endl;
             */
            int median=getMin(medianArr, kernel*kernel);
            //cout<<"Median is: "<<median<<endl;
            
            final = round(median);
            // cast result to uchar and set pixel in output image
            dst.at<uchar>(i - padding, j - padding) = (uchar)final;
            //double finalVal=dst.at<uchar>(i - padding, j - padding);
            //cout<<"Final val: "<<finalVal<<endl;
        }
    }
    /*
     imshow("final img: ",dst);
     waitKey(0);
     destroyAllWindows();
     */
    return true;
}

bool maxFilter(Mat& src, Mat& dst,int kernel)
{
    if(src.type()!=CV_8UC1){
        cout<<"Image is not grayscale!"<<endl;
        return false;
    }
    else if(kernel%2!=1){
        cout<<"Kernel is not uneven!"<<endl;
        return false;
    }
    else if(kernel<1){
        cout<<"Kernel must be of size greater than 1!"<<endl;
        return false;
    }
    
    //border size
    int padding = (kernel - 1) / 2;
    
    int median = 0.0;
    int final = 0;
    int imgRows, imgCols;
    cv::Mat img_temp;
    int medianArr[kernel*kernel];
    
    imgRows = src.size().height;
    imgCols = src.size().width;
    
    //make a border around image with border size
    copyMakeBorder(src, img_temp, padding, padding, padding, padding, BORDER_CONSTANT, 0);
    
    //output image will be grayscale
    dst = Mat::zeros(imgRows, imgCols, CV_8UC1);
    
    // loop over whole image and find mean of neighborhood of pixel
    for (unsigned int i = padding; i<imgRows + padding; i++){
        for (unsigned int j = padding; j<imgCols + padding; j++){
            median = 0.0;
            // loop over neighborhood
            int index=0;
            for (int x = -padding; x <= padding; x++){
                for (int y = -padding; y <= padding; y++){
                    //int val=img_temp.at<uchar>(i+x,j+y);
                    //cout<<"Value in imgtemp: "<<val<<endl;
                    medianArr[index]=(img_temp.at<uchar>(i+x,j+y));
                    index++;
                }
            }
            
            /*cout<<"Median Array"<<endl;
             for(int i=0;i<kernel*kernel;i++){
             cout<<medianArr[i]<<" ";
             }
             cout<<endl;
             */
            int median=getMax(medianArr, kernel*kernel);
            //cout<<"Median is: "<<median<<endl;
            
            final = round(median);
            // cast result to uchar and set pixel in output image
            dst.at<uchar>(i - padding, j - padding) = (uchar)final;
            //double finalVal=dst.at<uchar>(i - padding, j - padding);
            //cout<<"Final val: "<<finalVal<<endl;
        }
    }
    /*
     imshow("final img: ",dst);
     waitKey(0);
     destroyAllWindows();
     */
    return true;
}

bool midpointFilter(Mat& src, Mat& dst,int kernel)
{
    if(src.type()!=CV_8UC1){
        cout<<"Image is not grayscale!"<<endl;
        return false;
    }
    else if(kernel%2!=1){
        cout<<"Kernel is not uneven!"<<endl;
        return false;
    }
    else if(kernel<1){
        cout<<"Kernel must be of size greater than 1!"<<endl;
        return false;
    }
    
    //border size
    int padding = (kernel - 1) / 2;
    
    int midpoint = 0.0;
    int max = 0.0;
    int min = 0.0;
    int final = 0;
    int imgRows, imgCols;
    cv::Mat img_temp;
    int medianArr[kernel*kernel];
    
    imgRows = src.size().height;
    imgCols = src.size().width;
    
    //make a border around image with border size
    copyMakeBorder(src, img_temp, padding, padding, padding, padding, BORDER_CONSTANT, 0);
    
    //output image will be grayscale
    dst = Mat::zeros(imgRows, imgCols, CV_8UC1);
    
    // loop over whole image and find mean of neighborhood of pixel
    for (unsigned int i = padding; i<imgRows + padding; i++){
        for (unsigned int j = padding; j<imgCols + padding; j++){
            midpoint = 0.0;
            min=0.0;
            max=0.0;
            // loop over neighborhood
            int index=0;
            for (int x = -padding; x <= padding; x++){
                for (int y = -padding; y <= padding; y++){
                    //int val=img_temp.at<uchar>(i+x,j+y);
                    //cout<<"Value in imgtemp: "<<val<<endl;
                    medianArr[index]=(img_temp.at<uchar>(i+x,j+y));
                    index++;
                }
            }
            
            /*cout<<"Median Array"<<endl;
             for(int i=0;i<kernel*kernel;i++){
             cout<<medianArr[i]<<" ";
             }
             cout<<endl;
             */
            min=getMin(medianArr,kernel*kernel);
            max=getMax(medianArr,kernel*kernel);
            midpoint=(min+max)/2;
            //cout<<"Median is: "<<median<<endl;
            
            final = round(midpoint);
            // cast result to uchar and set pixel in output image
            dst.at<uchar>(i - padding, j - padding) = (uchar)final;
            //double finalVal=dst.at<uchar>(i - padding, j - padding);
            //cout<<"Final val: "<<finalVal<<endl;
        }
    }
    /*
     imshow("final img: ",dst);
     waitKey(0);
     destroyAllWindows();
     */
    return true;
}

bool alphaTrimmedFilter(Mat& src, Mat& dst,int kernel,int del)
{
    if(del%2!=0){
        cout<<"Number of elements deleted must be even!"<<endl;
        return false;
    }
    if(del<2||del>(kernel*kernel-1)){
        cout<<"Invalid number for del. Del must be at least two and at most (kernel*kernel-1)!"<<endl;
        return false;
    }
    if(src.type()!=CV_8UC1){
        cout<<"Image is not grayscale!"<<endl;
        return false;
    }
    else if(kernel%2!=1){
        cout<<"Kernel is not uneven!"<<endl;
        return false;
    }
    else if(kernel<1){
        cout<<"Kernel must be of size greater than 1!"<<endl;
        return false;
    }
    
    //border size
    int padding = (kernel - 1) / 2;
    int delFromEachSide=del/2;
    int median=0.0;
    int mean=0.0;
    int final = 0;
    int imgRows, imgCols;
    cv::Mat img_temp;
    int medianArr[kernel*kernel];
    
    imgRows = src.size().height;
    imgCols = src.size().width;
    
    //make a border around image with border size
    copyMakeBorder(src, img_temp, padding, padding, padding, padding, BORDER_CONSTANT, 0);
    
    //output image will be grayscale
    dst = Mat::zeros(imgRows, imgCols, CV_8UC1);
    
    // loop over whole image and find mean of neighborhood of pixel
    for (unsigned int i = padding; i<imgRows + padding; i++){
        for (unsigned int j = padding; j<imgCols + padding; j++){
            median = 0.0;
            mean = 0.0;
            // loop over neighborhood
            int index=0;
            for (int x = -padding; x <= padding; x++){
                for (int y = -padding; y <= padding; y++){
                    //int val=img_temp.at<uchar>(i+x,j+y);
                    //cout<<"Value in imgtemp: "<<val<<endl;
                    medianArr[index]=(img_temp.at<uchar>(i+x,j+y));
                    index++;
                }
            }
            
            int count=0;
            for(int i=delFromEachSide;i<(kernel*kernel)-delFromEachSide;i++){
                mean+=medianArr[i];
                count++;
            }
            
            mean=mean/count;
            
            final = round(mean);
            // cast result to uchar and set pixel in output image
            dst.at<uchar>(i - padding, j - padding) = (uchar)final;
            //double finalVal=dst.at<uchar>(i - padding, j - padding);
            //cout<<"Final val: "<<finalVal<<endl;
        }
    }
    /*
     imshow("final img: ",dst);
     waitKey(0);
     destroyAllWindows();
     */
    return true;
}

bool multiStageMedianFilter(Mat& src, Mat& dst,int kernel)
{
    if(src.type()!=CV_8UC1){
        cout<<"Image is not grayscale!"<<endl;
        return false;
    }
    else if(kernel%2!=1){
        cout<<"Kernel is not uneven!"<<endl;
        return false;
    }
    else if(kernel<1){
        cout<<"Kernel must be of size greater than 1!"<<endl;
        return false;
    }
    
    //border size
    int padding = (kernel - 1) / 2;
    
    int diagonalMedian1 = 0.0;
    int diagonalMedian2 = 0.0;
    int horizontalMedian = 0.0;
    int verticalMedian = 0.0;
    int index=0;
    int final = 0;
    int count=0;
    int imgRows, imgCols;
    cv::Mat img_temp;
    int medianArr[kernel];
    
    imgRows = src.size().height;
    imgCols = src.size().width;
    
    //make a border around image with border size
    copyMakeBorder(src, img_temp, padding, padding, padding, padding, BORDER_CONSTANT, 0);
    
    //output image will be grayscale
    dst = Mat::zeros(imgRows, imgCols, CV_8UC1);
    
    
    
    
    
    
    // loop over whole image and find mean of neighborhood of pixel
    for (unsigned int i = padding; i<imgRows + padding; i++){
        for (unsigned int j = padding; j<imgCols + padding; j++){
            
            
            
            
            
            
            //finding diagonal median 1 of neighborhood
            // loop over neighborhood
            index=0;
            count=0;
            for (int x = -padding; x <= padding; x++){
                for (int y = -padding; y <= padding; y++){
                    //int val=img_temp.at<uchar>(i+x,j+y);
                    //cout<<"Value in imgtemp: "<<val<<endl;
                    
                    if(x==y){
                        medianArr[index]=(img_temp.at<uchar>(i+x,j+y));
                        index++;
                        count++;
                    }
                    else{
                        continue;
                    }
                }
            }
            /*
             cout<<"Diagonal1 Median Array"<<endl;
             for(int i=0;i<count;i++){
             cout<<medianArr[i]<<" ";
             }
             cout<<endl;
             */
            diagonalMedian1=getMedian(medianArr, count);
            //cout<<"DiagonalMedian1 is: "<<diagonalMedian1<<endl;
            
            
            
            
            
            //find diagonal median 2 of neighborhood
            // loop over neighborhood
            count=0;
            index=0;
            for (int x = -padding; x <= padding; x++){
                for (int y = -padding; y <= padding; y++){
                    //int val=img_temp.at<uchar>(i+x,j+y);
                    //cout<<"Value in imgtemp: "<<val<<endl;
                    if(x==(y-j-1)){
                        medianArr[index]=(img_temp.at<uchar>(i+x,j+y));
                        index++;
                        count++;
                    }
                    else{
                        continue;
                    }
                }
            }
            /*
             cout<<"Diagonal Median2 Array"<<endl;
             for(int i=0;i<count;i++){
             cout<<medianArr[i]<<" ";
             }
             cout<<endl;
             */
            diagonalMedian2=getMedian(medianArr, count);
            //cout<<"Diagonal Median 2 is: "<<diagonalMedian2<<endl;
            
            
            
            //find horizontal median of neighborhood
            // loop over neighborhood
            index=0;
            count=0;
            for (int x = -padding; x <= padding; x++){
                for (int y = -padding; y <= padding; y++){
                    //int val=img_temp.at<uchar>(i+x,j+y);
                    //cout<<"Value in imgtemp: "<<val<<endl;
                    if(x==0){
                        medianArr[index]=(img_temp.at<uchar>(i+x,j+y));
                        index++;
                        count++;
                    }
                    else{
                        continue;
                    }
                }
            }
            /*
             cout<<"Horizontal Array"<<endl;
             for(int i=0;i<count;i++){
             cout<<medianArr[i]<<" ";
             }
             cout<<endl;
             */
            horizontalMedian=getMedian(medianArr, count);
            //cout<<"Horizontal median is: "<<horizontalMedian<<endl;
            
            
            //find vertical median of neighborhood
            // loop over neighborhood
            index=0;
            count=0;
            for (int x = -padding; x <= padding; x++){
                for (int y = -padding; y <= padding; y++){
                    //int val=img_temp.at<uchar>(i+x,j+y);
                    //cout<<"Value in imgtemp: "<<val<<endl;
                    if(y==0){
                        medianArr[index]=(img_temp.at<uchar>(i+x,j+y));
                        index++;
                        count++;
                    }
                    else{
                        continue;
                    }
                }
            }
            /*
             cout<<"Vertical Median Array"<<endl;
             for(int i=0;i<count;i++){
             cout<<medianArr[i]<<" ";
             }
             cout<<endl;
             */
            verticalMedian=getMedian(medianArr, count);
            //cout<<"Vertical Median is: "<<verticalMedian<<endl;
            
            int finalMedian;
            int allMedians[4]={diagonalMedian1,diagonalMedian2,horizontalMedian,verticalMedian};
            finalMedian=getMedian(allMedians, 4);
            //cout<<"final median is "<<finalMedian<<endl;
            dst.at<uchar>(i - padding, j - padding) = (uchar)finalMedian;
            
            
            
            
            
            
            
            
            
            /*
             // cast result to uchar and set pixel in output image
             dst.at<uchar>(i - padding, j - padding) = (uchar)final;
             double finalVal=dst.at<uchar>(i - padding, j - padding);
             cout<<"Final val: "<<finalVal<<endl;
             */
        }
    }
    /*
     imshow("final img: ",dst);
     waitKey(0);
     destroyAllWindows();
     */
    return true;
}



bool localNoiseFilterMedian(Mat& src, Mat&dst, int kernel){
    if(src.type()!=CV_8UC1){
        cout<<"Image is not grayscale!"<<endl;
        return false;
    }
    else if(kernel%2!=1){
        cout<<"Kernel is not uneven!"<<endl;
        return false;
    }
    else if(kernel<1){
        cout<<"Kernel must be of size greater than 1!"<<endl;
        return false;
    }
    
    //padding size
    int padding = (kernel - 1) / 2;
    //declare and initialize variables
    int mean = 0.0;
    int median=0.0;
    int meanSquared=0.0;
    int final = 0;
    int count=0;
    int imgRows, imgCols;
    int noiseVariance=0;
    Mat img_temp;
    Mat localMean;
    Mat localMedian;
    Mat nVarOverLocalVar;
    imgRows = src.size().height;
    imgCols = src.size().width;
    int localVariance[imgRows][imgCols];
    int medianArr[kernel*kernel];
    
    //make a border around image with 0s
    copyMakeBorder(src, img_temp, padding, padding, padding, padding, BORDER_CONSTANT, 0);
    
    //initialize Mat and array objects
    dst = Mat::zeros(imgRows, imgCols, CV_8UC1);
    localMean=Mat::zeros(imgRows, imgCols, CV_8UC1);
    localMedian=Mat::zeros(imgRows, imgCols, CV_8UC1);
    for(int i=0;i<imgRows;i++){
        for(int j=0;j<imgCols;j++){
            localVariance[i][j]=0;
        }
    }
    
    
    // finding local mean
    for (unsigned int i = padding; i<imgRows + padding; i++){
        for (unsigned int j = padding; j<imgCols + padding; j++){
            mean = 0.0;
            meanSquared=0.0;
            count=0;
            
            // loop over neighborhood to find mean
            for (int x = -padding; x <= padding; x++){
                for (int y = -padding; y <= padding; y++){
                    
                    mean +=img_temp.at<uchar>(i + x, j + y);
                    count++;
                    
                }
            }
            //local mean,put it in localmean mat at specific point:
            mean=mean/count;
            meanSquared=pow(mean,2);
            final = round(mean);
            //cout<<"Final mean value: "<<final<<endl;
            localMean.at<uchar>(i - padding, j - padding) = (uchar)final;
            
            //int localMeanVal=localMean.at<uchar>(i - padding, j - padding);
            //cout<<"Final local mean value: "<<localMeanVal<<endl;
            
            
            //average the local viariances
            mean=0.0;
            count=0;
            for (int x = -padding; x <= padding; x++){
                for (int y = -padding; y <= padding; y++){
                    //square the val in each window
                    mean+=pow(img_temp.at<uchar>(i + x, j + y),2);
                    count++;
                }
            }
            int meanWinSq=mean/count;
            int lvariance=meanWinSq-meanSquared;
            final=round(lvariance);
            //cout<<"final variance val: "<<final<<endl;
            
            localVariance[i - padding][j - padding]=final;
            //cout<<"final local variance val: "<<localVarVal<<endl;
            
        }
    }
    
    
    // loop over whole image and find median of neighborhood of pixel
    for (unsigned int i = padding; i<imgRows + padding; i++){
        for (unsigned int j = padding; j<imgCols + padding; j++){
            median = 0.0;
            // loop over neighborhood
            int index=0;
            for (int x = -padding; x <= padding; x++){
                for (int y = -padding; y <= padding; y++){
                    //int val=img_temp.at<uchar>(i+x,j+y);
                    //cout<<"Value in imgtemp: "<<val<<endl;
                    medianArr[index]=(img_temp.at<uchar>(i+x,j+y));
                    index++;
                }
            }
            
            /*cout<<"Median Array"<<endl;
             for(int i=0;i<kernel*kernel;i++){
             cout<<medianArr[i]<<" ";
             }
             cout<<endl;
             */
            int median=getMedian(medianArr, kernel*kernel);
            //cout<<"Median is: "<<median<<endl;
            
            final = round(median);
            // cast result to uchar and set pixel in output image
            localMedian.at<uchar>(i - padding, j - padding) = (uchar)final;
        }
    }
    
    
    //find avergae local variance
    count=0;
    mean=0;
    for(int i=0;i<imgRows;i++){
        for(int j=0;j<imgCols;j++){
            mean+=localVariance[i][j];
            count++;
        }
    }
    noiseVariance=mean/count;
    //cout<<"Noise Variance: "<<noiseVariance<<endl;
    
    //check if average local variance is greater than local variance at specific point. If so, replace point with the average local variance
    for(int i=0;i<imgRows;i++){
        for(int j=0;j<imgCols;j++){
            if(noiseVariance>localVariance[i][j]){
                localVariance[i][j]=noiseVariance;
            }
        }
    }
    
    //final image
    for(int i=0;i<imgRows;i++){
        for(int j=0;j<imgCols;j++){
            int origVal=src.at<uchar>(i,j);
            float noiseOverLocal=noiseVariance/(localVariance[i][j]);
            int localMedianVal=localMedian.at<uchar>(i,j);
            int imgMinusLocalMedian=origVal-localMedianVal;
            int final=origVal-(noiseOverLocal)*(imgMinusLocalMedian);
            dst.at<uchar>(i,j)=(uchar)final;
        }
    }
    
    return true;
    
}
