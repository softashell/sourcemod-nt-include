#if defined _neotokyo_included
  #endinput
#endif
#define _neotokyo_included

// Starting with SM 1.11, errors in unused stock functions are no longer suppressed.
// This means we have to include any dependencies here, regardless of whether they're
// actually used, or otherwise user code including this .inc file will error on compile.
#if SOURCEMOD_V_MAJOR > 1 || (SOURCEMOD_V_MAJOR == 1 && SOURCEMOD_V_MINOR >= 11)
#include <sdktools> // Required by RemovePlayerItem()
#endif

#define NEO_MAXPLAYERS	32

#define TEAM_NONE		0
#define TEAM_SPECTATOR	1
#define TEAM_JINRAI 	2
#define TEAM_NSF		3

#define AMMO_GRENADE	1
#define AMMO_SMOKE		2
#define AMMO_PRIMARY	4
#define AMMO_SECONDARY	5
#define AMMO_PZ			7
#define AMMO_SHOTGUN	11

#define VISION_NONE		0
#define VISION_NIGHT	2
#define VISION_THERMAL 	3
#define VISION_MOTION	4

#define CLASS_NONE		0
#define CLASS_RECON		1
#define CLASS_ASSAULT	2
#define CLASS_SUPPORT	3

#define IN_AIM			(1 << 23)
#define IN_LEANL		(1 << 24)
#define IN_LEANR		(1 << 25)
#define IN_SPRINT		(1 << 26)
#define IN_THERMOPTIC	(1 << 27)
#define IN_VISION		(1 << 28)
#define IN_TOSS			(1 << 29)

#define SLOT_NONE -1
#define SLOT_PRIMARY 0
#define SLOT_SECONDARY 1
#define SLOT_MELEE 2
#define SLOT_GRENADE 3

char weapons_primary[][] = {
	"weapon_ghost",
	"weapon_mpn",
	"weapon_srm",
	"weapon_srm_s",
	"weapon_jitte",
	"weapon_jittescoped",
	"weapon_zr68c",
	"weapon_zr68l",
	"weapon_zr68s",
	"weapon_supa7",
	"weapon_m41",
	"weapon_m41s",
	"weapon_mx",
	"weapon_mx_silenced",
	"weapon_aa13",
	"weapon_srs",
	"weapon_pz"
};

char weapons_secondary[][] = {
	"weapon_tachi",
	"weapon_milso",
	"weapon_kyla"
};

char weapons_grenade[][] = {
	"weapon_grenade",
	"weapon_smokegrenade",
	"weapon_remotedet"
};

stock void SetPlayerXP(int client, int xp)
{
	int rank = 0; // Rankless dog

	if(xp >= 0 && xp <= 3)
		rank = 1; // Private
	else if(xp >= 4 && xp <= 9)
		rank = 2; // Corporal
	else if(xp >= 10 && xp <= 19)
		rank = 3; // Sergeant
	else if(xp >= 20)
		rank = 4; // Lieutenant

	SetEntProp(client, Prop_Data, "m_iFrags", xp);
	SetPlayerRank(client, rank);
}

stock int GetPlayerXP(int client)
{
	return GetClientFrags(client);
}

stock void UpdatePlayerRank(int client)
{
	int xp = GetPlayerXP(client);

	int rank = 0; // Rankless dog

	if(xp >= 0 && xp <= 3)
		rank = 1; // Private
	else if(xp >= 4 && xp <= 9)
		rank = 2; // Corporal
	else if(xp >= 10 && xp <= 19)
		rank = 3; // Sergeant
	else if(xp >= 20)
		rank = 4; // Lieutenant

	SetPlayerRank(client, rank);
}

stock int GetPlayerRank(int client)
{
	return GetEntProp(client, Prop_Send, "m_iRank");
}

stock void SetPlayerRank(int client, int rank)
{
	SetEntProp(client, Prop_Send, "m_iRank", rank);
}

stock int GetPlayerDeaths(int client)
{
	return GetEntProp(client, Prop_Data, "m_iDeaths");
}

stock void SetPlayerDeaths(int client, int deaths)
{
	SetEntProp(client, Prop_Data, "m_iDeaths", deaths);
}

stock int GetPlayerStar(int client)
{
	return GetEntProp(client, Prop_Send, "m_iStar");
}

stock void SetPlayerStar(int client, int star)
{
	if(star < 0 || star > 5)
		return;

	SetEntProp(client, Prop_Send, "m_iStar", star);
}

stock void SetPlayerClass(int client, int class)
{
	SetEntProp(client, Prop_Send, "m_iClassType", class);
}

stock int GetPlayerClass(int client)
{
	return GetEntProp(client, Prop_Send, "m_iClassType");
}

