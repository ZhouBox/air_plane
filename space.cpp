#include "space.h"

Space::Space(QWidget *parent) :
    QGraphicsView(parent),
    m_scene(0, 0, GlobalParameter::instance()->windowsWidth, GlobalParameter::instance()->windowsHeight),
    m_isRunning(false),
    m_step(0),
    m_willBomb(false),
    m_bombs(0),
    _3blood("/ / /"),
    _2blood("/ /  "),
    _1blood("/    "),
    _0blood("- - -")
{
    setScene(&m_scene);
    setWindowFlags(Qt::FramelessWindowHint);
    QPalette palette;
    palette.setColor(backgroundRole(), QColor(0,0,51));
    setPalette(palette);
    palette.setColor(QPalette::Text, QColor(255,255,255));
    setPalette(palette);

    setBackgroundBrush(QPixmap(":/image/sky.png"));
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setCacheMode(QGraphicsView::CacheBackground);
    setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    setOptimizationFlags(QGraphicsView::DontClipPainter
                         | QGraphicsView::DontSavePainterState);
    setRenderHint(QPainter::Antialiasing);

    connect(&m_timer_updata, SIGNAL(timeout()), this, SLOT(slt_updata()));

    initSome();
}

Space::~Space()
{
    delete GlobalParameter::instance()->p_eplC;
}

void Space::slt_updata()
{
    doAbomb();
    foreach (QGraphicsItem *t, m_scene.items(m_scene.sceneRect())) {
        // ((Flyer*)t)->autofly();
        if (t->type() != CustomItem::Type) {
            Flyer *f = static_cast<Flyer*>(t);
            f->autofly();
        }

    }

    //m_scene.advance();//使用advance后，内部执行两步操作，所以速度会比上面使用的方法快一倍
    slt_updataScore(m_scoringCounter.score());

    ++m_step;
    if (m_step % 12 == 0) {
        slt_enemys();
    }
    if (m_step % 3 == 0) {
        m_player->shoot();
    }
    if (m_step % 570 == 0) {
        slt_supply();
        m_step = 0;
    }
}

void Space::slt_enemys()
{
    int num = Randomizer::creat(GlobalParameter::instance()->level * 3);

    for (int i = 0;i < num; ++i) {
        int x = Randomizer::creat(GlobalParameter::instance()->windowsWidth - PIXMAPWEIGHT);
        FlightVehicle *epl = NULL;
        // if (GlobalParameter::instance()->p_eplC->isEmpty()) {
        epl = new EnemyPlane(GlobalParameter::instance()->enemyPlanePixmap,1,
                             /*GlobalParameter::instance()->enemyPlaneLittleSpeed*/Randomizer::creat(6,13),&m_scene);
        // } else {
        //     epl = GlobalParameter::instance()->p_eplC->front();
        //     GlobalParameter::instance()->p_eplC->pop_front();
        //     epl->setSpeed(Randomizer::creat(6,25));
        // }
        epl->setPos(x,0);
        connect(epl, SIGNAL(sig_addScore(int)), this, SLOT(slt_addScore(int)));

    }

}



void Space::createEnemyM()
{
//    int num = Randomizer::creat(2);

//    for (int i = 0;i < num; ++i) {
        int x = Randomizer::creat(GlobalParameter::instance()->windowsWidth - PIXMAPWEIGHT);
        FlightVehicle *epl = NULL;
        // if (GlobalParameter::instance()->p_eplC->isEmpty()) {
        epl = new EnemyPlane(GlobalParameter::instance()->enemyPlaneMPixmap,7,
                             /*GlobalParameter::instance()->enemyPlaneLittleSpeed*/Randomizer::creat(1,8),&m_scene);
        // } else {
        //     epl = GlobalParameter::instance()->p_eplC->front();
        //     GlobalParameter::instance()->p_eplC->pop_front();
        //     epl->setSpeed(Randomizer::creat(6,25));
        // }
        epl->setPos(x,0);
        connect(epl, SIGNAL(sig_addScore(int)), this, SLOT(slt_addScore(int)));

//    }
}

