#include <STDInclude.hpp>
#include "Bullet.hpp"
#include "AntiLag.hpp"

namespace Components
{
	Dvar::Var Bullet::BGSurfacePenetration;
	Game::dvar_t* Bullet::BGBulletRange;

	float Bullet::ContactPointSave[3];
	float Bullet::VCSave[3];
	float Bullet::CalcRicochetSave[3];

	float Bullet::ColorYellow[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	float Bullet::ColorBlue[] = { 0.0f, 0.0f, 1.0f, 1.0f };
	float Bullet::ColorOrange[] = { 1.0f, 0.7f, 0.0f, 1.0f };
	float Bullet::ColorWhite[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	float Bullet::BG_GetSurfacePenetrationDepthStub(const Game::WeaponDef* weapDef, int surfaceType)
	{
		assert(weapDef);
		assert(weapDef->penetrateType != Game::PENETRATE_TYPE_NONE);
		AssertIn(weapDef->penetrateType, Game::PENETRATE_TYPE_COUNT);
		AssertIn(surfaceType, Game::SURF_TYPE_COUNT);

		const auto penetrationDepth = BGSurfacePenetration.get<float>();
		if (penetrationDepth > 0.0f)
		{
			// Custom depth
			return penetrationDepth;
		}

		// Game's code
		if (surfaceType != Game::SURF_TYPE_DEFAULT)
		{
			return (*Game::penetrationDepthTable)[weapDef->penetrateType][surfaceType];
		}

		return 0.0f;
	}

	void Bullet::BG_srand_Hk(unsigned int* pHoldrand)
	{
		*pHoldrand = static_cast<unsigned int>(std::rand());
	}

	void Bullet::BulletRicochet_Save(const float* contactPoint)
	{
		std::memcpy(ContactPointSave, contactPoint, sizeof(float[3]));
	}

	__declspec(naked) void Bullet::BulletRicochet_Stub()
	{
		__asm
		{
			pushad
			push[esp + 0x20 + 0xC]
			call BulletRicochet_Save
			add esp, 0x4
			popad

			// Game's code
			sub esp, 0x4C
			push ebp
			mov ebp, dword ptr[esp + 0x60]

			push 0x5D5B08
			ret
		}
	}

	void Bullet::_VectorMA_Stub(float* va, float scale, float* vb, float* vc)
	{
		vc[0] = va[0] + scale * vb[0];
		vc[1] = va[1] + scale * vb[1];
		vc[2] = va[2] + scale * vb[2];

		std::memcpy(VCSave, vc, sizeof(float[3]));
	}

	void Bullet::CalcRicochet_Stub(const float* incoming, const float* normal, float* result)
	{
		Utils::Hook::Call<void(const float*, const float*, float*)>(0x5D59F0)(incoming, normal, result);
		std::memcpy(CalcRicochetSave, result, sizeof(float[3]));
	}

	int Bullet::Bullet_Fire(Game::gentity_s* attacker,
		float spread,
		Game::weaponParms* wpParms,
		Game::gentity_s* weaponEnt,
		Game::PlayerHandIndex handIndex,
		int gameTime)
	{
		Game::AntilagClientStore antiLag_Backup;
		AntiLag::G_AntiLagRewindClientPos(attacker, gameTime, &antiLag_Backup);

#ifdef DEBUG_RIOT_SHIELD
		float tmp[3];

		Game::G_DebugStar(ContactPointSave, ColorYellow);

		tmp[0] = (CalcRicochetSave[0] * 100.0f) + VCSave[0];
		tmp[1] = (CalcRicochetSave[1] * 100.0f) + VCSave[1];
		tmp[2] = (CalcRicochetSave[2] * 100.0f) + VCSave[1];

		Game::G_DebugLineWithDuration(VCSave, tmp, ColorOrange, 1, 100);
		Game::G_DebugStar(tmp, ColorBlue);

		spread = 0;
#endif
		uint32_t perks[2] = { 0,0 };

		if (attacker->client) {
			perks[0] = attacker->client->ps.perks[0];
			perks[1] = attacker->client->ps.perks[1];
		}

		float fMinDamageRange = Bullet::BGBulletRange->current.value;
		int32_t nBullets = 1;

		const bool ShouldSpread = Game::BG_WeaponBulletFire_ShouldSpread(perks, wpParms->weapDef);
		if (ShouldSpread)
		{
			fMinDamageRange = wpParms->weapDef->fMinDamageRange;
			nBullets = wpParms->weapDef->shotCount - 1;
		}

		uint32_t randomSeed = gameTime;
		if (handIndex) {
			randomSeed = gameTime + 10;
		}

		BG_srand_Hk(&randomSeed);

		Dvar::Var g_debugBullet(0x19BD624);
		Game::BulletFireParams bulletContext;
		const int weaponIndex = weaponEnt ? weaponEnt->s.number : 0x7FE;

		Game::BulletTraceResults bulletTr;

		for (; nBullets > 0; nBullets--)
		{
			// #TODO: should we move Init out of iteration for optimization? (current code is IW4 copy)
			bulletContext.Init(weaponIndex, wpParms);
			bulletContext.methodOfDeath = Game::Bullet_GetMethodOfDeath(perks, wpParms->weapDef);

			Game::Bullet_Endpos(&randomSeed, spread, bulletContext.end, bulletContext.dir, wpParms, fMinDamageRange);

			if (g_debugBullet.get<int>() == 1) {
				Game::G_DebugLineWithDuration(bulletContext.origStart, bulletContext.end, ColorWhite, 1, 100);
			}

			if (Game::BG_WeaponBulletFire_ShouldPenetrate(perks, wpParms->weapDef))
			{
				Game::Bullet_FirePenetrate(&randomSeed, &bulletContext, &bulletTr, wpParms->weaponIndex, attacker, gameTime);
				continue;
			}

			__asm
			{
				mov     eax, gameTime
				push    eax
				mov     eax, [ebp + 10h]
				mov     ecx, [eax + 3Ch]
				push    ecx
				lea     edx, bulletContext
				push    edx
				lea     eax, randomSeed
				push    eax
				mov     eax, attacker
				lea     ecx, bulletTr
				call    Game::Bullet_FireExtended
				add     esp, 10h
			}
		}

		if (ShouldSpread)
		{
			float spreadDummy = 0, rangeDummy = 0; // required for fstp instruction
			__asm
			{
				mov     ecx, weaponEnt
				push    ecx
				fld		spread
				mov		esi, wpParms
				push    esi
				sub     esp, 8
				fstp	spreadDummy
				mov     eax, attacker
				fld		fMinDamageRange
				fstp	rangeDummy
				call    Game::Bullet_ShotgunSpread
				add     esp, 10h
			}
		}

		AntiLag::G_AntiLag_RestoreClientPos(&antiLag_Backup);
		return -1;
	}

	Bullet::Bullet()
	{
		BGSurfacePenetration = Dvar::Register<float>("bg_surfacePenetration", 0.0f,
			0.0f, std::numeric_limits<float>::max(), Game::DVAR_CODINFO, "Set to a value greater than 0 to override the surface penetration depth");
		BGBulletRange = Game::Dvar_RegisterFloat("bg_bulletRange", 8192.0f,
			0.0f, std::numeric_limits<float>::max(), Game::DVAR_CODINFO, "Max range used when calculating the bullet end position");

		Utils::Hook(0x4F6980, BG_GetSurfacePenetrationDepthStub, HOOK_JUMP).install()->quick();

		// we dont need this anymore since we rebuild Bullet_Fire
		//Utils::Hook(0x440368, BG_srand_Hk, HOOK_CALL).install()->quick();

		Utils::Hook(0x4A4E6B, Bullet_Fire, HOOK_CALL).install()->quick(); // FireWeapon
		Utils::Hook(0x4E24D0, Bullet_Fire, HOOK_CALL).install()->quick(); // VehCmd_FireWeapon
		Utils::Hook(0x498167, Bullet_Fire, HOOK_CALL).install()->quick(); // Scr_MagicBullet
		Utils::Hook(0x5FF174, Bullet_Fire, HOOK_CALL).install()->quick(); // Turret_Shoot_internal
		Utils::Hook(0x5D5C0B, Bullet_Fire, HOOK_CALL).install()->quick(); // Riot Shield related.

		std::memset(ContactPointSave, 0, sizeof(float[3]));
		std::memset(VCSave, 0, sizeof(float[3]));
		std::memset(CalcRicochetSave, 0, sizeof(float[3]));

#ifdef DEBUG_RIOT_SHIELD
		Utils::Hook(0x5D5B00, BulletRicochet_Stub, HOOK_JUMP).install()->quick();
		Utils::Hook::Nop(0x5D5B00 + 5, 3);

		Utils::Hook(0x5D5BBA, CalcRicochet_Stub, HOOK_CALL).install()->quick();

		Utils::Hook(0x5D5BD7, _VectorMA_Stub, HOOK_CALL).install()->quick();
#endif
	}
}
