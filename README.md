## 🛠️ Experiment Game Engine

Sebuah game engine modular yang sedang dalam pengembangan, fokus pada keterpisahan subsistem, kemudahan debugging, dan fleksibilitas jangka panjang.  
📦 Siap diperluas ke **Android** dan **Linux**.

---

# 🧠 Prinsip Arsitektur Game Engine: Non-Opiniatif & Modular

Engine ini dirancang dengan filosofi **non-opiniatif secara logika**, yaitu engine tidak memaksakan aturan atau keputusan logika tertentu kepada game yang menggunakannya. Semua keputusan terkait interaksi input, UI, audio, atau visual berada di ranah **game logic**, bukan di core engine.

---

## 🎯 Tujuan Desain

- 🔧 Memisahkan **mekanisme** (engine) dari **keputusan** (gameplay/UI)
- 🧱 Menyediakan sistem yang **modular, eksplisit, dan fleksibel**
- ⚖️ Memungkinkan game dari berbagai genre menggunakan engine ini tanpa batasan struktural

---

## 🧩 Prinsip Inti

### 1. Engine Tidak Opiniatif
- Engine **tidak mengambil keputusan logika gameplay maupun UI**
- Input tetap dikirim ke semua subsystem (UI, gameplay, dsb)
- Tidak ada auto-block input, auto-pause, atau auto-handle event oleh engine
- Contoh: *engine tidak otomatis menghentikan gameplay saat menu dibuka*

### 2. Semua Aliran Data Bersifat Terbuka
- `InputManager`, `RenderManager`, `AudioSystem`, dan `UISystem` hanya bekerja **berdasarkan data yang diberikan**
- Tidak menyimpan instance logic, hanya melakukan **proses terhadap data mentah**
- Game logic bertanggung jawab mengatur instance dan keputusan runtime

### 3. UI dan Sistem Lain Bersifat Pasif
- UI hanya melakukan `Scan` dan `HandleInput` **jika ada instance yang aktif**
- UI tidak memblokir sistem lain — hanya bereaksi terhadap input
- Sistem visual dan audio juga mengikuti prinsip ini: hanya bekerja berdasarkan data instance yang dikirim

---

## 🔁 Contoh Alur Per Frame

```cpp
inputManager->PollDevices();
inputManager->UpdateBufferAndState();

if (gameLogic->HasActiveUI()) {
    uiSystem->ScanUI(gameLogic->GetUIInstances());
    uiSystem->HandleInput(inputManager->GetInputBuffer());
}

gameLogic->Update(inputManager->GetInputState(), inputManager->GetInputBuffer());

renderManager->Render(gameLogic->GetVisualInstances());
```

---

## 🧩 Arsitektur UI (Progress Terkini)

Sedang membangun sistem UI modular berbasis event dan pointer abstraction. Struktur arsitekturnya dirancang sebagai berikut:

    UICoreSystem
    ├── UIPointerManager (mengelola gesture, klik, hold, swipe)
    ├── UIEventDispatcher (mendistribusi event: onClick, onHover, onDrag)
    ├── UIFocusManager (melacak elemen yang sedang difokuskan atau diseret)
    ├── UIDrawSystem (menggambar rect, teks, dan widget modular)
    └── UILayoutEngine? (opsional: auto layout seperti flex/grid)

### 🤔 Pertimbangan Desain

- Interface `IInputDevice` saat ini belum cukup generik untuk mewakili semua jenis input (mouse, touch, gamepad).
- Hal ini membuat beberapa bagian, terutama `UIPointerManager`, terlalu sering bergantung langsung pada class konkret (`MouseInputDevice`, dll).
- Masih dalam evaluasi apakah `IInputDevice` sebaiknya:
  - Dipertahankan hanya sebagai interface untuk update generik (`update()`, `getType()`), atau
  - Dihapus dan diganti dengan sistem manajemen input yang lebih kontekstual.

---

## 🛤️ Roadmap Pengembangan Selanjutnya

### 🔳 GUI System *(disesuaikan)*
- Sistem terpusat `UICoreSystem`
- Abstraksi pointer dari mouse, touch, gamepad (`UIPointerManager`)
- Event UI modular: klik, hover, fokus
- Komponen UI (widget) seperti tombol, panel, slider

### 🎮 Gamepad Support
- Backend: Raw Input, DirectInput, XInput
- Dukungan controller non-standar & remapping

### 🎨 Renderer Abstraction
- Backend berbasis OpenGL
- Fitur: batching, layering, atlas system

### 🧠 Entity Component System (ECS)
- Arsitektur data-driven
- Komponen dasar: transform, renderable, physics, dll.

### 🎧 Audio System
- Interface `IAudio` dan backend `OpenAL`
- Spatial audio, preset ruangan, efek 3D

### 🗃️ Resource & Asset Manager
- Loader modular: texture, font, model
- Caching dinamis & preload resource

### 🧰 Tools & Editor Mode
- Mode editor in-engine: GUI hierarki, properties, dan drag-drop
- Mode runtime: Client, Server (headless), Editor

---

## 📝 Prinsip Desain

- Fokus pada prinsip:
  - **SOLID**
  - **DRY** *(Don't Repeat Yourself)*
- Desain modular, subsistem terpisah
- Minim inheritance dan dependency besar
- Kompatibel dengan **Visual Studio 2010**

---

## 📦 Dependency: OpenAL SDK

1. Unduh OpenAL SDK: [https://openal-soft.org/](https://openal-soft.org/)
2. Konfigurasikan proyek:
   - Tambahkan `include/` ke compiler
   - Tambahkan `libs/Win32/OpenAL32.lib` ke linker input
   - Salin `OpenAL32.dll` ke direktori `.exe`

---

> 📁 Dokumentasi teknis, diagram arsitektur, dan update roadmap tersedia di folder `docs/` *(akan ditambahkan di masa depan)*
