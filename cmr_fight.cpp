#include "cmr_fight.h"
#include "cmr_player.h"
#include <iostream>
#include <string>
#include <QApplication>
#include <QPushButton>
#include <QPainter>
#include <QCoreApplication>
#include "cmr_walk.h"

//***************************************************************************Declarations and Deletes
fight::fight(class Player * p,QWidget *parent)
    : QMainWindow(parent)//initializes Qmainwindow, default is 0
{
    //sets game state parameters
    won = false;
    lost = false;
    changing = false;
    CurrentPoke = 0;
    player = p;
    //checks to make sure there are healthy pokemon in the party
    //starts the fight with the first healthy pokemon
    while((player->getPokemon(CurrentPoke)->getHealth() < 0)){
        CurrentPoke++;
        if(CurrentPoke == player->getPartySize())
        {
            cout << "no healthy Pokemon" << endl;
            lost = true;
        }
    }
    //creates enemy pokemon using random initialization number
    int l = rand()%POKECOUNT;
    enemy = new pokemon(l);
    //boosts enemy power to make the game harder
    enemy->setPower(20 + enemy->getPower());
    //prints enemy and player health
    clearConsole();
    print();

    // declares and connects initial buttons and swap buttons
    declareButtons();
    declareSwap();
    //hides swap buttons during initial
    hideSwap();
}
fight::~fight(){
    //deletes all new's
    delete enemy;
    deleteSwap();
    deleteButtons();
    //sets player state to not fighting
    player->setFightOpen(false);
}
void fight::declareButtons(){
    QString s = "";
    int i = 0;
    int j = 0;
    //each block initializes an attack button and attaches it to a attack handling slot

    s = QString::fromStdString(player->getPokemon(CurrentPoke)->getMove(0)->getname());
    attacks[0] = new QPushButton(s, this);
    attacks[0]->setGeometry(QRect(QPoint(60+200*i, 400 + 100 * j), QSize(150,75)));
    connect(attacks[0], SIGNAL (released()), this, SLOT(handleAttack1()));
    i++;
    s = QString::fromStdString(player->getPokemon(CurrentPoke)->getMove(1)->getname());
    attacks[1] = new QPushButton(s, this);
    attacks[1]->setGeometry(QRect(QPoint(60+200*i, 400 + 100 * j), QSize(150,75)));
    connect(attacks[1], SIGNAL (released()), this, SLOT(handleAttack2()));
    j++;
    s = QString::fromStdString(player->getPokemon(CurrentPoke)->getMove(2)->getname());
    attacks[2] = new QPushButton(s, this);
    attacks[2]->setGeometry(QRect(QPoint(60+200*i, 400 + 100 * j), QSize(150,75)));
    connect(attacks[2], SIGNAL (released()), this, SLOT(handleAttack3()));
    i--;
    s = QString::fromStdString(player->getPokemon(CurrentPoke)->getMove(3)->getname());
    attacks[3] = new QPushButton(s, this);
    attacks[3]->setGeometry(QRect(QPoint(60+200*i, 400 + 100 * j), QSize(150,75)));
    connect(attacks[3], SIGNAL (released()), this, SLOT(handleAttack4()));

    //creates a swapping button at the top of the screen attached to a handling slot
    s = QString::fromStdString("Swap Pokemon");
    swap = new QPushButton(s, this);
    swap->setGeometry(QRect(QPoint(130, 20), QSize(200,50)));
    connect(swap, SIGNAL (released()), this, SLOT(handleSwap()));

}
void fight::declareSwap(){
    int k = 0;
    QString s = "";

    int i = 0;
    int j = 0;
    //each block declares another swap button if there are pokemon in the party to fill it
    if(k < player->getPartySize()){
        s = QString::fromStdString(player->getPokemon(k)->getName());
        swapButton[k] = new QPushButton(s, this);
        swapButton[k]->setGeometry(QRect(QPoint(60+200*i, 100 + 100 * j), QSize(150,75)));
        connect(swapButton[k],SIGNAL (released()), this, SLOT(changePoke1()));


    }

    k++;
    i++;
    if(k < player->getPartySize()){
        s = QString::fromStdString(player->getPokemon(k)->getName());
        swapButton[k] = new QPushButton(s, this);
        swapButton[k]->setGeometry(QRect(QPoint(60+200*i, 100 + 100 * j), QSize(150,75)));
        connect(swapButton[k],SIGNAL (released()), this, SLOT(changePoke2()));
    }
    k++;
    i--;
    j++;
    if(k < player->getPartySize()){
        s = QString::fromStdString(player->getPokemon(k)->getName());
        swapButton[k] = new QPushButton(s, this);
        swapButton[k]->setGeometry(QRect(QPoint(60+200*i, 100 + 100 * j), QSize(150,75)));
        connect(swapButton[k],SIGNAL (released()), this, SLOT(changePoke3()));
    }
    k++;
    i++;
    if(k < player->getPartySize()){
        s = QString::fromStdString(player->getPokemon(k)->getName());
        swapButton[k] = new QPushButton(s, this);
        swapButton[k]->setGeometry(QRect(QPoint(60+200*i, 100 + 100 * j), QSize(150,75)));
        connect(swapButton[k],SIGNAL (released()), this, SLOT(changePoke4()));
    }
    k++;
    i--;
    j++;
    if(k < player->getPartySize()){
        s = QString::fromStdString(player->getPokemon(k)->getName());
        swapButton[k] = new QPushButton(s, this);
        swapButton[k]->setGeometry(QRect(QPoint(60+200*i, 100 + 100 * j), QSize(150,75)));
        connect(swapButton[k],SIGNAL (released()), this, SLOT(changePoke5()));
    }
    k++;
    i++;
    if(k < player->getPartySize()){
        s = QString::fromStdString(player->getPokemon(k)->getName());
        swapButton[k] = new QPushButton(s, this);
        swapButton[k]->setGeometry(QRect(QPoint(60+200*i, 100 + 100 * j), QSize(150,75)));
        connect(swapButton[k],SIGNAL (released()), this, SLOT(changePoke6()));

    }

}
void fight::deleteButtons(){
    //deletes all original screen buttons
    delete attacks[0];
    delete attacks[1];
    delete attacks[2];
    delete attacks[3];
    delete swap;

}
void fight::deleteSwap(){
    //deletes all used swap buttons
    for(int i = 0; i < player->getPartySize(); i++){
        delete swapButton[i];
    }
}

