//HEADER_GOES_HERE

#include "../types.h"

void __fastcall town_clear_upper_buf(unsigned char *a1)
{
	unsigned char *v1; // edi
	signed int v2; // edx
	signed int v3; // ebx
	unsigned char *v4; // edi
	signed int v5; // edx
	signed int v6; // ebx
	unsigned char *v7; // edi

	v1 = a1;
	v2 = 30;
	v3 = 1;
	while ( v1 >= gpBufEnd )
	{
		v4 = &v1[v2];
		memset(v4, 0, 4 * v3);
		v1 = &v4[4 * v3 - (WorkingWidth + 64) + v2];
		if ( !v2 )
		{
			v5 = 2;
			v6 = 15;
			do
			{
				if ( v1 < gpBufEnd )
					break;
				v7 = &v1[v5];
				memset(v7, 0, 4 * v6);
				v1 = &v7[4 * v6-- - (WorkingWidth + 64) + v5];
				v5 += 2;
			}
			while ( v5 != 32 );
			return;
		}
		v2 -= 2;
		++v3;
	}
}
// 69CF0C: using guessed type int gpBufEnd;

void __fastcall town_clear_low_buf(unsigned char *y_related)
{
	return;
	unsigned char *v1; // edi
	signed int v2; // edx
	signed int i; // ebx
	unsigned char *v4; // edi
	unsigned char *v5; // edi
	signed int v6; // edx
	signed int v7; // ebx
	unsigned char *v8; // edi
	unsigned char *v9; // edi

	v1 = y_related;
	v2 = 30;
	for ( i = 1; ; ++i )
	{
		if ( v1 < gpBufEnd )
		{
			v5 = &v1[v2];
			memset(v5, 0, 4 * i);
			v4 = &v5[4 * i + v2];
		}
		else
		{
			v4 = v1 + 64;
		}
		v1 = v4 - (WorkingWidth + 64);
		if ( !v2 )
			break;
		v2 -= 2;
	}
	v6 = 2;
	v7 = 15;
	do
	{
		if ( v1 < gpBufEnd )
		{
			v9 = &v1[v6];
			memset(v9, 0, 4 * v7);
			v8 = &v9[4 * v7 + v6];
		}
		else
		{
			v8 = v1 + 64;
		}
		v1 = v8 - (WorkingWidth + 64);
		--v7;
		v6 += 2;
	}
	while ( v6 != 32 );
}
// 69CF0C: using guessed type int gpBufEnd;

void __fastcall town_draw_clipped_e_flag(void *buffer, int x, int y, int sx, int sy)
{
	int v5; // ebx
	char *v6; // esi
	signed int v7; // edi
	int v8; // eax
	int v9; // eax
	void *unused; // [esp+Ch] [ebp-8h]
	unsigned char *a1; // [esp+10h] [ebp-4h]

	v5 = x;
	unused = buffer;
	a1 = (unsigned char *)buffer;
	v6 = (char *)dpiece_defs_map_1 + 32 * gendung_get_dpiece_num_from_coord(x, y);
	v7 = 0;
	do
	{
		v8 = *(unsigned short *)&v6[2 * v7];
		level_cel_block = *(unsigned short *)&v6[2 * v7];
		if ( v8 )
			drawLowerScreen(a1);
		v9 = *(unsigned short *)&v6[2 * v7 + 2];
		level_cel_block = *(unsigned short *)&v6[2 * v7 + 2];
		if ( v9 )
			drawLowerScreen(a1 + 32);
		a1 -= WorkingWidth * 32;
		v7 += 2;
	}
	while ( v7 < 12 );
	town_draw_clipped_town(unused, v5, y, sx, sy, 0);
}
// 69CF14: using guessed type int level_cel_block;

void __fastcall town_draw_clipped_town(void *unused, int x, int y, int sx, int sy, int some_flag)
{
	unsigned int v6; // edx
	int v7; // edi
	char v8; // al
	char v9; // al
	int v10; // esi
	int v11; // ebx
	int v12; // esi
	int v13; // ebx
	int v14; // eax
	int v15; // eax
	int v16; // esi
	int v17; // ebx
	char v18; // al
	int v19; // esi
	int v20; // ebx
	int v21; // edi
	char v22; // al
	char v23; // al
	int v24; // esi
	int v25; // ebx
	int v26; // edi
	char *v27; // [esp+Ch] [ebp-Ch]
	int xa; // [esp+10h] [ebp-8h]
	int v29; // [esp+14h] [ebp-4h]

	xa = x;
	v6 = 112 * x;
	v27 = (char *)gpBuffer + screen_y_times_width[sy] + sx;
	v7 = v6 + y;
	v29 = v6 + y;
	v8 = dItem[v6 / 0x70][y];
	if ( v8 )
	{
		v9 = v8 - 1;
		v10 = v9;
		v11 = sx - item[v10]._iAnimWidth2;
		AddItemToDrawQueue(v11, sy, v10);
		if (v9 == pcursitem || ShouldHighlightItems) {
			int color = GetItemHighlightColor(v9);
			CelDrawHdrClrHL(color,v11,sy,(char *)item[v10]._iAnimData,item[v10]._iAnimFrame,item[v10]._iAnimWidth,0,8);// was 181
		}
		Cel2DrawHdrOnly(v11, sy, (char *)item[v10]._iAnimData, item[v10]._iAnimFrame, item[v10]._iAnimWidth, 0, 8);
	}
	if ( dFlags[0][v7] & 0x10 )
	{
		v12 = -1 - dMonster[x][y-1]; // -1 - *(&dword_52D204 + v7); /* check */
		v13 = sx - towner[v12]._tAnimWidth2;
		if ( v12 == pcursmonst )
			CelDrawHdrClrHL(
				166,
				v13,
				sy,
				(char *)towner[v12]._tAnimData,
				towner[v12]._tAnimFrame,
				towner[v12]._tAnimWidth,
				0,
				8);
		Cel2DrawHdrOnly(v13, sy, (char *)towner[v12]._tAnimData, towner[v12]._tAnimFrame, towner[v12]._tAnimWidth, 0, 8);
	}
	v14 = dMonster[0][v7];
	if ( v14 > 0 )
	{
		v15 = v14 - 1;
		v16 = v15;
		v17 = sx - towner[v15]._tAnimWidth2;
		if ( v15 == pcursmonst )
			CelDrawHdrClrHL(
				166,
				v17,
				sy,
				(char *)towner[v16]._tAnimData,
				towner[v16]._tAnimFrame,
				towner[v16]._tAnimWidth,
				0,
				8);
		Cel2DrawHdrOnly(v17, sy, (char *)towner[v16]._tAnimData, towner[v16]._tAnimFrame, towner[v16]._tAnimWidth, 0, 8);
	}
	if ( dFlags[0][v7] & 0x20 )
	{
		v18 = -1 - dPlayer[x][y-1]; // -1 - *((_BYTE *)&themeLoc[49].height + v7 + 3);
		v19 = v18;
		v20 = sy + plr[v19]._pyoff;
		v21 = sx + plr[v19]._pxoff - plr[v19]._pAnimWidth2;
		if ( v18 == pcursplr )
			Cl2DecodeClrHL(165, v21, v20, (char *)plr[v19]._pAnimData, plr[v19]._pAnimFrame, plr[v19]._pAnimWidth, 0, 8);
		Cl2DecodeFrm4(v21, v20, (char *)plr[v19]._pAnimData, plr[v19]._pAnimFrame, plr[v19]._pAnimWidth, 0, 8);
		if ( some_flag && plr[v19]._peflag )
			town_draw_clipped_e_flag(v27 - 64, xa - 1, y + 1, sx - 64, sy);
		v7 = v29;
	}
	if ( dFlags[0][v7] & 4 )
		DrawDeadPlayer(xa, y, sx, sy, 0, 8, 1);
	v22 = dPlayer[0][v7];
	if ( v22 > 0 )
	{
		v23 = v22 - 1;
		v24 = v23;
		v25 = sy + plr[v24]._pyoff;
		v26 = sx + plr[v24]._pxoff - plr[v24]._pAnimWidth2;
		if ( v23 == pcursplr )
			Cl2DecodeClrHL(165, v26, v25, (char *)plr[v24]._pAnimData, plr[v24]._pAnimFrame, plr[v24]._pAnimWidth, 0, 8);
		Cl2DecodeFrm4(v26, v25, (char *)plr[v24]._pAnimData, plr[v24]._pAnimFrame, plr[v24]._pAnimWidth, 0, 8);
		if ( some_flag && plr[v24]._peflag )
			town_draw_clipped_e_flag(v27 - 64, xa - 1, y + 1, sx - 64, sy);
		v7 = v29;
	}
	if ( dFlags[0][v7] & 1 )
		DrawClippedMissile(xa, y, sx, sy, 0, 8, 0);
}
// 4B8CC0: using guessed type char pcursitem;
// 4B8CC2: using guessed type char pcursplr;

