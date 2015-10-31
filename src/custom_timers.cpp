/*
Bunny 2015-09-18
*/

#include <string>
#include <algorithm>

#include "custom_timers.h"

#include "unit.h"
#include "text.h"

namespace CustomTimers {

	//uint32_t dmgAmount = 1 * 256; // dmg per tick (period)

	void Timer::Expire(ProgressUnitResults* results) {}

	void Timer::TickEffect(ProgressUnitResults* results) {}

	Timer::Timer(Unit* p_owner, uint8_t p_ticksTotal, uint8_t p_tickPeriod) : owner(p_owner), ticksTotal(p_ticksTotal), tickPeriod(p_tickPeriod)
	{
		curTick = 0;
		elapsedTicks = 0;
	}

	bool Timer::Update(ProgressUnitResults* results)
	{
		bool hasExpired = false;
		//std::string a("1: curTick = " + std::to_string(curTick) + "; elapsedTicks = " + std::to_string(elapsedTicks));
		//Print(a.c_str());
		if (++curTick >= tickPeriod)
		{
			curTick = 0;
			//std::string b("2: curTick = " + std::to_string(curTick) + "; tickPeriod = " + std::to_string(tickPeriod));
			//Print(b.c_str());
			TickEffect(results);
			//std::string c("3: elapsedTicks = " + std::to_string(elapsedTicks) + "; ticksTotal = " + std::to_string(ticksTotal));
			//Print(c.c_str());
			if (++elapsedTicks >= ticksTotal)
			{
				hasExpired = true;
				//std::string d("4: elapsedTicks = " + std::to_string(elapsedTicks) + "; ticksTotal = " + std::to_string(ticksTotal));
				//Print(d.c_str());
				Expire(results);
			}
		}
		return hasExpired;
	}

	void ProportionalPoison::TickEffect(ProgressUnitResults* results)
	{
		int unit_id = owner->unit_id;
		if (~owner->flags & UnitStatus::Completed || owner->hitpoints <= 0)
			return;
		int damage = hpRatioDmg * owner->GetMaxHitPoints();
		damage += std::min(damage, owner->GetShields()); // increase the damage so that the damage is doubled against shields.
		//std::string s(std::to_string(damage));
		//Print(s.c_str());
		damage <<= 8;
		results->weapon_damages.emplace_back(attacker, attacker->player, owner, damage, weaponId, 0);
	}

	ProportionalPoison::ProportionalPoison(Unit* p_owner, uint8_t p_ticksTotal, uint8_t p_tickPeriod, double p_hpRatioDmg, Unit* p_attacker) : Timer(p_owner, p_ticksTotal, p_tickPeriod), hpRatioDmg(p_hpRatioDmg), attacker(p_attacker)
	{
		//std::string t("curTick = " + std::to_string(curTick));
		//Print(t.c_str());
		//std::string y("elapsedTicks = " + std::to_string(elapsedTicks));
		//Print(y.c_str());
		//std::string a("p_ticksTotal = " + std::to_string(p_ticksTotal) + "; ticksTotal = " + std::to_string(ticksTotal));
		//Print(a.c_str());
		//std::string b("p_tickPeriod = " + std::to_string(p_tickPeriod) + "; tickPeriod = " + std::to_string(tickPeriod));
		//Print(b.c_str());
	}

	UnitTimerManager::~UnitTimerManager()
	{
		for (auto &i : timers) {
			delete i;
		}
	}

	void UnitTimerManager::UpdateTimers(ProgressUnitResults* results)
	{
		if (timers.empty())
			return;
		// iterate and update
		for (int i = 0; i != timers.size(); i++)
		{
			if (timers.at(i)->Update(results)) { // the timer has expired
				timersToDelete.push_back(i);
			}
		}
		// clean up expired timers
		if (int numExpired = timersToDelete.size())
		{
			for (int j = 0; j != numExpired; j++)
			{
				delete timers.at(j);
				timers.erase(timers.begin() + timersToDelete.at(j));
			}
			timersToDelete.clear();
		}
	}

	void UnitTimerManager::AddTimer(Timer* t)
	{
		timers.push_back(t);
		//timers.emplace_back(t);
	}

}
