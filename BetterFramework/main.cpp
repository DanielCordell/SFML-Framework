#include "Engine.h"
#include <imgui-SFML.h>
#include <imgui.h>


int main()
{
	bf::Engine engine(1280, 720, "Test");
	engine.Start();

	return 0;
}
