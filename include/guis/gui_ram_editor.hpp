#pragma once

#include "guis/gui.hpp"
#include "types.h"

#include <vector>
#include <set>
#include <unordered_map>
#include <stdbool.h>

#include "helpers/debugger.hpp"
#include "helpers/memory_dump.hpp"

extern "C" {
  #include "helpers/dmntcht.h"
}

class GuiRAMEditor : public Gui {

public:
  GuiRAMEditor();
  ~GuiRAMEditor();

  void update();
  void draw();
  void onInput(u32 kdown);
  void onTouch(touchPosition &touch);
  void onGesture(touchPosition startPosition, touchPosition endPosition, bool finish);

private:
  Debugger *m_debugger;
  u8 m_ramBuffer[0x10 * 14] = { 0 };
  color_t m_memory[1024] = { 0 };

  u8 m_selectedEntry = 0;
  
  searchValue_t m_searchValue;
  enum { FORMAT_DEC, FORMAT_HEX } m_searchValueFormat = FORMAT_DEC;

  enum { CHEATS, CANDIDATES } m_menuLocation = CHEATS;
  enum { SEARCH_NONE, SEARCH_TYPE, SEARCH_MODE, SEARCH_REGION, SEARCH_VALUE } m_searchMenuLocation = SEARCH_NONE;
  searchType_t m_searchType = SEARCH_TYPE_NONE;
  searchMode_t m_searchMode = SEARCH_MODE_NONE;
  searchRegion_t m_searchRegion = SEARCH_REGION_NONE;

  std::vector<MemoryInfo> m_memoryInfo;
  MemoryDump *m_foundAddresses;
  std::map<u64, u64> m_frozenAddresses;

  bool m_attached = false;
  bool m_sysmodulePresent = false;

  u64 m_addressSpaceBaseAddr = 0x00;
  u64 m_heapBaseAddr = 0x00;
  u64 m_codeBaseAddr = 0x00;
  u8 m_buildID[0x20];

  DmntCheatEntry *m_cheats;
  u64 m_cheatCnt;

  void drawSearchRAMMenu();
};
