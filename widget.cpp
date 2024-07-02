#include "widget.h"
#include <QGuiApplication>
#include <QScreen>
#include <string>
#include <QDebug>
#include <QValidator>
#include <QStyleFactory>
#include <QApplication>

void SigSlotLay::mysetFlags()
{

    Qt::WindowFlags spFlags = this->windowFlags();

    spFlags = Qt::Window;
    spFlags |= Qt::CustomizeWindowHint;
    spFlags |= Qt::WindowTitleHint;
    spFlags |= Qt::WindowSystemMenuHint;

    this->setWindowFlags(spFlags);
}

QPushButton * SigSlotLay::CreateExitButton ()
{
    QPushButton * buttonExit = new QPushButton(QObject::tr("Exit"));
    buttonExit->setObjectName("ExitButton");
    buttonExit->setSizePolicy(QSizePolicy::Fixed , QSizePolicy::Fixed);
    QObject::connect(buttonExit, SIGNAL(clicked(bool)), this, SLOT(close()));
    return buttonExit;
}

QPushButton * SigSlotLay::CreateDisableButton ()
{
    QPushButton * buttonDisable = new QPushButton(QObject::tr("Disable"));
    buttonDisable->setObjectName("DisableButton");
    buttonDisable->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    QObject::connect(buttonDisable, SIGNAL(clicked(bool)), this, SLOT(slotSetDisabled(bool)));
    return buttonDisable;
}

QPushButton * SigSlotLay::CreateStyleButton ()
{
    QPushButton * buttonStyle = new QPushButton(QObject::tr("Fusion style"));
    buttonStyle->setObjectName("StyleButton");
    buttonStyle->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    QObject::connect(buttonStyle, SIGNAL(clicked(bool)), this, SLOT(slotSetStyle(bool)));
    return buttonStyle;
}


QFrame* SigSlotLay::CreateFrame (QWidget* parent)
{
    return new QFrame (parent);
}

QLineEdit* SigSlotLay::CreateLine (QWidget* parent)
{
    QLineEdit* temp = new QLineEdit(parent);
    QIntValidator *lineval = new QIntValidator(0, 50, temp);
    temp->setValidator(lineval);
    return temp;
}

QSpinBox* SigSlotLay::CreateSpinBox (QWidget* parent)
{
    QSpinBox * temp = new QSpinBox(parent);
    temp->setMaximum(50);
    temp->setValue(10);
    temp->setFixedSize(temp->sizeHint());
    return temp;
}

QSlider* SigSlotLay::CreateSlider (Qt::Orientation orientation, QWidget* parent)
{
    QSlider* temp = new QSlider(orientation, parent);
    temp->setRange(0, 50);
    temp->setSliderPosition(10);
    temp->setTickPosition(QSlider::TicksBothSides);
    temp->setTickInterval(10);
    temp->setSingleStep(1);
    temp->setMinimumWidth(50);
    return temp;
}

QLabel* SigSlotLay::CreateLabel (QString str, QWidget* parent)
{
    QLabel * temp = new QLabel (QObject::tr(str.toStdString().c_str()), parent);
    temp->setFrameStyle(1);
    temp->setMinimumWidth(40);
    temp->setMaximumHeight(20);
    temp->setAlignment(Qt::AlignCenter);

    return temp;
}

QComboBox* SigSlotLay::CreateComboBox(QWidget* parent)
{
    QComboBox * temp = new QComboBox(parent);
    temp->addItem(QString("Vertical"));
    temp->addItem(QString("Horizontal"));
    temp->addItem(QString("Grid"));

    return temp;
}

QVBoxLayout* SigSlotLay::CreateBVLayout (QWidget* parent)
{
    QVBoxLayout* temp = new QVBoxLayout(parent);
    temp->addWidget(MyComboBox);
    temp->addWidget(buttonExit/*, 1, Qt::AlignCenter*/);
    temp->addWidget(buttonDisable/*, 1, Qt::AlignCenter*/);
    temp->addWidget(buttonStyle/*, 1, Qt::AlignCenter*/);
    return temp;
}

