#pragma once
#include <string>
#include <cstdint>
#include <Windows.h>
#include <D3D9Types.h>

#pragma pack(push, 1)
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
	DWORD					dwPlayerIP[1004]; // always 0
};
#pragma pack(pop)

class Samp
{
private:
	uint32_t g_dwSAMP_Addr;
	struct stSAMP* g_SAMP;
public:

	Samp::Samp();
	bool Init();

	stPlayerPool* GetPlayers();
	char* GetServerHostname();

	void AddToChatWindow(char* text, DWORD textColor);
	void AddClientCommand(const char* command, void* function);

	D3DCOLOR GetSampColor(int id, DWORD trans = 0xFF000000);
};

extern Samp* pSamp;