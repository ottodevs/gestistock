/********************************************************************************
** Form generated from reading UI file 'widgetestadisticas.ui'
**
** Created: Mon 20. Aug 19:38:13 2012
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGETESTADISTICAS_H
#define UI_WIDGETESTADISTICAS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WidgetEstadisticas
{
public:
    QFrame *frame;
    QHBoxLayout *horizontalLayout_13;
    QFrame *frame_2;
    QGridLayout *gridLayout_3;
    QLabel *label;
    QLabel *label_3;

    void setupUi(QWidget *WidgetEstadisticas)
    {
        if (WidgetEstadisticas->objectName().isEmpty())
            WidgetEstadisticas->setObjectName(QString::fromUtf8("WidgetEstadisticas"));
        WidgetEstadisticas->resize(928, 550);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(WidgetEstadisticas->sizePolicy().hasHeightForWidth());
        WidgetEstadisticas->setSizePolicy(sizePolicy);
        WidgetEstadisticas->setMinimumSize(QSize(700, 550));
        frame = new QFrame(WidgetEstadisticas);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(130, 10, 462, 82));
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setMinimumSize(QSize(0, 82));
        frame->setMaximumSize(QSize(16777215, 82));
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout_13 = new QHBoxLayout(frame);
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        frame_2 = new QFrame(frame);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setFrameShape(QFrame::Box);
        frame_2->setFrameShadow(QFrame::Sunken);
        gridLayout_3 = new QGridLayout(frame_2);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label = new QLabel(frame_2);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_3->addWidget(label, 0, 0, 1, 1);


        horizontalLayout_13->addWidget(frame_2);

        label_3 = new QLabel(WidgetEstadisticas);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(40, 110, 761, 411));

        retranslateUi(WidgetEstadisticas);

        QMetaObject::connectSlotsByName(WidgetEstadisticas);
    } // setupUi

    void retranslateUi(QWidget *WidgetEstadisticas)
    {
        WidgetEstadisticas->setWindowTitle(QApplication::translate("WidgetEstadisticas", "Form", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("WidgetEstadisticas", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:26pt; font-weight:600;\">Estad\303\255sticas de compras</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_3->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class WidgetEstadisticas: public Ui_WidgetEstadisticas {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGETESTADISTICAS_H
