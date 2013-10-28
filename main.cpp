#include <QApplication>
#include <QDesktopWidget>
#include <QTime>

#include <space.h>
#include <global.h>

/**
 * @brief initConfigure 初始化全局使用参数，可是从文件加载或其他形式
 * @param gp
 */
static void initConfigure(GlobalParameter *gp)
{
    gp->level = 1;
    gp->bulletSpeed = 20;
    gp->bulletSupplySpeed = 1;
    gp->playerPlaneSpeed = 18;
    gp->enemyPlaneLittleSpeed = 16;
    gp->bloodSupplySpeed = 16;
    QPainterPath p;
    p.addRect(QRectF(0, 0, 5, 10));
    gp->_1bulletOutline = p;
#ifdef Q_OS_ANDROID
    //希望获得设备的屏幕大小，以来设置参数
    gp->windowsWidth = QApplication::desktop()->width();
    gp->windowsHeight = QApplication::desktop()->height();
#else
    gp->windowsWidth = 320;
    gp->windowsHeight = 440;
#endif

    QPixmap pix("://image/player.png");
    gp->playerPlanePixmap << pix;
    pix.load("://image/player_die1.png");
    gp->playerPlanePixmap << pix;
    pix.load("://image/player_die2.png");
    gp->playerPlanePixmap << pix;
    pix.load("://image/player_die3.png");
    gp->playerPlanePixmap << pix;
    pix.load("://image/player_die4.png");
    gp->playerPlanePixmap << pix;

    pix.load("://image/enemy.png");
    gp->enemyPlanePixmap << pix;
    pix.load("://image/enemy_die1.png");
    gp->enemyPlanePixmap << pix;
    pix.load("://image/enemy_die2.png");
    gp->enemyPlanePixmap << pix;
    pix.load("://image/enemy_die3.png");
    gp->enemyPlanePixmap << pix;


    pix.load("://image/enemyM.png");
    gp->enemyPlaneMPixmap << pix;
    pix.load("://image/enemyM_die1.png");
    gp->enemyPlaneMPixmap << pix;
    pix.load("://image/enemyM_die2.png");
    gp->enemyPlaneMPixmap << pix;
    pix.load("://image/enemyM_die3.png");
    gp->enemyPlaneMPixmap << pix;
    pix.load("://image/enemyM_die4.png");
    gp->enemyPlaneMPixmap << pix;
    // pix.load("://image/enemyM_hurt.png");
    // gp->enemyPlaneMPixmap << pix;


    pix.load("://image/enemyL.png");
    gp->enemyPlaneLPixmap << pix;
    pix.load("://image/enemyL_die1.png");
    gp->enemyPlaneLPixmap << pix;
    pix.load("://image/enemyL_die2.png");
    gp->enemyPlaneLPixmap << pix;
    pix.load("://image/enemyL_die3.png");
    gp->enemyPlaneLPixmap << pix;
    pix.load("://image/enemyL_die4.png");
    gp->enemyPlaneLPixmap << pix;
    pix.load("://image/enemyL_die5.png");
    gp->enemyPlaneLPixmap << pix;
    // pix.load("://image/enemyL_hurt.png");
    // gp->enemyPlaneLPixmap << pix;


    pix.load("://image/bulletA.png");

    gp->bulletSupplyPixmap << pix;

    pix.load("://image/bulletB.png");

    gp->bulletSupplyPixmap << pix;

    //gp->p_eplC = new enemyplaneLcahce();
}



int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    initConfigure(GlobalParameter::instance());

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    Space sw;
#ifdef Q_OS_ANDROID
    sw.showFullScreen();
#else
    sw.resize(GlobalParameter::instance()->windowsWidth,
              GlobalParameter::instance()->windowsHeight);
    sw.move(QApplication::desktop()->rect().center() -
            QPoint(GlobalParameter::instance()->windowsWidth/2,
                   GlobalParameter::instance()->windowsHeight/2));
    sw.show();
#endif
    return app.exec();
}
