#include "fuzzy.h"

Fuzzy::Fuzzy()
{
    inputP.name = "Erro";
    inputI.name = "Erro acumulado";
    inputD.name = "Derivada do erro";

    statusInputP = statusInputI = statusInputD = false;
}
