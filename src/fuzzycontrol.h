#ifndef FUZZYCONTROL_H
#define FUZZYCONTROL_H

#include "fuzzy.h"

#include <QDebug>

#define FUZZY_P 0
#define FUZZY_PI 1
#define FUZZY_PD 2
#define FUZZY_PID 3

class Defuzzification
{
private:
    int numberFunctions;

    double triangle(const QVector<float> range, const double x)
    {
        float a = range[0];
        float c = range[1];
        float b = range[2];

        if(x >= a && x <= c)
            return (x-a)/(c-a);
        else if(x >= c && x<=b)
            return (b-x)/(b-c);
        else
            return 0;
    }

    double trapeze(const QVector<float> range, const double x)
    {
        float a = range[0];
        float c = range[1];
        float d = range[2];
        float b = range[3];

        if(x >= a && x <= c)
            return (x-a)/(c-a);
        else if(c < x && x < d)
            return 1;
        else if(x >= d && x<=b)
            return (b-x)/(b-d);
        else
            return 0;
    }

    double getData(const FuzzyFunction & f, const double x)
    {
        if(f.type == 0)
            return triangle(f.range, x);
        else if(f.type == 1)
            return trapeze(f.range, x);
        else
            return 0;
    }

public:
    QList<double> getDefuzzification(const QList<FuzzyFunction> & functions, const double valueX)
    {
        QList<double> data;

        numberFunctions = functions.size();

        //if(numberFunctions == 0) return data;

        for(int f=0; f<numberFunctions; f++)
            data.push_back( getData( functions.at(f), valueX ) );

        return data;
    }
};

class FuzzyControl
{
private:
    Fuzzy myFuzzy;
    double setPoint;
    double tankLevel_1, tankLevel_2;
    double signal;
    double error, dError, d2Error;
    double previousError, previousPeviousError;
    /*
      -> In a PID control ( pid = p + i + d )
        u(t) = e + int(e) + d(e)/dt

      -> In a Fuzzy analogy (Fuzzy pid = p + i + d )
        d(u)/dt = d(e)/dt + e + d²(e)/dt²
            * output = output - previousOutput
            * p = error - previousError
            * i = error
            * d = previousError - previousPeviousError

        PS: e means error
    */

    double valueInp1, valueInp2, valueInp3;

    int modeFuzzyControl = 0;

    QList<QList<double>> defuzzification;

    Defuzzification def;

public:
    FuzzyControl();
    ~FuzzyControl();

    void setFuzzy(Fuzzy fuzzy, double setPoint);
    double getControl(double tankLevel_1, double tankLevel_2);
    double getError() const;

private:
    double getMin(const double a, const double b) const;
    double sugeno(void);
};

#endif // FUZZYCONTROL_H
