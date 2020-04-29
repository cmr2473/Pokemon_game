#ifndef WALL_H
#define WALL_H


#include <QImage>
#include <QRect>

class wall
{
public:
    wall(int,int);
    wall(int,int,int);
    ~wall();

public:
    QRect getRect();
    void  setRect(QRect);
    QImage & getImage();

private:
    //image data
    QImage image;
    QRect rect;
};

#endif // WALL_H
