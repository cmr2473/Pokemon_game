#ifndef WALK_H
#define WALK_H

#include <QWidget>
#include <QKeyEvent>
#include "cmr_player.h"
#include "cmr_wall.h"
#include "cmr_floor.h"
#include "cmr_grass.h"
#include "cmr_fight.h"
class walk : public QWidget
{
    Q_OBJECT
public:

    walk(QWidget *parent = 0);
    ~walk();

protected:
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);
    void drawObjects(QPainter *);

    void moveObjects();
    void stopObjects();
    void encounter();


    void startGame();
    void pauseGame();
    void stopGame();

    void checkCollision();


private:
    int x,y,speed;
    int timerId;
    static const int X_OF_DIRT = 13;
    static const int Y_OF_DIRT = 16;
    static const int N_OF_GRASS = 44;
    static const int N_OF_WALLS = 4;
    static const int DELAY = 5;
    static const int BOTTOM_EDGE = 400;

    grass * grassTiles[N_OF_GRASS];
    wall * walls[N_OF_WALLS];
    floor * dirt[X_OF_DIRT * Y_OF_DIRT];
    Player * player;

    bool gameStarted;
    bool paused;
    fight * window2;
private slots:
    void unPause();


};
#endif // WALK_H
