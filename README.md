# Teippi
Bw modhack thingy which removes several limits from the game and makes it run faster

## Pronogo Mod
This plugin has been given additional and altered functionality from the original Teippi in order to provide support for features as required by the client Pronogo.
These changes have been developed by Sand Wraith from staredit.net, AKA nekoshota. Thanks to Neiv for his insight and help.
Most (I have tried to document all) deviations from the original plugin code have been noted by comment terms "Bunny" and/or "Pronogo".

### Features

- Poison effect is applied by any weapon using the "Unknown (Crash)" explosion effect so long as some conditions are met.
  - This is meant to be used exclusively by the Photon Cannon.
  - Conditions are as follows:
    - Photon Cannons cannot ordinarily attack air
	- Upgrade id 45 must be researched up to level 2 to allow the poison to apply
	- Upgrade id 45 must be researched up to level 3 to allow the Photon Cannon to attack air
  - The poison effect behaves as follows:
    - It lasts 3 ticks, starting one period after the bullet impact
	- Poison has a period of 24 frames between each tick
	- On each tick, 10% of the target's HP is applied as additional damage by the attacker (even if attacker dies)
    - The damage applied by the poison does double damage to shields
	- Weapon id 81 specifies the damage type done by the poison (e.g. Concussive)
- Completed Pylons that subsequently die will cause damage to nearby units according to the weapon stats of weapon 72. Weapon 72 determines of the death explosion:
  - damage amount
  - damage type (e.g. Concussive)
  - inner/middle/outer splash radii
    - Only the outer splash radii is applied (and at 100% power) unless "Splash Radial" is selected as the explosion effect, in which case the regular 100%/50%/25% splash modifier set for inner/middle/outer set applies respectively.
  - This Pylon death effect can be disabled entirely by setting weapon 72's damage to 0.
- Unpowered Protoss buildings are immediately destroyed if owned by a non-neutral faction.
  - De-powering a building that is warping in will also cancel the warp-in without refund to the constructor
- Firebats no longer fire "flames" when attacking from inside a Bunker
- Marines attack at a faster rate if upgrade id 18 is researched
  - Cooldown is reduced by 25% for each point in upgrade 18
  - Cooldown still cannot be below the hard-coded minimum (which has been untouched)
- Marine's attack range upgrade (id 16) transferred to Firebat

# Building
Python 3 is required to run the build script, and either gcc 4.9.2, clang 3.5 or visual studio 2015 is required to compile the code.

Run `py -3 waf configure` followed by `py -3 waf` to build the plugin. The resulting file will be in build\teippi.qdp, which can be renamed to teippi.bwl to use it in Chaoslauncher.
If the automatic compiler detection is selecting a compiler you do not want, add `--check-cxx-compiler=<compiler>` to the configure command, where `<compiler>` can be `msvc`, `g++`, or `clang++`.

There is a visual studio project available which wraps around the build script.
You will have to run the configuration command before the project can build, though.

For compile options, see `py -3 waf --help`