stock int GetAmmoType(int weapon)
{
	return GetEntProp(weapon, Prop_Send, "m_iPrimaryAmmoType");
}

stock int GetWeaponAmmo(int client, int type)
{
	static int m_iAmmo;

	if(!m_iAmmo && (m_iAmmo = FindSendPropInfo("CBasePlayer", "m_iAmmo")) == -1)
	{
		ThrowError("Failed to obtain offset: \"m_iAmmo\"!");
	}

	return GetEntData(client, m_iAmmo + (type * 4));
}

stock void SetWeaponAmmo(int client, int type, int ammo)
{
	static int m_iAmmo;

	if(!m_iAmmo && (m_iAmmo = FindSendPropInfo("CBasePlayer", "m_iAmmo")) == -1)
	{
		ThrowError("Failed to obtain offset: \"m_iAmmo\"!");
	}

	SetEntData(client, m_iAmmo + (type * 4), ammo);
}

stock int GetActiveWeapon(int client)
{
	return GetEntPropEnt(client, Prop_Data, "m_hActiveWeapon");
}

stock int GetPlayerVision(int client)
{
	return GetEntProp(client, Prop_Send, "m_iVision");
}

stock void SetPlayerVision(int client, int vision)
{
	SetEntProp(client, Prop_Send, "m_iVision", vision);
}

stock int GetPlayerLean(int client)
{
	return GetEntProp(client, Prop_Send, "m_iLean");
}

stock void SetPlayerLean(int client, int lean)
{
	SetEntProp(client, Prop_Send, "m_iLean", lean);
}

stock float GetPlayerAUX(int client)
{
	return GetEntPropFloat(client, Prop_Send, "m_fSprintNRG");
}

stock void SetPlayerAUX(int client, float amount)
{
	SetEntPropFloat(client, Prop_Send, "m_fSprintNRG", amount);
}

stock float GetPlayerThermopticCharge(int client)
{
	return GetEntPropFloat(client, Prop_Send, "m_fThermopticNRG");
}

stock void SetPlayerThermopticCharge(int client, float amount)
{
	SetEntPropFloat(client, Prop_Send, "m_fThermopticNRG", amount);
}

stock bool IsCloaked(int client)
{
	int cloaked = GetEntProp(client, Prop_Send, "m_iThermoptic");

	if (cloaked > 0)
		return true;

	return false;
}

stock bool IsLeaning(int client)
{
	if (GetPlayerLean(client) > 0)
		return true;

	return false;
}

stock bool IsUsingVision(int client)
{
	if (GetPlayerVision(client) > 0)
		return true;

	return false;
}

stock bool IsValidClient(int client, bool ignoreClientInGameState = false)
{
	if (client < 1 || client > MaxClients)
		return false;

	if(!ignoreClientInGameState && !IsClientInGame(client))
		return false;

	return true;
}

stock void StripPlayerWeapons(int client, bool knife=false)
{
	static int hMyWeapons;

	if(!hMyWeapons && (hMyWeapons = FindSendPropInfo("CBasePlayer", "m_hMyWeapons")) == -1)
	{
		ThrowError("Failed to obtain offset: \"m_hMyWeapons\"!");
	}

	char classname[13];
	for(int slot = 0; slot <= 5; slot++)
	{
		int weapon = GetEntDataEnt2(client, hMyWeapons + (slot * 4));

		if(!IsValidEntity(weapon))
			continue;

		if(knife)
		{
			if(!GetEdictClassname(weapon, classname, sizeof(classname)))
				continue;

			if(StrEqual(classname, "weapon_knife"))
				continue;
		}

		RemovePlayerItem(client, weapon);
		RemoveEdict(weapon);
	}
}

stock int GetWeaponSlot(int weapon)
{
	if(!IsValidEdict(weapon))
		return SLOT_NONE;

	char classname[30];
	if(!GetEntityClassname(weapon, classname, sizeof(classname)))
		return SLOT_NONE; // Can't get class name

	if(StrContains(classname, "weapon_") == -1)
		return SLOT_NONE; // Not a weapon

	if(StrEqual(classname, "weapon_knife"))
		return SLOT_MELEE;

	int i;

	for(i = 0; i < sizeof(weapons_primary); i++)
	{
		if(StrEqual(classname, weapons_primary[i]))
			return SLOT_PRIMARY;
	}

	for(i = 0; i < sizeof(weapons_secondary); i++)
	{
		if(StrEqual(classname, weapons_secondary[i]))
			return SLOT_SECONDARY;
	}

	for(i = 0; i < sizeof(weapons_grenade); i++)
	{
		if(StrEqual(classname, weapons_grenade[i]))
			return SLOT_GRENADE;
	}

	return SLOT_NONE; // Unknown weapon
}
