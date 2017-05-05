#include "fuzzy.h"

Fuzzy::Fuzzy()
{
    inputP.name = "Erro";
    inputI.name = "Erro acumulado";
    inputD.name = "Derivada do erro";
    output.name = "Saída";

    statusInputP = statusInputI = statusInputD = false;
    statusOutput = true;
}
