#include "SetPriority.h"
#include <thread>

void Preview();

int main()
{
    /*
████████╗██╗░░██╗███████╗██╗░░██╗░█████╗░██╗░░░██╗██╗░░░░░░█████╗░██╗░░██╗
╚══██╔══╝██║░░██║██╔════╝██║░░██║██╔══██╗██║░░░██║██║░░░░░██╔══██╗██║░██╔╝
░░░██║░░░███████║█████╗░░███████║███████║╚██╗░██╔╝██║░░░░░██║░░██║█████═╝░
░░░██║░░░██╔══██║██╔══╝░░██╔══██║██╔══██║░╚████╔╝░██║░░░░░██║░░██║██╔═██╗░
░░░██║░░░██║░░██║███████╗██║░░██║██║░░██║░░╚██╔╝░░███████╗╚█████╔╝██║░╚██╗
░░░╚═╝░░░╚═╝░░╚═╝╚══════╝╚═╝░░╚═╝╚═╝░░╚═╝░░░╚═╝░░░╚══════╝░╚════╝░╚═╝░░╚═╝
    */
    HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_GREEN);

    Preview();

    for (;;)
    {
        std::cout << "Write the name of the program(ex. Program.exe): ";

        std::string progName;
        getline(std::cin, progName);
        std::cout << std::endl;

        Priority pr;
        if (pr.GetNamePId(progName))
        {
            continue;
        }

        std::cout << std::endl;
        std::cout << "Enter the serial number, to select all enter \"0\": ";
        int sNum;
        std::cin >> sNum;
        std::cin.ignore();

        int vSize = pr.selectedName.size();
        if (vSize < sNum)
        {
            continue;
        }

        if (sNum == 0)
        {
            threadOnOff = true;
            std::thread ChangePriority(&Priority::SetPriority, pr, pr.selectedPID, 0);
            ChangePriority.detach();
        }
        else
        {
            threadOnOff = true;
            std::thread ChangePriority(&Priority::SetPriority, pr, pr.selectedPID, sNum);
            ChangePriority.detach();
        }

        std::string stop = "";
        while (stop != "stop")
        {
            system("cls");
            Preview();
            std::cout << "To stop enter \"stop\": ";
            getline(std::cin, stop);
        }
        threadOnOff = false;

        system("cls");
        Preview();
    }
}

void Preview()
{
    std::wcout << R"( _____ _          _   _             _       _)" << std::endl;
    std::wcout << R"(|_   _| |        | | | |           | |     | |)" << std::endl;
    std::wcout << R"(  | | | |__   ___| |_| | __ ___   _| | ___ | | __)" << std::endl;
    std::wcout << R"(  | | | '_ \ / _ \  _  |/ _` \ \ / / |/ _ \| |/ /)" << std::endl;
    std::wcout << R"(  | | | | | |  __/ | | | (_| |\ V /| | (_) |   <)" << std::endl;
    std::wcout << R"(  \_/ |_| |_|\___\_| |_/\__,_| \_/ |_|\___/|_|\_\)" << std::endl;
    std::cout << std::endl;
}