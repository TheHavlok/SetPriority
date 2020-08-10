#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <vector>
#include <sstream>

bool threadOnOff = false;

class Priority
{
public:
    void SetPriority(std::vector<int> PId, int Option);
    int GetNamePId(std::string ProcName);

    std::vector<std::string> selectedName;
    std::vector<int> selectedPID;

private:
    std::vector<std::string> Name_;
    std::vector<std::string> PID_;
};

void Priority::SetPriority(std::vector<int> PId, int Option)
{
    while (threadOnOff)
    {
        HANDLE WH = GetForegroundWindow();

        PROCESSENTRY32W pe = { 0 };
        pe.dwSize = sizeof(pe);

        if (Option == 0)
        {
            for (size_t i = 0; i < PId.size(); ++i)
            {
                HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PId[i]);

                SetPriorityClass(hProcess, HIGH_PRIORITY_CLASS);
                if (!SetPriorityClass(hProcess, HIGH_PRIORITY_CLASS))
                {
                    DWORD err = GetLastError();
                    std::cout << err;
                }
            }
        }
        else
        {
            HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PId[Option - 1]);

            SetPriorityClass(hProcess, HIGH_PRIORITY_CLASS);
            if (!SetPriorityClass(hProcess, HIGH_PRIORITY_CLASS))
            {
                DWORD err = GetLastError();
                std::cout << err;
            }
        }
        Sleep(100);
    }
}

int Priority::GetNamePId(std::string ProcName)
{
    PROCESSENTRY32W pe = { 0 };
    pe.dwSize = sizeof(pe);
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (Process32FirstW(hSnapshot, &pe)) {
        do {

            std::wstring WprocName = pe.szExeFile;
            std::string procName(WprocName.begin(), WprocName.end());

            std::stringstream ss;
            ss << pe.th32ProcessID;
            std::string ProcessID = ss.str();

            Name_.push_back(procName);
            PID_.push_back(ProcessID);

        } while (Process32NextW(hSnapshot, &pe));
    }

    int vSize = Name_.size();

    for (int i = 0; i < vSize; ++i)
    {
        if (Name_[i] == ProcName)
        {
            //std::cout << count << ": " << Name_[i] << " " << PID_[i] << std::endl;
            selectedName.push_back(Name_[i]);
            selectedPID.push_back(atoi(PID_[i].c_str()));
        }
    }

    if (selectedName.empty())
    {
        std::cout << "Error! Nothing found... Try again" << std::endl;
        std::cout << std::endl;
        return 1;
    }
    else
    {
        std::cout << "Selected " << ProcName << ": " << std::endl;
        std::cout << "----------------------------" << std::endl;

        int count = 1;
        for (size_t i = 0; i < selectedName.size(); i++)
        {
            std::cout << count << ": " << selectedName[i] << " " << selectedPID[i] << std::endl;
            ++count;
        }
        return 0;
    }
}