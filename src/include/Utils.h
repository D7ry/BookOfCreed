#pragma once
#include <cmath>
#include  <random>
#include  <iterator>
#include "PCH.h"
#include "include/lib/TrueHUDAPI.h"
#include <shared_mutex>

#define CONSOLELOG(msg) RE::ConsoleLog::GetSingleton()->Print(msg);
#define PI 3.1415926535897932384626f

namespace RE
{

	enum DIFFICULTY
	{
		kNovice = 0,
		kApprentice = 1,
		kAdept = 2,
		kExpert = 3,
		kMaster = 4,
		kLegendary = 5
	};
	namespace Offset
	{

		typedef void(_fastcall* tPushActorAway_sub_14067D4A0)(RE::AIProcess* a_causer, RE::Actor* a_target, RE::NiPoint3& a_origin, float a_magnitude);
		inline static REL::Relocation<tPushActorAway_sub_14067D4A0> pushActorAway{ RELOCATION_ID(38858, 39895) };

		typedef void(_fastcall* _shakeCamera)(float strength, RE::NiPoint3 source, float duration);
		inline static REL::Relocation<_shakeCamera> shakeCamera{ RELOCATION_ID(32275, 33012) };

		typedef void(_fastcall* _destroyProjectile)(RE::Projectile* a_projectile);
		inline static REL::Relocation<_destroyProjectile> destroyProjectile{ RELOCATION_ID(42930, 44110) };

		typedef RE::TESObjectREFR*(_fastcall* _getEquippedShield)(RE::Actor* a_actor);
		inline static REL::Relocation<_getEquippedShield> getEquippedShield{ RELOCATION_ID(37624, 38577) };

		inline void SGTM(float a_in)
		{
			static float* g_SGTM = (float*)RELOCATION_ID(511883, 388443).address();
			*g_SGTM = a_in;
			using func_t = decltype(SGTM);
			REL::Relocation<func_t> func{ RELOCATION_ID(66989, 68246) };
			return;
		}

		static float* g_worldScaleInverse = (float*)RELOCATION_ID(230692, 187407).address();
		inline static float* g_deltaTime = (float*)RELOCATION_ID(523660, 410199).address();          // 2F6B948
		inline static float* g_deltaTimeRealTime = (float*)RELOCATION_ID(523661, 410200).address();  // 2F6B94C

		inline bool playPairedIdle(RE::AIProcess* proc, RE::Actor* attacker, RE::DEFAULT_OBJECT smth, RE::TESIdleForm* idle, bool a5, bool a6, RE::TESObjectREFR* target)
		{
			using func_t = decltype(&playPairedIdle);
			REL::Relocation<func_t> func{ RELOCATION_ID(38290, 39256) };
			return func(proc, attacker, smth, idle, a5, a6, target);
		}

		inline int soundHelper_a(void* manager, RE::BSSoundHandle* a2, int a3, int a4)  //sub_140BEEE70
		{
			using func_t = decltype(&soundHelper_a);
			REL::Relocation<func_t> func{ RELOCATION_ID(66401, 67663) };
			return func(manager, a2, a3, a4);
		}

		inline void soundHelper_b(RE::BSSoundHandle* a1, RE::NiAVObject* source_node)  //sub_140BEDB10
		{
			using func_t = decltype(&soundHelper_b);
			REL::Relocation<func_t> func{ RELOCATION_ID(66375, 67636) };
			return func(a1, source_node);
		}

		inline char __fastcall soundHelper_c(RE::BSSoundHandle* a1)  //sub_140BED530
		{
			using func_t = decltype(&soundHelper_c);
			REL::Relocation<func_t> func{ RELOCATION_ID(66355, 67616) };
			return func(a1);
		}

		inline char set_sound_position(RE::BSSoundHandle* a1, float x, float y, float z)
		{
			using func_t = decltype(&set_sound_position);
			REL::Relocation<func_t> func{ RELOCATION_ID(66370, 67631) };
			return func(a1, x, y, z);
		}

