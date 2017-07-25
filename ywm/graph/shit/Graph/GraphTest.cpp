#include "ALG.h"
#include "OLG.h"
#include "UDN.h"

int main()
{
    MGraph MG;
    ALGraph ALG;

    CreateUDN(MG);
    showAdj(MG);

    CreateDG_ALG(ALG);
    showAdj(ALG);

    OLGraph OLG;
    CreateDG_OLG(OLG);
    showAdj(OLG);

    return 0;
}