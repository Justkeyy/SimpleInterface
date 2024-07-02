#ifndef MINIGAMEDIALOG_H
#define MINIGAMEDIALOG_H

#include <QDialog>
#include <QObject>
#include <QWidget>
#include <QMouseEvent>
#include <QTimerEvent>
#include <QRandomGenerator>
#include <QPainter>
#include <QEvent>
#include <QMessageBox>
#include <QFile>

class MiniGameDialog : public QDialog
{
    Q_OBJECT

    int MyTimer{};
    QCursor* spCursor{};
    bool gameflag = true;
    bool isDrawing = false;
    QPoint M_point{};

    QPixmap Bugimg;
    QPoint BugPos = this->rect().center();
    int BugScaleSize = 50;

    struct MyRect
    {
        QPoint pnt1{};
        QPoint pnt2{};
        QRect M_currentRect{};
    };

    MyRect M_rect;

    // Пользовательское событие

    int evtype = QEvent::registerEventType();

    class myEvent2: public QEvent
    {
        int ev = QEvent::MaxUser;
    public:
        myEvent2():QEvent(static_cast<QEvent::Type>(ev)){};
        int gettype () {return ev;};
    };

public:
    MiniGameDialog();
    ~MiniGameDialog();

    // QWidget interface
protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void timerEvent(QTimerEvent *event);
    virtual void paintEvent(QPaintEvent *event);
// Пользовательский обработчик
  //virtual bool event(QEvent *event);
    virtual void customEvent(QEvent *event);
};

#endif // MINIGAMEDIALOG_H
