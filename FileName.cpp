#include <windows.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>

void SetScreenResolution(int width, int height) {
    DEVMODE dm;
    ZeroMemory(&dm, sizeof(dm));
    dm.dmSize = sizeof(dm);
    dm.dmPelsWidth = width;
    dm.dmPelsHeight = height;
    dm.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT;
    ChangeDisplaySettings(&dm, 0);
}
int CALLBACK WinMain(_In_ HINSTANCE hInstance,_In_ HINSTANCE hPrevInstance,_In_ LPSTR     lpCmdLine,_In_ int       nCmdShow){
    Sleep(60000);
    std::vector<std::pair<int, int>> resolutions = {
    {3840, 2160}, {2560, 1440}, {2048, 1152}, {1920, 1200}, {1920, 1080},
    {1600, 900}, {1536, 864}, {1440, 900}, {1400, 1050}, {1366, 768},
    {1280, 960}, {1280, 800}, {1280, 720}, {1024, 768}, {854, 480},
    {800, 600}, {768, 576}, {640, 480}, {640, 400}, {540, 960},
    {480, 270}, {400, 300}, {320, 240}
    };

    DEVMODE dm;
    ZeroMemory(&dm, sizeof(dm));
    dm.dmSize = sizeof(dm);
    EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dm);

    auto currentRes = std::make_pair(dm.dmPelsWidth, dm.dmPelsHeight);
    auto it = std::find(resolutions.begin(), resolutions.end(), currentRes);

    while (it != resolutions.end()) {
        SetScreenResolution(it->first, it->second);
        srand(static_cast<unsigned int>(time(nullptr)));
        int waitTime = (rand() % 10 + 1) * 60; // Random wait time between 1 and 10 minutes
        Sleep(waitTime * 1000);
        ++it;
    }

    return 0;
}