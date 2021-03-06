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
    //widget events for drawing and timer tests
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);
    void drawObjects(QPainter *);
    //move stop and collision checks
    void moveObjects();
    void stopObjects();
    void checkCollision();
    //random check for encounter when on grass
    void encounter();

    // changes in game state
    void startGame();
    void pauseGame();
    void stopGame();
    void healthCheck();



private:
    //movement and location of player
    int x,y,speed;
    //time counter
    int timerId;
    //constants
    static const int X_OF_DIRT = 13;
    static const int Y_OF_DIRT = 16;
    static const int N_OF_GRASS = 44;
    static const int N_OF_WALLS = 4;
    static const int DELAY = 5;
    static const int BOTTOM_EDGE = 400;
    //arrays for tilesets
    grass * grassTiles[N_OF_GRASS];
    wall * walls[N_OF_WALLS];
    floor * dirt[X_OF_DIRT * Y_OF_DIRT];
    //player
    Player * player;
    //gamestates
    bool gameStarted;
    bool paused;
    //seperate fight class for the fight gamestate
    fight * window2;
private slots:
    //slot to unpause after fight closes
    void unPause();



};
#endif // WALK_H