QHBoxLayout* SigSlotLay::CreateHBoxLayout (QWidget* parent)
{
    QHBoxLayout* temp = new QHBoxLayout(parent);
    temp->addWidget(MyLabel);
    temp->addWidget(MyLine);
    temp->addWidget(MySpinBox);
    temp->addWidget(MySlider);
    return temp;
}

QVBoxLayout* SigSlotLay::CreateVBoxLayout (QWidget* parent)
{
    QVBoxLayout* temp = new QVBoxLayout(parent);
    temp->addWidget(MyLabel, 1, Qt::AlignCenter);
    temp->addWidget(MyLine, 1, Qt::AlignCenter);
    temp->addWidget(MySpinBox, 1, Qt::AlignCenter);
    temp->addWidget(MySlider);
    return temp;
}



QGridLayout* SigSlotLay::CreateGridLayout (QWidget* parent)
{
    QGridLayout* temp = new QGridLayout(parent);
    temp->addWidget(MySpinBox, 0, 0, Qt::AlignCenter);
    temp->addWidget(MySlider, 0, 1);
    temp->addWidget(MyLine, 1, 0, Qt::AlignCenter);
    temp->addWidget(MyLabel, 1, 1, Qt::AlignCenter);
    return temp;
}

void SigSlotLay::mysetGeometry(QLayout* layout)
{
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screengeom = screen->availableGeometry();
    QPoint centerp = screengeom.center();
    QSize size = layout->sizeHint();
    this->setGeometry(centerp.x(), centerp.y(), size.width(),size.height());
}

 void SigSlotLay::mySlot(QString str)
 {
    int number= str.toInt();
    emit mySignal(number);
 }

 void SigSlotLay::slotChangeLayout(int index)
 {
     delete MyFrame->layout();
    // delete MyBVLayout;
    // delete MyMainLayout;

    // MyMainLayout = new QHBoxLayout(this);

     if(index == 0)
     {
         MyCVLayout = CreateVBoxLayout();
         MyFrame->setLayout(MyCVLayout);
         MyCVLayout->activate();
     }
     if(index == 1)
     {
         MyCHLayout = CreateHBoxLayout(MyFrame);
         //MyFrame->setLayout(MyCHLayout);
        // MyCHLayout->activate();
     }
     if(index == 2)
     {
         MyCGLayout = CreateGridLayout();
         MyFrame->setLayout(MyCGLayout);
         MyCGLayout->activate();
     }

   //  MyBVLayout = CreateBVLayout();

   //  MyMainLayout->addWidget(MyFrame);
   //  MyMainLayout->addLayout(MyBVLayout);
 }

 void SigSlotLay::slotSetDisabled(bool)
 {
     if (buttonDisable->text() == "Disable")
     {
         buttonDisable->setText("Enable");
         MyFrame->setEnabled(false);
     }
     else
     {
         buttonDisable->setText("Disable");
         MyFrame->setEnabled(true);
     }
 }

 void SigSlotLay::slotSetStyle(bool)
 {
    // qDebug()<<QStyleFactory::keys();
     if (buttonStyle->text() == "Fusion style")
     {
        buttonStyle->setText("Windows style");
        QApplication::setStyle(QStyleFactory::create("Fusion"));
     }
     else
     {
        buttonStyle->setText("Fusion style");
        QApplication::setStyle(QStyleFactory::create("windowsvista"));
     }
 }

 void SigSlotLay::keyPressEvent(QKeyEvent *event)
 {
     if (event->key() == Qt::Key_S)
     {
         MiniGameDialog *dlg = new MiniGameDialog();
         dlg->exec();
     }
 }

 void SigSlotLay::mousePressEvent(QMouseEvent *event)
 {
    this->setFocus();
 }




