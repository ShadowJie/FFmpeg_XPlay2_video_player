#pragma once
struct AVPacket;
class XDecode;
struct AVCodecParameters;
#include <list>
#include <mutex>
#include <qthread.h>
#include "IVideoCall.h"
#include "XDecodeThread.h"
//解码和显示视频
class XVideoThread : public XDecodeThread
{
public:
	//解码pts，如果接收到的解码数据pts >= seekpts return true并且显示画面
	virtual bool RepaintPts(AVPacket* pkt, long long seekpts);
	
	//打开，不管成功与否都清理
	virtual bool Open(AVCodecParameters* para, IVideoCall* call, int width, int height);
	void run();

	XVideoThread();
	virtual ~XVideoThread();

	
	//同步时间由外部传入
	long long synpts = 0;

	void SetPause(bool isPause);
	bool isPause = false;
protected:
	IVideoCall* call = 0;
	std::mutex vmux;

};