void __fastcall town_draw_lower(int x, int y, int sx, int sy, int a5, int some_flag)
{
	int v6; // ebx
	int *v7; // edi
	char *v8; // esi
	int v9; // eax
	int v10; // eax
	int *v11; // ebx
	int v12; // esi
	unsigned char *v13; // esi
	char *v14; // edi
	int v15; // eax
	int v16; // eax
	bool v17; // zf
	int *v18; // ebx
	unsigned char *v19; // esi
	char *v20; // edi
	int v21; // eax
	unsigned char *a1; // [esp+Ch] [ebp-10h]
	int a1a; // [esp+Ch] [ebp-10h]
	int ya; // [esp+10h] [ebp-Ch]
	signed int v25; // [esp+14h] [ebp-8h]
	signed int v26; // [esp+14h] [ebp-8h]
	signed int v27; // [esp+14h] [ebp-8h]
	signed int xa; // [esp+18h] [ebp-4h]
	int a5a; // [esp+2Ch] [ebp+10h]

	ya = y;
	xa = x;
	if ( some_flag )
	{
		if ( y >= 0 && y < 112 && x >= 0 && x < 112 && (level_cel_block = dPiece[0][y + 112 * x]) != 0 )
		{
			v6 = sy;
			v7 = &screen_y_times_width[sy];
			a1 = (unsigned char *)&gpBuffer->row_unused_1[0].col_unused_1[*v7 + 32 + sx];
			v25 = 1;
			v8 = (char *)dpiece_defs_map_1 + 32 * gendung_get_dpiece_num_from_coord(x, y);
			do
			{
				v9 = *(unsigned short *)&v8[2 * v25];
				level_cel_block = *(unsigned short *)&v8[2 * v25];
				if ( v9 )
					drawLowerScreen(a1);
				v25 += 2;
				a1 -= WorkingWidth * 32;
			}
			while ( v25 < 17 );
			town_draw_clipped_town((char *)gpBuffer + *v7 + sx, xa, ya, sx, sy, 0);
		}
		else
		{
			town_clear_low_buf((unsigned char *)gpBuffer + screen_y_times_width[sy] + sx);
			v6 = sy;
		}
		++xa;
		y = ya - 1;
		sx += 64;
		--ya;
	}
	else
	{
		v6 = sy;
	}
	v10 = a5 - some_flag;
	if ( a5 - some_flag > 0 )
	{
		v11 = &screen_y_times_width[v6];
		v12 = 112 * xa;
		a5a = 112 * xa;
		a1a = v10;
		do
		{
			if ( y >= 0 && y < 112 && v12 >= 0 && v12 < 112*112 && (level_cel_block = dPiece[0][v12 + y]) != 0 )
			{
				v13 = (unsigned char *)gpBuffer + *v11 + sx;
				v14 = (char *)dpiece_defs_map_1 + 32 * gendung_get_dpiece_num_from_coord(xa, ya);
				v26 = 0;
				do
				{
					v15 = *(unsigned short *)&v14[2 * v26];
					level_cel_block = *(unsigned short *)&v14[2 * v26];
					if ( v15 )
						drawLowerScreen(v13);
					v16 = *(unsigned short *)&v14[2 * v26 + 2];
					level_cel_block = *(unsigned short *)&v14[2 * v26 + 2];
					if ( v16 )
						drawLowerScreen(v13 + 32);
					v26 += 2;
					v13 -= WorkingWidth * 32;
				}
				while ( v26 < 16 );
				town_draw_clipped_town((char *)gpBuffer + *v11 + sx, xa, ya, sx, sy, 1);
				v12 = a5a;
			}
			else
			{
				town_clear_low_buf((unsigned char *)gpBuffer + *v11 + sx);
			}
			++xa;
			sx += 64;
			v12 += 112;
			y = ya - 1;
			v17 = a1a-- == 1;
			a5a = v12;
			--ya;
		}
		while ( !v17 );
		v6 = sy;
	}
	if ( some_flag )
	{
		if ( y >= 0 && y < 112 && xa >= 0 && xa < 112 && (level_cel_block = dPiece[0][y + 112 * xa]) != 0 )
		{
			v18 = &screen_y_times_width[v6];
			v19 = (unsigned char *)gpBuffer + *v18 + sx;
			v20 = (char *)dpiece_defs_map_1 + 32 * gendung_get_dpiece_num_from_coord(xa, ya);
			v27 = 0;
			do
			{
				v21 = *(unsigned short *)&v20[2 * v27];
				level_cel_block = *(unsigned short *)&v20[2 * v27];
				if ( v21 )
					drawLowerScreen(v19);
				v27 += 2;
				v19 -= WorkingWidth * 32;
			}
			while ( v27 < 16 );
			town_draw_clipped_town((char *)gpBuffer + *v18 + sx, xa, ya, sx, sy, 0);
		}
		else
		{
			town_clear_low_buf((unsigned char *)gpBuffer + screen_y_times_width[v6] + sx);
		}
	}
}
// 69CF14: using guessed type int level_cel_block;