//***************************************************************************Painting
void fight::paintScene(QPainter * Painter){

    //paints background
    background.load("background.png");
    backgroundRect = background.rect();
    backgroundRect.translate(0,0);

    //paints player's pokemon sprite in foreground
    QString s = QString::fromStdString(player->getPokemon(CurrentPoke)->getSprite(0));
    playerSprite.load(s);
    playerRect = playerSprite.rect();
    playerRect.translate(60,275);

    //paints enemy pokemon sprite in background
    QString j = QString::fromStdString(enemy->getSprite(1));
    enemySprite.load(j);
    enemyRect = enemySprite.rect();
    enemyRect.translate(250,100);
    //drawing of the two setup pieces
    Painter->drawImage(backgroundRect, background);
    Painter->drawImage(playerRect, playerSprite);
    Painter->drawImage(enemyRect, enemySprite);
}
void fight::paintEvent(QPaintEvent *e){
    Q_UNUSED(e);
    // changes paint event type based on gamestate
    QPainter Painter(this);
    if(won){
        finishFight(&Painter, "You Won!");
    }
    else if (lost){
        finishFight(&Painter, "You lost..");
    }
    else if (changing){
        swapPaint(&Painter);
    }
    else{
        paintScene(&Painter);
    }
}
void fight::swapPaint(QPainter *painter){
    //paints text at the top of the screen with given font type
    //repaints over main screen to hide main fight screen
    QFont font("Courier", 10, QFont::DemiBold);
    QFontMetrics fm(font);
    QString mesage;
    mesage = QString::fromStdString("Choose your next pokemon");
    int textWidth = fm.width(mesage);

    painter->setFont(font);
    painter->translate(QPoint(130,20));
    painter->drawText(-textWidth/2,0,mesage);

}

//***************************************************************************Closing
void fight::closeEvent(QCloseEvent * event){
    emit finished();
    event->accept();
    //signal emitter for pausing mechanism on initial overworld window

}
void fight::finishFight(QPainter * painter, string s){
    //paints a large message at the top of the screen
    QFont font("Courier", 15, QFont::DemiBold);
    QFontMetrics fm(font);
    QString mesage;
    mesage = QString::fromStdString(s);
    int textWidth = fm.width(mesage);
    // hides the UI
    hideSwap();
    hideButtons();
    painter->setFont(font);
    int h=height();
    int w=width();
    //painting
    painter->translate(QPoint(w/2,h/2));
    painter->drawText(-textWidth/2,0,mesage);


}

//***************************************************************************Console printing
void fight::print(){
    cout << "Player: " << player->getPokemon(CurrentPoke)->getName() << ": \n"
         << "        "<< "Health: " << player->getPokemon(CurrentPoke)->getHealth()<<endl << endl;
    // prints current health of each pokemon
    cout << "Enemy : " << enemy->getName() << ": \n"
         << "        "<< "Health: " << enemy->getHealth() << endl << endl;
    cout << endl << endl;
}
void fight::clearConsole(){
    //clears the console
    for(int i =0; i < 30 ; i++){
        cout << endl;
    }
}

//***************************************************************************Button updating
void fight::hideButtons(){
    //hides the main buttons on the UI
    for(int i = 0 ; i < 4 ; i ++){
        attacks[i]->hide();
    }
    swap->hide();
}
void fight::hideSwap(){
    //hides the swapping buttons for each pokemon
    for(int i = 0 ; i < player->getPartySize(); i ++){
        swapButton[i]->hide();
    }
}
void fight::showButtons(){
    //shows the main buttons for the UI
    for(int i = 0 ; i < 4 ; i ++){
        attacks[i]->show();
    }
    swap->show();
}
void fight::showSwap(){
    //Shows the swapping buttons for each pokemon
    for(int i = 0 ; i < player->getPartySize(); i ++){
        swapButton[i]->show();
    }
}
void fight::changeButtonNames(){
    //changes the attack button names when a pokemon is switched
    QString s = "";
    for(int i = 0; i < 4 ; i++){
        s = QString::fromStdString(player->getPokemon(CurrentPoke)->getMove(i)->getname());
        attacks[i]->setText(s);
    }

}

