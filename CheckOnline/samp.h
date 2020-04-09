#pragma once

// SAMP Structures
#pragma pack(push, 1) // размер выравнивания = 1 байт
struct stSAMPPools
{
	struct stActorPool		*pActor;
	struct stObjectPool		*pObject;
	struct stGangzonePool	*pGangzone;
	struct stTextLabelPool	*pText3D;
	struct stTextdrawPool	*pTextdraw;
	void					*pPlayerLabels;
	struct stPlayerPool		*pPlayer;
	struct stVehiclePool	*pVehicle;
	struct stPickupPool		*pPickup;
};

struct stSAMP
{
	void					*pUnk0;
	struct stServerInfo		*pServerInfo;
	uint8_t					byteSpace[24];
	char					szIP[257];
	char					szHostname[259];
	bool					bNametagStatus; // changes by /nametagstatus
	uint32_t				ulPort;
	uint32_t				ulMapIcons[100];
	int						iLanMode;
	int						iGameState;
	uint32_t				ulConnectTick;
	struct stServerPresets	*pSettings;
	void					*pRakClientInterface;
	struct stSAMPPools		*pPools;
};

struct stPlayerPool
{
	uint32_t				ulMaxPlayerID;
	uint16_t				sLocalPlayerID;
	void					*pVTBL_txtHandler;
	std::string				strLocalPlayerName;
	struct stLocalPlayer	*pLocalPlayer;
	int						iLocalPlayerPing;
	int						iLocalPlayerScore;
	struct stRemotePlayer	*pRemotePlayer[1004];
	int						iIsListed[1004];
	DWORD						dwPlayerIP[1004]; // always 0
};
#pragma pack(pop)


// Functions
D3DCOLOR samp_color_get(int id, DWORD trans = 0xFF000000);

extern void addToChatWindow(char *text, DWORD textColor);
extern void addClientCommand(const char *command, void *function);

// global pointer externals
extern struct stSAMP *g_SAMP;
extern struct stPlayerPool *g_Players;