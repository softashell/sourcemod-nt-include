#if defined _neotokyo_included
  #endinput
#endif
#define _neotokyo_included

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

stock SetPlayerXP(client, xp)
{
	return SetEntProp(client, Prop_Data, "m_iFrags", xp);
}

stock GetPlayerXP(client)
{
	return GetClientFrags(client);
}

stock UpdatePlayerRank(client)
{
	new xp = GetPlayerXP(client);

	new rank = 0; // Rankless dog

	if(xp >= 0 && xp <= 3)
		rank = 1; // Private
	else if(xp >= 4 && xp <= 9)
		rank = 2; // Corporal
	else if(xp >= 10 && xp <= 19)
		rank = 3; // Sergeant
	else if(xp >= 20)
		rank = 4; // Lieutenant

	return SetPlayerRank(client, rank);
}

stock GetPlayerRank(client)
{
	return GetEntProp(client, Prop_Send, "m_iRank");
}

stock SetPlayerRank(client, rank)
{
	return SetEntProp(client, Prop_Send, "m_iRank", rank);
}

stock GetPlayerDeaths(client)
{
	return GetEntProp(client, Prop_Data, "m_iDeaths");	
}

stock SetPlayerDeaths(client, deaths)
{
	return SetEntProp(client, Prop_Data, "m_iDeaths", deaths);
}

stock GetPlayerStar(client)
{
	return GetEntProp(client, Prop_Send, "m_iStar");
}

stock SetPlayerStar(client, star)
{
	if(star < 0 || star > 5)
		return;

	return SetEntProp(client, Prop_Send, "m_iStar", star);
}

stock SetPlayerClass(client, class)
{
	return SetEntProp(client, Prop_Send, "m_iClassType", class);
}

stock GetPlayerClass(client)
{
	return GetEntProp(client, Prop_Send, "m_iClassType");
}

stock GetAmmoType(weapon)
{
	return GetEntProp(weapon, Prop_Send, "m_iPrimaryAmmoType");
}

stock GetWeaponAmmo(client, type)
{
    new offsetAmmo = FindSendPropInfo("CBasePlayer", "m_iAmmo");

    return GetEntData(client, offsetAmmo + (type * 4));
}  

stock SetWeaponAmmo(client, type, ammo)
{
    new offsetAmmo = FindSendPropInfo("CBasePlayer", "m_iAmmo");

    return SetEntData(client, offsetAmmo + (type * 4), ammo);
}

stock GetActiveWeapon(client)
{
	return GetEntPropEnt(client, Prop_Data, "m_hActiveWeapon");
}

stock GetPlayerVision(client)
{
	return GetEntProp(client, Prop_Send, "m_iVision");
}

stock SetPlayerVision(client, vision)
{
	return SetEntProp(client, Prop_Send, "m_iVision", vision);
}

stock GetPlayerLean(client)
{
	return GetEntProp(client, Prop_Send, "m_iLean");
}

stock SetPlayerLean(client, lean)
{
	return SetEntProp(client, Prop_Send, "m_iLean", lean);
}

stock float:GetPlayerAUX(client)
{
	return GetEntPropFloat(client, Prop_Send, "m_fSprintNRG");
}

stock SetPlayerAUX(client, float:amount)
{
	return SetEntPropFloat(client, Prop_Send, "m_fSprintNRG", amount);
}

stock float:GetPlayerThermopticCharge(client)
{
	return GetEntPropFloat(client, Prop_Send, "m_fThermopticNRG");
}

stock SetPlayerThermopticCharge(client, float:amount)
{
	return SetEntPropFloat(client, Prop_Send, "m_fThermopticNRG", amount);
}

stock bool:IsCloaked(client)
{
	new cloaked = GetEntProp(client, Prop_Send, "m_iThermoptic");
	
	if (cloaked > 0)
		return true;
	
	return false;
}

stock bool:IsLeaning(client)
{
	if (GetPlayerLean(client) > 0)
		return true;
	
	return false;
}

stock bool:IsUsingVision(client)
{
	if (GetPlayerVision(client) > 0)
		return true;
	
	return false;
}

stock bool:IsValidClient(client)
{
	if ((client < 1) || (client > MaxClients))
		return false;
	
	if (!IsClientInGame(client))
		return false;
	
	if (IsFakeClient(client))
		return false;
	
	return true;
}

stock StripPlayerWeapons(client, bool:knife=false)
{
	static hMyWeapons;

	if (!hMyWeapons && (hMyWeapons = FindSendPropInfo("CBasePlayer", "m_hMyWeapons")) == -1)
	{
		ThrowError("Failed to obtain: \"m_hMyWeapons\"!");
	}

	new slot;

	for(slot = 0; slot <= 5; slot++)
	{
		new weapon = GetEntDataEnt2(client, hMyWeapons + (slot * 4));

		if(!IsValidEntity(weapon))
			continue;

		if(knife)
		{
			decl String:classname[13];

			if(!GetEdictClassname(weapon, classname, 13))
				continue;

			if(StrEqual(classname, "weapon_knife"))
				continue;
		}

		RemovePlayerItem(client, weapon);
		RemoveEdict(weapon);
	}
}