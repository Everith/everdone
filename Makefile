# .PHONY mindig uttatja a feladatot nem ellenörzi a fileokat
.PHONY = engine clean

all: generate

engine: Engine/src/main.cpp
	cmd /c .\Engine\build.bat
app: App/src/main.cpp
	cmd /c .\App\build.bat

generate:
	@echo "Generating GLFW and GLAD"

clean:
	rm -r -fo ./engine/build
	rm -r -fo ./build