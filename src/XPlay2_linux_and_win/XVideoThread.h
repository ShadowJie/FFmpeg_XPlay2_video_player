#pragma once
struct AVPacket;
class XDecode;
struct AVCodecParameters;
#include <list>
#include <mutex>
#include <qthread.h>
#include "IVideoCall.h"
#include "XDecodeThread.h"
//�������ʾ��Ƶ
class XVideoThread : public XDecodeThread
{
public:
	//����pts��������յ��Ľ�������pts >= seekpts return true������ʾ����
	virtual bool RepaintPts(AVPacket* pkt, long long seekpts);
	
	//�򿪣����ܳɹ��������
	virtual bool Open(AVCodecParameters* para, IVideoCall* call, int width, int height);
	void run();

	XVideoThread();
	virtual ~XVideoThread();

	
	//ͬ��ʱ�����ⲿ����
	long long synpts = 0;

	void SetPause(bool isPause);
	bool isPause = false;
protected:
	IVideoCall* call = 0;
	std::mutex vmux;

};

