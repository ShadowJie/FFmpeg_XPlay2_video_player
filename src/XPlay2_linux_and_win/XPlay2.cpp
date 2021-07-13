#include "XPlay2.h"
#include <qfiledialog.h>
#include <qdebug.h>
#include "XDemuxThread.h"
#include "qmessagebox.h"
static XDemuxThread dt;
XPlay2::XPlay2(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
	dt.Start();
	startTimer(40);
}
XPlay2::~XPlay2()
{
	dt.Close();
}

void XPlay2::SliderPress()
{
	isSliderPress = true;

}

void XPlay2::SliderRelease()
{
	isSliderPress = false;
	double pos = 0.0;
	pos = (double)ui.playPos->value() / (double)ui.playPos->maximum();
	dt.Seek(pos);
}
//定时器 滑动条显示
void XPlay2::timerEvent(QTimerEvent* e)
{
	if (isSliderPress) return;
	long long total = dt.totalMs;
	if (total > 0)
	{
		double pos = (double)dt.pts / (double)total;
		int v = ui.playPos->maximum() * pos;
		ui.playPos->setValue(v);
	}
}
//双击全屏
void XPlay2::mouseDoubleClickEvent(QMouseEvent* e)
{
	if (isFullScreen())
		this->showNormal();
	else
		this->showFullScreen();
}

//窗口尺寸变化
void XPlay2::resizeEvent(QResizeEvent* e)
{
	ui.playPos->move(50, this->height() - 100);
	ui.playPos->resize(this->width() - 100, ui.playPos->height());
	ui.openfile->move(100, this->height() - 150);
	ui.isplay->move(ui.openfile->x() + ui.openfile->width() + 10, ui.openfile->y());
	ui.video->resize(this->size());
}

void XPlay2::PlayOrPause()
{
	bool isPause = !dt.isPause;
	SetPause(isPause);
	dt.SetPause(isPause);

}
void XPlay2::SetPause(bool isPause)
{
	if (isPause)
		ui.isplay->setText(QString::fromLocal8Bit("播 放"));
	else
		ui.isplay->setText(QString::fromLocal8Bit("暂 停"));
}


void XPlay2::OpenFile()
{
	//选择文件
	QString name = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("选择视频文件"));
	if (name.isEmpty()) return;
	this->setWindowTitle(name);
	if (!dt.Open(name.toLocal8Bit(), ui.video))
	{
		QMessageBox::information(0, "error", "openn file failed!");
		return;
	}
	SetPause(dt.isPause);
	//qDebug() << name;
}
