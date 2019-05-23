#include <cstdio>
#include <thread>
#include <unistd.h>
#include <time.h>

#include <opencv2/opencv.hpp>

#include "VideoRecord.h"

using namespace std;
using namespace cv;

VideoCapture mCapture;
VideoWriter mWriter;

int mSrcType;
int mNode;
char mPath[128];
char mFilename[256];
bool bRecord;
int Width = 640;
int Height = 480;
thread mThreadVideoRecord;

void tVideoRecord()
{
    printf("\tmSrcType:\t%d\n", mSrcType);
    if(mSrcType == 0){
        mCapture.open(mNode);
        printf("\tOpen camera:\t%d\n", mNode);
    }else if(mSrcType == 1){
        mCapture.open(mPath);
        printf("\tOpen file:\t%s\n", mPath);
    }
    if(!mCapture.isOpened()){
        return;
    }
    printf("\tStore file:\t%s\n", mFilename);
    mWriter.open(mFilename, CV_FOURCC('M', 'J', 'P', 'G'), 30, Size(Width, Height));

    while(bRecord){
        Mat frame, frametmp;
        mCapture >> frame;
        if(!frame.empty()){
            if(frame.type() != 16){
                cv::cvtColor(frame, frame, CV_RGBA2RGB);
            }
            if(frame.cols != Width || frame.rows != Height ){
                cv::resize(frame, frametmp, Size(Width, Height), 0, 0, INTER_LINEAR);
                mWriter.write(frametmp);
            }else{
                mWriter.write(frame);
            }
        }
        usleep(25*1000);
    }
}

CVideoRecord::CVideoRecord()
{
    bRecord = false;
    mSrcType = -1;
    memset(mDeviceName, '\0', 64);
}

CVideoRecord::~CVideoRecord()
{
    bRecord = false;
}

int CVideoRecord::Open(int device_node)
{
    mSrcType = 0;
    mNode = device_node;
}

int CVideoRecord::Open(char *stream_path)
{
    mSrcType = 1;
    strcpy(mPath, stream_path);
}

int CVideoRecord::Start(char *filename)
{
    if(mSrcType == -1)
        return -1;
    
    bRecord = true;
    if(filename == NULL){
        time_t now;
        time(&now);
        tm *ltm = localtime(&now);
        sprintf(mFilename, "%s_%.4d_%.2d_%.2d_%.2d_%.2d_%.2d.avi", mDeviceName, 1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday, ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
    }else {
        strcpy(mFilename, filename);
    }
    
    mThreadVideoRecord = std::thread( tVideoRecord );
    
    return 0;
}

int CVideoRecord::Stop()
{
    bRecord = false;
    mSrcType = -1;
    mThreadVideoRecord.join();
    return 0;
}

int CVideoRecord::SetLabel(char *device_name)
{
    strcpy(mDeviceName, device_name);
    return 0;
}

int main(int argc, char** argv){
    
    int ret = -1;
    int sec = 5;
    CVideoRecord video_record;
    video_record.SetLabel((char*)"TestCam");
    
    if(argc >= 2){
        for(int i = 1; i < argc; i+=2){
            if(!strcmp(argv[i], "-camera")){
                video_record.Open(atoi(argv[i+1]));
            }else if(!strcmp(argv[i], "-file")){
                video_record.Open(argv[i+1]);
            }else if(!strcmp(argv[i], "-time")){
                sec = atoi(argv[i+1]);
            }else if(!strcmp(argv[i], "-v") || !strcmp(argv[i], "--version")){
                //printf("Face recognition SDK Demo (c) 2018.\nFaceRecognition SDK Version %s\n\n", frpkg.getVersion());
                return 0;
            }else if(!strcmp(argv[i], "--help") || !strcmp(argv[i], "-h")){
                printf( "\n\nList information about the Command Line\nUsage: FR [OPTION] [PARAMETER] ...\n\n"
                        "-camera\t\tOpen camera, the format is opencv videocapture.\n\t\tdefault: 0\n\n"
                        "-file\t\tOpen file to playback.\n\n");
                return 0;
            }
        }
    }
    
    ret = video_record.Start();
    if(ret != -1){
        
        usleep(sec * 1000 * 1000);

        video_record.Stop();
        
    }else{
        printf("[Error]Please set source video or exec --help\n");
    }
    
    return ret;
}
