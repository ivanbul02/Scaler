#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "DPIHelper.h"
#include <memory>
#include <cassert>


using namespace std;

int GetRecommendedDPIScaling()
{
    int dpi = 0;
    auto retval = SystemParametersInfo(SPI_GETLOGICALDPIOVERRIDE, 0, (LPVOID)&dpi, 1);

    if (retval != 0)
    {
        int currDPI = DpiVals[dpi * -1];
        return currDPI;
    }

    return -1;
}

void SetDpiScaling(int percentScaleToSet)
{
    int recommendedDpiScale = GetRecommendedDPIScaling();

    if (recommendedDpiScale > 0)
    {
        int index = 0, recIndex = 0, setIndex = 0 ;
        for (const auto& scale : DpiVals)
        {
            if (recommendedDpiScale == scale)
            {
                recIndex = index;
            }
            if (percentScaleToSet == scale)
            {
                setIndex = index;
            }
            index++;
        }
        
        int relativeIndex = setIndex - recIndex;
        SystemParametersInfo(SPI_SETLOGICALDPIOVERRIDE, relativeIndex, (LPVOID)0, 1);
    }
}

int main()
{
    std::cout << "LCtrl + Num+ to increase dpi, LCtrl + Num- to decrease dpi." << std::endl << "LCtrl + Num* to hide console, LCtrl + Num/ to show console." << std::endl;
    int dpiToSet = GetRecommendedDPIScaling();
    int lastdpi = dpiToSet;
    std::cout << "recommended dpi:" << dpiToSet << "%" << std::endl;
    do
    {
        if (GetKeyState(VK_LCONTROL) & 0x80 && GetKeyState(VK_ADD) & 0x80) { //LCtrl + Num+ увеличить dpi
            if (dpiToSet < 200) {       //Число отвечает за максимальный уровень dpi
                dpiToSet += 25;
                std::cout << "dpi:" << dpiToSet << "%" << std::endl;
                SetDpiScaling(dpiToSet);
                Sleep(200);
            }
            else {
                MessageBeep(MB_OK);
                std::cout << "dpi is too high" << std::endl;
                Sleep(200);
            }
    }
        else if (GetKeyState(VK_LCONTROL) & 0x80 && GetKeyState(VK_SUBTRACT) & 0x80) { //LCtrl + Num- уменьшить dpi
            if (dpiToSet > 100) {               
                dpiToSet -= 25;
                std::cout << "dpi:" << dpiToSet << "%" << std::endl;
                SetDpiScaling(dpiToSet);
                Sleep(200);
            }
            else {
                SetDpiScaling(100);
                MessageBeep(MB_OK);
                std::cout << "dpi is too low" << endl;
                Sleep(200);
            }
        }
        else if (GetKeyState(VK_LCONTROL) & 0x80 && GetKeyState(VK_MULTIPLY) & 0x80) { //LCtrl + Num* Спрятать окно
            ShowWindow(GetConsoleWindow(), SW_HIDE);
            
         }
        else if (GetKeyState(VK_LCONTROL) & 0x80 && GetKeyState(VK_DIVIDE) & 0x80) { //LCtrl + Num/ Показать окно 
            ShowWindow(GetConsoleWindow(), SW_SHOW);
            
        }
        
     } while (!(GetKeyState(VK_ESCAPE) & 0x80)); //При закрытии программы комбинацией LCtrl + ESC устанавливается рекомендуемый dpi
     SetDpiScaling(lastdpi);
}
