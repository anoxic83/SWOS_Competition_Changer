#pragma once
/*

MIT License

Copyright (c) 2021 Anoxic

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/
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
	uint8_t Res0;					// Relative to PlayOff
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

struct SWSCompGetTeams
{
	SWSComp* Competition;
	uint8_t Division;
	uint8_t Res0;
	uint8_t Res1;
	uint8_t Res2;
	uint8_t TeamNumber;				// Relative play-off team no // 0 - first team to qual. in play-off	
	uint8_t Res1_0;
	uint8_t Res1_1;
	uint8_t Res1_2;	
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