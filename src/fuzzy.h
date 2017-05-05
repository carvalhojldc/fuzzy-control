#ifndef FUZZY_H
#define FUZZY_H

#include <QStringList>
#include <QList>
#include <QVector>
#include <QtMath>
#include <QColor>

class FuzzyFunction
{
protected:
    const QStringList listFuzzyFunctions = { "Triangle", "Trapeze" };
    const QList<int> listFuzzyFunctions_numberPoints = { 3, 4 };

public:
    int getNumberPoints()
    {
        if(type < 0 || type+1 > listFuzzyFunctions_numberPoints.size())
            return -1;

        return listFuzzyFunctions_numberPoints.at(type);
    }

    void generateGraph(const QVector<float> rangeVariable)
    {
        float startX = rangeVariable[0];
        float endX   = rangeVariable[1];

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
                float D1 = fabs(range[0]-range[1]);
                float D2 = fabs(range[1]-range[2]);
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
                float D1 = fabs(range[0]-range[1]);
                float D2 = fabs(range[2]-range[3]);
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
    QVector<float> range;
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

};

class FuzzyVariable : protected FuzzyFunction
{
protected:
    const QStringList nameInference = {"Sugeno", "Mandani"};

public:
    QList<FuzzyFunction> fuzzyFunctions;
    QString name;
    QVector<float> range = { -30, 30 };
    //QVector<double> pointsX, pointsY;
};

class Rule
{
public:
    FuzzyVariable *io;
    int idFunction;
};

class FuzzyRule
{
public:
    FuzzyVariable *io;
    int idFunction;
};

class Fuzzy : protected FuzzyVariable
{
    friend class FunctionWindow;
    friend class RuleWindow;
    friend class MainWindow;

protected:
    const QStringList listControl = { "Fuzzy-P", "Fuzzy-PI", "Fuzzy-PD", "Fuzzy-PID" };

private:
    bool statusInputP, statusInputI, statusInputD, statusOutput;
    FuzzyVariable inputP, inputI, inputD, output;
    QList<QList<FuzzyRule>> rules;

public:
    Fuzzy();

};

#endif // FUZZY_H