		inline RE::TESObjectREFR* PlaceAtMe(RE::TESObjectREFR* self, RE::TESForm* a_form, std::uint32_t count, bool forcePersist, bool initiallyDisabled)
		{
			using func_t = RE::TESObjectREFR*(RE::BSScript::Internal::VirtualMachine*, RE::VMStackID, RE::TESObjectREFR*, RE::TESForm*, std::uint32_t, bool, bool);
			RE::VMStackID frame = 0;

			REL::Relocation<func_t> func{ RELOCATION_ID(55672, 56203) };
			auto vm = RE::BSScript::Internal::VirtualMachine::GetSingleton();

			return func(vm, frame, self, a_form, count, forcePersist, initiallyDisabled);
		};

	}
}


namespace Utils
{
	template <typename Iter, typename RandomGenerator>
	Iter select_randomly(Iter start, Iter end, RandomGenerator& g)
	{
		std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
		std::advance(start, dis(g));
		return start;
	}

	template <typename Iter>
	Iter select_randomly(Iter start, Iter end)
	{
		static std::random_device rd;
		static std::mt19937 gen(rd());
		return select_randomly(start, end, gen);
	}
	
	void queueMessageBox(RE::BSFixedString a_message);

	void playSound(RE::Actor* a, RE::BGSSoundDescriptorForm* a_descriptor, float a_volumeOverride = 1);
	
	RE::NiPoint3 get_abs_pos(RE::Actor* a_actor, RE::NiPoint3 a_relative_pos);

	void PushActorAway(RE::Actor* causer, RE::Actor* target, float magnitude);

	void SetRotationMatrix(RE::NiMatrix3& a_matrix, float sacb, float cacb, float sb);

	void slowTime(float a_duration, float a_percentage);

	namespace Actor
	{
		RE::TESObjectWEAP* getWieldingWeapon(RE::Actor* a_actor);
		bool isDualWielding(RE::Actor* a_actor);
		bool isEquippedShield(RE::Actor* a_actor);
		bool isPowerAttacking(RE::Actor* a_actor);
		bool isBashing(RE::Actor* a_actor);
		bool isHumanoid(RE::Actor* a_actor);
		void getBodyPos(RE::Actor* a_actor, RE::NiPoint3& pos);
		void getHeadPos(RE::Actor* a_actor, RE::NiPoint3& pos);
		void getHeadPos(RE::Actor* a_actor, RE::NiAVObject*& pos);
		void dropShield(RE::Actor* a_actor);
	}

	namespace math
	{
#define PI 3.14159265358979323846f
#define TWO_PI 6.28318530717958647692f
		float NormalRelativeAngle(float a_angle);
	}
	
};

/*Utilities related to combat*/
namespace ValhallaUtils
{
	bool is_adversary(RE::Actor* actor1, RE::Actor* actor2);
	bool isBackFacing(RE::Actor* actor1, RE::Actor* actor2);

};

namespace API
{
	inline bool TrueHUD_API_acquired = false;
	inline TRUEHUD_API::IVTrueHUD3* _TrueHud_API;

	void init();
};

/*Some of my own convenience stuff*/
namespace DtryUtils
{
	/*Helper class to batch load forms from plugin records.*/
	class formLoader
	{
	private:
		RE::BSFixedString _pluginName;
		RE::TESDataHandler* _dataHandler;
		int _loadedForms;

	public:
		formLoader(RE::BSFixedString pluginName);
		~formLoader();


		template <class formType>
		void load(formType*& formRet, RE::FormID formID)
		{
			formRet = _dataHandler->LookupForm<formType>(formID, _pluginName);
			if (!formRet) {
				logger::critical("Error: null formID or wrong form type when loading {} from {}", formID, _pluginName);
			}
			_loadedForms++;
		}
	};

	/*Helper class to load from a simple ini file.*/
	class settingsLoader
	{
	private:
		std::shared_ptr<CSimpleIniA> _ini;
		const char* _section;
		int _loadedSettings;
		const char* _settingsFile;
	public:
		settingsLoader(const char* settingsFile);
		/*Set the active section. Load() will load keys from this section.*/
		void setActiveSection(const char* section);
		
