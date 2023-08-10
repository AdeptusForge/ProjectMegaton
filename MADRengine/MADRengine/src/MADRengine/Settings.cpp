#include "Settings.h"
#include "MADRpch.h"
#include <fstream>
#include <Windows.h>
#include <Shlobj.h>
#include <Shlwapi.h>

using std::string;
string settingsPath = "";
void CreateGameSettingsFile()
{
    TCHAR my_documents[MAX_PATH];
    HRESULT result = SHGetFolderPath(NULL, CSIDL_MYDOCUMENTS, NULL, SHGFP_TYPE_CURRENT, my_documents);

    if (result != S_OK)
    {
        std::cerr << "Error: " << result << "\n";
        return;
    }
    LPWSTR path = const_cast<LPTSTR>(TEXT("DVNAMIS\\ProjectMegaton\\"));

    PathAppend(my_documents, path);
    bool r = SHCreateDirectoryEx(NULL, my_documents, NULL);
    /*if (r != ERROR_SUCCESS && r != ERROR_FILE_EXISTS && r != ERROR_ALREADY_EXISTS)
    {
        std::cerr << "Error: " << GetLastError() << "\n";
        return string();
    }*/
    PathAppend(my_documents, const_cast<LPTSTR>(TEXT("Settings.json")));

    std::basic_string<TCHAR> tMyText(my_documents);

    settingsPath = std::string(tMyText.begin(), tMyText.end());

    std::ifstream settingsFile = std::ifstream(settingsPath.c_str());
    if (settingsFile.good() == false)
    {
        settingsFile.close();
        std::ofstream outFile = std::ofstream(settingsPath.c_str());

        std::ifstream file("Assets/DefaultSettings.json");
        json data = json::parse(file);

        outFile << data.dump(2);
        outFile.close();
        file.close();
    }
    else
        settingsFile.close();
}

json GetGameSettings()
{
    if (settingsPath.size() == 0)
        CreateGameSettingsFile();

    std::ifstream settingsFile = std::ifstream(settingsPath.c_str());
    json data = json::parse(settingsFile);
    settingsFile.close();

    return data;
}

void SaveGameSettings(json data)
{
    std::ofstream settingsFile = std::ofstream(settingsPath.c_str());
    settingsFile << data.dump(2);
    settingsFile.close();
}