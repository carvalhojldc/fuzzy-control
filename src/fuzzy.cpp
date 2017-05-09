#include "fuzzy.h"

Fuzzy::Fuzzy()
{
    inputP.name = "Erro";
    inputI.name = "Der. do Erro";
    inputD.name = "Der. Seg. do Erro";
    output.name = "Saída";

    statusInputP = statusInputI = statusInputD = false;
    statusOutput = true;

    sugenoStatus = mamdaniStatus = false;
}
