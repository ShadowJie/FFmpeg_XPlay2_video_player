#pragma once
struct AVCodecParameters;
struct AVCodecContext;
struct AVFrame;
struct AVPacket;
#include <mutex>
extern void XFreePacket(AVPacket** pkt);
extern void XFreeFrame(AVFrame** frame);
class XDecode
{
public:
	bool isAudio = false;

	//��ǰ���뵽��pts
	long long pts = 0;
	//�򿪽����������ܳɹ�����ͷ�para�ռ�
	virtual bool Open(AVCodecParameters* para);

	//���͵������̣߳����ܳɹ��������pkt�ռ䣨�����ý�����ݣ�
	virtual bool Send(AVPacket* pkt);

	//��ȡ��������ݣ�һ��Send������Ҫ���Recv����ȡ�����е�����Send NULL��Recv���
	//ÿ�θ���һ�ݣ��ɵ������ͷ� av_frame_free()
	virtual AVFrame* Recv();


	virtual void Close();
	virtual void Clear();

	XDecode();
	virtual ~XDecode();
protected:
	AVCodecContext* codec = 0;
	std::mutex mux;
};

