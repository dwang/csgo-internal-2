#pragma once

#include "../../dependencies/utilities/netvars.hpp"
#include "../../dependencies/utilities/utilities.hpp"
#include "../math/vector.hpp"
#include "collideable.hpp"
#include "studio.hpp"

enum entity_flags
{
	fl_onground = (1 << 0),
	fl_ducking = (1 << 1),
	fl_waterjump = (1 << 2),
	fl_ontrain = (1 << 3),
	fl_inrain = (1 << 4),
	fl_frozen = (1 << 5),
	fl_atcontrols = (1 << 6),
	fl_client = (1 << 7),
	fl_fakeclient = (1 << 8),
	fl_inwater = (1 << 9),
	fl_fly = (1 << 10),
	fl_swim = (1 << 11),
	fl_conveyor = (1 << 12),
	fl_npc = (1 << 13),
	fl_godmode = (1 << 14),
	fl_notarget = (1 << 15),
	fl_aimtarget = (1 << 16),
	fl_partialground = (1 << 17),
	fl_staticprop = (1 << 18),
	fl_graphed = (1 << 19),
	fl_grenade = (1 << 20),
	fl_stepmovement = (1 << 21),
	fl_donttouch = (1 << 22),
	fl_basevelocity = (1 << 23),
	fl_worldbrush = (1 << 24),
	fl_object = (1 << 25),
	fl_killme = (1 << 26),
	fl_onfire = (1 << 27),
	fl_dissolving = (1 << 28),
	fl_transragdoll = (1 << 29),
	fl_unblockable_by_player = (1 << 30)
};

enum item_definition_indexes
{
	weapon_none = 0,
	weapon_deagle,
	weapon_elite,
	weapon_fiveseven,
	weapon_glock,
	weapon_ak47 = 7,
	weapon_aug,
	weapon_awp,
	weapon_famas,
	weapon_g3sg1,
	weapon_galilar = 13,
	weapon_m249,
	weapon_m4a1 = 16,
	weapon_mac10,
	weapon_p90 = 19,
	weapon_mp5sd = 23,
	weapon_ump45,
	weapon_xm1014,
	weapon_bizon,
	weapon_mag7,
	weapon_negev,
	weapon_sawedoff,
	weapon_tec9,
	weapon_taser,
	weapon_hkp2000,
	weapon_mp7,
	weapon_mp9,
	weapon_nova,
	weapon_p250,
	weapon_scar20 = 38,
	weapon_sg556,
	weapon_ssg08,
	weapon_knifegg,
	weapon_knife,
	weapon_flashbang,
	weapon_hegrenade,
	weapon_smokegrenade,
	weapon_molotov,
	weapon_decoy,
	weapon_incgrenade,
	weapon_c4,
	weapon_healthshot = 57,
	weapon_knife_t = 59,
	weapon_m4a1_silencer,
	weapon_usp_silencer,
	weapon_cz75a = 63,
	weapon_revolver,
	weapon_tagrenade = 68,
	weapon_fists,
	weapon_breachcharge,
	weapon_tablet = 72,
	weapon_melee = 74,
	weapon_axe,
	weapon_hammer,
	weapon_spanner = 78,
	weapon_knife_ghost = 80,
	weapon_firebomb,
	weapon_diversion,
	weapon_frag_grenade,
	weapon_bayonet = 500,
	weapon_knife_flip = 505,
	weapon_knife_gut,
	weapon_knife_karambit,
	weapon_knife_m9_bayonet,
	weapon_knife_tactical,
	weapon_knife_falchion = 512,
	weapon_knife_survival_bowie = 514,
	weapon_knife_butterfly,
	weapon_knife_push,
	weapon_knife_ursus = 519,
	weapon_knife_gypsy_jackknife,
	weapon_knife_stiletto = 522,
	weapon_knife_widowmaker
};

class entity_t
{
public:
	bool is_player()
	{
		return utilities::get().call_vfunc<153, bool>(this);
	}

	bool is_weapon()
	{
		return utilities::get().call_vfunc<160, bool>(this);
	}

	collideable_t* collideable()
	{
		return utilities::get().call_vfunc<3, collideable_t*>(this);
	}

	void* animating()
	{
		return reinterpret_cast<void*>(std::uintptr_t(this) + 0x4);
	}

	bool setup_bones(matrix_t* out, int max_bones, int mask, float time)
	{
		if (!this)
			return false;

		return utilities::get().call_vfunc<13, bool>(animating(), out, max_bones, mask, time);
	}

	int draw_model(int flags, uint8_t alpha)
	{
		return utilities::get().call_vfunc<9, int>(animating(), flags, alpha);
	}

	netvar_fn(int, flags, "DT_BasePlayer->m_fFlags");
	netvar_fn(unsigned long, owner_handle, "DT_BaseEntity->m_hOwnerEntity");
	offset_fn(bool, dormant, 0xED);
	netvar_fn(float, simulation_time, "DT_BaseEntity->m_flSimulationTime");
	netvar_fn(vec3_t, origin, "DT_BaseEntity->m_vecOrigin");
	netvar_fn(vec3_t, view_offset, "DT_BaseEntity->m_vecViewOffset");
	netvar_fn(int, team, "DT_BaseEntity->m_iTeamNum");
	netvar_fn(bool, spotted, "DT_BaseEntity->m_bSpotted");
};


class player_t : public entity_t
{
public:
	netvar_fn(bool, has_defuser, "DT_CSPlayer->m_bHasDefuser");
	netvar_fn(bool, has_gun_game_immunity, "DT_CSPlayer->m_bGunGameImmunity");
	netvar_fn(int, shots_fired, "DT_CSPlayer->m_iShotsFired");
	netvar_fn(vec3_t, eye_angles, "DT_CSPlayer->m_angEyeAngles[0]");
	netvar_fn(int, armor, "DT_CSPlayer->m_ArmorValue");
	netvar_fn(bool, has_helmet, "DT_CSPlayer->m_bHasHelmet");
	netvar_fn(bool, is_scoped, "DT_CSPlayer->m_bIsScoped");
	
	netvar_fn(float, lower_body_yaw, "DT_CSPlayer->m_flLowerBodyYawTarget");
	netvar_fn(float, flash_duration, "DT_CSPlayer->m_flFlashDuration");
	netvar_fn(int, health, "DT_BasePlayer->m_iHealth");
	netvar_fn(int, life_state, "DT_BasePlayer->m_lifeState");
	netvar_fn(int, tick_base, "DT_BasePlayer->m_nTickBase");
	netvar_fn(vec3_t, punch_angle, "DT_BasePlayer->m_viewPunchAngle");
	netvar_fn(vec3_t, aim_punch_angle, "DT_BasePlayer->m_aimPunchAngle");
	netvar_fn(vec3_t, velocity, "DT_BasePlayer->m_vecVelocity[0]");
	netvar_fn(float, max_speed, "DT_BasePlayer->m_flMaxspeed");
	netvar_fn(unsigned long, observer_target, "DT_BasePlayer->m_hObserverTarget");
	netvar_fn(unsigned long, active_weapon_handle, "DT_BaseCombatCharacter->m_hActiveWeapon");

	bool is_valid()
	{
		return (this && !this->dormant() && this->is_player() && this->health() > 0);
	}

	vec3_t get_bone_position(int bone)
	{
		matrix_t bone_matrix[128];

		if (setup_bones(bone_matrix, 128, bone_flags::bone_used_by_anything, 0.0f))
			return vec3_t(bone_matrix[bone][0][3], bone_matrix[bone][1][3], bone_matrix[bone][2][3]);

		return vec3_t{};
	}
};
