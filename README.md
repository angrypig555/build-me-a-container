![](https://hackatime-badge.hackclub.com/U09U824EK3P/build-me-a-container)
# 🐳 build-me-a-container

> [!IMPORTANT]
> Docker or podman is required to build the image that is generated.

build-me-a-container is a dockerfile and docker compose file generator for linux.

## 🎯️ Features
- Docker compose file generation with an interactive prompt
- Dockerfile generation with an interactive prompt

## 💿️ How to install
There are precompiled `.deb` and `.rpm` packages.

## 🔧️ How to build
To build, you can run the `build.sh` file.
Dependencies are: `cmake, g++`
Optional dependencies are: `pandoc` for generating man pages.
Built and tested on fedora linux.

## 📖️ How to use
There are 3 arguments
- --dockerfile - Generate a dockerfile (default if no arguments are given)
- --compose - Generate a compose file
- --help - Display the help menu
The dockerfile/compose file will be generated where this program is run, so it is advised that you run it inside a seperate folder.
You also need either docker or podman to run the generated file.


**For more information, see the `docs/build-me-a-container.1.md`**