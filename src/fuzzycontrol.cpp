#include "fuzzycontrol.h"

FuzzyControl::FuzzyControl()
{

}

FuzzyControl::~FuzzyControl()
{

}

void FuzzyControl::setFuzzy(Fuzzy fuzzy, double setPoint)
{
    qDebug() << "FuzzyControl::setFuzzy(Fuzzy fuzzy, double setPoint)";
    qDebug() << "##################################";

    this->myFuzzy = fuzzy;
    this->setPoint = setPoint;

    if(myFuzzy.statusInputP && myFuzzy.statusInputI)
        modeFuzzyControl = FUZZY_PI;
    else if(myFuzzy.statusInputP && myFuzzy.statusInputD)
        modeFuzzyControl = FUZZY_PD;
    else if(myFuzzy.statusInputP && myFuzzy.statusInputI && myFuzzy.statusInputD)
        modeFuzzyControl = FUZZY_PID;
    else
        modeFuzzyControl = FUZZY_P;
}

double FuzzyControl::getControl(double tankLevel_1, double tankLevel_2)
{
    qDebug() << "-------------";
    qDebug() << "getControl()";

    previousPeviousError = previousError;
    previousError = error;

    error = setPoint - tankLevel_2; // I
    dError = error - previousError; // P
    d2Error = previousError - previousPeviousError; // D

    qDebug() << "--------" << modeFuzzyControl;
    // defuzzification
    {
        defuzzification.clear();

        if(modeFuzzyControl == FUZZY_P) {
            defuzzification.push_back( \
                    def.getDefuzzification(myFuzzy.inputP.fuzzyFunctions, dError) );

            valueInp1 = dError;
            valueInp2 = 0;
            valueInp3 = 0;
        }
        else if(modeFuzzyControl == FUZZY_PI) {
            defuzzification.push_back( \
                    def.getDefuzzification(myFuzzy.inputP.fuzzyFunctions, dError) );
            defuzzification.push_back( \
                    def.getDefuzzification(myFuzzy.inputI.fuzzyFunctions, error) );

            valueInp1 = dError;
            valueInp2 = error;
            valueInp3 = 0;
        }
        else if(modeFuzzyControl == FUZZY_PD) {
            defuzzification.push_back( \
                    def.getDefuzzification(myFuzzy.inputP.fuzzyFunctions, dError) );
            defuzzification.push_back( \
                    def.getDefuzzification(myFuzzy.inputD.fuzzyFunctions, d2Error) );

            valueInp1 = dError;
            valueInp2 = d2Error;
            valueInp3 = 0;
        }
        else if(modeFuzzyControl == FUZZY_PID) {
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
        qDebug() << "sugeno";
        sugeno();
         return 1;
    }
    else if(myFuzzy.mamdaniStatus)
    {
        qDebug() << "mandani";
        return 0.0;
    }
    else
        return 0.0;
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

double FuzzyControl::sugeno(void)
{
    QList<QList<double>> alpha;

    // start Inference
    if(modeFuzzyControl != FUZZY_P)
    {
        QList<double> il = defuzzification.at(0);
        for(int i=0; i<il.size(); i++)
        {
            QList<double> jl = defuzzification.at(1);
            QList<double> temp;
            temp.clear();
            for(int j=0; j<jl.size(); j++)
            {
                if(modeFuzzyControl != FUZZY_PID)
                {
                    temp.push_back(getMin(il.at(i),jl.at(j)));
                }
                else
                {

                }
            }
            alpha.push_back(temp);
        }
    }
    else
    {
        alpha.push_back( defuzzification.at(0) );
    }
    // END Inference

    QList<double> fss;
    FuzzyFunction myFF;
    double value;
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

    double u[defuzzification.at(0).size()][defuzzification.at(1).size()] = { 0.0 };

    QList<FuzzyRule> rule;
    FuzzyRule myRule;
    for(int r=0; r<myFuzzy.rules.size(); r++)
    {
        rule = myFuzzy.rules.at(r);
/*
        myRule = rule.at(i);
        int x = myRule.idFunction;
        myRule = rule.at(i);
        if(myRule[1] != 0) {
            int y = myRule[2];
            u[x][y] = fss.at( myRule[4] );
        }*/
    }

    double signal;

    for(int i=0; i<defuzzification.at(0).size(); i++)
    {
        for(int j=0; j<defuzzification.at(1).size(); j++)
        {
            //signal =
        }
    }

    return 0;
}
