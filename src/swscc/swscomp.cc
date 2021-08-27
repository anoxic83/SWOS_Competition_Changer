#include "swscomp.h"
#include <cstring>
#include <pugixml.hpp>
#include "swosexe.h"




//const intptr_t CompStructPtr = 0x4768456; 
//const intptr_t CompStructPtr = 0x476A456;
//const intptr_t CompStructPtr = 0x476D456;
//const intptr_t CompStructPtr = 0x476F456;
//const intptr_t CompStructPtr = 0x477A95A;
const intptr_t CompStructPtr = 0x477A456;
const char* headch = "SWSCC";

const char* info = R"(
SWOS Competition Changer ver.0.2.4b
Author: AnoXic
------------------------------------
Info: This file is plugin to SWOS.
)";

SWSCompetitionChanger::SWSCompetitionChanger(const std::string& filename)
: m_Filename(filename)
{
  //MessageBoxA(NULL, "SWSCC Plugin sucessfull executed", "SWSCC", MB_OK);
  //
  pugi::xml_document doc;
  doc.load_file(m_Filename.c_str());
  std::vector<char> header(5);
  std::memcpy(reinterpret_cast<void*>(&header[0]), headch, 5);
  m_Data.clear();
  m_Data.insert(m_Data.begin(), header.begin(), header.end());
  m_CompAddrPairs.clear();
  for (pugi::xml_node natnode = doc.child("Nation"); natnode; natnode = natnode.next_sibling("Nation"))
  {
    int teamno = (std::string(natnode.child("TeamNo").child_value()) == "") ? 0 : std::stoi(natnode.child("TeamNo").child_value());
    if (teamno > -1)
    {
      pugi::xml_node legnode = natnode.child("League");
      SWSLeagueStr tmpc = {0,0,0,0,0,0,0,0,0,0,0,0,0};
      tmpc.CompType = SWSC_LEAGUE;
      uintptr_t compaddr;     // address in comp.table
      SWOS::ReadMemory(SWOS::GetBaseAddress()+CompStructPtr+(teamno*4), &compaddr, 4);
      uintptr_t lgeaddr;      // address lge
      SWOS::ReadMemory(compaddr, &lgeaddr, 4);
      m_CompAddrPairs.push_back(std::make_pair(compaddr, m_Data.size()));
      uint8_t compid;
      SWOS::ReadMemory(lgeaddr, &compid, 1);
      tmpc.CompID = compid;
      tmpc.NationNo = teamno;
      tmpc.StartDate = (std::string(legnode.child("BeginMonth").child_value()) == "") ? 0x20 : std::stoi(legnode.child("BeginMonth").child_value());
      tmpc.StartDate = (tmpc.StartDate - 1)*0x8;
      tmpc.EndDate = (std::string(legnode.child("EndMonth").child_value()) == "") ? 0x40 : std::stoi(legnode.child("EndMonth").child_value());
      tmpc.EndDate = (tmpc.EndDate - 1)*0x8;
      tmpc.DivisionsCount = (std::string(legnode.child("Divisions").child_value()) == "") ? 0x1 : std::stoi(legnode.child("Divisions").child_value());
      tmpc.Rounds = (std::string(legnode.child("Rounds").child_value()) == "") ? 0x2 : std::stoi(legnode.child("Rounds").child_value());
      tmpc.PtrForWin = (std::string(legnode.child("PtsForWin").child_value()) == "") ? 0x3 : std::stoi(legnode.child("PtsForWin").child_value());
      uint8_t subs = (std::string(legnode.child("Substitutes").child_value()) == "") ? 0x3 : std::stoi(legnode.child("Substitutes").child_value());
      uint8_t bench = (std::string(legnode.child("Bench").child_value()) == "") ? 0x5 : std::stoi(legnode.child("Bench").child_value());
      /*
      if (subs > 5)
        subs = 5;
      if (bench > 5)
        bench = 5;
      */
      tmpc.Substitusions = (subs << 4)+bench;
      std::vector<char> vec(sizeof(SWSLeagueStr));
      std::memcpy(reinterpret_cast<void*>(&vec[0]), reinterpret_cast<void*>(&tmpc), sizeof(SWSLeagueStr));
      m_Data.insert(m_Data.end(), vec.begin(), vec.end());
      for (pugi::xml_node divnode = legnode.child("Division"); divnode; divnode = divnode.next_sibling("Division"))
      {
        SWSDivision tmpd = {0,0,0,0,0,0};
        tmpd.Teams = (std::string(divnode.child("Teams").child_value()) == "") ? 0x10 : std::stoi(divnode.child("Teams").child_value());
        tmpd.Promoted = (std::string(divnode.child("Promoted").child_value()) == "") ? 0x0 : std::stoi(divnode.child("Promoted").child_value());
        tmpd.PromPlayOff = (std::string(divnode.child("PromPlayOff").child_value()) == "") ? 0x0 : std::stoi(divnode.child("PromPlayOff").child_value());
        tmpd.Relegated = (std::string(divnode.child("Relegated").child_value()) == "") ? 0x0 : std::stoi(divnode.child("Relegated").child_value());
        tmpd.RelPlayOff = (std::string(divnode.child("RelPlayOff").child_value()) == "") ? 0x0 : std::stoi(divnode.child("RelPlayOff").child_value());
        std::vector<char> vec(sizeof(SWSDivision));
        std::memcpy(reinterpret_cast<void*>(&vec[0]), reinterpret_cast<void*>(&tmpd), sizeof(SWSDivision));
        m_Data.insert(m_Data.end(), vec.begin(), vec.end());
      }
      char a[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
      m_Data.push_back(0);
      if (tmpc.DivisionsCount > 2)
        m_Data.insert(m_Data.end(), a, a+24);
      // END OF LEAGUE
      // BEGIN CUP
      uintptr_t cupaddr;
      SWOS::ReadMemory(compaddr+8, &cupaddr, 4);
      if (cupaddr != 0xffffffff)
      {
        m_CompAddrPairs.push_back(std::make_pair(compaddr+8, m_Data.size()));
        SWOS::ReadMemory(cupaddr, &compid, 1);
        pugi::xml_node cupnode = natnode.child("Cup");
        SWSCupStr tmpr = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        tmpr.CompID = compid;
        tmpr.CompType = SWSC_CUP;
        tmpr.NationNo = teamno;
        tmpr.StartDate = (std::string(cupnode.child("BeginMonth").child_value()) == "") ? 0x20 : std::stoi(cupnode.child("BeginMonth").child_value());
        tmpr.StartDate = (tmpr.StartDate - 1)*0x8;
        tmpr.EndDate = (std::string(cupnode.child("EndMonth").child_value()) == "") ? 0x40 : std::stoi(cupnode.child("EndMonth").child_value());
        tmpr.EndDate = (tmpr.EndDate - 1)*0x8;     
        tmpr.Teams = (std::string(cupnode.child("Teams").child_value()) == "") ? 0x10 : std::stoi(cupnode.child("Teams").child_value());
        tmpr.AwayGoals = (std::string(cupnode.child("AwayGoals").child_value()) == "") ? 0x0 : std::stoi(cupnode.child("AwayGoals").child_value());
        tmpr.FirtsRoundNo = (std::string(cupnode.child("FirstRoundNo").child_value()) == "") ? 0x1 : std::stoi(cupnode.child("FirstRoundNo").child_value());
        subs = (std::string(cupnode.child("Substitutes").child_value()) == "") ? 0x3 : std::stoi(cupnode.child("Substitutes").child_value());
        bench = (std::string(cupnode.child("Bench").child_value()) == "") ? 0x5 : std::stoi(cupnode.child("Bench").child_value());
        tmpr.Substitutions = (subs << 4)+bench;
        std::vector<char> vec2(sizeof(SWSCupStr));
        std::memcpy(reinterpret_cast<void*>(&vec2[0]), reinterpret_cast<void*>(&tmpr), sizeof(SWSCupStr));
        m_Data.insert(m_Data.end(), vec2.begin(), vec2.end());
        std::vector<char> rnds;
        for (pugi::xml_node rndnode = cupnode.child("Round"); rndnode; rndnode = rndnode.next_sibling("Round"))
        {
          uint8_t r = (std::string(rndnode.child_value()) == "") ? 0x54 : std::stoi(rndnode.child_value(), nullptr, 16);
          rnds.push_back(r);
        }
        m_Data.insert(m_Data.end(), rnds.begin(), rnds.end());
      }
    }  
  }
  for (auto addr: m_CompAddrPairs)
  {
    uintptr_t newaddress = addr.second + reinterpret_cast<uintptr_t>(&(m_Data[0]));
    SWOS::WriteMemory(addr.first, &newaddress, 4);
  }
  std::ofstream ofs("___XTEX.DTT", std::ios::binary);
  ofs.write((char*)&m_Data[0], m_Data.size());
  ofs.close();
}

void ShowInfo()
{
  MessageBoxA(0, info, "SWSCC", MB_OK);
}