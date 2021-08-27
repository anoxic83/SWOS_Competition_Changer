/*
Copyright <2020> <AnoXic>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), 
to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, 
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#pragma once
#include <vector>
#include <sstream>
#include <cstdint>
#include <cstring>


#pragma pack(push,1)
namespace SWOS{
namespace GUI
{
	enum EntryElementCode
	{
		kEndOfEntry,
		kInvisibilityCloak,
		kPositions,
		kCustomBackgroundFunc,
		kColor,
		kBackgroundSprite,
		kInvalid,
		kCustomForegroundFunc,
		kString,
		kForegroundSprite,
		kStringTable,
		kMultiLineText,
		kInteger,
		kOnSelect,
		kOnSelectWithMask,
		kBeforeDraw,
		kOnReturn,
		kLeftSkip,
		kRightSkip,
		kUpSkip,
		kDownSkip,
		kColorConvertedSprite
	};

	struct MenuEntry
	{
		uint16_t X;
		uint16_t Y;
		uint16_t Width;
		uint16_t Height;
	};

	struct EntryElement
	{
		uint16_t ElementCode;
	};


	struct EntryText : public EntryElement
	{
		uint16_t Flags;
		const char* Text;
	};

	struct EntryColor : public EntryElement
	{
		uint16_t Color;
	};

	struct EntryPositions : public EntryElement
	{
		int8_t Left;
		int8_t Right;
		int8_t Up;
		int8_t Down;
	};
	
	struct EntryNumber : public EntryElement
	{
		uint16_t Flags;
		int16_t Number;
	};

	struct EntryStringTable : public EntryElement
	{
		uint16_t Flags;
		void* StringTable;
	};

	struct EntryOnSelect : public EntryElement
	{
		void(*onSelect)();
	};


	struct Menu
	{
		void(*onInit)();
		void(*afterDraw)();
		void(*onDraw)();
		int32_t Selected;
	};

	int16_t kEndofMenu = -999;


}
}
#pragma pack(pop)