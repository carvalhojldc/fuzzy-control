#ifndef SIGNAL_H
#define SIGNAL_H

#include <QStringList>
#include <cstdlib>
#include <cmath>
#include <time.h>

#define PI 3.14159265359

class Signal
{
public:
    const QStringList typesSigns = { "Degrau", "Quadrada", "Senoidal", "Dente de Serra", "Aleatória" };

public:
    Signal();
    double degrau(double tensao, double offset);
    double seno(double tensao, double time, double periodo, double offset);
    double aleatorio(double ampMax, double ampMin);
    double quadrada(double tensao, double time, double periodo, double offset);
    double serra(double tensao, double time, double periodo, double offset);
    double periodoAleatorio(double durMax, double durMin);
};

#endif // SIGNAL_H
