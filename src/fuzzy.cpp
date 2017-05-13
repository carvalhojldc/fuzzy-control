#include "fuzzy.h"

Fuzzy::Fuzzy()
{
    inputP.name = "Der. do Erro";
    inputI.name = "Erro";
    inputD.name = "Der. Seg. do Erro";
    output.name = "Saída";

    statusInputP = statusInputI = statusInputD = false;
    statusOutput = true;

    sugenoStatus = mamdaniStatus = false;
}
