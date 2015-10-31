/*
Bunny 2015-09-18
*/

#ifndef CUSTOM_TIMERS_H
#define CUSTOM_TIMERS_H
#pragma once

#include <stdint.h>
#include <vector>

#include "types.h"
#include "bullet.h"

struct ProgressUnitResults;

namespace CustomTimers {

	/* A tick-based timer for units.
	*/
	class Timer {

		//friend class UnitTimerManager;

	protected:

		/* OVERRIDE
		Special effects associated with the expiration of the timer.
		@NOTES
		Excludes and does not require any sort of timer management.
		*/
		virtual void Expire(ProgressUnitResults* results);

		/* OVERRIDE
		Special effects associated with each tick of the timer.
		@NOTES
		Excludes and does not require any sort of timer management.
		*/
		virtual void TickEffect(ProgressUnitResults* results);

		uint8_t curTick; // track frames since start/last tick
		uint8_t elapsedTicks; // when elapsedTicks == ticksTotal, the timer expires

		Unit* owner; // unit which "owns" this timer
		uint8_t ticksTotal; // number of ticks before timer expires
		uint8_t tickPeriod; // number of frames between ticks

	public:

		/* Timer constructor.
		*/
		Timer(Unit* p_owner, uint8_t p_ticksTotal, uint8_t p_tickPeriod);

		/* Updates the timer and performs any effects associated with it.
		@RETURN
		true : when the timer has expired.
		false : otherwise
		*/
		bool Update(ProgressUnitResults* results);

	};

	/* ProportionalPoison is intended to deal a proportion of the afflicted unit's max HP per tick.
	*/
	class ProportionalPoison : public Timer {

	protected:

		double hpRatioDmg; // coefficient of hp so as to deal damage
		Unit *attacker;
		const int weaponId = Weapon::STAPhotonCannon; // weapon ID to derive certain properties (like Size-Damage type)

		virtual void TickEffect(ProgressUnitResults* results); // OVERRIIDE

	public:

		ProportionalPoison(Unit* p_owner, uint8_t p_ticksTotal, uint8_t p_tickPeriod, double p_hpRatioDmg, Unit* p_attacker);

	};

	/* UnitTimerManager is used by Unit to keep track of any form of custom unit timer for each individual unit.
	@NOTES
	We can probably make this more efficient through the use of hash maps instead of vectors.
	Even better would be a global scope UTM implemented as a hash map of unit to timer.
	*/
	class UnitTimerManager {

		std::vector<Timer*> timers;
		std::vector<int> timersToDelete;

	public:

		~UnitTimerManager();

		/* Automagically updates and cleans up any timers under this Manager's responsiibility.
		*/
		void UpdateTimers(ProgressUnitResults* results);

		/* Adds a Timer.
		*/
		void AddTimer(Timer* t);

	};

}

#endif