#pragma once

namespace Components
{
	class Bullet : public Component
	{
	public:
		Bullet();

	private:
		static Dvar::Var BGSurfacePenetration;
		// Can't use Var class inside assembly stubs
		static Game::dvar_t* BGBulletRange;

		static float ContactPointSave[];
		static float VCSave[];
		static float CalcRicochetSave[];

		static float ColorYellow[];
		static float ColorBlue[];
		static float ColorOrange[];
		static float ColorWhite[];

		static float BG_GetSurfacePenetrationDepthStub(const Game::WeaponDef* weapDef, int surfaceType);

		static void BG_srand_Hk(unsigned int* pHoldrand);
		static int Bullet_Fire(Game::gentity_s* attacker, float spread, Game::weaponParms* weaponParms, Game::gentity_s* weaponEnt, Game::PlayerHandIndex handIndex, int gameTime);

		static void BulletRicochet_Save(const float* contactPoint);
		static void BulletRicochet_Stub();

		static void CalcRicochet_Stub(const float* incoming, const float* normal, float* result);

		static void _VectorMA_Stub(float* va, float scale, float* vb, float* vc);
	};
}
