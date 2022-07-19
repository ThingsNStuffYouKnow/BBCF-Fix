# Update 7/19/2022
The vulnerability has been fixed by Arc System Works with an emergency patch in Ver2103.\
The update includes a fix for the vulnerability itself, as well as enabling ASLR and stack canaries on the main executable.\
Therefore, this repository is obsolete.

# Summary
Quick fix to prevent a remote code execution exploit in BlazBlue: Central Fiction (Ver2102) on Steam.\
Once other community fixes have been released I might link to them here.\
Further reading: https://github.com/ThingsNStuffYouKnow/BBCF-RCE-PoC

# Usage
Make sure to build as x86. Once the game is started, use your favourite DLL-Injector to load the dll into the BBCF.exe process during runtime.\
If you don't get the success message, the patch is not installed and you could be vulnerable.

# External
https://github.com/SteamRE/open-steamworks