void __fastcall town_draw_clipped_e_flag_2(void *buffer, int x, int y, int a4, int a5, int sx, int sy)
{
	int v7; // ebx
	unsigned char *v8; // edi
	short *v9; // esi
	int v10; // eax
	int v11; // eax
	void *v12; // [esp+8h] [ebp-8h]
	int xa; // [esp+Ch] [ebp-4h]
	int a4a; // [esp+1Ch] [ebp+Ch]

	v7 = a4;
	xa = x;
	v12 = buffer;
	if ( a4 )
		v8 = (unsigned char *)buffer + WorkingWidth * 32 * a4;
	else
		v8 = (unsigned char *)buffer;
	a4a = 0;
	v9 = &dpiece_defs_map_1[0][0][16 * gendung_get_dpiece_num_from_coord(x, y) + 3];
	do
	{
		if ( v7 <= a4a )
		{
			v10 = (unsigned short)*(v9 - 1);
			level_cel_block = (unsigned short)*(v9 - 1);
			if ( v10 )
				drawLowerScreen(v8);
			v11 = (unsigned short)*v9;
			level_cel_block = (unsigned short)*v9;
			if ( v11 )
				drawLowerScreen(v8 + 32);
		}
		v8 -= WorkingWidth * 32;
		++a4a;
		v9 += 2;
	}
	while ( a4a < 6 );
	if ( a5 < 8 )
		town_draw_clipped_town_2((int)v12, xa, y, v7, a5, sx, sy, 0);
}
// 69CF14: using guessed type int level_cel_block;

void __fastcall town_draw_clipped_town_2(int x, int y, int a3, int a4, int a5, int sx, int sy, int some_flag)
{
	unsigned int v8; // edx
	int v9; // ebx
	char v10; // al
	char v11; // al
	int v12; // esi
	int v13; // edi
	int v14; // esi
	int v15; // edi
	int v16; // eax
	int v17; // eax
	int v18; // esi
	int v19; // edi
	char v20; // al
	int v21; // esi
	int v22; // ebx
	int v23; // edi
	char v24; // al
	char v25; // al
	int v26; // esi
	int v27; // ebx
	int v28; // edi
	int v29; // [esp+Ch] [ebp-Ch]
	int xa; // [esp+10h] [ebp-8h]
	int v31; // [esp+14h] [ebp-4h]

	xa = y;
	v8 = 112 * y;
	v9 = v8 + a3;
	v29 = x;
	v31 = v8 + a3;
	v10 = dItem[v8 / 0x70][a3];
	if ( v10 )
	{
		v11 = v10 - 1;
		v12 = v11;
		v13 = sx - item[v12]._iAnimWidth2;
		AddItemToDrawQueue(v13, sy, v12);
		if (v11 == pcursitem || ShouldHighlightItems) {
			int color = GetItemHighlightColor(v11);
			CelDrawHdrClrHL(color,v13,sy,(char *)item[v12]._iAnimData,item[v12]._iAnimFrame,item[v12]._iAnimWidth,a5,8);//was 181
		}
		Cel2DrawHdrOnly(v13, sy, (char *)item[v12]._iAnimData, item[v12]._iAnimFrame, item[v12]._iAnimWidth, a5, 8);
	}
	if ( dFlags[0][v9] & 0x10 )
	{
		v14 = -1 - dMonster[x][y-1]; // -1 - *(&dword_52D204 + v9); /* check */
		v15 = sx - towner[v14]._tAnimWidth2;
		if ( v14 == pcursmonst )
			CelDrawHdrClrHL(
				166,
				v15,
				sy,
				(char *)towner[v14]._tAnimData,
				towner[v14]._tAnimFrame,
				towner[v14]._tAnimWidth,
				a5,
				8);
		Cel2DrawHdrOnly(v15, sy, (char *)towner[v14]._tAnimData, towner[v14]._tAnimFrame, towner[v14]._tAnimWidth, a5, 8);
	}
	v16 = dMonster[0][v9];
	if ( v16 > 0 )
	{
		v17 = v16 - 1;
		v18 = v17;
		v19 = sx - towner[v17]._tAnimWidth2;
		if ( v17 == pcursmonst )
			CelDrawHdrClrHL(
				166,
				v19,
				sy,
				(char *)towner[v18]._tAnimData,
				towner[v18]._tAnimFrame,
				towner[v18]._tAnimWidth,
				a5,
				8);
		Cel2DrawHdrOnly(v19, sy, (char *)towner[v18]._tAnimData, towner[v18]._tAnimFrame, towner[v18]._tAnimWidth, a5, 8);
	}
	if ( dFlags[0][v9] & 0x20 )
	{
			v20 = -1 - dPlayer[x][y]; // was dPlayer[x][y-1]// -1 - *((_BYTE *)&themeLoc[49].height + v9 + 3);
		v21 = v20;
		v22 = sy + plr[v21]._pyoff;
		v23 = sx + plr[v21]._pxoff - plr[v21]._pAnimWidth2;
		if ( v20 == pcursplr )
			Cl2DecodeClrHL(165, v23, v22, (char *)plr[v21]._pAnimData, plr[v21]._pAnimFrame, plr[v21]._pAnimWidth, a5, 8);
		Cl2DecodeFrm4(v23, v22, (char *)plr[v21]._pAnimData, plr[v21]._pAnimFrame, plr[v21]._pAnimWidth, a5, 8);
		if ( some_flag && plr[v21]._peflag )
			town_draw_clipped_e_flag_2((void *)(v29 - 64), xa - 1, a3 + 1, a4, a5, sx - 64, sy);
		v9 = v31;
	}
	if ( dFlags[0][v9] & 4 )
		DrawDeadPlayer(xa, a3, sx, sy, a5, 8, 1);
	v24 = dPlayer[0][v9];
	if ( v24 > 0 )
	{
		v25 = v24 - 1;
		v26 = v25;
		v27 = sy + plr[v26]._pyoff;
		v28 = sx + plr[v26]._pxoff - plr[v26]._pAnimWidth2;
		if ( v25 == pcursplr )
			Cl2DecodeClrHL(165, v28, v27, (char *)plr[v26]._pAnimData, plr[v26]._pAnimFrame, plr[v26]._pAnimWidth, a5, 8);
		Cl2DecodeFrm4(v28, v27, (char *)plr[v26]._pAnimData, plr[v26]._pAnimFrame, plr[v26]._pAnimWidth, a5, 8);
		if ( some_flag && plr[v26]._peflag )
			town_draw_clipped_e_flag_2((void *)(v29 - 64), xa - 1, a3 + 1, a4, a5, sx - 64, sy);
		v9 = v31;
	}
	if ( dFlags[0][v9] & 1 )
		DrawClippedMissile(xa, a3, sx, sy, a5, 8, 0);
}
// 4B8CC0: using guessed type char pcursitem;
// 4B8CC2: using guessed type char pcursplr;

