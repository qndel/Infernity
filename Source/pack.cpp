//HEADER_GOES_HERE

#include "../types.h"

int pack_cpp_init_value; // weak

const int pack_inf = 0x7F800000; // weak

struct pack_cpp_init
{
	pack_cpp_init()
	{
		pack_cpp_init_value = pack_inf;
	}
} _pack_cpp_init;
// 47F168: using guessed type int pack_inf;
// 67D7C8: using guessed type int pack_cpp_init_value;

void __fastcall PackPlayer(LATEST_PKPLAYER_STRUCT *pPack, int pnum, bool manashield)
{
	LATEST_PLAYERSTRUCT *pPlayer; // edi
	int i; // [esp+8h] [ebp-Ch]
	ItemStruct *pi; // [esp+Ch] [ebp-8h]
	PkItemStruct *pki; // [esp+10h] [ebp-4h]

	//memset(pPack, 0, 0x4F2);
	memset(pPack, 0, sizeof(LATEST_PKPLAYER_STRUCT));
	pPlayer = &plr[pnum];
	pPack->destAction = pPlayer->destAction;
	pPack->destParam1 = pPlayer->destParam1;
	pPack->destParam2 = pPlayer->destParam2;
	pPack->plrlevel = pPlayer->plrlevel;
	pPack->px = pPlayer->WorldX;
	pPack->py = pPlayer->WorldY;
	pPack->targx = pPlayer->_ptargx;
	pPack->targy = pPlayer->_ptargy;
	strcpy(pPack->pName, pPlayer->_pName);
	pPack->pClass = pPlayer->_pClass;
	pPack->pBaseStr = pPlayer->_pBaseStr;
	pPack->pBaseMag = pPlayer->_pBaseMag;
	pPack->pBaseDex = pPlayer->_pBaseDex;
	pPack->pBaseVit = pPlayer->_pBaseVit;
	pPack->pLevel = pPlayer->_pLevel;
	pPack->pStatPts = pPlayer->_pStatPts;
	pPack->pExperience = pPlayer->_pExperience;
	pPack->pGold = pPlayer->_pGold;
	pPack->pHPBase = pPlayer->_pHPBase;
	pPack->pMaxHPBase = pPlayer->_pMaxHPBase;
	pPack->pManaBase = pPlayer->_pManaBase;
	pPack->pMaxManaBase = pPlayer->_pMaxManaBase;
	pPack->pMemSpells = pPlayer->_pMemSpells[0];
	pPack->pMemSpells2 = pPlayer->_pMemSpells[1];

	for(i = 0; i < 37; i++)
		pPack->pSplLvl[i] = pPlayer->_pSplLvl[i];

	pki = pPack->InvBody;
	pi = pPlayer->InvBody;

	for(i = 0; i < 7; i++)
		PackItem(pki++, pi++);

	pki = pPack->InvList;
	pi = pPlayer->InvList;

	for(i = 0; i < 40; i++)
		PackItem(pki++, pi++);

	for(i = 0; i < 40; i++)
		pPack->InvGrid[i] = pPlayer->InvGrid[i];

	pPack->_pNumInv = pPlayer->_pNumInv;
	pki = pPack->SpdList;
	pi = pPlayer->SpdList;

	for(i = 0; i < 8; i++)
		PackItem(pki++, pi++);

	pPack->pDiabloKillLevel = pPlayer->pDiabloKillLevel;

	if ( gbMaxPlayers == 1 || manashield )
		pPack->pManaShield = pPlayer->pManaShield;
	else
		pPack->pManaShield = 0;

	pPack->version = CurVersion;	
	
	pPack->currentInventoryIndex=pPlayer->currentInventoryIndex;

	for (int j = 0; j < 4; ++j) {
		pPack->NumInvExpanded[j]= pPlayer->NumInvExpanded[j];
		for (i = 0; i < 40; i++) {
			pPack->InvGridExpanded[j][i] = pPlayer->InvGridExpanded[j][i];
		}
	}

	for (int j = 0; j < 4; ++j) {
		//pki = &pPack->InvListExpanded[j][0];
		//pi = &pPlayer->InvListExpanded[j][0];

		for (i = 0; i < 40; i++) {
			//PackItem(pki++, pi++);
			PackItem(&pPack->InvListExpanded[j][i], &pPlayer->InvListExpanded[j][i]);
		}


	}

	PackItem(&pPack->alternateWeapons[0], &pPlayer->alternateWeapons[0]);
	PackItem(&pPack->alternateWeapons[1], &pPlayer->alternateWeapons[1]);
	pPack->currentWeaponSet = pPlayer->currentWeaponSet;

	
	for (int j = 0; j < MAX_STASH_TABS; ++j) {
		strcpy(pPack->StashNames[j], pPlayer->StashNames[j]);
		pPack->StashNumInv[j] = pPlayer->StashNumInv[j];
		for (i = 0; i < 40; i++) {
			pPack->StashInvGrid[j][i] = pPlayer->StashInvGrid[j][i];
		}
	}

	for (int j = 0; j < MAX_STASH_TABS; ++j) {
		for (i = 0; i < 40; i++) {
			PackItem(&pPack->StashInvList[j][i], &pPlayer->StashInvList[j][i]);
		}
	}
	pPack->lastTab = pPlayer->lastTab;
	for (int i = 0; i < 12; ++i) {
		pPack->NewSpellTHotkeys[i] = pPlayer->NewSpellTHotkeys[i];
		pPack->NewSpellHotkeys[i] = pPlayer->NewSpellHotkeys[i];
	}
	
	

}
// 679660: using guessed type char gbMaxPlayers;

