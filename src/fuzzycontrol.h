#ifndef FUZZYCONTROL_H
#define FUZZYCONTROL_H

#include "fuzzy.h"

#include <QDebug>

class FuzzyControl
{
private:
    Fuzzy myFuzzy;
    double setPoint;
    double tankLevel_1, tankLevel_2;
    double signal;
    double error;

public:
    FuzzyControl();
    ~FuzzyControl();

    void setFuzzy(Fuzzy fuzzy, double setPoint);
    double getControl(double tankLevel_1, double tankLevel_2);
    double getError() const;

private:
    double sugeno(void);
};

#endif // FUZZYCONTROL_H
