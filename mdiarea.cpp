#include "mdiarea.h"

MdiArea::MdiArea(QImage backgroundImage, QBrush backgroundBrush)
{
    i = backgroundImage;
    b = backgroundBrush;
}

void MdiArea::resizeEvent(QResizeEvent *resizeEvent)
{
    QImage newBackground(resizeEvent->size(), QImage::Format_ARGB32_Premultiplied);
    QPainter p(&newBackground);
    p.fillRect(newBackground.rect(), b);

    QImage scaled = i.scaled(resizeEvent->size(),Qt::KeepAspectRatio);
    QRect scaledRect = scaled.rect();
    scaledRect.moveCenter(newBackground.rect().center());
    p.drawImage(scaledRect, scaled);
    setBackground(newBackground);
    QMdiArea::resizeEvent(resizeEvent);
}
