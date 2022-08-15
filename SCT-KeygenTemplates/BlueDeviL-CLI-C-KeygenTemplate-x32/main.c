#include "Files\SCT.h"

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

    // Play Music
    HINSTANCE hInstance = GetModuleHandle(NULL);
    uFMOD_PlaySong((void*)RCD_MUSIC, hInstance, XM_RESOURCE);

    ClearCmdPrompt();
    PrintBanner(bluedevil00, title_eng);

    GenerateKey();

    // Stop music
    uFMOD_PlaySong(0, 0, 0);

    system("pause");
    return 0;
}