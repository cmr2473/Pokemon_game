#ifndef FLOOR_H
#define FLOOR_H

#include <QImage>
#include <QRect>


class floor
{
public:
    floor(int, int);
    ~floor();

public:
    QRect getRect();
    void  setRect(QRect);
    QImage & getImage();

protected:
    QImage image;
    QRect rect;

};

#endif // FLOOR_H
