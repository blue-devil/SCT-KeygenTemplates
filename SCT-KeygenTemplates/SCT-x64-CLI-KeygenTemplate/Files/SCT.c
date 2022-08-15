#include "SCT.h"


void PrintBanner(const char* banner, const char* baslik) {
    fprintf(stdout, "%s", banner);
    fprintf(stdout, "%s", baslik);
}

void ClearCmdPrompt()
{
    system("cls");
}