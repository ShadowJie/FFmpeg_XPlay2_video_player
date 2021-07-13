#include "XPlay2.h"
#include <QtWidgets/QApplication>
#include <iostream>
using namespace std;
#include "XDemux.h"
#include "XDecode.h"
#include <qthread.h>
#include "XResample.h"
#include "XAudioPlay.h"
#include "XAudioThread.h"
#include "XVideoThread.h"
#include "XVideoWidget.h"
class TestThread :public QThread
{
public:
	XAudioThread at;
	XVideoThread vt;
	void Init()
	{
	
		//湖南卫视
		//char* url = "rtmp://58.200.131.2:1935/livetv/hunantv";
        const char* url = "v1080.flv";
		cout << "demux.Open = " << demux.Open(url);
		demux.Read();
		demux.Clear();
		demux.Close();
		url = "v1080.flv";
		cout << "demux.Open = " << demux.Open(url);
		//cout << "demux.CopyVpara = " << demux.CopyVpara() << endl;
		//cout << "demux.CopyApara = " << demux.CopyApara() << endl;
		//cout << "seek = " << demux.Seek(0.95) << endl;

		/////////////////////////////////////////		
		//cout << "vdecode.Open() = " << vdecode.Open(demux.CopyVpara()) << endl;
		//vdecode.Clear();
		//vdecode.Close();	
		//cout << "adecode.Open() = " << adecode.Open(demux.CopyApara()) << endl;
		//cout << "resample.Open = " << resample.Open(demux.CopyApara()) << endl;
		//XAudioPlay::Get()->channels = demux.channels;
		//XAudioPlay::Get()->sampleRate = demux.sampleRate;

		//cout << "XAudioPlay::Get()->Open() = " << XAudioPlay::Get()->Open() << endl;
		
		cout << "at.Open = " << at.Open(demux.CopyApara(), demux.sampleRate, demux.channels) << endl;
		vt.Open(demux.CopyVpara(), video, demux.width, demux.height);
		at.start();
		vt.start();
	}
	unsigned char* pcm = new unsigned char[1024 * 1024];
	void run()
	{
		for (;;)
		{
			AVPacket* pkt = demux.Read();
			if (demux.IsAudio(pkt))
			{
				at.Push(pkt);
				/*adecode.Send(pkt);
				AVFrame* frame = adecode.Recv();
				int len = resample.Resample(frame, pcm);
				cout << "Resample:" << len << " ";
				while (len > 0)
				{
					if (XAudioPlay::Get()->GetFree() >= len)
					{
						XAudioPlay::Get()->Write(pcm, len);
						break;
					}
					msleep(1);
				}	*/			
				//cout << "Audio: " << frame << endl;
			}
			else
			{
				vt.Push(pkt);
				//vdecode.Send(pkt);
				//AVFrame* frame = vdecode.Recv();
				//video->Repaint(frame);
				//msleep(17);
				//cout << "Video: " << frame << endl;
			}
			if (!pkt) break;
		}
	}
	//测试XDemux
	XDemux demux;
	///解码测试
	//XDecode vdecode;
	//XDecode adecode;
	XVideoWidget* video = 0;
	//XResample resample;
};
#include "XDemuxThread.h"
//v1080.flv
int main(int argc, char *argv[])
{

	//初始化显示

	/*
	for (;;)
	{
		AVPacket* pkt = demux.Read();
		if (demux.IsAudio(pkt))
		{
			adecode.Send(pkt);
			AVFrame* frame = adecode.Recv();
			//cout << "Audio: " << frame << endl;
		}
		else
		{
			vdecode.Send(pkt);
			AVFrame* frame = vdecode.Recv();
			//cout << "Video: " << frame << endl;
		}
		if (!pkt) break;
	}
	*/
	//TestThread tt;
    QApplication a(argc, argv);
    XPlay2 w;
    w.show();

	//初始化gl窗口
	//w.ui.video->Init(tt.demux.width, tt.demux.height);
	//tt.video = w.ui.video;
	//tt.Init();
	//tt.start();
	//XDemuxThread dt;
	//char* url = "rtmp://58.200.131.2:1935/livetv/gdtv";
	//url = "v1080.mp4";
	//dt.Open(url, w.ui.video);
	//dt.Start();

    return a.exec();
}