void __fastcall town_draw_lower_2(int x, int y, int sx, int sy, int a5, int a6, int some_flag)
{
	int v7; // esi
	int v8; // ebx
	int *v9; // edi
	short *v10; // eax
	int v11; // esi
	int v12; // eax
	int *v13; // ebx
	int v14; // edi
	short *v15; // edi
	int v16; // eax
	int v17; // eax
	int v18; // eax
	bool v19; // zf
	int *v20; // edi
	short *v21; // ebx
	int v22; // eax
	short *v23; // [esp+Ch] [ebp-10h]
	int v24; // [esp+Ch] [ebp-10h]
	unsigned char *a1; // [esp+10h] [ebp-Ch]
	unsigned char *a1a; // [esp+10h] [ebp-Ch]
	unsigned char *a1b; // [esp+10h] [ebp-Ch]
	signed int ya; // [esp+14h] [ebp-8h]
	signed int xa; // [esp+18h] [ebp-4h]
	signed int sxa; // [esp+24h] [ebp+8h]
	signed int sxb; // [esp+24h] [ebp+8h]
	signed int sxc; // [esp+24h] [ebp+8h]
	int a5a; // [esp+2Ch] [ebp+10h]
	ya = y;
	xa = x;
	if ( some_flag )
	{
		if ( y < 0 || y >= 112 || x < 0 || x >= 112 )
		{
			v7 = sx;
		}
		else
		{
			v7 = sx;
			level_cel_block = dPiece[0][y + 112 * x];
			if ( level_cel_block )
			{
				v8 = sy;
				v9 = &screen_y_times_width[sy];
				a1 = (unsigned char *)gpBuffer + *v9 + sx - (WorkingWidth * 31 + 736); //24544
				sxa = 0;
				v10 = &dpiece_defs_map_1[0][0][16 * gendung_get_dpiece_num_from_coord(x, y) + 3];
				v23 = v10;
				do
				{
					if ( a6 <= sxa )
					{
						level_cel_block = (unsigned short)*v10;
						if ( level_cel_block )
							drawLowerScreen(a1);
					}
					a1 -= WorkingWidth * 32;
					++sxa;
					v10 = v23 + 2;
					v23 += 2;
				}
				while ( sxa < 7 );
				if ( 2 * a6 + 2 < 8 )
					town_draw_clipped_town_2((int)gpBuffer + *v9 + v7, xa, ya, a6, 2 * a6 + 2, v7, sy, 0);
				goto LABEL_16;
			}
		}
		town_clear_low_buf((unsigned char *)gpBuffer + screen_y_times_width[sy] + v7);
		v8 = sy;
LABEL_16:
		++xa;
		--ya;
		v11 = v7 + 64;
		goto LABEL_18;
	}
	v11 = sx;
	v8 = sy;
LABEL_18:
	v12 = a5 - some_flag;
	if ( a5 - some_flag > 0 )
	{
		v13 = &screen_y_times_width[v8];
		v14 = 112 * xa;
		a5a = 112 * xa;
		v24 = v12;
		do
		{
			if ( ya >= 0 && ya < 112 && v14 >= 0 && v14 < 12544 && (level_cel_block = dPiece[0][v14 + ya]) != 0 )
			{
				a1a = (unsigned char *)gpBuffer + *v13 + v11 - WorkingWidth * 32;
				sxb = 0;
				v15 = &dpiece_defs_map_1[0][0][16 * gendung_get_dpiece_num_from_coord(xa, ya) + 3];
				do
				{
					if ( a6 <= sxb )
					{
						v16 = (unsigned short)*(v15 - 1);
						level_cel_block = (unsigned short)*(v15 - 1);
						if ( v16 )
							drawLowerScreen(a1a);
						v17 = (unsigned short)*v15;
						level_cel_block = (unsigned short)*v15;
						if ( v17 )
							drawLowerScreen(a1a + 32);
					}
					a1a -= WorkingWidth * 32;
					++sxb;
					v15 += 2;
				}
				while ( sxb < 7 );
				v18 = 2 * a6 + 2;
				if ( v18 < 8 )
					town_draw_clipped_town_2((int)gpBuffer + *v13 - WorkingWidth*16 * v18 + v11, xa, ya, a6, 2 * a6 + 2, v11, sy, 1);
				v14 = a5a;
			}
			else
			{
				town_clear_low_buf((unsigned char *)gpBuffer + *v13 + v11);
			}
			++xa;
			v14 += 112;
			--ya;
			v11 += 64;
			v19 = v24-- == 1;
			a5a = v14;
		}
		while ( !v19 );
		v8 = sy;
	}
	if ( some_flag )
	{
		if ( ya >= 0 && ya < 112 && xa >= 0 && xa < 112 && (level_cel_block = dPiece[0][ya + 112 * xa]) != 0 )
		{
			v20 = &screen_y_times_width[v8];
			a1b = (unsigned char *)gpBuffer + *v20 + v11 - WorkingWidth * 32;
			sxc = 0;
			v21 = &dpiece_defs_map_1[0][0][16 * gendung_get_dpiece_num_from_coord(xa, ya) + 2];
			do
			{
				if ( a6 <= sxc )
				{
					v22 = (unsigned short)*v21;
					level_cel_block = (unsigned short)*v21;
					if ( v22 )
						drawLowerScreen(a1b);
				}
				a1b -= WorkingWidth * 32;
				++sxc;
				v21 += 2;
			}
			while ( sxc < 7 );
			if ( 2 * a6 + 2 < 8 )
				town_draw_clipped_town_2((int)gpBuffer + *v20 + v11, xa, ya, a6, 2 * a6 + 2, v11, sy, 0);
		}
		else
		{
			town_clear_low_buf((unsigned char *)gpBuffer + screen_y_times_width[v8] + v11);
		}
	}
}
// 69CF14: using guessed type int level_cel_block;

void __fastcall town_draw_e_flag(void *buffer, int x, int y, int a4, int dir, int sx, int sy)
{
	int v7; // ebx
	char *v8; // esi
	int v9; // edi
	int v10; // eax
	int v11; // eax
	void *buffera; // [esp+Ch] [ebp-8h]
	unsigned char *a1; // [esp+10h] [ebp-4h]

	v7 = x;
	buffera = buffer;
	a1 = (unsigned char *)buffer;
	v8 = (char *)dpiece_defs_map_1 + 32 * gendung_get_dpiece_num_from_coord(x, y);
	v9 = 0;
	do
	{
		if ( a4 >= v9 )
		{
			v10 = *(unsigned short *)&v8[4 * v9];
			level_cel_block = *(unsigned short *)&v8[4 * v9];
			if ( v10 )
				drawUpperScreen(a1);
			v11 = *(unsigned short *)&v8[4 * v9 + 2];
			level_cel_block = *(unsigned short *)&v8[4 * v9 + 2];
			if ( v11 )
				drawUpperScreen(a1 + 32);
		}
		a1 -= WorkingWidth * 32;
		++v9;
	}
	while ( v9 < 7 );
	town_draw_town_all(buffera, v7, y, a4, dir, sx, sy, 0);
}
// 69CF14: using guessed type int level_cel_block;

