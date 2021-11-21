# SWOS Competition Changer
---
Autor: AnoXic
Plugin for SWOS to enable more divisions in any country. Extra wrapper to load any custom plugins.

---
# SWOS-Win32-ASI
SWOS-Win32-ASI is a framework to create patches to **Sensible World of Soccer** version Windows 32-bit port.
Plugins swaps winmm.dll and load all files with .ASI extension from swos/plugins folder.
.ASI files are a windows .dll files.

----
# Compilation
On this moment only support MSVC compliler (winmm.dll). 
Suggested method use Visual Studio Code:
Download CMake Tools extension.
Open this directory as Open Folder, select kit as Visual Studio x86 and complile.

---
# Files
include/winmm/winmmmain.h - header of wrapper to winmm.dll (Loaded orginaly by SWOS)
include/winmm/winmmmain.def - definition to windows dll file (exports)
include/swosasi/swosexe.h - support functions to create patches.
include/swosasi/swosgui.h - support functions and structs to create gui.
include/swscc/swscomp.h - header of main plugin SWOS Competition Changer
src/swscc/swscc.cc - dll main entry for asi plugin
src/swscc/swscomp.cc - main cpp file of plugin SWOS Competition Changer
src/winmm/winmmmain.cc - main cpp file of wrapper

data/swscc.xml - example xml definition file for SWOS Competition Changer (changed Poland to two division).
data/TEAM.028 - SWOS team file (Polish League with two division)

---
# Requirements
pugixml library download and copy to folder deps/pugixml

# Installation
copy compiled file winmm.dll (from bin folder) to main swos folder (where is swos-port-Release.exe),
copy plugins folder to this same directory or create directory plugins and copy file swscc.asi
copy swscc.xml to plugins folder.
copy TEAM.028 to DATA directory.

# Change Log
v0.2.6b
- Update to SWOS 2020 v3.0.0
v0.2.5b
- Fix some errors, changes in WinMM
- Update to SWOS 2020 v2.4.1
v0.2.4b
- Initial github release