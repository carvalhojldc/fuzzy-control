#include "fuzzycontrol.h"

FuzzyControl::FuzzyControl()
{

}

FuzzyControl::~FuzzyControl()
{

}

void FuzzyControl::setFuzzy(Fuzzy fuzzy, double setPoint)
{
    this->myFuzzy = fuzzy;
    this->setPoint = setPoint;
}

double FuzzyControl::getControl(double tankLevel_1, double tankLevel_2)
{
    this->error = this->setPoint - tankLevel_2;

    if(myFuzzy.sugenoStatus)
    {
        qDebug() << "sugeno";
        return sugeno();
    }
    else if(myFuzzy.mamdaniStatus)
    {
        qDebug() << "mandani";
    }
    else
        return 0.0;
}

double FuzzyControl::getError() const
{
    return this->error;
}

double FuzzyControl::sugeno(void)
{

}