void Space::createEnemyL()
{
//    int num = Randomizer::creat(2);

//    for (int i = 0;i < num; ++i) {
        int x = Randomizer::creat(GlobalParameter::instance()->windowsWidth - PIXMAPWEIGHT - 30);
        FlightVehicle *epl = NULL;
        // if (GlobalParameter::instance()->p_eplC->isEmpty()) {
        epl = new EnemyPlane(GlobalParameter::instance()->enemyPlaneLPixmap,12,
                             /*GlobalParameter::instance()->enemyPlaneLittleSpeed*/Randomizer::creat(1,5),&m_scene);
        // } else {
        //     epl = GlobalParameter::instance()->p_eplC->front();
        //     GlobalParameter::instance()->p_eplC->pop_front();
        //     epl->setSpeed(Randomizer::creat(6,25));
        // }
        epl->setPos(x,0);
        connect(epl, SIGNAL(sig_addScore(int)), this, SLOT(slt_addScore(int)));

//    }
}

void Space::slt_bulletSupply()
{
    int x = Randomizer::creat(GlobalParameter::instance()->windowsWidth - PIXMAPWEIGHT);
    BulletSupply *bs = new BulletSupply(GlobalParameter::instance()->bloodSupplySpeed,
                                        &m_scene,GlobalParameter::instance()->bulletSupplyPixmap,x%2+4);
    bs->setPos(x,0);
}

void Space::slt_playerDead()
{
    m_isRunning = false;
    int s = m_scoringCounter.score();
    m_scoringCounter.clear();
    timersStop();
    showResult->setVisible(true);
    showResult->setHtml(tr("<b><font color=white>@^@  Game Over! Score:%1</font></b>").arg(s * 1000));
    showResult->setPos(GlobalParameter::instance()->windowsWidth/2 -
                       showResult->sceneBoundingRect().width()/2,
                       GlobalParameter::instance()->windowsHeight/2);
}

void Space::timersStop()
{
    m_timer_updata.stop();
}


void Space::timersStart()
{
    m_timer_updata.start(1000/24);
}




void Space::slt_addScore(int score)
{
    m_scoringCounter + score;
    if (m_scoringCounter.score() != 0){


        if( m_scoringCounter.score() % (15000 / 1000) == 0)  {
            createEnemyM();
        }

        if( m_scoringCounter.score() % (32000 / 1000) == 0)  {
            createEnemyL();
        }


        if( m_scoringCounter.score() % (100000 / 1000) == 0)  {
            slt_bulletSupply();
        }

        if (m_scoringCounter.score() % (180000 / 1000) == 0) {
            createAbomb();
        }
    }
}


void Space::slt_newGame()
{
    //GlobalParameter::instance()->p_eplC->clear();
    m_scene.clear();
    initSome();
    setBloodsText(_3blood);
    setBombText(m_bombs);
    //reInit();
    m_player->setFocus();
    timersStart();
    m_isRunning = true;


}


void Space::slt_pauseGame()
{
    if (m_isRunning)
        timersStop();
}

void Space::slt_startGame()
{
    if (m_isRunning) {
        timersStart();
        m_player->setFocus();
    }

}

void Space::slt_supply()
{
    int x = Randomizer::creat(GlobalParameter::instance()->windowsWidth - PIXMAPWEIGHT);
    BloodSupply *bs = new BloodSupply(GlobalParameter::instance()->bloodSupplySpeed,&m_scene);
    bs->setPos(x,0);
}

void Space::slt_level(int level)
{
    GlobalParameter::instance()->level = (level + 1);
}


void Space::initSome()
{
    m_step = 0;
    m_menu = new MenuItem();
    m_scene.addItem(m_menu);
    connect(m_menu, SIGNAL(sig_menu()), this, SLOT(slt_menu()));

    m_scoreItem = new TextItem("0");
    m_scene.addItem(m_scoreItem);
    m_scoreItem->setPos(m_menu->sceneBoundingRect().width(), 0);

    m_bloods = new TextItem("/ / /");
    m_scene.addItem(m_bloods);
    m_bloods->setZValue(2);
    m_bloods->setPos(m_scene.width() - m_bloods->sceneBoundingRect().width(),0);


    this->bomb = new TextItem("Bomb:x0");
    m_scene.addItem(this->bomb);
    this->bomb->setPos(m_scene.width() - m_bloods->sceneBoundingRect().width() -
                       this->bomb->sceneBoundingRect().width() - 10, 0);

    showResult = new TextItem(QString());
    showResult->setZValue(2);
    m_scene.addItem(showResult);

    bulletInfo = new TextItem(QString("X:XXs")); //A:XXs
    bulletInfo->setVisible(false);
    m_scene.addItem(bulletInfo);
    bulletInfo->setZValue(2);
    bulletInfo->setPos(0,m_scene.height() - bulletInfo->sceneBoundingRect().height());


    m_player = new PlayerPlane(GlobalParameter::instance()->playerPlanePixmap,
                               3,GlobalParameter::instance()->playerPlaneSpeed,&m_scene);
    //计分
    connect(m_player, SIGNAL(sig_fall()), this, SLOT(slt_playerDead()));
    connect(m_player, SIGNAL(sig_blood(int)), this, SLOT(slt_updataBlood(int)));
    connect(m_player, SIGNAL(sig_bulletTimes(int,int)), this,
            SLOT(slt_updataBulletTimes(int,int)));
    connect(m_player, SIGNAL(sig_aBomb()), this, SLOT(slt_aBomb()));
}

