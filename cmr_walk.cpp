#include <QPainter>
#include <QApplication>
#include <stdlib.h>
#include "cmr_walk.h"
#include "cmr_fight.h"
#include <ctime>

walk::walk(QWidget *parent)
    : QWidget(parent)
{
    //seed the randomizers
    srand(time(NULL));
    x = 0;
    y = 0;

    speed = 1;
    gameStarted = false;
    paused = false;
    //allocation for objects
    player = new Player();
    player->print();
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
    //frees memory
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
    //creates painter objects with this class as the target
    QPainter painter(this);
    //calls drawing function with painter class
    drawObjects(&painter);

}



void walk::drawObjects(QPainter *painter){
    //paints dirt then grass then player then walls
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
    //used to help fix collisions of the player with the walls
    player->setDx(0);
    player->setDy(0);
    moveObjects();
}

void walk::timerEvent(QTimerEvent *e){
    Q_UNUSED(e);
    //moves the player 40 times with speed one, hence 40 pixels or one grass width
    //creates movement 'animation'
    for(int i = 0; i < 40; i++){
        moveObjects();//moves
        checkCollision();//checks for a collision with either walls or grass
        //repaints
        repaint();
    }
    //checks for whether encounter conditions are met
    encounter();
    //stops movement of player
    stopObjects();
    healthCheck();
}

void walk::moveObjects(){
    //moves the player
    player->move();

}

void walk::keyReleaseEvent(QKeyEvent *e){

    int dx = 0;
    int dy = 0;
    //takes the input of the arrow keys and stops the movement
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
    //takes input of the arrow keys and either starts movement or changes gamestate to paused or closed
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
    //starts game after space is pressed, resets player to mid screen
    if(!gameStarted) {
        player->resetState();
        gameStarted = true;
        //starts time with predetermined delay
        timerId = startTimer(DELAY);
    }
}

void walk::pauseGame() {
    //pauses and unpauses game (toggle)
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
    // strictly unpauses the game and resets the console
    if (paused) {
        timerId = startTimer(DELAY);
        paused = false;
        window2->clearConsole();
        player->print();
    }
}
void walk::healthCheck(){
    int check = 0;
    //checks how many pokemon are dead
    for(int i = 0; i < player->getPartySize(); i++){
        if(player->getPokemon(i)->getHealth() < 0){
            check ++;
        }
    }
    //if all pokemon are dead ends the game
    if(check == player->getPartySize()){
        window2->clearConsole();
        cout << "        ******** All pokemon dead ********         " << endl;
        stopGame();
    }
}
void walk::stopGame() {
    killTimer(timerId);
    //ends game
    gameStarted = false;
}


void walk::checkCollision(){
    //checks each wall for interaction
    for(int i =0; i < N_OF_WALLS; i++){
        if(player->getRect().intersects(walls[i]->getRect())){ // if there is collision
            int x = player->getRect().x();
            int y = player->getRect().y();
            if((player->getDx() != 0)){ // gives direction of new velocity for player to be towards the center always
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
            if(player->getDy() != 0){// makes new direction towards center, this implementation limits collision to be towards the center
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
            player->move();//moves and stops player movement
            stopObjects();
        }
    }
}

void walk::encounter(){
    for(int i=0; i < N_OF_GRASS; i++){//checks each grass tile for interaction
        if((player->getRect().intersects(grassTiles[i]->getRect()))  &&//checks for overlap of tiles and for movement in player
                ((player->getDx() !=0) || (player->getDy() !=0))){     //otherwise fights would start indefinitly while idling
            if(rand()%999 > 950){ // small chance to trigger a fight
                window2 = new fight(player);//new window is made for the fight sequence
                connect(window2, SIGNAL(finished()), window2, SLOT(deleteLater()));//signals emitted from window2 //deletes on closing
                connect(window2, SIGNAL(finished()), this, SLOT(unPause()));//signal emitted from window2 // unpauses on closing
                window2->resize(480,600);
                window2->setWindowTitle("Fight!");
                pauseGame();
                window2->show();



            }
        }
    }
}