		void load(bool& settingRef, const char* key);
		void load(float& settingRef, const char* key);
		void load(uint32_t& settingRef, const char* key);
		void load(int& settingRef, const char* key);
		
		void log();
	};

	class rayCast
	{

#define YELLOW 0xFFFF00      // yellow
#define GREEN 0xff00ff   //green
	public:

		/*Do a simple raycast at a singular point to check if anything exists there.
		If anything exists, update A_POS argument to the position where raycast is hit.*/
		static bool object_exists(RE::NiPoint3& a_pos, float a_range = 30.f);
		/*Cast a ray from the center of the actor to a_rayEnd, return the first object encountered, or nullptr if nothing is hit.*/
		static RE::TESObjectREFR* cast_ray(RE::Actor* a_actor, RE::NiPoint3 a_rayEnd, float a_castPos = 0.5f, float* ret_rayDist = nullptr);
				
		
	};
}


/*Interface for manipulating all actor's animation speeds. Manipulation is done by hooking animation_update function. Doesn't work for player.*/
class AnimSpeedManager
{
	class on_updateAnimation_internal;
	class on_updateAnimation_player;

public:
	static void setAnimSpeed(RE::ActorHandle a_actorHandle, float a_speedMult, float a_dur);
	static void revertAnimSpeed(RE::ActorHandle a_actorHandle);
	static void revertAllAnimSpeed();
	
	static void init() {
		on_updateAnimation_internal::install();
		on_updateAnimation_player::install();
	}

private:
	struct AnimSpeedData
	{
		float speedMult;
		float dur;
	};
	static inline std::unordered_map<RE::ActorHandle, AnimSpeedData> _animSpeeds = {};
	static inline std::shared_mutex _animSpeedsLock;

	static void update(RE::ActorHandle a_actorHandle, float& a_deltaTime);
	
	class on_updateAnimation_player
	{
	public:
		static void install()
		{
			auto& trampoline = SKSE::GetTrampoline();
			REL::Relocation<std::uintptr_t> PlayerCharacterVtbl{ RE::VTABLE_PlayerCharacter[0] };
			_PlayerCharacter_UpdateAnimation = PlayerCharacterVtbl.write_vfunc(0x7D, PlayerCharacter_UpdateAnimation);
			logger::info("hook:on_updateAnimation_player");
		}

	private:
		static void PlayerCharacter_UpdateAnimation(RE::PlayerCharacter* a_this, float a_deltaTime)
		{
			AnimSpeedManager::update(a_this->GetHandle(), a_deltaTime);
			_PlayerCharacter_UpdateAnimation(a_this, a_deltaTime);
		}
		static inline REL::Relocation<decltype(PlayerCharacter_UpdateAnimation)> _PlayerCharacter_UpdateAnimation;
	};

	class on_updateAnimation_internal
	{
	public:
		static void install()
		{
			auto& trampoline = SKSE::GetTrampoline();
			REL::Relocation<uintptr_t> hook{ RELOCATION_ID(40436, 41453) };                                                                // 6E1990, 70A840, RunOneActorAnimationUpdateJob
			_UpdateAnimationInternal = trampoline.write_call<5>(hook.address() + RELOCATION_OFFSET(0x74, 0x74), UpdateAnimationInternal);  // 6E1A04, 70A8B4;
			logger::info("hook:on_updateAnimation_internal");
		}

	private:
		static void UpdateAnimationInternal(RE::Actor* a_this, float a_deltaTime)
		{
			AnimSpeedManager::update(a_this->GetHandle(), a_deltaTime);
			_UpdateAnimationInternal(a_this, a_deltaTime);
		}
		static inline REL::Relocation<decltype(UpdateAnimationInternal)> _UpdateAnimationInternal;
	};
};

constexpr uint32_t hash(const char* data, size_t const size) noexcept
{
	uint32_t hash = 5381;

	for (const char* c = data; c < data + size; ++c) {
		hash = ((hash << 5) + hash) + (unsigned char)*c;
	}

	return hash;
}

constexpr uint32_t operator"" _h(const char* str, size_t size) noexcept
{
	return hash(str, size);
}
