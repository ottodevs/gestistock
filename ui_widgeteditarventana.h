/********************************************************************************
** Form generated from reading UI file 'widgeteditarventana.ui'
**
** Created: Fri 17. Aug 12:39:52 2012
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGETEDITARVENTANA_H
#define UI_WIDGETEDITARVENTANA_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WidgetEditarVentana
{
public:

    void setupUi(QWidget *WidgetEditarVentana)
    {
        if (WidgetEditarVentana->objectName().isEmpty())
            WidgetEditarVentana->setObjectName(QString::fromUtf8("WidgetEditarVentana"));
        WidgetEditarVentana->resize(640, 480);

        retranslateUi(WidgetEditarVentana);

        QMetaObject::connectSlotsByName(WidgetEditarVentana);
    } // setupUi

    void retranslateUi(QWidget *WidgetEditarVentana)
    {
        WidgetEditarVentana->setWindowTitle(QApplication::translate("WidgetEditarVentana", "Form", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class WidgetEditarVentana: public Ui_WidgetEditarVentana {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGETEDITARVENTANA_H
