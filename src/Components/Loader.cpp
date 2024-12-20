#include <STDInclude.hpp>
#include <Utils/InfoString.hpp>

#include "Modules/AntiLag.hpp"
#include "Modules/ArenaLength.hpp"
#include "Modules/Auth.hpp"
#include "Modules/Bans.hpp"
#include "Modules/Bots.hpp"
#include "Modules/Branding.hpp"
#include "Modules/Bullet.hpp"
#include "Modules/CardTitles.hpp"
#include "Modules/Ceg.hpp"
#include "Modules/Changelog.hpp"
#include "Modules/Chat.hpp"
#include "Modules/ClanTags.hpp"
#include "Modules/ClientCommand.hpp"
#include "Modules/ConnectProtocol.hpp"
#include "Modules/Console.hpp"
#include "Modules/ConfigStrings.hpp"
#include "Modules/D3D9Ex.hpp"
#include "Modules/Debug.hpp"
#include "Modules/Discord.hpp"
#include "Modules/Discovery.hpp"
#include "Modules/Download.hpp"
#include "Modules/Elevators.hpp"
#include "Modules/Events.hpp"
#include "Modules/Exception.hpp"
#include "Modules/FastFiles.hpp"
#include "Modules/Friends.hpp"
#include "Modules/Gamepad.hpp"
#include "Modules/Huffman.hpp"
#include "Modules/IPCPipe.hpp"
#include "Modules/Lean.hpp"
#include "Modules/MapDump.hpp"
#include "Modules/MapRotation.hpp"
#include "Modules/Materials.hpp"
#include "Modules/Melee.hpp"
#include "Modules/ModList.hpp"
#include "Modules/ModelCache.hpp"
#include "Modules/ModelSurfs.hpp"
#include "Modules/NetworkDebug.hpp"
#include "Modules/News.hpp"
#include "Modules/Node.hpp"
#include "Modules/Party.hpp"
#include "Modules/PlayerMovement.hpp"
#include "Modules/PlayerName.hpp"
#include "Modules/Playlist.hpp"
#include "Modules/QuickPatch.hpp"
#include "Modules/RawFiles.hpp"
#include "Modules/RawMouse.hpp"
#include "Modules/RCon.hpp"
#include "Modules/Rumble.hpp"
#include "Modules/Security.hpp"
#include "Modules/ServerCommands.hpp"
#include "Modules/ServerInfo.hpp"
#include "Modules/ServerList.hpp"
#include "Modules/Session.hpp"
#include "Modules/SlowMotion.hpp"
#include "Modules/StartupMessages.hpp"
#include "Modules/Stats.hpp"
#include "Modules/StringTable.hpp"
#include "Modules/StructuredData.hpp"
#include "Modules/TextRenderer.hpp"
#include "Modules/Theatre.hpp"
#include "Modules/Threading.hpp"
#include "Modules/Toast.hpp"
#include "Modules/UIFeeder.hpp"
#include "Modules/Updater.hpp"
#include "Modules/VisionFile.hpp"
#include "Modules/Voice.hpp"
#include "Modules/Vote.hpp"
#include "Modules/Weapon.hpp"
#include "Modules/Window.hpp"

#include "Modules/BotLib/lPrecomp.hpp"

namespace Components
{
	bool Loader::Pregame = true;
	bool Loader::Postgame = false;
	bool Loader::Uninitializing = false;
	std::vector<Component*> Loader::Components;

	bool Loader::IsPregame()
	{
		return Pregame;
	}

	bool Loader::IsPostgame()
	{
		return Postgame;
	}

	bool Loader::IsUninitializing()
	{
		return Uninitializing;
	}

