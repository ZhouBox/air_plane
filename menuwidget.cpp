#include "menuwidget.h"

MenuWidget::MenuWidget(QWidget *parent, bool isRunning) :
    QDialog(parent),
    states(isRunning)
{
    setWindowFlags(Qt::FramelessWindowHint);
    initUI();
    setMinimumSize(100,200);
    setMaximumSize(100,200);
    //move(parent->rect().center() - QPoint(150/2,300/2));
    connect(m_new, SIGNAL(clicked()), this, SLOT(slt_newGame()));
    connect(m_quit, SIGNAL(clicked()), this ,SLOT(slt_quit()));
    connect(m_back, SIGNAL(clicked()), this, SLOT(slt_back()));

}

void MenuWidget::initUI()
{
    m_new = new QPushButton("New Game");
    m_back = new QPushButton("Back");
    m_quit = new QPushButton("Quit");

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addStretch();
    mainLayout->addWidget(m_new);
    mainLayout->addWidget(m_back);
    mainLayout->addWidget(m_quit);
    mainLayout->addStretch();

    setLayout(mainLayout);
}


void MenuWidget::setRunning(bool isRunning)
{
    states = isRunning;
    if (states) {
        m_new->setDisabled(true);
        m_back->setDisabled(false);
    } else {
        m_back->setDisabled(true);
        m_new->setDisabled(false);
    }
}

void MenuWidget::slt_quit()
{
    emit sig_quit();
    close();
}

void MenuWidget::slt_newGame()
{
    emit sig_newGame();
}

void MenuWidget::slt_back()
{
    emit sig_back();
}
