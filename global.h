#ifndef GLOBAL_H
#define GLOBAL_H


#include <QPainterPath>




#define PIXMAPHEIGHT 48 //图片的高

#define PIXMAPWEIGHT 50 //图片的宽


#define BULLET 0 //子弹

#define PLAYERPLANE 1 //玩家

#define ENEMYPLANE 2 //敌机

#define BLOODSUPPLY 3 //血补给

#define BULLETSUPPLYA 4 // A弹

#define BULLETSUPPLYB 5 // B弹

#define BOMB 12//炸弹

typedef QList<QPixmap> QPixmaps;

class FlightVehicle;

typedef QList<FlightVehicle*> enemyplaneLcahce;


/**
 * @brief The GlobalParameter class 全局的配置参数，可以从文件中加载
 */

class GlobalParameter
{
public:
    static GlobalParameter* instance() {
        static GlobalParameter global;
        static GlobalParameter *globalConfigure = &global;
        return globalConfigure;
    }


    GlobalParameter():playerPlaneSpeed(0),
        enemyPlaneLittleSpeed(0),
        bloodSupplySpeed(0),
        bulletSupplySpeed(0),
        bulletSpeed(0),
        _1bulletOutline(QPainterPath()),
        windowsWidth(440),
        windowsHeight(320),
        bulletClassFlag(BULLET),
        playerPlaneClassFlag(PLAYERPLANE),
        enemyPlaneClassFlag(ENEMYPLANE),
        bloodSupplyClassFlag(BLOODSUPPLY),
        bombClassFlag(BOMB),
        playerPlanePixmap(QPixmaps()),
        enemyPlanePixmap(QPixmaps()),
        enemyPlaneMPixmap(QPixmaps()),
        enemyPlaneLPixmap(QPixmaps()),
        bulletSupplyPixmap(QPixmaps()),
        level(1),
        p_eplC(0) {


    }

    /**
     * @brief playerPlaneSpeed 玩家的飞行速度
     */
    unsigned int playerPlaneSpeed;

    /**
     * @brief enemyPlaneLittle 小型敌机速度
     */
    unsigned int enemyPlaneLittleSpeed;

    /**
     * @brief bloodSupplySpeed 血补给的速度
     */
    unsigned int bloodSupplySpeed;

    /**
     * @brief bulletSupplySpeed 子弹补给的速度
     */
    unsigned int bulletSupplySpeed;

    /**
     * @brief bulletSpeed 子弹飞行速度
     */
    unsigned int bulletSpeed;

    /**
     * @brief _1bulletOutline _1子弹的轮廓
     */
    QPainterPath _1bulletOutline;

    /**
     * @brief windowsWidth 屏幕宽
     */
    int windowsWidth;
    /**
     * @brief windowsHeight 屏幕高
     */
    int windowsHeight;

    /**
     * @brief bulletClassFlag 在类层次中标识这个类 子弹
     */
    int bulletClassFlag;

    /**
     * @brief playerPlaneClassFlag 玩家飞机
     */
    int playerPlaneClassFlag;

    /**
     * @brief enemyPlaneClassFlag 敌机
     */
    int enemyPlaneClassFlag;


    /**
     * @brief bloodSupplyClassFlag 血补给
     */
    int bloodSupplyClassFlag;


    int bombClassFlag;

    /**
     * @brief playerPlanePixmap 玩家用到的图片
     */
    QPixmaps playerPlanePixmap;

    /**
     * @brief enemyPlanePixmap 敌机用到的图片
     */
    QPixmaps enemyPlanePixmap;

    /**
     * @brief enemyPlaneMPixmap 中型敌机使用的图片
     */
    QPixmaps enemyPlaneMPixmap;

    /**
     * @brief enemyPlaneLPixmap 大型敌机使用的图片
     */
    QPixmaps enemyPlaneLPixmap;


    QPixmaps bulletSupplyPixmap;

    /**
     * @brief level  难易水平
     */
    int level;
    /**
     * @brief p_eplC 缓存指针
     */
    enemyplaneLcahce * p_eplC;

private:



};

#endif // GLOBAL_H