void __fastcall PackItem(PkItemStruct *id, ItemStruct *is)
{
	short v2; // ax
	short v3; // bx

	if ( is->_itype == -1 )
	{
		id->idx = -1;
	}
	else
	{
		id->idx = is->IDidx;
		if ( is->IDidx == IDI_EAR )
		{
			_LOBYTE(v2) = 0;
			_LOBYTE(v3) = 0;
			_HIBYTE(v2) = is->_iName[7];
			id->iCreateInfo = is->_iName[8] | v2;
			id->iSeed = is->_iName[12] | ((is->_iName[11] | ((is->_iName[10] | (is->_iName[9] << 8)) << 8)) << 8);
			id->bId = is->_iName[13];
			id->bDur = is->_iName[14];
			id->bMDur = is->_iName[15];
			id->bCh = is->_iName[16];
			id->bMCh = is->_iName[17];
			_HIBYTE(v3) = is->_iName[18];
			id->wValue = _LOWORD(is->_ivalue) | v3 | ((_LOWORD(is->_iCurs) - 19) << 6);
			id->dwBuff = is->_iName[22] | ((is->_iName[21] | ((is->_iName[20] | (is->_iName[19] << 8)) << 8)) << 8);
		}
		else
		{
			id->iSeed = is->_iSeed;
			id->iCreateInfo = is->_iCreateInfo;
			id->bId = _LOBYTE(is->_iIdentified) + 2 * is->_iMagical;
			id->bDur = is->_iDurability;
			id->bMDur = is->_iMaxDur;
			id->bCh = is->_iCharges;
			id->bMCh = is->_iMaxCharges;
			id->dwBuff = is->isRare;
			if ( !is->IDidx )
				id->wValue = is->_ivalue;
		}
	}
}

void __fastcall VerifyGoldSeeds(LATEST_PLAYERSTRUCT *pPlayer)
{
	int i; // ebp
	int j; // ecx

	for(i = 0; i < pPlayer->_pNumInv; i++)
	{
		if ( pPlayer->InvList[i].IDidx == IDI_GOLD && pPlayer->_pNumInv > 0 )
		{
			for(j = 0; j < pPlayer->_pNumInv; j++)
			{
				if ( i != j )
				{
					if ( pPlayer->InvList[j].IDidx == IDI_GOLD && pPlayer->InvList[i]._iSeed == pPlayer->InvList[j]._iSeed )
					{
						pPlayer->InvList[i]._iSeed = GetRndSeed();
						j = -1;
					}
				}
			}
		}
	}
}

