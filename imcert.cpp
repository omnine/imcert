// imcert.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include <Windows.h>

int main()
{
    std::cout << "Hello World!\n";


    DWORD dwProcessId, dwSessionId;

    if (ProcessIdToSessionId(dwProcessId,  &dwSessionId) == 0) {
        return 50;
    }

    // get the active console session ID of the logged on user
    if (!WTSQueryUserToken(WTSGetActiveConsoleSessionId(), &hToken))
    {
        ShowErrorText("WTSQueryUserToken failed.", GetLastError(), true);
        return;
    }

    HANDLE hDuplicated;

    // duplicate the token
    if (!DuplicateToken(hToken, SecurityImpersonation, &hDuplicated))
    {
        ShowErrorText("DuplicateToken failed.", GetLastError(), true);
    }
    else
    {
        ShowErrorText("DuplicateToken succeeded.", 0, true);
    }

    // impersonate the logged on user
    if (!ImpersonateLoggedOnUser(hToken))
    {
        ShowErrorText("ImpersonateLoggedOnUser failed.", GetLastError(), true);
        return;
    }

    // retrieve the DC name 
    if (!GetPrimaryDC(DC))
    {
        ShowErrorText("GetPrimaryDC failed.", 0, true);
    }
    PROFILEINFO lpProfileInfo;

    ZeroMemory(&lpProfileInfo, sizeof(PROFILEINFO));
    lpProfileInfo.dwSize = sizeof(PROFILEINFO);
    lpProfileInfo.lpUserName = CurrentUser;

    // get type of profile. roaming, mandatory or temporary
    int ret = GetTypeOfProfile();
    if (ret == 2)
    {
        // if roaming profile get the path of it
        if (!GetRoamingProfilePath(DC, CurrentUser, RoamingProfilePath))
        {
            ShowErrorText("Failed to retrieve roaming profile path.", GetLastError(), true);
        }
    }
    if (RevertToSelf())
    {
        ShowErrorText("Impersonation ended successfully.", 0, true);
    }



}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
