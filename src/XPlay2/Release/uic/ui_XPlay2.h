/********************************************************************************
** Form generated from reading UI file 'XPlay2.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XPLAY2_H
#define UI_XPLAY2_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include "XSlider.h"
#include "XVideoWidget.h"

QT_BEGIN_NAMESPACE

class Ui_XPlay2Class
{
public:
    XVideoWidget *video;
    QPushButton *openfile;
    XSlider *playPos;
    QPushButton *isplay;

    void setupUi(QWidget *XPlay2Class)
    {
        if (XPlay2Class->objectName().isEmpty())
            XPlay2Class->setObjectName(QStringLiteral("XPlay2Class"));
        XPlay2Class->resize(1280, 720);
        video = new XVideoWidget(XPlay2Class);
        video->setObjectName(QStringLiteral("video"));
        video->setGeometry(QRect(0, 0, 1280, 720));
        openfile = new QPushButton(XPlay2Class);
        openfile->setObjectName(QStringLiteral("openfile"));
        openfile->setGeometry(QRect(450, 600, 81, 41));
        playPos = new XSlider(XPlay2Class);
        playPos->setObjectName(QStringLiteral("playPos"));
        playPos->setGeometry(QRect(10, 670, 1251, 22));
        playPos->setMaximum(999);
        playPos->setOrientation(Qt::Horizontal);
        isplay = new QPushButton(XPlay2Class);
        isplay->setObjectName(QStringLiteral("isplay"));
        isplay->setGeometry(QRect(620, 600, 91, 41));

        retranslateUi(XPlay2Class);
        QObject::connect(openfile, SIGNAL(clicked()), XPlay2Class, SLOT(OpenFile()));
        QObject::connect(isplay, SIGNAL(clicked()), XPlay2Class, SLOT(PlayOrPause()));
        QObject::connect(playPos, SIGNAL(sliderPressed()), XPlay2Class, SLOT(SliderPress()));
        QObject::connect(playPos, SIGNAL(sliderReleased()), XPlay2Class, SLOT(SliderRelease()));

        QMetaObject::connectSlotsByName(XPlay2Class);
    } // setupUi

    void retranslateUi(QWidget *XPlay2Class)
    {
        XPlay2Class->setWindowTitle(QApplication::translate("XPlay2Class", "XPlay2", Q_NULLPTR));
        openfile->setText(QApplication::translate("XPlay2Class", "\346\211\223\345\274\200\346\226\207\344\273\266", Q_NULLPTR));
        isplay->setText(QApplication::translate("XPlay2Class", "\346\222\255\346\224\276", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class XPlay2Class: public Ui_XPlay2Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XPLAY2_H
