#include <STDInclude.hpp>
#include "Melee.hpp"
#include "AntiLag.hpp"

namespace Components
{
	void Melee::FireWeaponMelee(Game::gentity_s* ent, int gameTime)
	{
		if (AntiLag::IsDisabled()) {
			gameTime = Game::level->time;
		}
		else if (AntiLag::IsDebugging()) {
			Logger::Debug("FireWeaponMelee: at tick {}, level.time {}\n", gameTime, Game::level->time);
		}

		Game::FireWeaponMelee(ent, gameTime);
	}

	Game::gentity_s* Melee::Melee_Trace(
		Game::gentity_s* attacker,
		Game::weaponParms* wpParms,
		float player_meleeRange,
		float player_meleeWidth,
		float player_meleeHeight)
	{
		float hitPoint[3];
		Game::trace_t tr;

		const Game::WeaponDef* weapDef = wpParms->weapDef;
		int iMeleeDamage = weapDef->iMeleeDamage;
		if (!Game::Melee_Trace_Internal(
			attacker,
			wpParms,
			iMeleeDamage,
			player_meleeRange,
			player_meleeWidth,
			player_meleeHeight,
			&tr,
			hitPoint))
		{
			return nullptr;
		}

		// game does not check if entityHitId is valid, should we start to do it for safer code?
		uint16_t entityHitId = Game::Trace_GetEntityHitId(&tr);
		Game::gentity_s* hitEntity = &Game::g_entities[entityHitId];
		const bool specialPartgroup = tr.partGroup == 19;

		if (attacker->client && hitEntity->client && !specialPartgroup) {
			Game::G_AddEvent(attacker, Game::EV_MELEE_BLOOD, 0);
		}

		const Game::entity_event_t entityEvent = !hitEntity->client ? Game::EV_MELEE_MISS : Game::EV_MELEE_HIT;
		Game::gentity_s* meleeTempEvent = Game::G_TempEntity(hitPoint, entityEvent);

		meleeTempEvent->s.otherEntityNum = hitEntity->s.number;
		meleeTempEvent->s.weapon = attacker->s.weapon;
		meleeTempEvent->s.un2.__s1.weaponModel = attacker->s.un2.__s1.weaponModel;
		meleeTempEvent->s.eventParm = 0;

		if (weapDef->knifeModel && attacker->client) {
			meleeTempEvent->s.eventParm = 1;
		}
		if (specialPartgroup) {
			meleeTempEvent->s.eventParm |= 2u;
		}

		if (hitEntity->s.number == 0x7FE || !hitEntity->takedamage) {
			return nullptr;
		}

		float endPoint[3];
		endPoint[0] = wpParms->forward[0];
		endPoint[1] = wpParms->forward[1];
		endPoint[2] = wpParms->forward[2] + 0.25f;

		int		 damageRand = (int)rand() % 5 + iMeleeDamage;
		uint16_t partName = tr.partName;
		uint16_t partGroup = tr.partGroup;

		if (specialPartgroup)
		{
			partName = *Game::PartName_None;
			partGroup = 0;

			if (hitEntity->client)
			{
				Game::G_ShieldNotifyAndDamage(
					hitEntity,
					attacker,
					attacker,
					endPoint,
					hitPoint,
					damageRand,
					16,
					8,
					-1,
					0);
				return hitEntity;
			}
		}

		Game::G_Damage(
			hitEntity,
			attacker,
			attacker,
			endPoint,
			hitPoint,
			damageRand,
			specialPartgroup ? 16 : 0,
			8u,
			-1,
			partGroup,
			tr.modelIndex,
			partName,
			0);

		return hitEntity;
	}

	void Melee::Weapon_Melee(
		Game::gentity_s* attacker,
		Game::weaponParms* wpParms,
		float player_meleeRange,
		float player_meleeWidth,
		float player_meleeHeight,
		int gameTime)
	{
		Game::AntilagClientStore antilagStore;

		AntiLag::G_AntiLagRewindClientPos(attacker, gameTime, &antilagStore);
		Melee::Melee_Trace(attacker, wpParms, player_meleeRange, player_meleeWidth, player_meleeHeight);
		AntiLag::G_AntiLag_RestoreClientPos(&antilagStore);
	}

	Melee::Melee()
	{
		Utils::Hook(0x5D6D6C, Melee::FireWeaponMelee, HOOK_CALL).install()->quick();
		Utils::Hook(0x4F251F, Weapon_Melee, HOOK_CALL).install()->quick(); // Weapon_Melee
	}
}
