// Experiment game.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GameEngine.h"


/*NOTES:
Klik kanan project → Properties.
Masuk ke Linker → System.
Pada Subsystem, pilih:
Console (/SUBSYSTEM:CONSOLE) → untuk main.
Windows (/SUBSYSTEM:WINDOWS) → untuk WinMain.
*/

//entry point Windows CLI
int _tmain(int argc, _TCHAR* argv[])
{
	GameEngine engine;

    engine.init();

    for (int i = 0; i < 50000; ++i) { // simulasi 5 puluh ribu frame
		//std::cout << "==frame ke " << i+1 << "===" << std::endl;
        engine.update();
		//std::cout << "=======" << std::endl << std::endl;
    }

    engine.shutdown();

    return 0;
}

//entry point Windows GUI
/*
int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	GameEngine engine;

    engine.init(hInstance);

    for (int i = 0; i < 50000; ++i) { // simulasi 5 puluh ribu frame
		std::cout << "==frame ke " << i+1 << "===" << std::endl;
        engine.update();
		std::cout << "=======" << std::endl << std::endl;
    }

    engine.shutdown();

    return 0;
}
*/