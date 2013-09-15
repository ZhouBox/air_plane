#include "randomizer.h"

Randomizer::Randomizer(QObject *parent) :
    QObject(parent)
{
}


/**
 * @brief Randomizer::creat 产生0~i-1的随机整数
 * @param i
 * @return
 */
int Randomizer::creat(int i)
{
    return qrand() % i;
}


int Randomizer::creat(int l, int h)
{
    return qrand() % (h - l) + l;
}
