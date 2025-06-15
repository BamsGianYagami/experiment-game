- Siap diperluas ke Android & Linux

---

## 🛤️ Roadmap Pengembangan Selanjutnya

### 🔲 GUI System
- Interface `IGUI` & `IRendererGUI`
- Widget modular: tombol, panel, dsb.
- Interaksi melalui mouse & keyboard

### 🎮 Gamepad Support
- Backend untuk Raw Input, DirectInput, dan XInput
- Support untuk controller non-standar

### 🎨 Renderer Abstraction
- Backend berbasis OpenGL
- Dukungan batching, layering, dan atlas atlas

### 🧠 Entity Component System (ECS)
- Arsitektur data-driven
- Komponen: transform, renderable, physics, dll.

### 🎧 Audio System
- Interface `IAudio` dan backend `OpenAL`
- Spatial audio & efek ruangan

### 🗃️ Resource & Asset Manager
- Loader modular: texture, font, model
- Sistem cache & preload dinamis

### 🧩 Tools & Editor Mode
- Mode editor dengan GUI, hierarki objek
- Mode runtime: client, server (headless), editor

---

## 📝 Catatan Tambahan

- Fokus pada prinsip desain software:
- **SOLID**
- **DRY** (Don't Repeat Yourself)
- Keterpisahan antar subsistem
- Kemudahan debugging & eksperimen jangka panjang

- Tidak bergantung pada library besar
- Dikembangkan menggunakan **Visual Studio 2010** untuk kompatibilitas maksimal

---

## 📦 Dependency: OpenAL SDK

Untuk menjalankan proyek ini:

1. Unduh OpenAL SDK dari: https://openal-soft.org/
2. Tambahkan:
 - `include/` ke path include compiler
 - `libs/Win32/OpenAL32.lib` ke linker input
 - `OpenAL32.dll` ke direktori runtime (satu folder dengan `.exe`)

---

> Untuk dokumentasi teknis, diagram arsitektur, dan pembaruan roadmap, silakan lihat folder `docs/` (jika tersedia di masa depan).
