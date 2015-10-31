#include "upgrade.h"
#include "offsets.h"
#include "strings.h"
#include "unit.h"

const char *GetUpgradeName(int upgrade)
{
    Assert(upgrade >= 0 && upgrade < Upgrade::None);
    return (*bw::stat_txt_tbl)->GetTblString(upgrades_dat_label[upgrade]);
}

int GetUpgradeLevel(int upgrade, int player)
{
    Assert(upgrade >= 0 && upgrade < Upgrade::None);
    if (upgrade < 0x2e)
        return bw::upgrade_level_sc[player][upgrade];
    else
        return bw::upgrade_level_bw[player][upgrade - 0x2e];
}

void SetUpgradeLevel(int upgrade, int player, int amount)
{
    Assert(upgrade >= 0 && upgrade < Upgrade::None);
    if (upgrade < 0x2e)
        bw::upgrade_level_sc[player][upgrade] = amount;
    else
        bw::upgrade_level_bw[player][upgrade - 0x2e] = amount;
}

int MovementSpeedUpgradeUnit(int upgrade)
{
    switch (upgrade)
    {
        case Upgrade::IonThrusters:
            return Unit::Vulture;
        case Upgrade::LegEnhancements:
            return Unit::Zealot;
        case Upgrade::GraviticThrusters:
            return Unit::Scout;
        case Upgrade::GraviticBoosters:
            return Unit::Observer;
        case Upgrade::GraviticDrive:
            return Unit::Shuttle;
        case Upgrade::MetabolicBoost:
            return Unit::Zergling;
        case Upgrade::PneumatizedCarapace:
            return Unit::Overlord;
        case Upgrade::MuscularAugments:
            return Unit::Hydralisk;
        case Upgrade::AnabolicSynthesis:
            return Unit::Ultralisk;
        default:
            return Unit::None;
    }
}

int AttackSpeedUpgradeUnit(int upgrade)
{
    if (upgrade == Upgrade::AdrenalGlands)
        return Unit::Zergling;
	if (upgrade == Upgrade::BurstLasers) // Pronogo
		return Unit::Marine;
    return Unit::None;
}
