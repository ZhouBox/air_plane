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
    gp->windowsWidth = 320;//QApplication::desktop()->width();
    gp->windowsHeight = 440;//QApplication::desktop()->height();

    //    gp->windowsWidth = QApplication::desktop()->width() - 20;
    //    gp->windowsHeight = QApplication::desktop()->height() - 50;


    QPixmap pix(":/image/player.png");
    gp->playerPlanePixmap << pix << pix << pix;

    pix.load(":/image/enemy.png");

    gp->enemyPlanePixmap << pix << pix << pix;

    pix.load(":/image/A.png");

    gp->bulletSupplyPixmap << pix;

    pix.load(":/image/B.png");

    gp->bulletSupplyPixmap << pix;

    //gp->p_eplC = new enemyplaneLcahce();
}



int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    initConfigure(GlobalParameter::instance());

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));



    Space sw;
    sw.resize(GlobalParameter::instance()->windowsWidth,
              GlobalParameter::instance()->windowsHeight);
    sw.move(QApplication::desktop()->rect().center() -
            QPoint(GlobalParameter::instance()->windowsWidth/2, GlobalParameter::instance()->windowsHeight/2));
    sw.show();


    return app.exec();
}
