#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdint>
#include <vector>
#include <filesystem>

#ifdef MAKEDLL
#  define EXPORT __declspec(dllexport)
#else
#  define EXPORT __declspec(dllimport)
#endif


#define SWSC_LEAGUE       0
#define SWSC_CUP          1
#define SWSC_TOURNAMENT   2

struct SWSDivision
{
	uint8_t Teams;
	uint8_t Promoted;
	uint8_t PromPlayOff;
	uint8_t Relegated;
	uint8_t RelPlayOff;
	uint8_t Res0;
};

struct SWSComp
{
	uint8_t CompID;
	uint8_t CompType;
	uint8_t NationNo;
	uint8_t StartDate;
	uint8_t EndDate;
	uint8_t Res0; //Relative Ptr To Names??
	uint8_t Res1; //Relative Ptr To Teams??
	uint8_t Res2;
	uint8_t Res3;
	// SWSLeague or SWSCup
};

struct SWSLeagueStr : public SWSComp
{
	uint8_t DivisionsCount;
	uint8_t Rounds;
	uint8_t PtrForWin;
	uint8_t Substitusions;
};

struct SWSCupStr: public SWSComp
{
	uint8_t Res0;
	uint8_t Teams;
	uint8_t AwayGoals;
	uint8_t Substitutions;
	uint8_t FirtsRoundNo;
	// Rounds
};



class SWSCompetitionChanger
{
  std::string m_Filename;
  std::vector<char> m_Data;
  std::vector<std::pair<uintptr_t, uintptr_t>> m_CompAddrPairs;
  // first address of SWOS competion in memory
  // second relative to begin vector address of newcomp
public:
  SWSCompetitionChanger(const std::string& filename);
  virtual ~SWSCompetitionChanger() = default;
};

extern "C"
{
  void EXPORT ShowInfo();
}