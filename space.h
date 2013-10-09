#ifndef SPACE_H
#define SPACE_H

#include <QGraphicsView>
#include <QTimer>
#include <QScopedPointer>
#include <QtOpenGL/QGLWidget>

#include "playerPlane.h"
#include "enemyplane.h"
#include "randomizer.h"
#include "scoringdevice.h"
#include "bloodsupply.h"
#include "menuitem.h"
#include "textitem.h"
#include "menuwidget.h"
#include "bulletsupply.h"
#include "bomb.h"
/**
 * @brief The Space class 太空
 */

class Space : public QGraphicsView
{
    Q_OBJECT
public:
    explicit Space(QWidget *parent = 0);
    ~Space();
    
signals:
    
public slots:



protected:
    void mouseDoubleClickEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *event);
protected slots:
    void slt_updata();

    void slt_enemys();//产生敌机


    /**
     * @brief slt_playerDead 玩家飞机被击落调用
     */
    void slt_playerDead();


    void slt_addScore(int score);


    void slt_startGame();

    void slt_newGame();

    void slt_pauseGame();


    void slt_supply();


    void slt_level(int level);

    void slt_menu();

    void slt_updataScore(int score);

    void slt_updataBlood(int i);

    void slt_bulletSupply();

    void slt_updataBulletTimes(int flag, int sec);

    void slt_aBomb();

private:
    QGraphicsScene m_scene;
    PlayerPlane *m_player;
    TextItem *m_scoreItem;
    TextItem *m_bloods;
    TextItem *showResult;
    TextItem *bulletInfo;
    TextItem *bomb;
    MenuItem *m_menu;
    QTimer m_timer_updata;
    ScoringDevice m_scoringCounter;
    bool m_isRunning;
    int m_step;
    bool m_willBomb;
    int m_bombs;
    QString _3blood;
    QString _2blood;
    QString _1blood;
    QString _0blood;

    void timersStop();
    void timersStart();
    void initSome();
    void reInit();
    void createAbomb();
    void doAbomb();
    void setBloodsText(const QString &text);
    void setBombText(int val);
    void createEnemyM();
    void createEnemyL();

    /**
     * @brief levelAdding 难度算法，f(x) = 3/2000000 * x;
     * @param socre 当前的分数
     */
    void levelAdding(uint socre);
};

#endif // SPACE_H
