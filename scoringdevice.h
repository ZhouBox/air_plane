#ifndef SCORINGDEVICE_H
#define SCORINGDEVICE_H


/**
 * @brief The ScoringDevice class 计分器
 */

class ScoringDevice
{
public:
    ScoringDevice();
    ~ScoringDevice(){}
    ScoringDevice operator ++(int);//后置
    ScoringDevice& operator ++();
    ScoringDevice& operator --();
    ScoringDevice operator --(int);
    ScoringDevice operator +(int x);
    void clear();
    int score() const {
        return m_score;
    }
private:
    int m_score;
};

#endif // SCORINGDEVICE_H
