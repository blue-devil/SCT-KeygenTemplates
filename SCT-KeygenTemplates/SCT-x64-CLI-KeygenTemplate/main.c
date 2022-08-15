#include "Files\SCT.h"
#include "Files\xmp.h"

void GenerateKey()
{
    char temp[256];
    char key[256];

    printf("  [ * ] Username: ");
    if (fgets(temp, sizeof(temp), stdin)) {
        strcpy_s(key, sizeof(strSCT), strSCT);
        strcat_s(key, 256, "-");
        strcat_s(key, 256, temp);
        printf("  [ * ] Serial: %s", key);
    }
}

int main(int argc, char** argv)
{
    SetConsoleOutputCP(65001);
    ClearCmdPrompt();

    // Play Music
    SCT_XMplay((void*)RCD_MUSIC, 0, XM_RESOURCE);

    PrintBanner(sct_eng, title_eng);

    GenerateKey();

    system("pause");

    // Stop music
    SCT_XMstop();

    return 0;
}