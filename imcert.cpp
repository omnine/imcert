// imcert.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

#include <Windows.h>
#include <wtsapi32.h>
#include <iphlpapi.h>

using namespace std;

int main()
{
    std::cout << "Hello World!\n";


    vector<unsigned char> buffer;
    DWORD dwSize = sizeof(MIB_TCPTABLE_OWNER_PID);
    DWORD dwRetValue = 0;

    do {
        buffer.resize(dwSize, 0);
        dwRetValue = GetExtendedTcpTable(buffer.data(), &dwSize, TRUE, AF_INET, TCP_TABLE_OWNER_PID_ALL, 0);
    } while (dwRetValue == ERROR_INSUFFICIENT_BUFFER);
    if (dwRetValue == ERROR_SUCCESS)
    {
        PMIB_TCPTABLE_OWNER_PID ptTable = reinterpret_cast<PMIB_TCPTABLE_OWNER_PID>(buffer.data());
        cout << "Number of Entries: " << ptTable->dwNumEntries << endl << endl;
        for (DWORD i = 0; i < ptTable->dwNumEntries; i++) {
            DWORD pid = ptTable->table[i].dwOwningPid;
            cout << "PID: " << pid << endl;
 //           cout << "Name: " << processName(ptTable->table[i].dwOwningPid) << endl;
            cout << "State: " << ptTable->table[i].dwState << endl;
            cout << "Local Port: "
                << htons((unsigned short)ptTable->table[i].dwLocalPort)
                << endl;

            cout << "Remote Port: "
                << htons((unsigned short)ptTable->table[i].dwRemotePort)
                << endl;

            cout << endl;
        }
    }


    DWORD dwProcessId, dwSessionId;
    dwProcessId = 1000;

    if (ProcessIdToSessionId(dwProcessId,  &dwSessionId) == 0) {
        return 50;
    }

    HANDLE hToken = NULL;

    // get the active console session ID of the logged on user
    //the calling application must be running within the context of the LocalSystem account and have the SE_TCB_NAME privilege.
    if (!WTSQueryUserToken(WTSGetActiveConsoleSessionId(), &hToken))
    {
        return 51;
    }

    HANDLE hDuplicated;

    // duplicate the token
    if (!DuplicateToken(hToken, SecurityImpersonation, &hDuplicated))
    {
        return 52;
    }
    else
    {
        //ShowErrorText("DuplicateToken succeeded.", 0, true);
    }

    // impersonate the logged on user
    if (!ImpersonateLoggedOnUser(hToken))
    {
       
        return 53;
    }

    //open user cert store.
    // Open a system store, in this case, the My store.

    HCERTSTORE hSysStore = NULL;
    if (hSysStore = CertOpenStore(
        CERT_STORE_PROV_SYSTEM,          // The store provider type
        0,                               // The encoding type is
                                         // not needed
        NULL,                            // Use the default HCRYPTPROV
        CERT_SYSTEM_STORE_CURRENT_USER,  // Set the store location in a
                                         // registry location
        L"MY"                            // The store name as a Unicode 
                                         // string
    ))
    {
        printf("The system store was created successfully.\n");
    }
    else
    {
        printf("An error occurred during creation "
            "of the system store!\n");
        return 54;
    }


    if (RevertToSelf())
    {
        //ShowErrorText("Impersonation ended successfully.", 0, true);
    }

    return 0;

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
