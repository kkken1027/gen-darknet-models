#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char* argv[])
{
    if(argc != 5)
    {
        printf("Usage: %s <w> <h> <srcImg> <dstImg>\n", argv[0]);
        return -1;
    }
    
    int w = atoi(argv[1]);
    int h = atoi(argv[2]);
    
    cv::Mat src = imread(argv[3]); 
    if(src.empty())
    {
        fprintf(stderr, "Can not load the image file %s.\n", argv[3]);
        return -1;
    }
    
    cv::Mat dst;
    
    resize(src, dst, cv::Size(w, h), 0, 0, INTER_LINEAR);
    
    cv::imwrite(argv[4], dst);
    
    return 0;
}