SigSlotLay::SigSlotLay(QWidget *parent)
    : QWidget(parent)
{
    mysetFlags(); // Настройка окна
    MyFrame = CreateFrame(this);
    MyFrame->setFrameStyle(QFrame::Panel | QFrame::Plain);

    MyLabel = CreateLabel(QObject::tr(" "));
    MyLabel->setObjectName("MyLabel");

    MyLine = CreateLine();
    MyLine->setObjectName("MyLine");

    MySpinBox = CreateSpinBox();
    MySpinBox->setObjectName("MySpinBox");

    MySlider = CreateSlider(Qt::Orientation::Horizontal);
    MySlider->setObjectName("MySlider");
    MySlider->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    MyComboBox = CreateComboBox();
    MyComboBox->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    MyTipLabel = new QLabel;
    MyTipLabel->setFrameStyle(1);
    MyTipLabel->setObjectName("TipForGame");
    MyTipLabel->setText("To start a game - press S!");


    //Кнопки
    buttonExit = CreateExitButton ();
    buttonDisable = CreateDisableButton ();
    buttonStyle = CreateStyleButton ();

    //Установка связей

#if 1 //старая форма connect
    QObject::connect(MyComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slotChangeLayout(int)));

    QObject::connect(MySpinBox, SIGNAL(valueChanged(int)), MySlider, SLOT(setValue(int)));
  //  QObject::connect(MySpinBox, SIGNAL(valueChanged(int)), this, SLOT(mySlot2(int))); //!!!!!

    QObject::connect(MySpinBox, SIGNAL(textChanged(QString)), MyLine, SLOT(setText(QString)));
    QObject::connect(MySpinBox, SIGNAL(textChanged(QString)), MyLabel, SLOT(setText(QString)));

    QObject::connect(MySlider, SIGNAL(valueChanged(int)), MySpinBox, SLOT(setValue(int)));

    QObject::connect(MyLine, SIGNAL(textChanged(QString)), this, SLOT(mySlot(QString)));

    QObject::connect(this, SIGNAL(signalChangeLayout(int)), MyComboBox, SLOT(setCurrentIndex(int)));
//    QObject::connect(this, SIGNAL(mySignal2(QString)), MyLine, SLOT(setText(QString)));
//    QObject::connect(this, SIGNAL(mySignal2(QString)), MyLabel, SLOT(setText(QString)));
    QObject::connect(this, SIGNAL(mySignal(int)), MySpinBox, SLOT(setValue(int)));
//    QObject::connect(this, SIGNAL(mySignal(int)), MySlider, SLOT(setValue(int)));
#endif

#if 1 //новая форма connect
     QObject::connect(MyLine, &QLineEdit::textChanged, mySlotfunctor());
//     QObject::connect(MyLine, &QLineEdit::textChanged, mySlotfunctor1());
#endif

    //Компановки

    MyMainLayout = new QHBoxLayout();

    MyBVLayout = CreateBVLayout();
    MyCVLayout = CreateVBoxLayout();

    MyFrame->setLayout(MyCVLayout);

    MyMainLayout->addWidget(MyFrame);
    MyMainLayout->addLayout(MyBVLayout);

    MyGameLayout->addLayout(MyMainLayout);
    MyGameLayout->addWidget(MyTipLabel);

    // Стиль

    QFile file("style.qss");
    file.open(QFile::ReadOnly);
    stylesheet = file.readAll();
    qApp->setStyleSheet(stylesheet);
    qDebug()<<stylesheet;
   // mysetGeometry(MyMainLayout);


    QPixmap IconPix(".\\Images_lab1\\ruler.png");
    IconPix.setMask(QBitmap(".\\Images_lab1\\ruler.png"));

    QIcon myicon(IconPix);
    this->setWindowIcon(myicon);

    this->dumpObjectTree();

    MySpinBox->setValue(19);

}

SigSlotLay::~SigSlotLay() {}
