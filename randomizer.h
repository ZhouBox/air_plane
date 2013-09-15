#ifndef RANDOMIZER_H
#define RANDOMIZER_H

#include <QObject>

/**
 * @brief The Randomizer class 随机数发生器
 */

class Randomizer : public QObject
{
    Q_OBJECT
public:
    static int creat(int i);

    static int creat(int l, int h);

    
signals:
    
public slots:

private:
    explicit Randomizer(QObject *parent = 0);
    
};

#endif // RANDOMIZER_H
