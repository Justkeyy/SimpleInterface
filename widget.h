#ifndef SIGSLOT_H
#define SIGSLOT_H

#include <QWidget>
#include <QPushButton>
#include <QFrame>
#include <QLineEdit>
#include <QSpinBox>
#include <QSlider>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLayout>
#include <QString>
#include <QComboBox>
#include <QFile>
#include <QEvent>
#include <QKeyEvent>

#include "minigamedialog.h"

class SigSlotLay : public QWidget
{
    Q_OBJECT

public:
    SigSlotLay(QWidget *parent = nullptr);
    ~SigSlotLay();

    void mysetFlags();
    void mysetGeometry(QLayout* layout);

    QPushButton * CreateExitButton ();
    QPushButton * CreateDisableButton ();
    QPushButton * CreateStyleButton ();

    QFrame* CreateFrame (QWidget* parent = nullptr);
    QLineEdit* CreateLine (QWidget* parent = nullptr);
    QSpinBox* CreateSpinBox (QWidget* parent = nullptr);
    QSlider* CreateSlider (Qt::Orientation orientation, QWidget* parent = nullptr);
    QLabel* CreateLabel (QString str, QWidget* parent = nullptr);
    QComboBox* CreateComboBox(QWidget* parent = nullptr);


    QVBoxLayout* CreateBVLayout (QWidget* parent = nullptr);
    QHBoxLayout* CreateHBoxLayout (QWidget* parent = nullptr);
    QVBoxLayout* CreateVBoxLayout (QWidget* parent = nullptr);
    QGridLayout* CreateGridLayout (QWidget* parent = nullptr);

signals:
    void mySignal(int);
    void signalChangeLayout(int);

public slots:
    void mySlot(QString str);
    void slotChangeLayout(int index);
    void slotSetDisabled(bool);
    void slotSetStyle(bool);

private:

    QPushButton * buttonExit;
    QPushButton * buttonDisable;
    QPushButton * buttonStyle;

    QFrame * MyFrame;
    QLineEdit * MyLine;
    QLabel * MyLabel;
    QSpinBox * MySpinBox;
    QSlider * MySlider;
    QComboBox * MyComboBox;

    QLabel * MyTipLabel;

    QVBoxLayout* MyGameLayout = new QVBoxLayout(this);

    QHBoxLayout* MyMainLayout;

    QVBoxLayout* MyBVLayout;
    QVBoxLayout* MyCVLayout;
    QHBoxLayout* MyCHLayout;
    QGridLayout* MyCGLayout;

    QString stylesheet;

    // QObject interface

protected:
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
};

class mySlotfunctor
{
public:
    void operator() (QString str)
    {
        int number= str.toInt();
        qDebug() << number;
    }
};

// class mySlotfunctor1: public QObject
// {
//     Q_OBJECT

// signals:
//     void mySignal(int);

// public:

//     void operator() (QString str)
//     {
//         int number= str.toInt();
//         qDebug() << number;
//         emit mySignal(number);
//     }

//     Q_DISABLE_COPY_MOVE(mySlotfunctor1)

// };

#endif // SIGSLOT_H
