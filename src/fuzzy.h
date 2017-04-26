#ifndef FUZZY_H
#define FUZZY_H

#include <QStringList>

#include <QList>
#include <QStack>
#include <vector>

using namespace  std;

class FuzzyFunction
{
protected:
    QStringList nameFuzzyFunctions = { "Triangle", "Trapeze", "Gaus" };

public:
    QString range;
    QString name;
    int type;
};

class FuzzyVariable : protected FuzzyFunction
{
protected:
    QStringList nameInference = {"Sugeno", "Mandani"};

public:
    QList<FuzzyFunction> fuzzyFunctions;
    QString name;
    QString range = "[0 0]";
};

//class FuzzyUI;

class Fuzzy : protected FuzzyVariable
{
    friend class FuzzyConfigUI;

protected:
    QStringList controlFuzzy = { "Fuzzy-P", "Fuzzy-PI", "Fuzzy-PD", "Fuzzy-PID" };
  //  QVector<FuzzyVariable> fuzzyInput[3];
    FuzzyVariable inputP, inputI, inputD, output;

public:
    Fuzzy();
};

class FuzzyControl
{


public:

};

#endif // FUZZY_H
