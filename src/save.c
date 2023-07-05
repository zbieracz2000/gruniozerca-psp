#include "includes.h"
#include "data.h"
PspUtilitySavedataListSaveNewData newData;
#define DATABUFFLEN   0x20
char string[128];
int mode = 0;
char *titleShow = "New Save";
int running = 1;
char nameMultiple[][20] =	// End list with ""
{
 "0000",
 "0001",
 "0002",
 "0003",
 "0004",
 ""
};

char key[] = "ofkqk2342favca3";	// Key to encrypt or decrypt savedata

void initSavedata(SceUtilitySavedataParam * savedata, int mode)
{
	memset(savedata, 0, sizeof(SceUtilitySavedataParam));
	savedata->base.size = sizeof(SceUtilitySavedataParam);

	savedata->base.language = PSP_SYSTEMPARAM_LANGUAGE_ENGLISH;
	savedata->base.buttonSwap = PSP_UTILITY_ACCEPT_CROSS;
	savedata->base.graphicsThread = 0x11;
	savedata->base.accessThread = 0x13;
	savedata->base.fontThread = 0x12;
	savedata->base.soundThread = 0x10;

	savedata->mode = mode;
	savedata->overwrite = 1;
	savedata->focus = PSP_UTILITY_SAVEDATA_FOCUS_LATEST; // Set initial focus to the newest file (for loading)

#if _PSP_FW_VERSION >= 200
	strncpy(savedata->key, key, 16);
#endif

	strcpy(savedata->gameName, "Gruniozerca");	// First part of the save name, game identifier name
	strcpy(savedata->saveName, "0000");	// Second part of the save name, save identifier name

	// List of multiple names
	savedata->saveNameList = nameMultiple;

	strcpy(savedata->fileName, "DATA.BIN");	// name of the data file

	// Allocate buffers used to store various parts of the save data
	savedata->dataBuf = malloc(DATABUFFLEN);
	savedata->dataBufSize = DATABUFFLEN;
	savedata->dataSize = DATABUFFLEN;

	// Set some data
	if (mode == PSP_UTILITY_SAVEDATA_AUTOSAVE)
	{
	memset(savedata->dataBuf, 0, DATABUFFLEN);
	sprintf(savedata->dataBuf,"%d",hiscore);
	strcpy(savedata->sfoParam.title,"Gruniozerca Highscore");
	strcpy(savedata->sfoParam.savedataTitle,"Highscore:");
	sprintf(savedata->sfoParam.detail,"%d",hiscore);
	savedata->sfoParam.parentalLevel = 1;
	
	// No icon1
	savedata->icon1FileData.buf = NULL;
	savedata->icon1FileData.bufSize = 0;
	savedata->icon1FileData.size = 0;

	savedata->pic1FileData.buf = pic1;
	savedata->pic1FileData.bufSize = size_pic1;
	savedata->pic1FileData.size = size_pic1;

	savedata->icon0FileData.buf = icon0;
	savedata->icon0FileData.bufSize = size_icon0;
	savedata->icon0FileData.size = size_icon0;
	
	// No snd0
	savedata->snd0FileData.buf = snd0;
	savedata->snd0FileData.bufSize = size_snd0;
	savedata->snd0FileData.size = size_snd0;

	// Set title
	newData.title = titleShow;

	// Set new data
	savedata->newData = &newData;
	
	savedata->focus = PSP_UTILITY_SAVEDATA_FOCUS_FIRSTEMPTY; // If saving, set inital focus to the first empty slot
	}
}

void ShowSaveDialog (int mode)
{
	SceUtilitySavedataParam dialog;
	
    initSavedata(&dialog, mode);
	
    sceUtilitySavedataInitStart(&dialog);

    while(running) {
			g2dFlip(G2D_VSYNC);

	switch(sceUtilitySavedataGetStatus()) {

	case PSP_UTILITY_DIALOG_VISIBLE :

	    sceUtilitySavedataUpdate(1);
	    break;

	case PSP_UTILITY_DIALOG_QUIT :

	    sceUtilitySavedataShutdownStart();
	    break;
	    
	case PSP_UTILITY_DIALOG_FINISHED :
		if(mode == PSP_UTILITY_SAVEDATA_LISTSAVE)
			sprintf(string, "Saved: score = 10");
		else
			hiscore=atoi((char*)dialog.dataBuf);
		screen=0;

	case PSP_UTILITY_DIALOG_NONE :
	    return;
	}
    }
}