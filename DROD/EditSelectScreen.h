// $Id$

/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is Deadly Rooms of Death.
 *
 * The Initial Developer of the Original Code is
 * Caravel Software.
 * Portions created by the Initial Developer are Copyright (C) 1995, 1996, 
 * 1997, 2000, 2001, 2002, 2005 Caravel Software. All Rights Reserved.
 *
 * Contributor(s):
 * Mike Rimer (mrimer)
 *
 * ***** END LICENSE BLOCK ***** */

#ifndef EDITSELECTSCREEN_H
#define EDITSELECTSCREEN_H

#include "DrodScreen.h"

class CDbHold;
class CDbLevel;
class CDbRoom;
class CImageWidget;
class CListBoxWidget;
class CMapWidget;
class CMoveCoord;
class CEditRoomWidget;
class CEntranceSelectDialogWidget;
class CScalerWidget;
class CEditSelectScreen : public CDrodScreen
{
public:
	UINT     GetPrevHoldID() const;
	void     ResetSelectedHold();
	void     SetToCopiedHold(CDbHold *pHold, CDbLevel *pLevel);
	WSTRING  GetSelectedStyle() const;

protected:
	friend class CDrodScreenManager;

	CEditSelectScreen();
	virtual ~CEditSelectScreen();

	virtual bool   SetForActivate();
	void     FreeMembers();
	virtual bool   UnloadOnDeactivate() const {return false;}

private:
	virtual void   OnBetweenEvents();
	virtual void   OnClick(const UINT dwTagNo);
	virtual void   OnDoubleClick(const UINT dwTagNo);
	virtual void   OnKeyDown(const UINT dwTagNo, const SDL_KeyboardEvent &Key);
	virtual void   OnRearranged(const UINT dwTagNo);
	virtual void   OnSelectChange(const UINT dwTagNo);
	virtual void   Paint(bool bUpdateRect=true);

	void     GoToRoomEditor();

	UINT     AddHold();
	void     CopyHold();
	void     EditHoldSettings();
	bool     ModifyHold();
	void     RenameHold();
	bool     SelectFirstHold();
	bool     SelectHold(const UINT dwHoldID, const bool bLoadHoldRecordOnly=false);

	void     AddNewLevelLineToLevelList();
	void     AddNewMapLineToMapList();

	UINT     AddLevel();
	void     DeleteLevel();
	void     MakeLevelFirst();
	void     RenameLevel();
	bool     SelectFirstLevel();
	bool     SelectLevel(const UINT dwLevelID, const bool bLoadLevelRecordOnly=false);

	UINT     AddRoom(const UINT dwRoomX, const UINT dwRoomY);
	void     GetLevelEntrancesInRoom();
	void     SelectLevelEntranceRoom();
	void     SelectRoom(const UINT dwRoomX, const UINT dwRoomY);
	void     SetSelectedRoom(CDbRoom *pRoom);
	void     SetRoomStyle(const WCHAR* pwStyle);

	UINT     AddWorldMap();
	void     DeleteWorldMap();
	void     RenameWorldMap();
	bool     SelectFirstWorldMap();
	bool     SelectWorldMap(const UINT dwWorldMapID);
	bool     SetImageWorldMap();
	void     DrawScaledWorldMapImage();

	bool     PasteLevel();
	void     PopulateLevelListBox();
	void     PopulateHoldListBox();
	void     PopulateStyleListBox();
	void     PopulateWorldMapListBox();
	void     ReflectLevelX();
	void     ReflectLevelY();
	void     SelectListStyle(const WSTRING& style);
	bool     SetWidgets();
	void     SetWidgetStates();

	//List of holds/levels/styles.
	CListBoxWidget *  pLevelListBoxWidget;
	CListBoxWidget *  pHoldListBoxWidget;
	CListBoxWidget *  pStyleListBoxWidget;
	CListBoxWidget *  pWorldMapListBoxWidget;
	CEntranceSelectDialogWidget * pEntranceBox;     //choose from list of levels

	//Currently selected hold/level/room.
	CDbHold *         pSelectedHold;
	CDbLevel *        pSelectedLevel;
	CDbRoom *         pSelectedRoom;
	vector<CMoveCoord*> LevelEntrances;  //level entrances in the current room
	UINT dwPrevHoldID;
	UINT selectedWorldMapID;

	CDbLevel *        pLevelCopy; //level being copied
	bool              addLevelAfterEvents, addWorldMapAfterEvents;

	//Level/room display.
	CMapWidget *      pMapWidget;
	CEditRoomWidget * pRoomWidget;
	CScalerWidget    *pScaledRoomWidget, *pScaledWorldMapWidget;
	CImageWidget     *pWorldMapImage;
};

#endif //...#ifndef EDITSELECTSCREEN_H
