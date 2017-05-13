#ifndef FUZZYCONTROL_H
#define FUZZYCONTROL_H

#include "fuzzy.h"
#include "array3d.h"
#include <QDebug>

#define FUZZY_P 0
#define FUZZY_PI 1
#define FUZZY_PD 2
#define FUZZY_PID 3

class Defuzzification
{
private:

    double triangle(QVector<double> range, const double x)
    {
        double a = range[0];
        double c = range[1];
        double b = range[2];

        if(x >= a && x <= c)
            return (x-a)/(c-a);
        else if(x >= c && x<=b)
            return (b-x)/(b-c);
        else
            return 0;
    }

    double trapeze(QVector<double> range, const double x)
    {
        double a = range[0];
        double c = range[1];
        double d = range[2];
        double b = range[3];

        if(x >= a && x <= c)
            return (x-a)/(c-a);
        else if(c < x && x < d)
            return 1;
        else if(x >= d && x<=b)
            return (b-x)/(b-d);
        else
            return 0;
    }

public:
    QVector<double> getDefuzzification(const QList<FuzzyFunction> & functions, const double valueX)
    {
        QVector<double> data;

        FuzzyFunction ff;
        double defuzzification;

        for(int f=0; f<functions.size(); f++)
        {
            ff = functions.at(f);

            if(ff.type == 0)
                defuzzification = triangle(ff.range, valueX);
            else if(ff.type == 1)
                defuzzification = trapeze(ff.range, valueX);
            else
                defuzzification = 0;

            data.push_back( defuzzification);
        }
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

    double controlOutput, previousControlOutput, finalControlOutput;

    int modeFuzzyControl = 0;

    QVector<QVector<double>> defuzzification;

    Defuzzification def;

    Array3D *alpha;
    Array3D *u;

public:
    FuzzyControl();
    ~FuzzyControl();

    void setFuzzy(Fuzzy fuzzy, double setPoint);
    double getControl(double tankLevel_2);
    double getError() const;

private:
    double getMin(const double a, const double b) const;
    double getMin(const double a, const double b, const double c) const;
    double sugeno(void);
};

#endif // FUZZYCONTROL_H
