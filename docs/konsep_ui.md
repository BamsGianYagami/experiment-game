# 📖 Riset Konsep Root & Hierarki UI di Game Engine

## 🎯 Latar Belakang
Pada UI tradisional berbasis Win32 (mis. Windows XP, 7), setiap *Window* berdiri sendiri dan di-render langsung tanpa konsep hierarki visual global. Semua logika layout, event handling, dan rendering terjadi per-jendela secara terpisah.

Seiring berkembangnya framework modern (WPF, UWP, WinUI, dan game engines), konsep **Root/Top-Level Container** diperkenalkan sebagai entry point utama ke dalam *tree of UI elements*. Semua elemen UI dalam satu jendela diorganisasi di bawah `Root` agar lebih terstruktur dan mudah dikelola.

---

## 🔍 Apa Itu `Root`?
**Root** adalah elemen induk tertinggi untuk semua elemen UI dalam sebuah jendela.  
Fungsinya:
- Sebagai **entry point traversal** untuk `Update()` dan `Draw()`.
- Tempat **hit-testing & event dispatching** dimulai.
- Menyediakan **koordinat acuan** untuk elemen anak.

---

## ✨ Manfaat dan Keunggulan
Dari sudut pandang pengembangan maupun pengalaman pengguna, konsep `Root` membawa keuntungan:

| Manfaat | Deskripsi |
|---------|------------|
| 💨 Responsif dan Smooth | Perubahan UI lebih efisien, hanya cabang visual tree yang berubah perlu di-*update* dan di-*redraw*. |
| 🧮 Skalabilitas HiDPI | Satu titik pusat untuk menangani scaling UI di layar ber-DPI tinggi. |
| 🎨 Styling dan Theming | Tema dan style bisa diterapkan secara global dari `Root` hingga semua anak. |
| 🧭 Event Dispatching Teratur | Event input (click, drag, key) di-*bubble* dan di-*capture* secara hierarkis. |
| 🧩 Modular dan Reusable | Komponen UI bisa di-*attach/detach* ke node mana pun dalam tree. |
| 🔄 Animasi dan Transisi | Efek transisi di tingkat global (fade seluruh UI, scale container) mudah diimplementasikan. |

---

## 🧠 Dibandingkan Dengan Pendekatan Flat
Pada desain klasik (tanpa `Root`):
- Setiap `Window` di-*update* dan di-*draw* secara manual.
- Tidak ada mekanisme global untuk hit-testing dan event dispatching.
- Perubahan layout harus diatur manual per komponen.

Dengan `Root` dan *tree structure*:
- `UIManager` cukup memanggil `Root->Update()` dan `Root->Draw()`.
- Perubahan layout dan event dispatching berlangsung otomatis dan hierarkis.
- Memudahkan pengelompokan elemen UI untuk kebutuhan seperti tab, panel, dan overlay.

---

## 🎮 Relevansi untuk Game Engine
Dalam game engine:
- Kita bisa membuat **UI scene graph**: `Root → Window → Panel → Button`.
- Input (mouse/keyboard/gamepad) dikirim ke `Root`, lalu di-propagasi ke anak.
- Memungkinkan desain UI lebih modular, scalable, dan mudah di-maintain.
- Cocok untuk membuat fitur seperti HUD, Main Menu, Inventory Panel, dan Debug Overlay.

---

## 📝 Kesimpulan
Penggunaan `Root` dalam arsitektur UI game engine memberikan:
- Struktur data lebih jelas dan rapi.
- Kemudahan event handling.
- Dukungan untuk fitur-fitur modern (scaling, theming, animasi global).
- Persiapan untuk multiplatform dan adaptasi tampilan di perangkat berbeda.

Pada akhirnya, konsep `Root` bukanlah kewajiban teknis, melainkan **best practice** untuk mengorganisasi UI agar lebih mudah dikembangkan dan diperluas di masa depan.

---

> **Selanjutnya:**  
> Kita bisa merancang struktur data `UIElement`, `UIRoot`, `UIManager`, dan contoh event dispatching sesuai kebutuhan engine.
