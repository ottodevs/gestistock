/********************************************************************************
** Form generated from reading UI file 'widgetlistacompra.ui'
**
** Created: Fri 20. Jul 17:52:38 2012
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGETLISTACOMPRA_H
#define UI_WIDGETLISTACOMPRA_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLCDNumber>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QTableWidget>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WindowListaCompra
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_3;
    QFrame *frame;
    QVBoxLayout *verticalLayout;
    QFrame *frame_2;
    QGridLayout *gridLayout;
    QLabel *label;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_8;
    QHBoxLayout *horizontalLayout;
    QLabel *label_4;
    QLineEdit *lineEdit_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_5;
    QLineEdit *lineEdit_3;
    QHBoxLayout *horizontalLayout_7;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_9;
    QLineEdit *lineEdit_7;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_6;
    QLineEdit *lineEdit_4;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_8;
    QLineEdit *lineEdit_6;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_7;
    QLineEdit *lineEdit_5;
    QVBoxLayout *verticalLayout_4;
    QTableWidget *twArticulos;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_3;
    QLCDNumber *lcdNumber;
    QMenuBar *menubar;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *WindowListaCompra)
    {
        if (WindowListaCompra->objectName().isEmpty())
            WindowListaCompra->setObjectName(QString::fromUtf8("WindowListaCompra"));
        WindowListaCompra->resize(988, 641);
        centralwidget = new QWidget(WindowListaCompra);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_3 = new QGridLayout(centralwidget);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        frame = new QFrame(centralwidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(frame);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        frame_2 = new QFrame(frame);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setFrameShape(QFrame::Box);
        frame_2->setFrameShadow(QFrame::Sunken);
        gridLayout = new QGridLayout(frame_2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(frame_2);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMinimumSize(QSize(321, 42));
        label->setMaximumSize(QSize(321, 42));

        gridLayout->addWidget(label, 0, 0, 1, 1);


        verticalLayout->addWidget(frame_2);


        gridLayout_3->addWidget(frame, 0, 0, 1, 1);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setMinimumSize(QSize(161, 151));
        label_2->setMaximumSize(QSize(161, 151));
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/imagenes/noimagen.png")));
        label_2->setScaledContents(true);

        horizontalLayout_9->addWidget(label_2);

        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setSizeConstraint(QLayout::SetFixedSize);
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);
        label_4->setMinimumSize(QSize(56, 13));
        label_4->setMaximumSize(QSize(56, 13));

        horizontalLayout->addWidget(label_4);

        lineEdit_2 = new QLineEdit(groupBox);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        sizePolicy.setHeightForWidth(lineEdit_2->sizePolicy().hasHeightForWidth());
        lineEdit_2->setSizePolicy(sizePolicy);
        lineEdit_2->setMinimumSize(QSize(131, 20));
        lineEdit_2->setMaximumSize(QSize(131, 20));

        horizontalLayout->addWidget(lineEdit_2);


        horizontalLayout_8->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy);
        label_5->setMinimumSize(QSize(54, 13));
        label_5->setMaximumSize(QSize(54, 13));

        horizontalLayout_2->addWidget(label_5);

        lineEdit_3 = new QLineEdit(groupBox);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        sizePolicy.setHeightForWidth(lineEdit_3->sizePolicy().hasHeightForWidth());
        lineEdit_3->setSizePolicy(sizePolicy);
        lineEdit_3->setMinimumSize(QSize(251, 20));
        lineEdit_3->setMaximumSize(QSize(251, 20));

        horizontalLayout_2->addWidget(lineEdit_3);


        horizontalLayout_8->addLayout(horizontalLayout_2);


        verticalLayout_2->addLayout(horizontalLayout_8);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        sizePolicy.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy);
        label_9->setMinimumSize(QSize(93, 13));
        label_9->setMaximumSize(QSize(93, 13));

        horizontalLayout_3->addWidget(label_9);

        lineEdit_7 = new QLineEdit(groupBox);
        lineEdit_7->setObjectName(QString::fromUtf8("lineEdit_7"));
        sizePolicy.setHeightForWidth(lineEdit_7->sizePolicy().hasHeightForWidth());
        lineEdit_7->setSizePolicy(sizePolicy);
        lineEdit_7->setMinimumSize(QSize(41, 20));
        lineEdit_7->setMaximumSize(QSize(41, 20));

        horizontalLayout_3->addWidget(lineEdit_7);


        horizontalLayout_7->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        sizePolicy.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy);
        label_6->setMinimumSize(QSize(29, 13));
        label_6->setMaximumSize(QSize(29, 13));

        horizontalLayout_4->addWidget(label_6);

        lineEdit_4 = new QLineEdit(groupBox);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));
        sizePolicy.setHeightForWidth(lineEdit_4->sizePolicy().hasHeightForWidth());
        lineEdit_4->setSizePolicy(sizePolicy);
        lineEdit_4->setMinimumSize(QSize(61, 20));
        lineEdit_4->setMaximumSize(QSize(61, 20));

        horizontalLayout_4->addWidget(lineEdit_4);


        horizontalLayout_7->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        sizePolicy.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy);
        label_8->setMinimumSize(QSize(23, 13));
        label_8->setMaximumSize(QSize(23, 13));

        horizontalLayout_5->addWidget(label_8);

        lineEdit_6 = new QLineEdit(groupBox);
        lineEdit_6->setObjectName(QString::fromUtf8("lineEdit_6"));
        sizePolicy.setHeightForWidth(lineEdit_6->sizePolicy().hasHeightForWidth());
        lineEdit_6->setSizePolicy(sizePolicy);
        lineEdit_6->setMinimumSize(QSize(31, 20));
        lineEdit_6->setMaximumSize(QSize(31, 20));

        horizontalLayout_5->addWidget(lineEdit_6);


        horizontalLayout_7->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        sizePolicy.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy);
        label_7->setMinimumSize(QSize(75, 13));
        label_7->setMaximumSize(QSize(75, 13));

        horizontalLayout_6->addWidget(label_7);

        lineEdit_5 = new QLineEdit(groupBox);
        lineEdit_5->setObjectName(QString::fromUtf8("lineEdit_5"));
        sizePolicy.setHeightForWidth(lineEdit_5->sizePolicy().hasHeightForWidth());
        lineEdit_5->setSizePolicy(sizePolicy);
        lineEdit_5->setMinimumSize(QSize(61, 20));
        lineEdit_5->setMaximumSize(QSize(61, 20));

        horizontalLayout_6->addWidget(lineEdit_5);


        horizontalLayout_7->addLayout(horizontalLayout_6);


        verticalLayout_2->addLayout(horizontalLayout_7);


        gridLayout_2->addLayout(verticalLayout_2, 0, 0, 1, 1);


        horizontalLayout_9->addWidget(groupBox);


        verticalLayout_5->addLayout(horizontalLayout_9);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        twArticulos = new QTableWidget(centralwidget);
        if (twArticulos->columnCount() < 3)
            twArticulos->setColumnCount(3);
        QFont font;
        font.setFamily(QString::fromUtf8("Microsoft Yi Baiti"));
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
        __qtablewidgetitem->setFont(font);
        twArticulos->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
        __qtablewidgetitem1->setFont(font);
        twArticulos->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
        __qtablewidgetitem2->setFont(font);
        twArticulos->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        twArticulos->setObjectName(QString::fromUtf8("twArticulos"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(twArticulos->sizePolicy().hasHeightForWidth());
        twArticulos->setSizePolicy(sizePolicy1);
        twArticulos->setMinimumSize(QSize(900, 0));
        twArticulos->setMaximumSize(QSize(900, 16777215));
        twArticulos->setFont(font);
        twArticulos->viewport()->setProperty("cursor", QVariant(QCursor(Qt::PointingHandCursor)));
        twArticulos->setFrameShape(QFrame::NoFrame);
        twArticulos->setFrameShadow(QFrame::Plain);
        twArticulos->setLineWidth(10);
        twArticulos->setEditTriggers(QAbstractItemView::NoEditTriggers);
        twArticulos->setDragDropOverwriteMode(true);
        twArticulos->setAlternatingRowColors(true);
        twArticulos->setSelectionMode(QAbstractItemView::NoSelection);
        twArticulos->setSelectionBehavior(QAbstractItemView::SelectItems);
        twArticulos->setTextElideMode(Qt::ElideLeft);
        twArticulos->setShowGrid(true);
        twArticulos->setGridStyle(Qt::SolidLine);
        twArticulos->setSortingEnabled(false);
        twArticulos->horizontalHeader()->setStretchLastSection(true);
        twArticulos->verticalHeader()->setVisible(false);
        twArticulos->verticalHeader()->setDefaultSectionSize(30);

        verticalLayout_4->addWidget(twArticulos);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);
        label_3->setMinimumSize(QSize(95, 13));
        label_3->setMaximumSize(QSize(95, 13));

        verticalLayout_3->addWidget(label_3);

        lcdNumber = new QLCDNumber(centralwidget);
        lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));
        sizePolicy.setHeightForWidth(lcdNumber->sizePolicy().hasHeightForWidth());
        lcdNumber->setSizePolicy(sizePolicy);
        lcdNumber->setMinimumSize(QSize(111, 41));
        lcdNumber->setMaximumSize(QSize(111, 41));

        verticalLayout_3->addWidget(lcdNumber);


        verticalLayout_4->addLayout(verticalLayout_3);


        verticalLayout_5->addLayout(verticalLayout_4);


        gridLayout_3->addLayout(verticalLayout_5, 1, 0, 1, 1);

        WindowListaCompra->setCentralWidget(centralwidget);
        menubar = new QMenuBar(WindowListaCompra);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 988, 21));
        WindowListaCompra->setMenuBar(menubar);
        statusbar = new QStatusBar(WindowListaCompra);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        WindowListaCompra->setStatusBar(statusbar);
        toolBar = new QToolBar(WindowListaCompra);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        WindowListaCompra->addToolBar(Qt::TopToolBarArea, toolBar);

        retranslateUi(WindowListaCompra);

        QMetaObject::connectSlotsByName(WindowListaCompra);
    } // setupUi

    void retranslateUi(QMainWindow *WindowListaCompra)
    {
        WindowListaCompra->setWindowTitle(QApplication::translate("WindowListaCompra", "MainWindow", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("WindowListaCompra", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:26pt; font-weight:600;\">Lista de la compra</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_2->setText(QString());
        groupBox->setTitle(QApplication::translate("WindowListaCompra", "Datos Art\303\255culo", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("WindowListaCompra", "C\303\263digo EAN", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("WindowListaCompra", "Descripci\303\263n", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("WindowListaCompra", "Cantidad disponible", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("WindowListaCompra", "Precio", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("WindowListaCompra", "I.V.A", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("WindowListaCompra", "Precio con I.V.A", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = twArticulos->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("WindowListaCompra", "C\303\263digo EAN", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = twArticulos->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("WindowListaCompra", "Descripci\303\263n", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = twArticulos->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("WindowListaCompra", "Precio", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("WindowListaCompra", "N\303\272mero de art\303\255culos", 0, QApplication::UnicodeUTF8));
        toolBar->setWindowTitle(QApplication::translate("WindowListaCompra", "toolBar", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class WindowListaCompra: public Ui_WindowListaCompra {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGETLISTACOMPRA_H