void __fastcall town_draw_town_all(void *buffer, int x, int y, int a4, int dir, int sx, int sy, int some_flag)
{
	//int v9; // ebx
	int id; // esi
	int yy; // ebx
	int xx; // edi

	//v9 = 112 * x + y;
	if ( dItem[x][y] )
	{
		id = dItem[x][y] - 1;
		xx = sx - item[id]._iAnimWidth2;
		AddItemToDrawQueue(xx,sy,id);
		if (id == pcursitem || ShouldHighlightItems) {
			int color = GetItemHighlightColor(id);
			CelDecodeClr(color, xx, sy, (char *)item[id]._iAnimData, item[id]._iAnimFrame, item[id]._iAnimWidth, 0, dir);//was 181
		}
		CelDrawHdrOnly(xx, sy, (char *)item[id]._iAnimData, item[id]._iAnimFrame, item[id]._iAnimWidth, 0, dir);
	}
	if ( dFlags[x][y] & 0x10 )
	{
		id = -1 - dMonster[x][y-1]; // -1 - *(&dword_52D204 + v9); /* check */
		xx = sx - towner[id]._tAnimWidth2;
		if ( id == pcursmonst )
			CelDecodeClr(166, xx, sy, (char *)towner[id]._tAnimData, towner[id]._tAnimFrame, towner[id]._tAnimWidth, 0, dir);
		CelDrawHdrOnly(xx, sy, (char *)towner[id]._tAnimData, towner[id]._tAnimFrame, towner[id]._tAnimWidth, 0, dir);
	}
	if ( dMonster[x][y] > 0 )
	{
		id = dMonster[x][y] - 1;
		xx = sx - towner[id]._tAnimWidth2;
		if ( id == pcursmonst )
			CelDecodeClr(166, xx, sy, (char *)towner[id]._tAnimData, towner[id]._tAnimFrame, towner[id]._tAnimWidth, 0, dir);
		CelDrawHdrOnly(xx, sy, (char *)towner[id]._tAnimData, towner[id]._tAnimFrame, towner[id]._tAnimWidth, 0, dir);
	}
	if ( dFlags[x][y] & 0x20 )
	{
		id = -1 - dPlayer[x][y-1]; // -1 - *((_BYTE *)&themeLoc[49].height + v9 + 3);
		yy = sy + plr[id]._pyoff;
		xx = sx + plr[id]._pxoff - plr[id]._pAnimWidth2;
		if ( id == pcursplr )
			Cl2DecodeFrm2(165, xx, yy, (char *)plr[id]._pAnimData, plr[id]._pAnimFrame, plr[id]._pAnimWidth, 0, dir);
		Cl2DecodeFrm1(xx, yy, (char *)plr[id]._pAnimData, plr[id]._pAnimFrame, plr[id]._pAnimWidth, 0, dir);
		if ( some_flag && plr[id]._peflag )
			town_draw_e_flag((char *)buffer - 64, x - 1, y + 1, a4, dir, sx - 64, sy);
	}
	if ( dFlags[x][y] & 4 )
		DrawDeadPlayer(x, y, sx, sy, 0, dir, 0);
	if ( dPlayer[x][y] > 0 )
	{
		id = dPlayer[x][y] - 1;
		yy = sy + plr[id]._pyoff;
		xx = sx + plr[id]._pxoff - plr[id]._pAnimWidth2;
		if ( id == pcursplr )
			Cl2DecodeFrm2(165, xx, yy, (char *)plr[id]._pAnimData, plr[id]._pAnimFrame, plr[id]._pAnimWidth, 0, dir);
		Cl2DecodeFrm1(xx, yy, (char *)plr[id]._pAnimData, plr[id]._pAnimFrame, plr[id]._pAnimWidth, 0, dir);
		if ( some_flag && plr[id]._peflag )
			town_draw_e_flag((char *)buffer - 64, x - 1, y + 1, a4, dir, sx - 64, sy);
	}
	if ( dFlags[x][y] & 1 )
		DrawMissile(x, y, sx, sy, 0, dir, 0);
}
// 4B8CC0: using guessed type char pcursitem;
// 4B8CC2: using guessed type char pcursplr;


void __fastcall town_draw_upper2(int row, int col, int aXPos, int aYPos, int AreaWidth, int AreaRow, int Odd)
{
	int YPos;         // ebx@9
	int xPos;        // esi@16
	int v12;          // edi@19
	int* YOffsetPtr;   // ebx@25
	uchar* CurSurfPtr;  // edi@25
	int v30;          // [sp+18h] [bp-Ch]@1
	int v32;          // [sp+10h] [bp-14h]@9
	unsigned int v33; // [sp+Ch] [bp-18h]@19
	v30 = 2 * AreaRow + 2;
	if (v30 > 8) {
		v30 = 8;
	}
	xPos = aXPos;
	YPos = aYPos;
	if (AreaWidth > 0) {
		v33 = AreaWidth;
		v12 = 112 * row;
		v32 = 112 * row;
		do {
			if (col >= 0 && col < 112 && v12 >= 0 && v12 < 112 * 112
				&& (level_cel_block = dPiece[row][col], level_cel_block)) {
				YOffsetPtr = &screen_y_times_width[YPos];
				CurSurfPtr = (uchar*)&gpBuffer[xPos] + *YOffsetPtr;
				aXPos = 0;
				if (level_cel_block != CurFineMap) {
					for (int i = 0; i < 8; ++i) {
						if (AreaRow >= i) {
							char *v19 = (char *)dpiece_defs_map_1 + 32 * gendung_get_dpiece_num_from_coord(row,col);
							level_cel_block = *(unsigned short *)&v19[4 * i];
							if (level_cel_block) drawUpperScreen(CurSurfPtr);
							level_cel_block = *(unsigned short *)&v19[4 * i + 2];
							if (level_cel_block) drawUpperScreen(CurSurfPtr + 32);
						}
						CurSurfPtr -= 32 * WorkingWidth;
					}
				}
				else {
					town_clear_upper_buf((unsigned char *)&gpBuffer[xPos] + screen_y_times_width[YPos]);
				}
				town_draw_town_all((char *)(&gpBuffer[xPos] + *YOffsetPtr), row, col, AreaRow, v30, xPos, aYPos, 1);
				YPos = aYPos;
				v12 = v32;
			}
			else {
				town_clear_upper_buf((unsigned char *)&gpBuffer[xPos] + screen_y_times_width[YPos]);
			}
			++row;
			v12 += 112;
			--col;
			xPos += 64;
			v32 = v12;
		} while (v33-- != 1);
	}
}

