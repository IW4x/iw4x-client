#pragma once

namespace Components
{
	class AntiLag : public Component
	{
	public:
		AntiLag();

		static void FireWeapon(Game::gentity_s* ent, int gameTime, int a3);

		static void G_AntiLagRewindClientPos(Game::gentity_s* owner, int gameTime, Game::AntilagClientStore* antilagStore);
		static void G_AntiLag_RestoreClientPos(Game::AntilagClientStore* antilagStore);

		static bool ShouldRewind(uintptr_t stack, uintptr_t returnAddress, Game::gentity_s** attacker);

		static bool IsDisabled();
		static bool IsDebugging(const int mode = 1);

		static Dvar::Var G_AntiLag, G_AntiLagDebug;
		static bool AntiLagFilled;
		static float ColorRed[];
		static float ColorGreen[];
		static float ColorWhite[];
	};
}