void Space::slt_menu()
{
    if (m_isRunning) {
        slt_pauseGame();
        QScopedPointer<MenuWidget> w(new MenuWidget(true, this));
        connect(w.data(), SIGNAL(sig_newGame()), this, SLOT(slt_newGame()));
        connect(w.data(), SIGNAL(sig_quit()), this, SLOT(close()));
        w->setModal(true);
        w->show();
        w->exec();
        slt_startGame();
    } else {
        QScopedPointer<MenuWidget> w(new MenuWidget(m_isRunning, this));
        connect(w.data(), SIGNAL(sig_newGame()), this, SLOT(slt_newGame()));
        connect(w.data(), SIGNAL(sig_quit()), this, SLOT(close()));
        w->setModal(true);
        w->show();
        w->exec();
    }
}

void Space::slt_updataScore(int score)
{
    m_scoreItem->setHtml(tr("<b><font color=white>%1</font></b>").arg(score * 1000));
}

void Space::slt_updataBlood(int i)
{
    switch (i) {
    case 3:
        setBloodsText(_3blood);
        break;
    case 2:
        setBloodsText(_2blood);
        break;
    case 1:
        setBloodsText(_1blood);
        break;
    case 0:
        setBloodsText(_0blood);
        break;
    default:
        setBloodsText("error");
        break;
    }

}

void Space::reInit()
{
    showResult->setVisible(false);
    foreach (QGraphicsItem *t, m_scene.items(m_scene.sceneRect())) {
        if (t->type() != CustomItem::Type) {
            Flyer *f = static_cast<Flyer*>(t);
            if (f->name() != GlobalParameter::instance()->playerPlaneClassFlag) {
                f->setVisible(false);
            }
        }

    }
    m_player->reinit();
    slt_updataScore(0);
    slt_updataBlood(3);
}

void Space::slt_updataBulletTimes(int flag, int sec)
{
    if (sec != 0 && !bulletInfo->isVisible()) {
        bulletInfo->setVisible(true);
    }
    if (sec == 0) {
        bulletInfo->setVisible(false);
        return;
    }
    QString s = "";
    if (flag == BulletFactory::_2) {
        s = "A";
    } else {
        s = "B";
    }
    QString s2 = QString::number(sec);
    bulletInfo->setHtml(tr("<b><font color=white>%1:%2s</font></b>").arg(s,s2));
}

void Space::mouseDoubleClickEvent(QMouseEvent *e)
{
    if (m_isRunning) {
        if (m_bombs > 0) {
            m_willBomb = true;
        }
    }
    e->accept();

}

void Space::doAbomb()
{
    if(m_willBomb) {
        foreach (QGraphicsItem *t, m_scene.items(m_scene.sceneRect())) {
            if (t->type() != CustomItem::Type) {
                Flyer *f = static_cast<Flyer*>(t);
                if (f->name() == GlobalParameter::instance()->enemyPlaneClassFlag) {
                    f->fall();
                }
            }

        }
        m_willBomb = false;
        --m_bombs;
        setBombText(m_bombs);
    }
}

void Space::slt_aBomb()
{
    ++m_bombs;
    setBombText(m_bombs);

}

void Space::createAbomb()
{
    int x = Randomizer::creat(GlobalParameter::instance()->windowsWidth - PIXMAPWEIGHT);
    Bomb *bs = new Bomb(GlobalParameter::instance()->bloodSupplySpeed,&m_scene);
    bs->setPos(x,0);
}

inline
void Space::setBloodsText(const QString &text)
{
    m_bloods->setHtml(QString("<b><font color=white>") + text + "</font></b>");
}

inline
void Space::setBombText(int val)
{
    this->bomb->setHtml(tr("<b><font color=white>Bomb:x%1</font></b>").arg(QString::number(val)));

}