void __fastcall town_draw_upper(int x, int y, int sx, int sy, int a5, int a6, int some_flag)
{
	signed int v7; // ebx
	int v8; // esi
	int v9; // eax
	bool v10; // zf
	int v11; // eax
	short *v12; // ebx
	int v13; // eax
	int v14; // esi
	int v15; // edi
	int v16; // eax
	Screen *v17; // eax
	unsigned char *v18; // ebx
	char *v19; // edi
	int v20; // eax
	int v21; // eax
	int v22; // eax
	int v23; // eax
	unsigned char *v24; // edi
	char *v25; // ebx
	int v26; // eax
	int *a1; // [esp+Ch] [ebp-10h]
	int *a1a; // [esp+Ch] [ebp-10h]
	int dir; // [esp+10h] [ebp-Ch]
	int ya; // [esp+14h] [ebp-8h]
	signed int xa; // [esp+18h] [ebp-4h]
	signed int sxa; // [esp+24h] [ebp+8h]
	signed int sxb; // [esp+24h] [ebp+8h]
	signed int sxc; // [esp+24h] [ebp+8h]
	int a5a; // [esp+2Ch] [ebp+10h]

	xa = x;
	v7 = y;
	ya = y;
	dir = 2 * a6 + 2;
	if ( dir > 8 )
		dir = 8;
	if ( some_flag )
	{
		if ( y < 0 || y >= 112 || x < 0 || x >= 112 )
		{
			v11 = sy;
			v8 = sx;
		}
		else
		{
			v8 = sx;
			v9 = dPiece[0][y + 112 * x];
			level_cel_block = v9;
			v10 = v9 == 0;
			v11 = sy;
			if ( !v10 )
			{
				a1 = (int *)&gpBuffer->row_unused_1[0].col_unused_1[sx + 32 + screen_y_times_width[sy]];
				sxa = 0;
				v12 = &dpiece_defs_map_1[0][0][16 * gendung_get_dpiece_num_from_coord(x, y) + 1];
				do
				{
					if ( a6 >= sxa )
					{
						v13 = (unsigned short)*v12;
						level_cel_block = (unsigned short)*v12;
						if ( v13 )
							drawUpperScreen((unsigned char *)a1);
					}
					a1 -= WorkingWidth*8;
					++sxa;
					v12 += 2;
				}
				while ( sxa < 7 );
				town_draw_town_all((char *)gpBuffer + v8 + screen_y_times_width[sy], xa, ya, a6, dir, v8, sy, 0);
				v7 = ya;
				goto LABEL_17;
			}
		}
		town_clear_upper_buf((unsigned char *)gpBuffer + screen_y_times_width[v11] + v8);
LABEL_17:
		++xa;
		ya = --v7;
		v14 = v8 + 64;
		goto LABEL_19;
	}
	v14 = sx;
LABEL_19:
	if ( a5 - some_flag > 0 )
	{
		a1a = (int *)(a5 - some_flag);
		v15 = 112 * xa;
		a5a = 112 * xa;
		do
		{
			if ( v7 < 0 || v7 >= 112 || v15 < 0 || v15 >= 12544 )
			{
				v17 = gpBuffer;
			}
			else
			{
				v16 = dPiece[0][v15 + v7];
				level_cel_block = v16;
				v10 = v16 == 0;
				v17 = gpBuffer;
				if ( !v10 )
				{
					v18 = (unsigned char *)gpBuffer + v14 + screen_y_times_width[sy];
					v19 = (char *)dpiece_defs_map_1 + 32 * gendung_get_dpiece_num_from_coord(xa, ya);
					sxb = 0;
					do
					{
						if ( a6 >= sxb )
						{
							v20 = *(unsigned short *)&v19[4 * sxb];
							level_cel_block = *(unsigned short *)&v19[4 * sxb];
							if ( v20 )
								drawUpperScreen(v18);
							v21 = *(unsigned short *)&v19[4 * sxb + 2];
							level_cel_block = *(unsigned short *)&v19[4 * sxb + 2];
							if ( v21 )
								drawUpperScreen(v18 + 32);
						}
						v18 -= WorkingWidth * 32;
						++sxb;
					}
					while ( sxb < 7 );
					town_draw_town_all((char *)gpBuffer + v14 + screen_y_times_width[sy], xa, ya, a6, dir, v14, sy, 1);
					v15 = a5a;
					v7 = ya;
					goto LABEL_36;
				}
			}
			town_clear_upper_buf((unsigned char *)v17 + v14 + screen_y_times_width[sy]);
LABEL_36:
			++xa;
			v15 += 112;
			--v7;
			v14 += 64;
			v10 = a1a == (int *)1;
			a1a = (int *)((char *)a1a - 1);
			a5a = v15;
			ya = v7;
		}
		while ( !v10 );
	}
	if ( some_flag )
	{
		if ( v7 < 0 || v7 >= 112 || xa < 0 || xa >= 112 )
		{
			v23 = sy;
		}
		else
		{
			v22 = dPiece[0][v7 + 112 * xa];
			level_cel_block = v22;
			v10 = v22 == 0;
			v23 = sy;
			if ( !v10 )
			{
				v24 = (unsigned char *)gpBuffer + v14 + screen_y_times_width[sy];
				v25 = (char *)dpiece_defs_map_1 + 32 * gendung_get_dpiece_num_from_coord(xa, v7);
				sxc = 0;
				do
				{
					if ( a6 >= sxc )
					{
						v26 = *(unsigned short *)&v25[4 * sxc];
						level_cel_block = *(unsigned short *)&v25[4 * sxc];
						if ( v26 )
							drawUpperScreen(v24);
					}
					v24 -= WorkingWidth*32;
					++sxc;
				}
				while ( sxc < 7 );
				town_draw_town_all((char *)gpBuffer + v14 + screen_y_times_width[sy], xa, ya, a6, dir, v14, sy, 0);
				return;
			}
		}
		town_clear_upper_buf((unsigned char *)gpBuffer + screen_y_times_width[v23] + v14);
	}
}
// 69CF14: using guessed type int level_cel_block;

int GetWidthForRes(int what) 
{
	return ceil(ScreenWidth * what / 640)*2;
}

void DrawGame(int x, int y, bool isTown)
{
	int targetHeight = GLOBAL_HEIGHT - GLOBAL_HEIGHT * globalScrollZoom / 200;
	int targetWidth = GLOBAL_WIDTH - GLOBAL_WIDTH * globalScrollZoom / 200;
	int widthDiff = GLOBAL_WIDTH - targetWidth;
	int heightDiff = GLOBAL_HEIGHT - targetHeight;

	int yofs = 175;
	int yofs2 = heightDiff / 6;
	int posx = x - ceil(ScreenWidth / 64);
	int posy = y - 1;
	int offsetX = ScrollInfo._sxoff + 64;
	int offsetY = ScrollInfo._syoff + yofs;
	int HorCellDrawCount = ceil(ScreenWidth / 64);
	switch (ScrollInfo._sdir)
	{
	case DIR_W:
	case DIR_SW: {
		offsetY = ScrollInfo._syoff + yofs - 32;
		--posx;
		--posy;
		++HorCellDrawCount;
		break;
	}
	case DIR_NW:
	case DIR_N:
	case DIR_NE:
	{
		++HorCellDrawCount;
		++HorCellDrawCount;
		break;
	}
	case DIR_E:
	case DIR_SE: {
		offsetX -= 64;
		--posx;
		++posy;
		++HorCellDrawCount;
		++HorCellDrawCount;
		break;
	}
	case DIR_OMNI: {
		offsetX -= 64;
		offsetY = ScrollInfo._syoff + yofs - 32;
		posx -= 2;
		++HorCellDrawCount;
		++HorCellDrawCount;
		break;
	}
	default:
		break;
	}
	int screenCellRow = 0;
	gpBufEnd = (unsigned char *)gpBuffer + screen_y_times_width[160];
	do {
		if (isTown) {
			town_draw_upper(posx, posy++, offsetX, offsetY, HorCellDrawCount, screenCellRow, 0);
			town_draw_upper(posx++, posy, offsetX - 32, offsetY + 16, HorCellDrawCount, screenCellRow, 1);
		}
		else {
			scrollrt_draw_upper(posx, posy++, offsetX, offsetY, HorCellDrawCount, screenCellRow, 0);
			scrollrt_draw_upper(posx++, posy, offsetX - 32, offsetY + 16, HorCellDrawCount, screenCellRow, 1);
		}
		offsetY += 32;
		++screenCellRow;
	} while (offsetY <= WorkingHeight + 256);
	gpBufEnd = (unsigned char *)gpBuffer + screen_y_times_width[WorkingWidth + 32];
	yofs -= 32;
	for (int i = ScreenHeight - 1; i >= yofs2; --i) {
		for (int j = ScreenWidth - 1; j >= 0; --j) {
			gpBuffer->row[i].pixels[j] = gpBuffer->row[i - yofs2].pixels[j];
		}
	}
	int hd2 = (heightDiff >> 1);
	int wd2 = (widthDiff >> 1);
	for (int i = 0; i < ScreenHeight/2;++i) {
		for (int j = 0; j < ScreenWidth/2; ++j) {
			int tmprow = hd2+ i * targetHeight / GLOBAL_HEIGHT;
			int tmprow2 = GLOBAL_HEIGHT-1-tmprow;
			int tmpcol = wd2 + j * targetWidth / GLOBAL_WIDTH;
			int tmpcol2 = GLOBAL_WIDTH-tmpcol-1;
			gpBuffer->row[i].pixels[j] = gpBuffer->row[tmprow].pixels[tmpcol];
			gpBuffer->row[i].pixels[ScreenWidth - 1 - j] = gpBuffer->row[tmprow].pixels[tmpcol2];
			gpBuffer->row[ScreenHeight-1-i].pixels[j] = gpBuffer->row[tmprow2].pixels[tmpcol];
			gpBuffer->row[ScreenHeight-1-i].pixels[ScreenWidth - 1 - j] = gpBuffer->row[tmprow2].pixels[tmpcol2];
		}
	}
}

