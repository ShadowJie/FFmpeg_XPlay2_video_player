#pragma once
struct AVPacket;
class XDecode;

#include <list>
#include <mutex>
#include <qthread.h>
class XDecodeThread : public QThread
{
public:
	XDecodeThread();
	virtual ~XDecodeThread();
	virtual void Push(AVPacket* pkt);

	//清理队列
	virtual void Clear();

	//清理资源，停止线程
	virtual void Close();

	//取出一帧数据，并出栈，如果没有返回NULL
	virtual AVPacket* Pop();
	//最大队列
	int maxList = 200;//100一般能存放两秒
	bool isExit = false;

protected:
	XDecode* decode = 0;
	//创建一个链表，先进先出队列
	std::list<AVPacket*> packs;
	std::mutex mux;

};

