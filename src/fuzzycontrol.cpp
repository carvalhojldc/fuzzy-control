#include "fuzzycontrol.h"

FuzzyControl::FuzzyControl()
{
    alpha = nullptr;
    u = nullptr;
}

FuzzyControl::~FuzzyControl()
{
    if(alpha != nullptr) delete alpha;
    if(u != nullptr) delete u;
}

void FuzzyControl::setFuzzy(Fuzzy fuzzy, double setPoint)
{
    int height = 0;
    int width  = 0;
    int depht  = 0;

    qDebug() << "this->setPoint " << this->setPoint;
    this->myFuzzy  = fuzzy;
    this->setPoint = setPoint;
    qDebug() << "this->setPoint " << this->setPoint;

    previousPeviousError  = previousError = error = 0;

    previousControlOutput = controlOutput = finalControlOutput = 0;

    height = myFuzzy.inputP.fuzzyFunctions.size();
    modeFuzzyControl = FUZZY_P;

    if(myFuzzy.statusInputP && myFuzzy.statusInputI)
    {
        modeFuzzyControl = FUZZY_PI;
        width = myFuzzy.inputI.fuzzyFunctions.size();
    }
    else if(myFuzzy.statusInputP && myFuzzy.statusInputD)
    {
        modeFuzzyControl = FUZZY_PD;
        width = myFuzzy.inputD.fuzzyFunctions.size();
    }
    else if(myFuzzy.statusInputP && myFuzzy.statusInputI && myFuzzy.statusInputD)
    {
        modeFuzzyControl = FUZZY_PID;
        width = myFuzzy.inputI.fuzzyFunctions.size();
        depht = myFuzzy.inputI.fuzzyFunctions.size();
    }

    if(alpha != nullptr) delete alpha;
    if(u != nullptr) delete u;

    alpha = new Array3D(height, width, depht);
    u = new Array3D(height, width, depht);

    for(int i=0; i<alpha->getHeight(); i++)
        for(int j=0; j<alpha->getWidth(); j++)
            for(int k=0; k<alpha->getDepth(); k++)
            {
                alpha->setValue(i,j,k,0.0);
                u->setValue(i,j,k,0.0);
            }
}

double FuzzyControl::getControl(double tankLevel_2)
{
    qDebug() << "FuzzyControl::getControl()";

    previousPeviousError = previousError;
    previousError        = error;

    error   = setPoint - tankLevel_2; // I
    dError  = error - previousError; // P
    d2Error = previousError - previousPeviousError; // D

    previousControlOutput = controlOutput;

    // defuzzification
    {
        defuzzification.clear();

        if(modeFuzzyControl == FUZZY_P)
        {
            defuzzification.push_back( \
                    def.getDefuzzification(myFuzzy.inputP.fuzzyFunctions, dError) );

            valueInp1 = dError;
            valueInp2 = 0;
            valueInp3 = 0;
        }
        else if(modeFuzzyControl == FUZZY_PI)
        {
            defuzzification.push_back( \
                    def.getDefuzzification(myFuzzy.inputP.fuzzyFunctions, dError) );
            defuzzification.push_back( \
                    def.getDefuzzification(myFuzzy.inputI.fuzzyFunctions, error) );

            valueInp1 = dError;
            valueInp2 = error;
            valueInp3 = 0;
        }
        else if(modeFuzzyControl == FUZZY_PD)
        {
            defuzzification.push_back( \
                    def.getDefuzzification(myFuzzy.inputP.fuzzyFunctions, dError) );
            defuzzification.push_back( \
                    def.getDefuzzification(myFuzzy.inputD.fuzzyFunctions, d2Error) );

            valueInp1 = dError;
            valueInp2 = d2Error;
            valueInp3 = 0;
        }
        else if(modeFuzzyControl == FUZZY_PID)
        {
            defuzzification.push_back( \
                    def.getDefuzzification(myFuzzy.inputP.fuzzyFunctions, dError) );
            defuzzification.push_back( \
                    def.getDefuzzification(myFuzzy.inputI.fuzzyFunctions, error) );
            defuzzification.push_back( \
                    def.getDefuzzification(myFuzzy.inputD.fuzzyFunctions, d2Error) );

            valueInp1 = dError;
            valueInp2 = error;
            valueInp3 = d2Error;
        }
    }

    if(myFuzzy.sugenoStatus)
    {
        controlOutput = sugeno();
    }
    else if(myFuzzy.mamdaniStatus)
    {
        return 0.0;
    }
    else
        return 0.0;

    //finalControlOutput = valueInp1 + valueInp2 + valueInp3 + previousControlOutput;

    finalControlOutput = controlOutput + previousControlOutput;

    return finalControlOutput;
}

double FuzzyControl::getError() const
{
    return this->error;
}

double FuzzyControl::getMin(const double a, const double b) const
{
    if(a<=b) return a;
    else return b;
}

double FuzzyControl::getMin(const double a, const double b, const double c) const
{
    if(a<=b && a<=c) return a;
    else if(b<=a && b<=c) return b;
    else return c;
}

double FuzzyControl::sugeno(void)
{
    double signal;
    double s1 = 0, s2 = 0;

    QVector<double> fss;
    FuzzyFunction myFF;
    double value;

    QList<FuzzyRule> rule;

    int x=0, y=0, z=0;

    for(int i=0; i<alpha->getHeight(); i++)
    {
        if(modeFuzzyControl != FUZZY_P)
            for(int j=0; j<alpha->getWidth(); j++)
            {
                if(modeFuzzyControl != FUZZY_PID)
                    alpha->setValue(i,j, 0, getMin(defuzzification[0][i], defuzzification[1][j]) );
                else // FUZZY_PID
                    for(int k=0; k<alpha->getDepth(); k++)
                        alpha->setValue(i,j,k, getMin( \
                                defuzzification[0][i], defuzzification[1][j], defuzzification[2][k] ) );

            }
        else
            alpha->setValue(i,0,0, defuzzification[0][i]);
    }

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

    for(int r=0; r<myFuzzy.rules.size(); r++)
    {
        rule = myFuzzy.rules.at(r);

        // first
        x = rule.at(0).idFunction;

        if(rule.size() != 2)
            y = rule.at(1).idFunction;

        if(rule.size() == 4)
            z = rule.at(2).idFunction;

        u->setValue(x,y,z, fss[ rule.last().idFunction ] );
    }

    for(int i=0; i<alpha->getHeight(); i++)
        for(int j=0; j<alpha->getWidth(); j++)
            for(int k=0; k<alpha->getDepth(); k++) {
                s1 = s1 + u->getValue(i,j,k)*alpha->getValue(i,j,k);
                s2 = s2 + alpha->getValue(i,j,k);
            }

    if(s2!=0)
        signal = s1/s2;
    else
        signal = 0.0;

    return signal;
}
