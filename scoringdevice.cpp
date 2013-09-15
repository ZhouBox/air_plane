#include "scoringdevice.h"

ScoringDevice::ScoringDevice():
    m_score(0)
{
}

ScoringDevice ScoringDevice::operator ++(int)
{
    ScoringDevice t = *this;
    ++m_score;
    return t;
}

ScoringDevice& ScoringDevice::operator ++()
{
    ++m_score;
    return *this;
}

ScoringDevice ScoringDevice::operator --(int)
{
    ScoringDevice t = *this;
    --m_score;
    return *this;
}

ScoringDevice& ScoringDevice::operator --()
{
    --m_score;
    return *this;
}

void ScoringDevice::clear()
{
    m_score = 0;
}



ScoringDevice ScoringDevice::operator +(int x)
{
    m_score += x;
    return *this;
}
