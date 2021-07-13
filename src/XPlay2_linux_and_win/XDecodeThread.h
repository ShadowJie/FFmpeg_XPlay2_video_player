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

	//�������
	virtual void Clear();

	//������Դ��ֹͣ�߳�
	virtual void Close();

	//ȡ��һ֡���ݣ�����ջ�����û�з���NULL
	virtual AVPacket* Pop();
	//������
	int maxList = 200;//100һ���ܴ������
	bool isExit = false;

protected:
	XDecode* decode = 0;
	//����һ�������Ƚ��ȳ�����
	std::list<AVPacket*> packs;
	std::mutex mux;

};

