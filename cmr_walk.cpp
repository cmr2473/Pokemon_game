#include <QPainter>
#include <QApplication>
#include <stdlib.h>
#include "cmr_walk.h"
#include "cmr_fight.h"
#include <ctime>

walk::walk(QWidget *parent)
    : QWidget(parent)
{
    srand(time(NULL));
    x = 0;
    y = 0;

    speed = 1;
    gameStarted = false;
    paused = false;

    player = new Player();

    walls[0] = new wall(-20, 0);
    walls[1] = new wall(460, 0);
    walls[2] = new wall(0, -20,1);
    walls[3] = new wall(0,580,1);

    int k =0;
    for(int i = 0; i < X_OF_DIRT; i++){
        for(int j =0; j < Y_OF_DIRT; j++){
            dirt[k] = new class floor(20 + 40 * i, 40 * j);
            k ++;
        }
    }
    k=0;
    for(int i = 0 ; i < 4; i++){
        for( int j = 0; j < 10-i; j++){
            grassTiles[k] = new grass(20+j * 40, 40 * i );
            k++;
        }
        for( int j = 0; j < 4-i; j++){
            grassTiles[k] = new grass(20+j * 40, 160 + 40 * i );
            k++;
        }
    }

    cout << "****   press 'space' to start the game   ****" << endl;
}

walk::~walk(){
    delete player;
    for(int i = 0 ; i < N_OF_WALLS; i++){
        delete walls[i];
    }
    for(int i = 0 ; i < N_OF_GRASS; i++){
        delete grassTiles[i];
    }
    for(int i = 0 ; i < X_OF_DIRT * Y_OF_DIRT; i++){
        delete dirt[i];
    }
}

void walk::paintEvent(QPaintEvent *e){
    Q_UNUSED(e);

    QPainter painter(this);

    drawObjects(&painter);

}



void walk::drawObjects(QPainter *painter){
    for(int i = 0; i < X_OF_DIRT * Y_OF_DIRT; i++){
        painter->drawImage(dirt[i]->getRect(),dirt[i]->getImage());
    }
    for(int i = 0; i < N_OF_GRASS; i++){
        painter->drawImage(grassTiles[i]->getRect(),grassTiles[i]->getImage());
    }
    painter->drawImage(player->getRect(), player->getImage());
    for(int i = 0; i < N_OF_WALLS ; i++){
        painter->drawImage(walls[i]->getRect(),walls[i]->getImage());
    }
}
void walk::stopObjects(){
    player->setDx(0);
    player->setDy(0);
    moveObjects();
}

void walk::timerEvent(QTimerEvent *e){
    Q_UNUSED(e);
    for(int i = 0; i < 40; i++){
        moveObjects();
        checkCollision();
        //stopObjects();
        repaint();
    }
    encounter();
    stopObjects();
}

void walk::moveObjects(){

    player->move();

}

void walk::keyReleaseEvent(QKeyEvent *e){

    int dx = 0;
    int dy = 0;

    switch (e->key()){
    case Qt::Key_Left:
        dx = 0;
        player->setDx(dx);
        break;
    case Qt::Key_Right:
        dx = 0;
        player->setDx(dx);
        break;
    case Qt::Key_Up:
        dy = 0;
        player->setDy(dy);
        break;
    case Qt::Key_Down:
        dy = 0;
        player->setDy(dy);
        break;
    }


}

void walk::keyPressEvent(QKeyEvent *e) {
    int dx = 0;
    int dy = 0;

    switch (e->key()){
    case Qt::Key_Left:
        dx = -speed;
        player->setDx(dx);
        break;
    case Qt::Key_Right:
        dx = speed;
        player->setDx(dx);
        break;
    case Qt::Key_Up:
        dy = -speed;
        player->setDy(dy);
        break;
    case Qt::Key_Down:
        dy = speed;
        player->setDy(dy);
        break;
    case Qt::Key_P:

        pauseGame();
        break;
    case Qt::Key_Space:

        startGame();
        break;
    case Qt::Key_Escape:

        qApp->exit();
        break;
    default:
        QWidget::keyPressEvent(e);
    }
}

void walk::startGame(){
    if(!gameStarted) {
        player->resetState();


        gameStarted = true;
        timerId = startTimer(DELAY);
    }
}

void walk::pauseGame() {
    if (paused) {
        timerId = startTimer(DELAY);
        paused = false;
    }
    else{
        paused = true;
        killTimer(timerId);
    }
}

void walk::unPause(){
    if (paused) {
        timerId = startTimer(DELAY);
        paused = false;
    }
}

void walk::stopGame() {
    killTimer(timerId);

    gameStarted = false;
}


void walk::checkCollision(){
    for(int i =0; i < N_OF_WALLS; i++){
        if(player->getRect().intersects(walls[i]->getRect())){
            int x = player->getRect().x();
            int y = player->getRect().y();
            if((player->getDx() != 0)){
                int j = 250-x;
                int k;
                if(j < 0){
                    k = -1;
                }
                else{
                    k = 1;
                }
                player->setDx( k * speed);
            }
            if(player->getDy() != 0){
                int j = 300-y;
                int k;
                if(j < 0){
                    k = -1;
                }
                else{
                    k = 1;
                }
                player->setDy(k*speed);
            }
            player->move();
            stopObjects();
        }
    }
}

void walk::encounter(){
    for(int i=0; i < N_OF_GRASS; i++){
        if((player->getRect().intersects(grassTiles[i]->getRect()))  &&
                ((player->getDx() !=0) || (player->getDy() !=0))){
            if(rand()%999 > 969){
                window2 = new fight(player);
                connect(window2, SIGNAL(finished()), window2, SLOT(deleteLater()));
                connect(window2, SIGNAL(finished()), this, SLOT(unPause()));
                window2->resize(480,600);
                window2->setWindowTitle("Fight!");
                pauseGame();
                window2->show();



            }
        }
    }
}