//***************************************************************************PokeSwap Handling
//I needed a seperate slot for each function since the SLOT() wouldn't take arguments and compile
//each slot handles checking to make sure the pokemon chosen is alive.
void fight::changePoke1(){

    if(player->getPokemon(0)->getHealth() > 0 ){
        changePoke(0);
    }
    else {
        clearConsole();
        cout << "********        PLEASE CHOOSE A POKEMON WITH HEALTH LEFT        ********" << endl;
        player->print();
    }
}
void fight::changePoke2(){
    if(player->getPokemon(1)->getHealth() > 0 ){
        changePoke(1);
    }
    else {
        clearConsole();
        cout << "********        PLEASE CHOOSE A POKEMON WITH HEALTH LEFT        ********" << endl;
        player->print();
    }
}
void fight::changePoke3(){
    if(player->getPokemon(2)->getHealth() > 0 ){
        changePoke(2);
    }
    else {
        clearConsole();
        cout << "********        PLEASE CHOOSE A POKEMON WITH HEALTH LEFT        ********" << endl;
        player->print();
    }
}
void fight::changePoke4(){
    if(player->getPokemon(3)->getHealth() > 0 ){
        changePoke(3);
    }
    else {
        clearConsole();
        cout << "********        PLEASE CHOOSE A POKEMON WITH HEALTH LEFT        ********" << endl;
        player->print();
    }
}
void fight::changePoke5(){
    if(player->getPokemon(4)->getHealth() > 0 ){
        changePoke(4);
    }
    else {
        clearConsole();
        cout << "********        PLEASE CHOOSE A POKEMON WITH HEALTH LEFT        ********" << endl;
        player->print();
    }
}
void fight::changePoke6(){
    if(player->getPokemon(5)->getHealth() > 0 ){
        changePoke(5);
    }
    else {
        clearConsole();
        cout << "********        PLEASE CHOOSE A POKEMON WITH HEALTH LEFT        ********" << endl;
        player->print();
    }
}
//true handling function
void fight::changePoke(int i){
    //sets the array index for current poke
    CurrentPoke = i;
    //changes the attack names to the correct names
    changeButtonNames();
    //hides the swapping buttons
    hideSwap();
    //turns off the changing gamestate for the painter
    changing = false;
    //sends a null value to handle attack so the enemy will still attack
    handleAttack(-1);
    //shows the main UI buttons
    showButtons();
    //repaints to new scene
    repaint();
}
void fight::handleSwap(){
    //changes gamestate for painter
    changing = true;
    //hides the main UI buttons
    hideButtons();
    //shows the buttons to swap to different pokemon
    showSwap();
    //repaints scene
    repaint();

}

//***************************************************************************Attack Handling
void fight::handleAttack1(){
    handleAttack(0);
}
void fight::handleAttack2(){
    handleAttack(1);
}
void fight::handleAttack3(){
    handleAttack(2);
}
void fight::handleAttack4(){
    handleAttack(3);
}
//true handle attack function
void fight::handleAttack(int i){
    clearConsole();

    cout << "Player Turn: " << endl << endl;
    //checks to make sure player hasn't swapped pokemon to make the players move
    if(i != -1){
        player->getPokemon(CurrentPoke)->turn(player->getPokemon(CurrentPoke)->getMove(i),enemy);
    }
    //checks if the enemy has died after player turn
    if(enemy->getHealth() <= 0){
        print();
        cout << "*****     Please exit the fight window     *****" << endl;
        won = true;
        repaint();//sends to end screen
    }
    else{
        cout << "Enemy Turn: " << endl << endl;
        int r = rand()%20; // makes a random choice of a move with a preferance towards attacking
        //I put the preferance in so the 'bot' stood at least a chance
        if(r > 10){
            r = 0;
        }
        else if(r <= 10 && r > 7){
            r = 1;
        }
        else if(r <= 7 && r > 4){
            r = 2;
        }
        else if(r <= 4){
            r = 3;
        }
        //enemy takes turn with randomized move
        enemy->turn(enemy->getMove(r), player->getPokemon(CurrentPoke));

        print();

        //checks if players pokemon has died
        if(player->getPokemon(CurrentPoke)->getHealth() <= 0)
        {
            bool anotherPoke = false;//temporary variable
            //checks each pokemon in the players party for being alive
            for(int i = 0; i < player->getPartySize(); i++){
                if(player->getPokemon(i)->getHealth() > 0)
                {
                    anotherPoke = true;
                }
            }
            //if there is another live pokemon player can switch
            if(anotherPoke){
                handleSwap();
            }
            else{
                //send to losing screen
                cout << "*****     Please exit the fight window     *****" << endl;
                lost = true;
                repaint();

            }


        }

    }

}

