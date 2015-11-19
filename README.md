# Teippi
Bw modhack thingy which removes several limits from the game and makes it run faster

# _PronogoMod
This plugin has been given additional and altered functionality from the original Teippi in order to provide support for features as required by the client Pronogo.
These changes have been developed by Sand Wraith from staredit.net.
Most changes have been noted by comment terms "Bunny" and "Pronogo".

# Building
Python 3 is required to run the build script, and either gcc 4.9.2, clang 3.5 or visual studio 2015 is required to compile the code.

Run `py -3 waf configure` followed by `py -3 waf` to build the plugin. The resulting file will be in build\teippi.qdp, which can be renamed to teippi.bwl to use it in Chaoslauncher.
If the automatic compiler detection is selecting a compiler you do not want, add `--check-cxx-compiler=<compiler>` to the configure command, where `<compiler>` can be `msvc`, `g++`, or `clang++`.

There is a visual studio project available which wraps around the build script.
You will have to run the configuration command before the project can build, though.

For compile options, see `py -3 waf --help`
