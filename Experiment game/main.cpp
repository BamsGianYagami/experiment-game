// Experiment game.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GameEngine.h"


/**
 * NOTES:
 * Klik kanan project → Properties.
 * Masuk ke Linker → System.
 * Pada Subsystem, pilih:
 * Console (/SUBSYSTEM:CONSOLE) → untuk main.
 * Windows (/SUBSYSTEM:WINDOWS) → untuk WinMain.
 */

/**
 * @file main.cpp
 * @brief Titik masuk utama (Entry Point) untuk aplikasi Windows CLI
 */
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

/**
 * @file main.cpp
 * @brief Titik masuk utama (Entry Point) untuk aplikasi Windows GUI.
 *
 * File ini berisi entry point utama aplikasi Windows dengan subsystem GUI.
 * Walaupun terlihat sederhana, fungsi entry point Windows menyimpan banyak
 * artefak sejarah dan keputusan desain yang berasal dari era awal Windows.
 *
 * 1. **hPrevInstance**
 *
 *    Parameter `hPrevInstance` merupakan peninggalan langsung dari Windows 16-bit
 *    (seperti Windows 3.1). Pada masa itu, Windows memungkinkan beberapa instance
 *    aplikasi yang sama untuk berbagi resource demi menghemat RAM yang sangat
 *    terbatas. Sejak Windows beralih ke arsitektur 32-bit dengan address space
 *    terisolasi, parameter ini kehilangan relevansinya dan di Windows modern
 *    (32-bit maupun 64-bit) selalu bernilai NULL. Keberadaannya dipertahankan
 *    semata-mata demi kompatibilitas historis.
 *
 * 2. **_tWinMain**
 *
 *    Fungsi `_tWinMain` menggunakan awalan `_t` sebagai bagian dari sistem makro
 *    `TCHAR`. Pendekatan ini memungkinkan satu basis kode yang sama dikompilasi
 *    baik dalam mode ANSI maupun Unicode. Jika Unicode diaktifkan, fungsi ini
 *    dipetakan menjadi `wWinMain`, sedangkan pada mode ANSI menjadi `WinMain`.
 *    Mekanisme ini berasal dari masa transisi Windows 95 (ANSI) ke Windows NT
 *    (Unicode), dan meskipun kini jarang dibutuhkan, masih sering dijumpai pada
 *    kode Windows lama.
 *
 * 3. **HINSTANCE**
 *
 *    Tipe `HINSTANCE` bukan sekadar ID numerik, melainkan merepresentasikan base
 *    address di mana file executable (.exe) di-load ke dalam memori virtual
 *    proses. Hal ini dapat diverifikasi dengan memanggil `GetModuleHandle(NULL)`,
 *    yang akan mengembalikan alamat yang sama dengan `hInstance`. Pemahaman ini
 *    penting ketika mengakses resource internal aplikasi seperti icon, dialog,
 *    atau data embedded lainnya.
 *
 * 4. **GUI vs Console**
 *
 *    Meskipun fungsi ini merupakan entry point untuk aplikasi GUI, aplikasi
 *    tetap dapat berinteraksi dengan console. Console dapat dialokasikan secara
 *    eksplisit dengan memanggil `AllocConsole()`, atau dengan mengubah pengaturan
 *    linker subsystem menjadi `/SUBSYSTEM:CONSOLE`. Pendekatan ini sering
 *    digunakan selama proses debugging untuk memanfaatkan output teks seperti
 *    `std::cout` tanpa mengorbankan antarmuka grafis.
 *    @note
 *    👦🏻 Bams: Tapi baiknya lewat main biasa aja deh untuk console, soalnya biar cross-platform.
 *    kalau ini Khusus entry point windows
 */
/*
int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	GameEngine engine;

	//metode seperti ini yang mengambil hInstance dari entry point sudah tidak diperlukan,
	//karena bisa langsung dari GetModuleHandle() ketika di hilight memiliki alamat pointer yang identik sama.
	//engine.init(hInstance);

    engine.init();

    for (int i = 0; i < 50000; ++i) { // simulasi 5 puluh ribu frame
		std::cout << "==frame ke " << i+1 << "===" << std::endl;
        engine.update();
		std::cout << "=======" << std::endl << std::endl;
    }

    engine.shutdown();

    return 0;
}
*/