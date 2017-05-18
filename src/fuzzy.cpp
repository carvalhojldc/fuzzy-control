#include "fuzzy.h"

Fuzzy::Fuzzy()
{
    error.name = "Erro";
    output.name = "Saída";
    errorFirstDerivative.name = "Der. do Erro";
    errorSecondDerivative.name = "Der. Seg. do Erro";

    statusError = statusErrorFiDerivative = statusErrorSeDerivative = false;
    statusOutput = true;

    sugenoStatus = mamdaniStatus = false;
}