	void Loader::Initialize()
	{
		Pregame = true;
		Postgame = false;
		Uninitializing = false;
		Utils::Memory::GetAllocator()->clear();

		// High priority
		Register(new Singleton());

		Register(new Auth());
		Register(new Command());
		Register(new Dvar());
		Register(new Exception()); // Install our exception handler as early as possible to get better debug dumps from startup crashes
		Register(new IPCPipe());
		Register(new Network());
		Register(new Logger());
		Register(new UIScript());
		Register(new ZoneBuilder());

		Register(new ConfigStrings()); // Needs to be there early !! Before modelcache & weapons

		Register(new AntiLag());
		Register(new ArenaLength());
		Register(new AssetHandler());
		Register(new Bans());
		Register(new Bots());
		Register(new Branding());
		Register(new Bullet());
		Register(new CardTitles());
		Register(new Ceg());
		Register(new Changelog());
		Register(new Chat());
		Register(new ClanTags());
		Register(new ClientCommand());
		Register(new ConnectProtocol());
		Register(new Console());
		Register(new D3D9Ex());
		Register(new Debug());
		Register(new Dedicated());
		Register(new Discord());
		Register(new Discovery());
		Register(new Download());
		Register(new Elevators());
		Register(new Events());
		Register(new FastFiles());
		Register(new FileSystem());
		Register(new Friends());
		Register(new Gamepad());
		Register(new Rumble());
		Register(new Huffman());
		Register(new Lean());
		Register(new Localization());
		Register(new MapDump());
		Register(new MapRotation());
		Register(new Maps());
		Register(new Materials());
		Register(new Melee());
		Register(new Menus());
		Register(new ModList());
		Register(new ModelCache());
		Register(new ModelSurfs());
		Register(new NetworkDebug());
		Register(new News());
		Register(new Node());
		Register(new Party());
		Register(new PlayerMovement());
		Register(new PlayerName());
		Register(new Playlist());
		Register(new QuickPatch());
		Register(new RawFiles());
		Register(new RawMouse());
		Register(new RCon());
		Register(new Renderer());
		Register(new Scheduler());
		Register(new Security());
		Register(new ServerCommands());
		Register(new ServerInfo());
		Register(new ServerList());
		Register(new Session());
		Register(new SlowMotion());
		Register(new StartupMessages());
		Register(new Stats());
		Register(new StringTable());
		Register(new StructuredData());
		Register(new TextRenderer());
		Register(new Theatre());
		Register(new Threading());
		Register(new Toast());
		Register(new UIFeeder());
		Register(new Updater());
		Register(new VisionFile());
		Register(new Voice());
		Register(new Vote());
		Register(new Weapon());
		Register(new Window());
		Register(new Zones());

		Register(new GSC::GSC());

		Register(new BotLib::lPrecomp());

		Pregame = false;

		// Make sure preDestroy is called when the game shuts down
		Scheduler::OnGameShutdown(PreDestroy);
	}

	void Loader::Uninitialize()
	{
		Uninitializing = true;
		PreDestroyNoPostGame();

		std::reverse(Components.begin(), Components.end());
		for (auto& component : Components)
		{
#ifdef DEBUG
			if (!IsPerformingUnitTests())
			{
				Logger::Print("Unregister component: {}\n", component->getName());
			}
#endif
			delete component;
		}

		Components.clear();
		Utils::Memory::GetAllocator()->clear();
		Uninitializing = false;
	}

	void Loader::PreDestroy()
	{
		if (!Postgame)
		{
			Postgame = true;

			auto components = Components;

			std::reverse(components.begin(), components.end());
			for (auto& component : components)
			{
				component->preDestroy();
			}
		}
	}

	void Loader::PreDestroyNoPostGame()
	{
		if (!Postgame)
		{
			auto components = Components;

			std::reverse(components.begin(), components.end());
			for (auto& component : components)
			{
				component->preDestroy();
			}

			Postgame = true;
		}
	}

	bool Loader::PerformUnitTests()
	{
		bool result = true;

		Logger::Print("Performing unit tests for components:\n");

		for (const auto& component : Components)
		{
#if defined(FORCE_UNIT_TESTS)
			Logger::Debug("Testing '{}'...\n", component->getName());
#endif
			auto startTime = std::chrono::high_resolution_clock::now();
			auto testRes = component->unitTest();
			auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - startTime).count();
			Logger::Print("Test done ({}ms): {}\n\n", duration, (testRes ? "Success" : "Error"));
			result &= testRes;
		}

		return result;
	}

	bool Loader::IsPerformingUnitTests()
	{
#if defined(DEBUG) || defined(FORCE_UNIT_TESTS)
		return Flags::HasFlag("tests");
#else
		return false;
#endif
	}

	void Loader::Register(Component* component)
	{
		if (component)
		{
#if defined(DEBUG) || defined(FORCE_UNIT_TESTS)
			if (!IsPerformingUnitTests())
			{
				Logger::Print("Component registered: {}\n", component->getName());
			}
#endif
			Components.push_back(component);
		}
	}
}
