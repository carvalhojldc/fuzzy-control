#ifndef FUZZY_H
#define FUZZY_H

#include <QStringList>
#include <QList>
#include <QVector>
#include <QtMath>
#include <QColor>

#define RULE_END  -1
#define RULE_THEN 0
#define RULE_AND  1
#define RULE_OR   2

#define FUZZY_P   0
#define FUZZY_PI  1
#define FUZZY_PD  2
#define FUZZY_PID 3

class FuzzyFunction
{
protected:
    const QStringList listFuzzyFunctions = { "Triangle", "Trapeze" };
    const QList<int> listFuzzyFunctions_numberPoints = { 3, 4 };

    const QStringList listSugenoFunctions = { "Constante", "Linear"};
public:
    int getNumberPoints()
    {
        if(type < 0 || type+1 > listFuzzyFunctions_numberPoints.size())
            return -1;

        return listFuzzyFunctions_numberPoints.at(type);
    }

    void generateGraph(const QVector<double> rangeVariable)
    {
        double startX = rangeVariable[0];
        double endX   = rangeVariable[1];

        int size;

        if(startX < 0)
            size = ( fabs(startX) + fabs(endX) ) * 10;
        else
            size = (endX - startX) * 10;

        size += 1;

        QVector<double> x(size), y(size);

        for (int i=0; i<size; i++)
        {
            x[i] = startX + 0.1*i;
            y[i] = 0.0;

            // for triangle
            if( type == 0 && \
            ( range[0] <= x[i] && x[i] <= range[2] ) )
            {
                double D1 = fabs(range[0]-range[1]);
                double D2 = fabs(range[1]-range[2]);
                if(x[i] <= range[1]) {
                    y[i] = fabs(range[0]-x[i])/D1;
                } else {
                    y[i] = 1-fabs(range[1]-x[i])/D2;
                }
            }
            // for trapeze
            else if(type == 1 && \
            ( range[0] <= x[i] && x[i] <= range[3] ) )
            {
                double D1 = fabs(range[0]-range[1]);
                double D2 = fabs(range[2]-range[3]);
                if(x[i] <= range[1]) {
                    y[i] = fabs(range[0]-x[i])/D1;
                }
                else if(x[i] > range[1] && x[i] <= range[2]) {
                    y[i] = 1.0;
                }
                else {
                    y[i] = 1-fabs(range[2]-x[i])/D2;
                }
            }
        }

        graph.clear();
        graph.push_back(x);
        graph.push_back(y);
        graphColor =  QColor(rand()%200+10, rand()%200+10, rand()%200+10, 255);
    }

public:
    QVector<QVector<double>> graph;
    QColor graphColor;
    QVector<double> range;
    QString name;
    int type;

    FuzzyFunction & operator = (const FuzzyFunction & other)
    {
        (*this).graphColor = other.graphColor;
        (*this).graph = other.graph;
        (*this).range = other.range;
        (*this).name  = other.name;
        (*this).type  = other.type;

        return *this;
    }

    void Clear()
    {
        graph.clear();
        range.clear();
    }
};

class FuzzyVariable : protected FuzzyFunction
{
protected:
    const QStringList nameInference = {"Sugeno", "Mandani"};
    const QStringList sugenoMode = {"Contante", "Linear"};

public:
    QList<FuzzyFunction> fuzzyFunctions;
    QString name;
    QVector<double> range = { -30, 30 };
    //QVector<double> pointsX, pointsY;

    FuzzyVariable & operator = (const FuzzyVariable & other)
    {
        this->fuzzyFunctions = other.fuzzyFunctions;
        this->name = other.name;
        this->range = other.range;

        return *this;
    }


   void Clear()
   {
        fuzzyFunctions.clear();
        range = { -30, 30 };
   }
};

class FuzzyRule
{
public:
    FuzzyVariable *io;
    int idFunction;
    int operation;
};

class Fuzzy : protected FuzzyVariable
{
    friend class FunctionWindow;
    friend class RuleWindow;
    friend class MainWindow;
    friend class FuzzyControl;

protected:
    const QStringList listControl = { "Fuzzy-P", "Fuzzy-PI", "Fuzzy-PD", "Fuzzy-PID" };

private:
    bool statusError,
         statusErrorFiDerivative,
         statusErrorSeDerivative,
         statusOutput;

    FuzzyVariable error,
                  errorFirstDerivative,
                  errorSecondDerivative,
                  output;

    QList<QList<FuzzyRule>> rules;

    bool sugenoStatus, mamdaniStatus;

    int type;

public:
    Fuzzy();

    Fuzzy & operator = (const Fuzzy & other)
    {
        this->statusOutput            = other.statusOutput;
        this->statusError             = other.statusError;
        this->statusErrorFiDerivative = other.statusErrorFiDerivative;
        this->statusErrorSeDerivative = other.statusErrorSeDerivative;

        this->output                = other.output;
        this->error                 = other.error;
        this->errorFirstDerivative  = other.errorFirstDerivative;
        this->errorSecondDerivative = other.errorSecondDerivative;

        this->rules = other.rules;

        this->sugenoStatus  = other.sugenoStatus;
        this->mamdaniStatus = other.mamdaniStatus;

        this->type = other.type;

        return *this;
    }

};

#endif // FUZZY_H
