#include "fuzzycontrol.h"

FuzzyControl::FuzzyControl()
{
    alpha = nullptr;
    rules = nullptr;
}

FuzzyControl::~FuzzyControl()
{
    if(alpha != nullptr) delete alpha;
    if(rules != nullptr) delete rules;
}

void FuzzyControl::setFuzzy(Fuzzy fuzzy, double setPoint)
{
    int height = 0;
    int width  = 0;
    int depht  = 0;

    this->myFuzzy  = fuzzy;
    this->setPoint = setPoint;

    previousPeviousError  = previousError = error = 0;
    previousControlOutput = controlOutput = finalControlOutput = 0;

    height = myFuzzy.error.fuzzyFunctions.size();
    width  = myFuzzy.errorFirstDerivative.fuzzyFunctions.size();
    depht  = myFuzzy.errorSecondDerivative.fuzzyFunctions.size();

    {
        if(alpha != nullptr) delete alpha;
        if(rules != nullptr) delete rules;

        alpha = new Array3D(height, width, depht);
        rules = new Array3D(height, width, depht);

        for(int i=0; i<alpha->getHeight(); i++)
            for(int j=0; j<alpha->getWidth(); j++)
                for(int k=0; k<alpha->getDepth(); k++)
                {
                    alpha->setValue(i, j, k, 0.0 );
                    rules->setValue(i, j, k, 0.0 );
                }
    }
}

double FuzzyControl::getControl(double tankLevel_2)
{
    previousPeviousError = previousError;
    previousError        = error;

    error   = setPoint - tankLevel_2; // I
    dError  = error - previousError; // P
    d2Error = previousError - previousPeviousError; // D

    previousControlOutput = controlOutput;

    // defuzzification
    {
        defuzzification.clear();

        defuzzification.push_back( \
                def.getDefuzzification(myFuzzy.error.fuzzyFunctions, error) );
        defuzzification.push_back( \
                def.getDefuzzification(myFuzzy.errorFirstDerivative.fuzzyFunctions, dError) );
        defuzzification.push_back( \
                def.getDefuzzification(myFuzzy.errorSecondDerivative.fuzzyFunctions, d2Error) );

        valueInp1 = error;
        valueInp2 = dError;
        valueInp3 = d2Error;
    }

    //------------

    if(myFuzzy.sugenoStatus)
    {
        controlOutput = sugeno();
    }
    else if(myFuzzy.mamdaniStatus)
    {
        controlOutput = 0.0;
    }
    else
    {
        controlOutput = 0.0;
    }

    //------------

    if(myFuzzy.type == FUZZY_P)
    {
        finalControlOutput = controlOutput;
    }
    else if(myFuzzy.type  == FUZZY_PD)
    {
        finalControlOutput = controlOutput;
    }
    else
    {
        finalControlOutput = controlOutput + previousControlOutput;
    }

    //------------

    return finalControlOutput;
}

double FuzzyControl::getError() const
{
    return this->error;
}

double FuzzyControl::getMin(const double a, const double b, const double c) const
{
    if(a<=b && a<=c) return a;
    else if(b<=a && b<=c) return b;
    else return c;
}

double FuzzyControl::sugeno(void)
{
    double s1 = 0, s2 = 0;

    FuzzyFunction myFF;
    double value;

    QList<FuzzyRule> rule;

    int x=0, y=0, z=0;

    // Mat Alpha
    for(int i=0; i<alpha->getHeight(); i++)
        for(int j=0; j<alpha->getWidth(); j++)
            for(int k=0; k<alpha->getDepth(); k++)
                alpha->setValue(i,j,k, \
                        getMin( defuzzification[0][i], defuzzification[1][j], defuzzification[2][k] ) );

    // Sugeno terms
    for(int f=0; f<myFuzzy.output.fuzzyFunctions.size(); f++)
    {
        myFF = myFuzzy.output.fuzzyFunctions.at(f);
        if(myFF.range.size() == 2)
            value = myFF.range.at(0) * valueInp1 + myFF.range.at(1);
        else if(myFF.range.size() == 3)
            value = myFF.range.at(0) * valueInp1 + myFF.range.at(1) * valueInp2 + \
                    myFF.range.at(2);
        else if(myFF.range.size() == 4)
            value = myFF.range.at(0) * valueInp1 + myFF.range.at(1) * valueInp2 + \
                    myFF.range.at(2) * valueInp3 + myFF.range.at(3);
        else // myFF.range.size() == 1 (constant value)
            value = myFF.range.at(0);

        fss.push_back( value );
    }

    // Mat Rules
    for(int r=0; r<myFuzzy.rules.size(); r++)
    {
        rule = myFuzzy.rules.at(r);

        // first
        x = rule.at(0).idFunction;

        if(rule.size() != 2)
            y = rule.at(1).idFunction;

        if(rule.size() == 4)
            z = rule.at(2).idFunction;

        rules->setValue(x,y,z, fss[ rule.last().idFunction ] );
    }

    for(int i=0; i<alpha->getHeight(); i++)
        for(int j=0; j<alpha->getWidth(); j++)
            for(int k=0; k<alpha->getDepth(); k++)
            {
                s1 = s1 + rules->getValue(i,j,k)*alpha->getValue(i,j,k);
                s2 = s2 + alpha->getValue(i,j,k);
            }

    if(s2!=0)
        return s1/s2;
    else
        return 0.0;
}


