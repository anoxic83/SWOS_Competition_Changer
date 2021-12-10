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

# Files
include/winmm/winmmmain.h - header of wrapper to winmm.dll (Loaded orginaly by SWOS)
include/winmm/winmmmain.def - definition to windows dll file (exports)
include/swosasi/swoshook.h - support functions to create patches and finding pattern in memory.
include/swscc/swscomp.h - header of main plugin SWOS Competition Changer
src/swosasi/swoshook.cc - main cpp file of hook
src/swscc/swscc.cc - dll main entry for asi plugin
src/swscc/swscomp.cc - main cpp file of plugin SWOS Competition Changer
src/winmm/winmmmain.cc - main cpp file of wrapper

data/swscc.xml - example xml definition file for SWOS Competition Changer (changed Poland to two division).
data/TEAM.028 - SWOS team file (Polish League with two division)

# Requirements
pugixml library download and copy to folder deps/pugixml

# Installation
copy compiled file winmm.dll (from bin folder) to main swos folder (where is swos-port-Release.exe),
copy plugins folder to this same directory or create directory plugins and copy file swscc.asi
copy swscc.xml to plugins folder.
copy TEAM.028 to DATA directory.

---
# Release
Unpack 7z file and copy all files from folder swos to directory where is swos-port-Release.exe file.

# Configuration
To configuration competition use swscc.xml located in plugins folder.

Warning! More than 2 division by nation is not supported yet.

```xml
<?xml version = "1.0" encoding = "UTF-8" ?>
<!--  SWOS Competition Changer v.0.3.1b -->
<!--  Author: AnoXic -->

<Nation>
  <TeamNo>28</TeamNo>										<!-- SWOS Team (National) No -->
  <League>															<!-- Start League Section -->
    <BeginMonth>8</BeginMonth>					
    <EndMonth>5</EndMonth>
    <Divisions>2</Divisions>						<!-- No of divisions (yet max. 2) -->
    <Rounds>2</Rounds>									
    <PtsForWin>3</PtsForWin>
    <Substitutes>3</Substitutes>
    <Bench>5</Bench>
    <Division>
      <Teams>16</Teams>
      <Promoted>0</Promoted>
      <PromPlayOff>0</PromPlayOff>
      <Relegated>3</Relegated>
      <RelPlayOff>0</RelPlayOff>
    </Division>
    <Division>
      <Teams>18</Teams>
      <Promoted>3</Promoted>
      <PromPlayOff>0</PromPlayOff>
      <Relegated>3</Relegated>
      <RelPlayOff>0</RelPlayOff>
    </Division>
    <!-- 
      If add more leagues change Divisions above and add definition below...
      Play-Off for Promotion and Relegations not supported yet
    <Division>
    </Division>
    -->
  </League>
  <Cup>
    <BeginMonth>10</BeginMonth>
    <EndMonth>5</EndMonth>
    <Teams>32</Teams>
    <AwayGoals>0</AwayGoals>
    <Substitutes>3</Substitutes>
    <Bench>5</Bench>
    <FirstRoundNo>3</FirstRoundNo>
    <Round>54</Round>
    <Round>54</Round>
    <Round>94</Round>
    <Round>94</Round>
    <Round>14</Round>
    <!-- 
      If add more rounds in cup change Teams above and add definition below...
      Number in Round is SWOS data, 54 - one match with PENS/EXTRA time 94 - 2legs etc..
    <Round>14<Round>
    -->
  </Cup>
</Nation>
<!-- 
<Nation>
  here add another nation competition...
</Nation>
-->
```
---
# Change Log
**v0.3.2b**
- Update wrapper to SWOS 2020 v3.0.12
**v0.3.1b**
- Update wrapper to SWOS 2020 v3.0.9

**v0.3.0b**
- Add SWOSHook API to find Competition Table address automatic
- Update wrapper to SWOS 2020 v3.0.6

**v0.2.6b**
- Update to SWOS 2020 v3.0.0

**v0.2.5b**
- Fix some errors, changes in WinMM
- Update to SWOS 2020 v2.4.1

**v0.2.4b**
- Initial github release