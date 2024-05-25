#include "Window/AppWindow.h"

#include <stdio.h>
#include "Window/WindowElements/Label.h"

#include "Cpu/Memory.h"
#include "Cpu/Cpu.h"
#include "Doom/DoomGame.h"
#include "Window/Terminal/Terminal.h"


int main(int argc, char** argv)
{
	Memory mem;
	mem.SetupTest();
	CPU cpu;
	cpu.Reset(mem);
	cpu.Fetch(mem);
	cpu.Fetch(mem);

	std::string s = cpu.ToString();

	printf("%s\n", cpu.ToString().c_str());

	AppWindow window;

	int w = 640 * 2;
	int h = 400 * 2;

	window.CreateAppWindow(NULL, &w, &h);
	window.ShowAppWindow(10);

	Keyboard& kb = window.GetKeyboard();

	std::wstring terminal = L"";

	auto& gfx = window.GetGraphics();

	/*Label* l = new Label(0, 0, w, h);
	l->SetColor(0xFFFFFF, &gfx);*/

	//window.AddWindowElement(l);

	Terminal t(&window, &gfx, 0, 0, w, h);
	t.SetColor(0xFFFFFF, &gfx);

	window.AddWindowElement(&t);

	t.AddCommand(L"/test", [&]() {
		t.Print(L"Test");
		});

	DoomGame* inst = nullptr;

	bool playDoom = false;

	while (!window.IsClosed()) 
	{
		window.PeekMsg();

		while (auto cd = kb.GetEvent())
		{
			if (cd == std::nullopt)
				continue;

			if(cd.value().GetType() == KeyEvent::Type::Pressed)
				t.HandleKeyCode(cd.value().GetCode());
		}

		while (auto ch = kb.GetCharacters())
		{
			if (ch == std::nullopt)
				continue;

			t.HandleChar(ch.value());

			//if (ch == VK_BACK) //'\b'
			//{
			//	if (terminal.size() > 0 && !playDoom)
			//		terminal.pop_back();
			//}
			//else if (ch == '+')
			//{
			//	playDoom = !playDoom;
			//	if (playDoom)
			//	{
			//		if (!inst)
			//		{
			//			inst = DoomGame::CreateInstance(w, h, &window, &gfx, argv, argc);
			//			inst->Run();
			//		}
			//		window.DisableGraphics();
			//	}
			//	else
			//		window.EnableGraphics();
			//}
			//else
			//{
			//	if(!playDoom)
			//		terminal += ch.value();
			//}
		}

		/*if(!playDoom)
			l->SetText(terminal);
		else
			DoomGame::GetInstance()->Tick();*/
		
	}
}