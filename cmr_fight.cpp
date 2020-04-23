#include "cmr_fight.h"
#include "cmr_player.h"
#include <iostream>
#include <string>
#include <QApplication>
#include <QPushButton>
#include <QPainter>
#include <QCoreApplication>
#include "cmr_walk.h"


fight::fight(class Player * p,QWidget *parent)
    : QMainWindow(parent)
{
    won = false;
    lost = false;
    changing = false;
    CurrentPoke = 0;
    player = p;

    while((player->getPokemon(CurrentPoke)->getHealth() < 0)){
        CurrentPoke++;
        if(CurrentPoke == player->getPartySize() - 1)
        {
            cout << "no healthy Pokemon" << endl;
            lost = true;
        }
    }
    int l = rand()%POKECOUNT;
    enemy = new pokemon(l);
    enemy->setPower(20 + enemy->getPower());
    clearConsole();
    print();


    declareButtons();
    declareSwap();
    hideSwap();
}
fight::~fight(){
    delete enemy;
    deleteSwap();
    deleteButtons();
    player->setFightOpen(false);
}
void fight::declareButtons(){
    QString s = "";
    int i = 0;
    int j = 0;
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


    s = QString::fromStdString("Swap Pokemon");
    swap = new QPushButton(s, this);
    swap->setGeometry(QRect(QPoint(130, 20), QSize(200,50)));
    connect(swap, SIGNAL (released()), this, SLOT(handleSwap()));

}
void fight::deleteButtons(){
    delete attacks[0];
    delete attacks[1];
    delete attacks[2];
    delete attacks[3];
    delete swap;

}
void fight::paintScene(QPainter * Painter){

    QString s = QString::fromStdString(player->getPokemon(CurrentPoke)->getSprite(0));
    playerSprite.load(s);
    playerRect = playerSprite.rect();
    playerRect.translate(60,275);


    QString j = QString::fromStdString(enemy->getSprite(1));
    enemySprite.load(j);
    enemyRect = enemySprite.rect();
    enemyRect.translate(250,100);

    Painter->drawImage(playerRect, playerSprite);
    Painter->drawImage(enemyRect, enemySprite);
}
void fight::paintEvent(QPaintEvent *e){
    Q_UNUSED(e);

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

    QFont font("Courier", 10, QFont::DemiBold);
    QFontMetrics fm(font);
    QString mesage;
    mesage = QString::fromStdString("Choose your next pokemon");
    int textWidth = fm.width(mesage);

    painter->setFont(font);
    painter->translate(QPoint(130,20));
    painter->drawText(-textWidth/2,0,mesage);

}
void fight::handleAttack(int i){
    clearConsole();
    cout << "Player Turn: " << endl << endl;
    if(i != -1){
        player->getPokemon(CurrentPoke)->turn(player->getPokemon(CurrentPoke)->getMove(i),enemy);
    }

    if(enemy->getHealth() <= 0){
        print();
        won = true;
        repaint();
    }
    else{
        cout << "Enemy Turn: " << endl << endl;
        int r = rand()%20;
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

        enemy->turn(enemy->getMove(r), player->getPokemon(CurrentPoke));

        print();


        if(player->getPokemon(CurrentPoke)->getHealth() <= 0)
        {
            lost = true;
            repaint();
        }

    }

}
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
void fight::handleSwap(){
    changing = true;
    hideButtons();
    showSwap();
    repaint();

}
void fight::declareSwap(){
    int k = 0;
    QString s = "";

    int i = 0;
    int j = 0;
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
void fight::changePoke1(){
    changePoke(0);
}
void fight::changePoke2(){
    changePoke(1);
}
void fight::changePoke3(){
    changePoke(2);
}
void fight::changePoke4(){
    changePoke(3);
}
void fight::changePoke5(){
    changePoke(4);
}
void fight::changePoke6(){
    changePoke(5);
}
void fight::changePoke(int i){
    CurrentPoke = i;
    changeButtonNames();
    hideSwap();
    changing = false;
    handleAttack(-1);
    showButtons();
    repaint();
}
void fight::deleteSwap(){
    for(int i = 0; i < player->getPartySize(); i++){
        delete swapButton[i];
    }
}
void fight::closeEvent(QCloseEvent * event){
    emit finished();
    event->accept();

}
void fight::print(){
    cout << "Player: " << player->getPokemon(CurrentPoke)->getName() << ": \n"
         << "Health: " << player->getPokemon(CurrentPoke)->getHealth()<<endl << endl;

    cout << "Enemy : " << enemy->getName() << ": \n"
         << "Health: " << enemy->getHealth() << endl << endl;
    cout << endl << endl;
}
void fight::finishFight(QPainter * painter, string s){
    QFont font("Courier", 15, QFont::DemiBold);
    QFontMetrics fm(font);
    QString mesage;
    mesage = QString::fromStdString(s);
    int textWidth = fm.width(mesage);

    painter->setFont(font);
    int h=height();
    int w=width();

    painter->translate(QPoint(w/2,h/2));
    painter->drawText(-textWidth/2,0,mesage);

}
void fight::clearConsole(){
    for(int i =0; i < 30 ; i++){
        cout << endl;
    }
}
void fight::hideButtons(){
    for(int i = 0 ; i < 4 ; i ++){
        attacks[i]->hide();
    }
    swap->hide();
}
void fight::hideSwap(){
    for(int i = 0 ; i < player->getPartySize(); i ++){
        swapButton[i]->hide();
    }
}
void fight::showButtons(){
    for(int i = 0 ; i < 4 ; i ++){
        attacks[i]->show();
    }
    swap->show();
}
void fight::showSwap(){
    for(int i = 0 ; i < player->getPartySize(); i ++){
        swapButton[i]->show();
    }
}
void fight::changeButtonNames(){
    QString s = "";
    for(int i = 0; i < 4 ; i++){
        s = QString::fromStdString(player->getPokemon(CurrentPoke)->getMove(i)->getname());
        attacks[i]->setText(s);
    }

}
