#pragma once

#include <QtWidgets/QWidget>
#include "ui_XPlay2.h"

class XPlay2 : public QWidget
{
    Q_OBJECT

public:
    XPlay2(QWidget *parent = Q_NULLPTR);
	~XPlay2();

	//��ʱ�� ��������ʾ
	void timerEvent(QTimerEvent* e);

	//���ڳߴ�仯
	void resizeEvent(QResizeEvent* e);

	//˫��ȫ��
	void mouseDoubleClickEvent(QMouseEvent* e);
	void SetPause(bool isPause);

	public slots:
	void OpenFile();
	void PlayOrPause();
	void SliderPress();
	void SliderRelease();
private:
	bool isSliderPress = false;
    Ui::XPlay2Class ui;
};