void __fastcall T_DrawView(int StartX, int StartY)
{
	light_table_index = 0;
	drawQ.clear();
	cel_transparency_active = 0;
	DrawGame(StartX, StartY, /*isTown*/true);
	if ( automapflag )
		DrawAutomap();
	ShouldHighlightItems = ((GetConfigBoolVariable("alwaysHighlightObjectsWithoutPressingAlt") && !(GetAsyncKeyState(VK_MENU) < 0)) || (!GetConfigBoolVariable("alwaysHighlightObjectsWithoutPressingAlt") && (GetAsyncKeyState(VK_MENU) < 0)));
	if (ShouldHighlightItems) {// alt pressed
		HighlightItemsNameOnMap();
	}
	if ( stextflag && !qtextflag )
		DrawSText();
	if ( invflag )
	{
		DrawInv();
	}
	else if ( sbookflag )
	{
		DrawSpellBook();
	}
	DrawDurIcon();
	if ( chrflag )
	{
		DrawChr();
	}
	else if ( questlog )
	{
		DrawQuestLog();
	}
	else if ( plr[myplr]._pStatPts && !spselflag )
	{
		DrawLevelUpIcon();
	}
	if (uitemflag == 1)
		DrawUniqueInfo();
	if (uitemflag == 2)
		DrawRareInfo();
	if ( qtextflag )
		DrawQText();
	if ( spselflag )
		DrawSpellList();
	if ( dropGoldFlag )
		DrawGoldSplit(dropGoldValue);
	if (nameStashTabFlag)
		DrawStashRename(renameStashValue);
	if ( helpflag )
		DrawHelp();
	if ( msgflag )
		DrawDiabloMsg();
	if ( PauseMode && !deathflag )
		gmenu_draw_pause();
	DrawPlrMsg();
	gmenu_draw();
	doom_draw();
	DrawInfoBox();
	DrawLifeFlask();
	DrawManaFlask();
}
// 4B84DC: using guessed type int dropGoldFlag;
// 4B8968: using guessed type int sbookflag;
// 4B8C98: using guessed type int spselflag;
// 525740: using guessed type int PauseMode;
// 52B9F1: using guessed type char msgflag;
// 646D00: using guessed type char qtextflag;
// 69BD04: using guessed type int questlog;
// 69BEF8: using guessed type int light_table_index;
// 69CF94: using guessed type int cel_transparency_active;
// 6AA705: using guessed type char stextflag;

void __cdecl town_init_dpiece_defs_map()
{
	int (*v0)[112]; // ebx
	int v1; // ebp
	int v2; // esi
	char *v3; // edi
	char *v4; // ecx
	signed int v5; // eax
	int (*v6)[112]; // [esp+10h] [ebp-8h]
	int y; // [esp+14h] [ebp-4h]

	y = 0;
	v6 = dPiece;
	do
	{
		v0 = v6;
		v1 = 0;
		do
		{
			v2 = (*v0)[0];
			v3 = (char *)dpiece_defs_map_1 + 32 * gendung_get_dpiece_num_from_coord(v1, y);
			if ( v2 )
			{
				v4 = (char *)pLevelPieces + 32 * v2 - 32;
				v5 = 0;
				do
				{
					*(_WORD *)&v3[2 * v5] = *(_WORD *)&v4[2 * ((v5 & 1) - (v5 & 0xE)) + 28];
					++v5;
				}
				while ( v5 < 16 );
			}
			else
			{
				memset(v3, 0, 0x20u);
			}
			++v1;
			++v0;
		}
		while ( v1 < 112 );
		v6 = (int (*)[112])((char *)v6 + 4);
		++y;
	}
	while ( (signed int)v6 < (signed int)dPiece[1] );
}
// 5C2FF8: using guessed type int dword_5C2FF8;
// 5C2FFC: using guessed type int dword_5C2FFC;
// 5C3000: using guessed type int scr_pix_width;
// 5C3004: using guessed type int scr_pix_height;

void __fastcall T_FillSector(unsigned char *P3Tiles, unsigned char *pSector, int xi, int yi, int w, int h) /* check 7 params: int AddSec */
{
	int v7; // ebx
	int v8; // edx
	int v9; // edi
	int *v10; // ecx
	int v11; // eax
	unsigned char *v12; // esi
	unsigned short v13; // ax
	int v14; // eax
	int v15; // [esp+4h] [ebp-14h]
	int v16; // [esp+8h] [ebp-10h]
	unsigned char *v17; // [esp+Ch] [ebp-Ch]
	unsigned char *v18; // [esp+10h] [ebp-8h]
	signed int v19; // [esp+14h] [ebp-4h]
	int a4; // [esp+24h] [ebp+Ch]
	int a6; // [esp+2Ch] [ebp+14h]

	v7 = h;
	v17 = pSector;
	v8 = yi;
	v18 = P3Tiles;
	v19 = 4;
	if ( h > 0 )
	{
		do
		{
			v9 = w;
			if ( w > 0 )
			{
				v10 = &dPiece[1][v8 + 112 * xi];
				do
				{
					v11 = *(unsigned short *)&v17[v19];
					if ( (_WORD)v11 )
					{
						v12 = &v18[8 * (v11 - 1)];
						v13 = *(_WORD *)v12;
						v12 += 2;
						v14 = v13 + 1;
						a4 = v14;
						_LOWORD(v14) = *(_WORD *)v12;
						v12 += 2;
						a6 = ++v14;
						_LOWORD(v14) = *(_WORD *)v12;
						v16 = ++v14;
						_LOWORD(v14) = *((_WORD *)v12 + 1);
						v15 = v14 + 1;
					}
					else
					{
						a4 = 0;
						a6 = 0;
						v16 = 0;
						v15 = 0;
					}
					v19 += 2;
					*(v10 - 112) = a4;
					*v10 = a6;
					*(v10 - 111) = v16;
					v10[1] = v15;
					v10 += 224;
					--v9;
				}
				while ( v9 );
			}
			v8 += 2;
			--v7;
		}
		while ( v7 );
	}
}

