/********************************************************************************
** Form generated from reading UI file 'fonts.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FONTS_H
#define UI_FONTS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Fonts
{
public:
    QWidget *centralWidget;
    QComboBox *fontSelectCB;
    QTableWidget *symbolsTW;
    QLabel *label;
    QLabel *paintQL;
    QCheckBox *displayTransparentCB;
    QSpinBox *meshSizeSpin;
    QPushButton *setMeshButton;
    QLabel *label_2;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Fonts)
    {
        if (Fonts->objectName().isEmpty())
            Fonts->setObjectName(QStringLiteral("Fonts"));
        Fonts->resize(1000, 600);
        Fonts->setMinimumSize(QSize(800, 600));
        centralWidget = new QWidget(Fonts);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        fontSelectCB = new QComboBox(centralWidget);
        fontSelectCB->setObjectName(QStringLiteral("fontSelectCB"));
        fontSelectCB->setGeometry(QRect(10, 20, 411, 22));
        symbolsTW = new QTableWidget(centralWidget);
        if (symbolsTW->columnCount() < 16)
            symbolsTW->setColumnCount(16);
        if (symbolsTW->rowCount() < 16)
            symbolsTW->setRowCount(16);
        symbolsTW->setObjectName(QStringLiteral("symbolsTW"));
        symbolsTW->setGeometry(QRect(10, 50, 450, 450));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(symbolsTW->sizePolicy().hasHeightForWidth());
        symbolsTW->setSizePolicy(sizePolicy);
        symbolsTW->setMaximumSize(QSize(450, 450));
        symbolsTW->setBaseSize(QSize(10, 10));
        symbolsTW->setLayoutDirection(Qt::LeftToRight);
        symbolsTW->setAutoFillBackground(false);
        symbolsTW->setInputMethodHints(Qt::ImhPreferLatin);
        symbolsTW->setFrameShape(QFrame::StyledPanel);
        symbolsTW->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContentsOnFirstShow);
        symbolsTW->setEditTriggers(QAbstractItemView::NoEditTriggers);
        symbolsTW->setRowCount(16);
        symbolsTW->setColumnCount(16);
        symbolsTW->horizontalHeader()->setVisible(false);
        symbolsTW->verticalHeader()->setVisible(false);
        symbolsTW->verticalHeader()->setHighlightSections(false);
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(500, 20, 381, 16));
        label->setMinimumSize(QSize(380, 16));
        paintQL = new QLabel(centralWidget);
        paintQL->setObjectName(QStringLiteral("paintQL"));
        paintQL->setGeometry(QRect(500, 80, 441, 451));
        paintQL->setMinimumSize(QSize(440, 450));
        displayTransparentCB = new QCheckBox(centralWidget);
        displayTransparentCB->setObjectName(QStringLiteral("displayTransparentCB"));
        displayTransparentCB->setGeometry(QRect(840, 40, 151, 17));
        meshSizeSpin = new QSpinBox(centralWidget);
        meshSizeSpin->setObjectName(QStringLiteral("meshSizeSpin"));
        meshSizeSpin->setGeometry(QRect(610, 40, 81, 22));
        setMeshButton = new QPushButton(centralWidget);
        setMeshButton->setObjectName(QStringLiteral("setMeshButton"));
        setMeshButton->setGeometry(QRect(700, 40, 75, 23));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(550, 40, 47, 21));
        Fonts->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Fonts);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1000, 21));
        Fonts->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Fonts);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Fonts->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Fonts);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Fonts->setStatusBar(statusBar);

        retranslateUi(Fonts);

        QMetaObject::connectSlotsByName(Fonts);
    } // setupUi

    void retranslateUi(QMainWindow *Fonts)
    {
        Fonts->setWindowTitle(QApplication::translate("Fonts", "Fonts", Q_NULLPTR));
        label->setText(QApplication::translate("Fonts", "TextLabel", Q_NULLPTR));
        paintQL->setText(QString());
        displayTransparentCB->setText(QApplication::translate("Fonts", "Display Transparent Lines", Q_NULLPTR));
        setMeshButton->setText(QApplication::translate("Fonts", "Set", Q_NULLPTR));
        label_2->setText(QApplication::translate("Fonts", "Cell Size:", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Fonts: public Ui_Fonts {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FONTS_H
