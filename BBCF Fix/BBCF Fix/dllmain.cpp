#include "Include.h"

typedef bool(__fastcall* tReadP2PPacket)(void* _this, void* edx, void* pubDest, uint32 cubDest, uint32* pcubMsgSize, CSteamID* psteamIDRemote, int iVirtualPort);
tReadP2PPacket oReadP2PPacket = (tReadP2PPacket)0;

bool __fastcall hReadP2PPacket(void* _this, void* edx, void* pubDest, uint32 cubDest, uint32* pcubMsgSize, CSteamID* psteamIDRemote, int iVirtualPort)
{
    if (cubDest > 4096 && iVirtualPort == 3)
    {
        // Overflow prevented
        cubDest = 0;
    }

    return oReadP2PPacket(_this, edx, pubDest, cubDest, pcubMsgSize, psteamIDRemote, iVirtualPort);
}

void Attach()
{
    bool patched = false;
    offsets.Initialize();
    BBCF::SteamInterfaces interfaces{};
    if (BBCF::GetSteamInterfaces(&interfaces))
    {
        if (interfaces.steamNetworking005)
        {
            oReadP2PPacket = (tReadP2PPacket)HookVMT((std::uintptr_t)interfaces.steamNetworking005, (std::uintptr_t)&hReadP2PPacket, 2);
            patched = true;
            MessageBoxA(NULL, "Successfully installed patch.", "BBCF Fix - Ok", MB_OK);
        }

        else
            MessageBoxA(NULL, "SteamNetworking handle was null.", "BBCF Fix - Error", MB_OK);
    }

    if (!patched)
        MessageBoxA(NULL, "Couldn't install patch.", "BBCF Fix - Error", MB_OK);
}

void Detach()
{
    if (oReadP2PPacket)
    {
        BBCF::SteamInterfaces interfaces{};
        if (BBCF::GetSteamInterfaces(&interfaces))
        {
            if (interfaces.steamNetworking005)
                HookVMT((std::uintptr_t)interfaces.steamNetworking005, (std::uintptr_t)oReadP2PPacket, 2);
        }
    }
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        Attach();
        break;
    case DLL_THREAD_ATTACH:
        break;
    case DLL_THREAD_DETACH:
        break;
    case DLL_PROCESS_DETACH:
        Detach();
        break;
    }
    return TRUE;
}