void __fastcall T_FillTile(unsigned char *P3Tiles, int xx, int yy, int t)
{
	unsigned char *v4; // esi
	unsigned short v5; // ax
	int v6; // eax
	int v7; // ST10_4
	int v8; // ST0C_4
	int v9; // ST08_4

	v4 = &P3Tiles[8 * (t - 1)];
	v5 = *(_WORD *)v4;
	v4 += 2;
	v6 = v5 + 1;
	v7 = v6;
	_LOWORD(v6) = *(_WORD *)v4;
	v4 += 2;
	v8 = ++v6;
	_LOWORD(v6) = *(_WORD *)v4;
	v9 = ++v6;
	_LOWORD(v6) = *((_WORD *)v4 + 1);
	dPiece[xx][yy] = v7;
	dPiece[xx + 1][yy] = v8;
	dPiece[xx][yy + 1] = v9;
	dPiece[xx + 1][yy + 1] = v6 + 1;
}

void __cdecl T_Pass3()
{
	int *v1; // esi
	int *v2; // eax
	signed int v3; // ecx
	unsigned char *P3Tiles; // esi
	unsigned char *pSector; // edi
	int xx; // edi

	v1 = dPiece[1];
	do
	{
		v2 = v1;
		v3 = 56;
		do
		{
			*(v2 - 112) = 0;
			*v2 = 0;
			*(v2 - 111) = 0;
			v2[1] = 0;
			v2 += 224;
			--v3;
		}
		while ( v3 );
		v1 += 2;
	}
	while ( (signed int)v1 < (signed int)dPiece[2] );
	P3Tiles = LoadFileInMem("Levels\\TownData\\Town.TIL", 0);
	pSector = LoadFileInMem("Levels\\TownData\\Sector1s.DUN", 0);
	T_FillSector(P3Tiles, pSector, 46, 46, 25, 25);
	mem_free_dbg(pSector);
	pSector = LoadFileInMem("Levels\\TownData\\Sector2s.DUN", 0);
	T_FillSector(P3Tiles, pSector, 46, 0, 25, 23);
	mem_free_dbg(pSector);
	pSector = LoadFileInMem("Levels\\TownData\\Sector3s.DUN", 0);
	T_FillSector(P3Tiles, pSector, 0, 46, 23, 25);
	mem_free_dbg(pSector);
	pSector = LoadFileInMem("Levels\\TownData\\Sector4s.DUN", 0);
	T_FillSector(P3Tiles, pSector, 0, 0, 23, 23);
	mem_free_dbg(pSector);
	if ( gbMaxPlayers == 1 )
	{
		if ( !(plr[myplr].pTownWarps & 1) )
		{
			T_FillTile(P3Tiles, 48, 20, 320);
		}
		if ( !(plr[myplr].pTownWarps & 2) )
		{
			T_FillTile(P3Tiles, 16, 68, 332);
			T_FillTile(P3Tiles, 16, 70, 331);
		}
		if ( !(plr[myplr].pTownWarps & 4) )
		{
			xx = 36;
			do
			{
				T_FillTile(P3Tiles, xx++, 78, random(0, 4) + 1);
			}
			while ( xx < 46 );
		}
	}
	if ( quests[13]._qactive != 3 && quests[13]._qactive )
		T_FillTile(P3Tiles, 60, 70, 342);
	else
		T_FillTile(P3Tiles, 60, 70, 71);
	mem_free_dbg(P3Tiles);
}
// 45FDE6: could not find valid save-restore pair for edi
// 679660: using guessed type char gbMaxPlayers;

void __fastcall CreateTown(int entry)
{
	int v1; // edi
	int (*v2)[112]; // esi
	_BYTE *v3; // eax
	int (*v4)[112]; // edx
	signed int v5; // ebp
	int v6; // ecx

	v1 = 0;
	dminx = 10;
	dminy = 10;
	dmaxx = 84;
	dmaxy = 84;
	if ( entry )
	{
		if ( entry == 1 )
		{
			ViewX = 25;
			ViewY = 31;
		}
		else if ( entry == 7 )
		{
			if ( TWarpFrom == 5 )
			{
				ViewX = 49;
				ViewY = 22;
			}
			if ( TWarpFrom == 9 )
			{
				ViewX = 18;
				ViewY = 69;
			}
			if ( TWarpFrom == 13 )
			{
				ViewX = 41;
				ViewY = 81;
			}
		}
	}
	else
	{
		ViewX = 75;
		ViewY = 68;
	}
	T_Pass3();
	memset(dTransVal, 0, 0x3100u);
	memset(dFlags, 0, 0x3100u);
	memset(dPlayer, 0, 0x3100u);
	memset(dMonster, 0, 0xC400u);
	memset(dObject, 0, 0x3100u);
	memset(dItem, 0, 0x3100u);
	memset(dArch, 0, 0x3100u);
	v2 = dPiece;
	do
	{
		v3 = (unsigned char *)dArch + v1;
		v4 = v2;
		v5 = 112;
		do
		{
			v6 = (*v4)[0];
			if ( (*v4)[0] == 360 )
			{
				*v3 = 1;
			}
			else
			{
				switch ( v6 )
				{
					case 358:
						*v3 = 2;
						break;
					case 129:
						*v3 = 6;
						break;
					case 130:
						*v3 = 7;
						break;
					case 128:
						*v3 = 8;
						break;
					case 117:
						*v3 = 9;
						break;
					case 157:
						*v3 = 10;
						break;
					case 158:
						*v3 = 11;
						break;
					case 156:
						*v3 = 12;
						break;
					case 162:
						*v3 = 13;
						break;
					case 160:
						*v3 = 14;
						break;
					case 214:
						*v3 = 15;
						break;
					case 212:
						*v3 = 16;
						break;
					case 217:
						*v3 = 17;
						break;
					case 216:
						*v3 = 18;
						break;
				}
			}
			++v4;
			v3 += 112;
			--v5;
		}
		while ( v5 );
		v2 = (int (*)[112])((char *)v2 + 4);
		++v1;
	}
	while ( (signed int)v2 < (signed int)dPiece[1] );
	town_init_dpiece_defs_map();
}
// 5CF328: using guessed type int dmaxx;
// 5CF32C: using guessed type int dmaxy;
// 5D2458: using guessed type int dminx;
// 5D245C: using guessed type int dminy;
// 6ABB30: using guessed type int TWarpFrom;