void __fastcall UnPackPlayer(LATEST_PKPLAYER_STRUCT *pPack, int pnum, bool killok)
{
	LATEST_PLAYERSTRUCT *pPlayer; // esi
	signed int v6; // eax
	int i; // [esp+10h] [ebp-8h]
	ItemStruct *pi; // [esp+14h] [ebp-4h]
	PkItemStruct *pki; // [esp+20h] [ebp+8h]

	pPlayer = &plr[pnum];
	ClearPlrRVars(&plr[pnum]);
	pPlayer->WorldX = (unsigned char)pPack->px;
	pPlayer->WorldY = (unsigned char)pPack->py;
	pPlayer->_px = (unsigned char)pPack->px;
	pPlayer->_py = (unsigned char)pPack->py;
	pPlayer->_ptargx = (unsigned char)pPack->targx;
	pPlayer->_ptargy = (unsigned char)pPack->targy;
	pPlayer->plrlevel = (unsigned char)pPack->plrlevel;
	ClrPlrPath(pnum);
	pPlayer->destAction = -1;
	strcpy(pPlayer->_pName, pPack->pName);
	_LOBYTE(pPlayer->_pClass) = pPack->pClass;
	InitPlayer(pnum, TRUE);
	pPlayer->_pBaseStr = (unsigned char)pPack->pBaseStr;
	pPlayer->_pStrength = (unsigned char)pPack->pBaseStr;
	pPlayer->_pBaseMag = (unsigned char)pPack->pBaseMag;
	pPlayer->_pMagic = (unsigned char)pPack->pBaseMag;
	pPlayer->_pBaseDex = (unsigned char)pPack->pBaseDex;
	pPlayer->_pDexterity = (unsigned char)pPack->pBaseDex;
	pPlayer->_pBaseVit = (unsigned char)pPack->pBaseVit;
	pPlayer->_pVitality = (unsigned char)pPack->pBaseVit;
	pPlayer->_pLevel = pPack->pLevel;
	pPlayer->_pStatPts = (unsigned char)pPack->pStatPts;
	pPlayer->_pExperience = pPack->pExperience;
	pPlayer->_pGold = pPack->pGold;
	pPlayer->_pMaxHPBase = pPack->pMaxHPBase;
	v6 = pPack->pHPBase;
	pPlayer->_pHPBase = v6;
	if ( !killok )
	{
		_LOBYTE(v6) = v6 & 0xC0;
		if ( v6 < 64 )
			pPlayer->_pHPBase = 64;
	}
	pPlayer->_pMaxManaBase = pPack->pMaxManaBase;
	pPlayer->_pManaBase = pPack->pManaBase;
	pPlayer->_pMemSpells[0] = pPack->pMemSpells;
	pPlayer->_pMemSpells[1] = pPack->pMemSpells2;

	for(i = 0; i < 37; i++)
		pPlayer->_pSplLvl[i] = pPack->pSplLvl[i];

	pki = pPack->InvBody;
	pi = pPlayer->InvBody;

	for(i = 0; i < 7; i++)
		UnPackItem(pki++, pi++);

	pki = pPack->InvList;
	pi = pPlayer->InvList;

	for(i = 0; i < 40; i++)
		UnPackItem(pki++, pi++);

	for(i = 0; i < 40; i++)
		pPlayer->InvGrid[i] = pPack->InvGrid[i];

	pPlayer->_pNumInv = (unsigned char)pPack->_pNumInv;
	VerifyGoldSeeds(pPlayer);

	pki = pPack->SpdList;
	pi = pPlayer->SpdList;

	for(i = 0; i < 8; i++)
		UnPackItem(pki++, pi++);

	if ( pnum == myplr )
	{
		for(i = 0; i < 20; i++)
			witchitem[i]._itype = -1;
	}


	//CalcPlrInv(pnum, 0);
	pPlayer->pTownWarps = 0;
	pPlayer->pDungMsgs = 0;
	pPlayer->pLvlLoad = 0;
	pPlayer->pDiabloKillLevel = pPack->pDiabloKillLevel;
	pPlayer->pBattleNet = pPack->pBattleNet;
	pPlayer->pManaShield = pPack->pManaShield;
	pPlayer->version = pPack->version;
	SaveVersion = pPlayer->version;
	
	if (pPlayer->version > 0) {
		pPlayer->currentInventoryIndex = pPack->currentInventoryIndex;

		for (int j = 0; j < 4; ++j) {
			 pPlayer->NumInvExpanded[j]= pPack->NumInvExpanded[j];
			for (i = 0; i < 40; i++)
				pPlayer->InvGridExpanded[j][i] = pPack->InvGridExpanded[j][i];
		}


		for (int j = 0; j < 4; ++j) {
			//pki = &pPack->InvListExpanded[j][0];
			//pi = &pPlayer->InvListExpanded[j][0];

			for (i = 0; i < 40; i++) {
				//UnPackItem(pki++, pi++);
				UnPackItem(&pPack->InvListExpanded[j][i], &pPlayer->InvListExpanded[j][i]);
			}
		}
		//SwitchInvTab(pPack->currentInventoryIndex);
	}

	if (pPlayer->version > 1) {
		pPlayer->currentWeaponSet = pPack->currentWeaponSet;
		UnPackItem(&pPack->alternateWeapons[0], &pPlayer->alternateWeapons[0]);
		UnPackItem(&pPack->alternateWeapons[1], &pPlayer->alternateWeapons[1]);
	}
	else {
		memset(&pPlayer->alternateWeapons[0], 0, StructSize<ItemStruct>());
		memset(&pPlayer->alternateWeapons[1], 0, StructSize<ItemStruct>());
		pPlayer->alternateWeapons[0]._itype = -1;
		pPlayer->alternateWeapons[1]._itype = -1;
	}

	
	
	if (pPlayer->version > 3) {

		pPlayer->lastTab = pPack->lastTab;
		for (int i = 0; i < MAX_STASH_TABS; ++i) {
			strcpy(&pPlayer->StashNames[i][0], &pPack->StashNames[i][0]);
			pPlayer->StashNumInv[i] = pPack->StashNumInv[i];
			for (int j = 0; j < 40; ++j) {
				UnPackItem(&pPack->StashInvList[i][j], &pPlayer->StashInvList[i][j]);
				pPlayer->StashInvGrid[i][j] = pPack->StashInvGrid[i][j];
			}
		}
	}
	else {
		pPlayer->lastTab = 0;
		for (int i = 0; i < MAX_STASH_TABS; ++i) {
			strcpy(&pPlayer->StashNames[i][0], "Click to rename");
			pPlayer->StashNumInv[i] = 0;
			for (int j = 0; j < 40; ++j) {
				memset(&pPlayer->StashInvList[i][j], 0, StructSize<ItemStruct>());
				pPlayer->StashInvList[i][j]._itype = -1;
				pPlayer->StashInvGrid[i][j] = 0;
			}
		}
	}
	for (int i = 0; i < 12; ++i) {
		if (pPlayer->version > 4) {
			pPlayer->NewSpellHotkeys[i] = pPack->NewSpellHotkeys[i];
			pPlayer->NewSpellTHotkeys[i] = pPack->NewSpellTHotkeys[i];
		}
		else {
			pPlayer->NewSpellHotkeys[i] = -1;
			pPlayer->NewSpellTHotkeys[i] = -1;
		}
	}
	
	CalcPlrInv(pnum, 0);
}

