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

private slots:
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
    void changePoke(int i);
    void handleAttack(int i);
    QPushButton *attacks[4];
    QPushButton *swap;
    QPushButton *swapButton[6];
    Player * player;
    void paintScene(QPainter *);
    void swapPaint(QPainter *);
    void closeEvent(QCloseEvent *event);
    void declareButtons();
    void declareSwap();
    void hideButtons();
    void showButtons();
    void hideSwap();
    void showSwap();
    void changeButtonNames();

    void deleteButtons();
    void deleteSwap();
    QImage playerSprite;
    QRect playerRect;
    QImage enemySprite;
    QRect enemyRect;
    int CurrentPoke;
    pokemon *enemy;
    bool won;
    bool lost;
    bool changing;
    void clearConsole();
protected:
    void finishFight(QPainter *, string s);
    void paintEvent(QPaintEvent *);
    void print();


};

#endif // FIGHT_H
