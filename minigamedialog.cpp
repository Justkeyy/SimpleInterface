#include "minigamedialog.h"

MiniGameDialog::MiniGameDialog()
{
  this->setStatusTip("Catch the bug!");
  spCursor = new QCursor(Qt::PointingHandCursor);
  this->setCursor(*spCursor);

  Bugimg = QPixmap(".\\Images_lab1\\bug.png");
  Bugimg.setMask(QBitmap(".\\Images_lab1\\bug.png"));

  QIcon myicon(Bugimg);
  this->setWindowIcon(myicon);

  MyTimer = this->startTimer(10);


}

void MiniGameDialog::mousePressEvent(QMouseEvent *event)
{
    M_point = event->pos();

    if (event->button() == Qt::LeftButton)
    {
        isDrawing = true;

        M_rect.pnt1 = M_point;
        M_rect.pnt2 = M_point;
        M_rect.M_currentRect = QRect(M_rect.pnt1, M_rect.pnt2);
    }
}

void MiniGameDialog::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        isDrawing = false;
        bool cont = M_rect.M_currentRect.contains(QRect(BugPos.x(), BugPos.y(), BugScaleSize, BugScaleSize));
        qDebug() << cont;
         qDebug() << M_rect.M_currentRect;
          qDebug() << QRect(BugPos.x(), BugPos.y(), BugScaleSize, BugScaleSize);
        if (cont)
        {
            isDrawing = false;
            qDebug() << "Are you wining, son?";
            this->killTimer(MyTimer);

            #if 1 // Вариант 1
            QEvent* myEvent = new QEvent(static_cast<QEvent::Type>(evtype)); // для отправки в очередь (post event)
            QCoreApplication::postEvent(this ,myEvent);
            #endif

            #if 1 // Вариант 2
            myEvent2 ev2 = myEvent2(); // для неотложной отправки и обработки (send event)
            QCoreApplication::sendEvent(this, &ev2);
            #endif

        }
    }
}

void MiniGameDialog::mouseMoveEvent(QMouseEvent *event)
{
    M_point = event->pos();

    if (isDrawing == true)
    {
        M_rect.pnt2 = M_point;
        M_rect.M_currentRect = QRect(M_rect.pnt1, M_rect.pnt2);
    }

    if (!this->rect().contains(M_point))
    {
        spCursor->setPos(this->mapToGlobal(QPoint(this->rect().center())));
    }

    if (isDrawing == true)
    {
        QWidget::repaint();
    }

}

void MiniGameDialog::timerEvent(QTimerEvent *event)
{
    int Tid = event->timerId();

    if (Tid == MyTimer)
    {

        QRandomGenerator gen(time(NULL));
        int rand1 = (gen.generate()%(this->width()))-2;
        int rand2 = (gen.generate()%(this->height()))-2;

        BugPos = QPoint(rand1, rand2);

        QWidget::repaint();
    }

}

void MiniGameDialog::paintEvent(QPaintEvent *event)
{
    QPainter painter (this);

    QPen RectPen;
    QPainter RectPainter (this);
    RectPen.setWidth(2);
    RectPen.setColor(QColor(255,0,0,255));
    RectPainter.setPen(RectPen);

    painter.drawPixmap(BugPos,Bugimg.scaled(BugScaleSize, BugScaleSize, Qt::KeepAspectRatio));

    RectPainter.drawRect(M_rect.M_currentRect);

}

// bool MiniGameDialog::event(QEvent *event)
// {
//     if (event->type() == evtype)
//     {
//         qDebug() << "ev 1";
//         return true;
//     }

//     QDialog::event(event);
//     return false;
// }

void MiniGameDialog::customEvent(QEvent *event)
{
    if (event->type() == evtype)
         {
             qDebug() << "ev 1";

             QMessageBox mybox(this);
             mybox.setText("Congratulations! You won!!!");
             mybox.setWindowTitle("You won!");
             mybox.setIcon(QMessageBox::Information);
             QIcon myicon(Bugimg);
             mybox.setWindowIcon(myicon);

             mybox.exec();
             this->close();
         }

}

MiniGameDialog::~MiniGameDialog()
{
    if (spCursor)
    {
        delete spCursor;
        spCursor = nullptr;
    }
}