// Note: last slot of item[MAXITEMS+1] used as temporary buffer
// find real name reference below, possibly [sizeof(item[])/sizeof(ItemStruct)]
void __fastcall UnPackItem(PkItemStruct *is, ItemStruct *id)
{
	PkItemStruct *v2; // esi
	ItemStruct *v3; // edi
	int v5; // ecx

	v2 = is;
	v3 = id;

	if ( is->idx == -1 )
	{
		id->_itype = -1;
	}
	else
	{
		if ( is->idx == IDI_EAR )
		{
			RecreateEar(
				MAXITEMS,
				is->iCreateInfo,
				is->iSeed,
				is->bId,
				(unsigned char)is->bDur,
				(unsigned char)is->bMDur,
				(unsigned char)is->bCh,
				(unsigned char)is->bMCh,
				(unsigned short)is->wValue,
				is->dwBuff);
		}
		else
		{
			v5 = (unsigned short)is->wValue;
			_LOWORD(v5) = v2->iCreateInfo;
			RecreateItem(MAXITEMS, is->idx, v5, v2->iSeed, (unsigned short)v2->wValue, v2->dwBuff);
			item[MAXITEMS]._iMagical = (unsigned char)v2->bId >> 1;
			item[MAXITEMS]._iIdentified = v2->bId & 1;
			item[MAXITEMS]._iDurability = (unsigned char)v2->bDur;
			item[MAXITEMS]._iMaxDur = (unsigned char)v2->bMDur;
			item[MAXITEMS]._iCharges = (unsigned char)v2->bCh;
			item[MAXITEMS]._iMaxCharges = (unsigned char)v2->bMCh;
			item[MAXITEMS].isRare = v2->dwBuff;
		}
		qmemcpy(v3, &item[MAXITEMS], sizeof(ItemStruct));
	}
}
