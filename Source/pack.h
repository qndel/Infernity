//HEADER_GOES_HERE
#ifndef __PACK_H__
#define __PACK_H__

extern int pack_cpp_init_value; // weak

void __cdecl pack_cpp_init();
void __fastcall PackPlayer(LATEST_PKPLAYER_STRUCT *pPack, int pnum, bool manashield);
void __fastcall PackItem(PkItemStruct *id, ItemStruct *is);
void __fastcall VerifyGoldSeeds(LATEST_PLAYERSTRUCT *pPlayer);
void __fastcall UnPackPlayer(LATEST_PKPLAYER_STRUCT *pPack, int pnum, bool killok);
void __fastcall UnPackItem(PkItemStruct *is, ItemStruct *id);

/* rdata */

extern const int pack_inf; // weak

#endif /* __PACK_H__ */
