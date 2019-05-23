#ifndef _VIDEORECORD_H_
#define _VIDEORECORD_H_


class CVideoRecord
{
    
    public:

        CVideoRecord();
        ~CVideoRecord();
        
        int SetLabel(char *device_name);
        int Open(int device_node);
        int Open(char *stream_path);
        int Start(char *filename = NULL);
        int Stop();


    private:
        char mDeviceName[64];

};


#endif //_VIDEORECORD_H_
