#include <STDInclude.hpp>
#include "AntiLag.hpp"

namespace Components
{
	Dvar::Var AntiLag::G_AntiLag;
	Dvar::Var AntiLag::G_AntiLagDebug;
	bool AntiLag::AntiLagFilled = false;
	float AntiLag::ColorRed[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	float AntiLag::ColorGreen[] = { 0.0f, 1.0f, 0.0f, 1.0f };
	float AntiLag::ColorWhite[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	bool AntiLag::IsDisabled()
	{
		return G_AntiLag.get<int>() == 0;
	}

	bool AntiLag::IsDebugging(const int mode)
	{
		return G_AntiLagDebug.get<int>() >= mode;
	}

	void AntiLag::FireWeapon(Game::gentity_s* ent, int gameTime, int eventType)
	{
		if (AntiLag::IsDisabled()) {
			gameTime = Game::level->time;
		}
		else if (AntiLag::IsDebugging()) {
			Logger::Debug("FireWeapon: at tick {}, level.time {}\n", gameTime, Game::level->time);
		}

		Game::FireWeapon(ent, gameTime, eventType);
	}

	void AntiLag::G_AntiLagRewindClientPos(Game::gentity_s* owner, int gameTime, Game::AntilagClientStore* antilagStore)
	{
		const int antiLagMode = G_AntiLag.get<int>();
		if (antiLagMode == 0) {
			return;
		}

		antilagStore->Reset();

		// GetClientPositionsAtTime results arrays.
		std::array<bool, Game::MAX_CLIENTS> clientsMoved;
		std::array<Game::vec3_t, Game::MAX_CLIENTS> clientsAngles;
		std::array<Game::vec3_t, Game::MAX_CLIENTS> clientsPositions;

		const int deltaTime = Game::level->time - gameTime;
		const int targetTime = deltaTime > 400 ? (Game::level->time - 400) : gameTime;

		clientsMoved.fill(false);

		if (!Game::GetClientPositionAtTime(targetTime, clientsPositions.data(), clientsAngles.data(), clientsMoved.data()))
		{
			if (AntiLag::IsDebugging()) {
				Logger::Debug("GetClientPositionAtTime failed: tick {}, level.time {}\n", targetTime, Game::level->time);
			}

			return;
		}

		for (int i = 0; i < Game::level->maxclients; ++i)
		{
			Game::gentity_s& ent = Game::g_entities[i];

			bool clientMoved = clientsMoved[i];
			if (antiLagMode == 2)
			{
				// skip teammates here.
				if (owner != nullptr && owner->s.number != ent.s.number && Game::OnSameTeam(owner, &ent) /*&& src_friendlyFire.get<bool>()*/) {
					clientMoved = false;
				}
			}

			if (!clientMoved)
			{
				antilagStore->clientMoved[i] = false;
				continue;
			}

			Utils::Maths::VectorCopy(ent.r.currentOrigin, antilagStore->realClientPositions[i]);
			Utils::Maths::VectorCopy(ent.r.currentAngles, antilagStore->realClientAngles[i]);

			if (AntiLag::IsDebugging(3))
			{
				float org[3];
				Utils::Maths::VectorCopy(ent.r.currentOrigin, org);
				org[2] += ent.r.box.halfSize[2] * 2;

				// draw current origin
				Game::G_DebugLineWithDuration(org, ent.r.currentOrigin, ColorRed, 1, 100);

				Utils::Maths::VectorCopy(clientsPositions[i], org);
				org[2] += ent.r.box.halfSize[2] * 2;

				// draw lag compensated origin
				Game::G_DebugLineWithDuration(org, clientsPositions[i], ColorGreen, 1, 100);
			}

			Utils::Maths::VectorCopy(clientsAngles[i], ent.r.currentAngles);
			Utils::Maths::VectorCopy(clientsPositions[i], ent.r.currentOrigin);

			Game::SV_LinkEntity(&ent);

			if (AntiLag::IsDebugging(2)) {
				Logger::Debug("antiLag: moving entity ({}) tick {}, level.time {}\n", i, targetTime, Game::level->time);
			}

			antilagStore->clientMoved[i] = true;
		}

		AntiLag::AntiLagFilled = true;
	}

	void AntiLag::G_AntiLag_RestoreClientPos(Game::AntilagClientStore* antilagStore)
	{
		if (!AntiLag::AntiLagFilled) {
			return;
		}

		for (int i = 0; i < Game::level->maxclients; ++i)
		{
			Game::gentity_s& ent = Game::g_entities[i];

			if (!antilagStore->clientMoved[i]) {
				continue;
			}

			Utils::Maths::VectorCopy(antilagStore->realClientAngles[i], ent.r.currentAngles);
			Utils::Maths::VectorCopy(antilagStore->realClientPositions[i], ent.r.currentOrigin);

			Game::SV_LinkEntity(&ent);

			antilagStore->clientMoved[i] = false;
		}

		AntiLag::AntiLagFilled = false;
	}

	static void G_RunMissile(Game::gentity_s* missile)
	{
		// idk if we need to make this static, since it does not search for anything.
		Dvar::Var missileDebugDraw(0x1A865D4);

		if (missile->linkedEntity)
		{
			float org[3];
			Utils::Maths::VectorCopy(missile->r.currentOrigin, org);

			Game::G_GeneralLink(missile);
			Game::G_RunThink(missile);

			if (missileDebugDraw.get<bool>()) {
				Game::G_DebugLineWithDuration(org, missile->r.currentOrigin, AntiLag::ColorWhite, 1, 1000);
			}

			return;
		}

		Game::WeaponDef* WeaponDef = Game::BG_GetWeaponDef(missile->s.weapon);

		const bool hitGround = missile->s.groundEntityNum == 0x7FE;
		const bool canStick = (WeaponDef->stickiness == Game::WEAPSTICKINESS_ALL
			|| WeaponDef->stickiness == Game::WEAPSTICKINESS_ALL_ORIENT
			|| WeaponDef->stickiness == Game::WEAPSTICKINESS_KNIFE);

		bool isThrowingKnife = WeaponDef->weapClass == Game::WEAPCLASS_THROWINGKNIFE;

		// l3d note: this check below does not exist in original iw engine.
		if (isThrowingKnife && hitGround && canStick)
		{
			// we did stick, no need for rewinding anymore.
			isThrowingKnife = false;
		}

		// game does not run antilag on throwables except throwing knife.
		if (!isThrowingKnife) {
			return Game::G_RunMissileInternal(missile);
		}

		Game::AntilagClientStore antilagStore;

		// i have no idea why it is dereferencing attachModelNames - thats what its actually pointing in this structure...
		// the structure itself can be wrong. throwingDelay equals negative numbers like -67
		// 05.12.24 UPD: Caball009 made a PR with fixed gentity_s struct, so this line below starts to point at "missile->entData.missile.antilagTimeOffset"
		int32_t throwingDelay = *reinterpret_cast<int32_t*>(&missile->attachModelNames[10]);

		if (!AntiLag::IsDisabled() && AntiLag::IsDebugging()) {
			Logger::Debug("G_RunMissile: at tick {}, level.time {}\n", Game::level->time + throwingDelay, Game::level->time);
		}

		uint16_t ownerId = missile->r.ownerNum.number;
		Game::gentity_s* attacker = nullptr;
		if (ownerId > 0 && ownerId <= Game::level->maxclients) {
			attacker = &Game::g_entities[static_cast<int>(ownerId) - 1];
		}

		AntiLag::G_AntiLagRewindClientPos(attacker, Game::level->time + throwingDelay, &antilagStore);
		Game::G_RunMissileInternal(missile);
		AntiLag::G_AntiLag_RestoreClientPos(&antilagStore);
	}

	AntiLag::AntiLag()
	{
		G_AntiLag = Game::Dvar_RegisterInt("g_antilag", 1, 0, 2, Game::DVAR_CODINFO, "Perform antiLag.\nModes: 1 = original antiLag behaviour, 2 = optimized antiLag.");
		G_AntiLagDebug = Game::Dvar_RegisterInt("g_antilag_debug", 0, 0, 3, Game::DVAR_CHEAT, "AntiLag debugging: positions and logs.\nModes: 1 = logs, 2 = extended logs, 3 = debug overlays & extended logs.");

		AntiLag::AntiLagFilled = false;

		Utils::Hook(0x5D6D59, AntiLag::FireWeapon, HOOK_CALL).install()->quick();
		Utils::Hook(0x5E4F9E, G_RunMissile, HOOK_CALL).install()->quick(); // #todo: this needs its own file - Missile.cpp...

		// antilag is being called in Melee.cpp and Bullet.cpp now.
	}
}
