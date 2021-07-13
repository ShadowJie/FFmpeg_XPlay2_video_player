#include "XVideoThread.h"
#include "XDecode.h"
#include <iostream>
using namespace std;
bool XVideoThread::Open(AVCodecParameters* para, IVideoCall* call, int width, int height)
{
	if (!para) return false;

	Clear();

	vmux.lock();
	synpts = 0;
	//初始化显示窗口
	this->call = call;
	if (call)
	{
		call->Init(width, height);
	}
	vmux.unlock();
	int re = true;
	if (!decode->Open(para))
	{
		re = false;
		cout << "Audio XDecode open failed!" << endl;
	}
	
	cout << "XAudioThread::Open : " << re << endl;
}

void XVideoThread::SetPause(bool isPause)
{
	vmux.lock();
	this->isPause = isPause;
	vmux.unlock();
}
void XVideoThread::run()
{
	while (!isExit)
	{
		vmux.lock();
		if (this->isPause)
		{
			vmux.unlock();
			msleep(5);
			continue;
		}

		//音视频同步
		if (synpts > 0 && synpts < decode->pts)
		{
			vmux.unlock();
			msleep(1);
			continue;
		}
		AVPacket* pkt = Pop();
		////没有数据
		//if (packs.empty() || !decode)
		//{
		//	vmux.unlock();
		//	msleep(1);
		//	continue;
		//}
		//

		//AVPacket* pkt = packs.front();//获取数据，数据先入先出
		//packs.pop_front();//出队
		bool re = decode->Send(pkt);
		//解码失败
		if (!re)
		{
			vmux.unlock();
			msleep(1);
			continue;
		}
		//成功，可能一次send 多次recv
		while (!isExit)
		{
			AVFrame* frame = decode->Recv();
			if (!frame) break;
			//显示视频
			if (call)
			{
				call->Repaint(frame);
			}
		}
		vmux.unlock();
	}
}
//解码pts，如果接收到的解码数据pts >= seekpts return true并且显示画面
bool XVideoThread::RepaintPts(AVPacket* pkt, long long seekpts)
{
	vmux.lock();
	bool re = decode->Send(pkt);
	if (!re)
	{
		vmux.unlock();
		return true;//表示结束解码
	}
	AVFrame* frame = decode->Recv();
	if (!frame)
	{
		vmux.unlock();
		return false;
	}//到达位置
	if (decode->pts >= seekpts)
	{
		if(call)
			call->Repaint(frame);
		vmux.unlock();
		return true;
	}
	XFreeFrame(&frame);
	vmux.unlock();
	return false;
}
XVideoThread::XVideoThread()
{
}


XVideoThread::~XVideoThread()
{
	
}
