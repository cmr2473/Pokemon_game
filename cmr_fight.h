#ifndef FIGHT_H
#define FIGHT_H
#include <QPushButton>
#include "cmr_player.h"
#include <QMainWindow>
#include <QEvent>
#include <QImage>
#include <QRect>
#include <QPainter>
namespace Ui{
    class fight;
}


class fight:public QMainWindow
{
    Q_OBJECT
public:

     fight(Player *,QWidget * = 0);
     ~fight();


signals:
     void finished();

private slots: // most slots redirect to functions that can take in integer inputs
    void handleAttack1();
    void handleAttack2();
    void handleAttack3();
    void handleAttack4();
    void handleSwap();
    void changePoke1();
    void changePoke2();
    void changePoke3();
    void changePoke4();
    void changePoke5();
    void changePoke6();
private:
    //handle variable button inputs
    void handleAttack(int i);
    void changePoke(int i);
    //all buttons
    QPushButton *attacks[4];
    QPushButton *swap;
    QPushButton *swapButton[6];
    Player * player;
    //all paint events and big screen changes
    void paintScene(QPainter *);
    void swapPaint(QPainter *);
    void closeEvent(QCloseEvent *event);
    void finishFight(QPainter *, string s);
    void paintEvent(QPaintEvent *);
    //cleans up the constructor
    void declareButtons();
    void declareSwap();
    //button managment functions
    void hideButtons();
    void showButtons();
    void hideSwap();
    void showSwap();
    void changeButtonNames();
    //cleans up the destructor
    void deleteButtons();
    void deleteSwap();
    //image data for the screen painting
    QImage playerSprite;
    QRect playerRect;
    QImage enemySprite;
    QRect enemyRect;
    QImage background;
    QRect backgroundRect;
    //data for game states
    int CurrentPoke;
    pokemon *enemy;
    bool won;
    bool lost;
    bool changing;
    //console output functions
    void print();
public:
    static void clearConsole();



};

#endif // FIGHT_H
