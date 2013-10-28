#ifndef MENUWIDGET_H
#define MENUWIDGET_H

#include <QDialog>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QPushButton>


/**
 * @brief The MenuWidget class 菜单窗体
 */

class MenuWidget : public QDialog
{
    Q_OBJECT
public:
    explicit MenuWidget(QWidget *parent = 0, bool isRunning = false);
    void setRunning(bool isRunning);

signals:
    void sig_newGame();
    void sig_quit();
    void sig_back();
public slots:

protected slots:
    void slt_quit();
    void slt_newGame();
    void slt_back();

private:
    //QStackedWidget *m_workSpace;

    QPushButton *m_new;
    QPushButton *m_back;
    QPushButton *m_quit;



    bool states;

    void initUI();
};

#endif // MENUWIDGET_H
