## to-do

### 1. Cari tahu Best Practice tentang Input
Setelah menghapus file yang deprecated, berikutnya buang method dan proses yang sudah tidak akan dipakai lagi di `InputManager` seperti:
  1. `updateAllDevices`
  2. `RegisterDevice`
  3. `GetDevice`
  4. `GetAsyncState` (jika masih ada — ini menyebabkan input tetap dibaca walau window tidak fokus)

Karena input sekarang menggunakan event listener dari library platform seperti yang telah diimplementasi di Windows.  
Tetapi masih harus riset lagi apakah device lain seperti gamepad masih bisa lewat jalur yang sama, dengan callback seperti keyboard dan mouse.

---

### 2. Arsitektur Subsystem: Platform & Surface (Re-Refactor)

Awalnya direncanakan untuk digabung, namun diputuskan untuk tetap **Dipisahkan** antara `IPlatformLayer` dan `IRenderSurface` dengan alasan:

- **Headless Support:** Memungkinkan engine berjalan tanpa window fisik (misalnya untuk dedicated server atau automated testing).
- **Separation of Concerns:** - `IPlatformLayer` bertanggung jawab atas OS lifecycle, window management, dan input.
    - `IRenderSurface` bertanggung jawab atas abstraksi swapchain, resolusi, dan native handle yang dibutuhkan Renderer.
- **Dependency Flow:** Renderer kini hanya bergantung pada `IRenderSurface`. Jika surface tidak diinisialisasi (null), maka renderer akan masuk ke mode headless.

**Catatan Penting:** Pastikan urutan inisialisasi dilakukan dengan benar: `Platform` -> `Surface` (optional) -> `Renderer`. Jangan memanggil draw command jika `Surface` belum di-attach ke `Platform`.

---

### 3. Bersihkan Cross-Reference
Pastikan dependency tersusun rapi:

- `PlatformLayer` **tidak tahu** apa pun tentang `InputManager`  
  (hanya menyimpan function callback / event hook)
- `InputManager` **tidak tergantung** implementasi platform
- `GameEngine` menjadi penghubung yang bersih  
  (inject callback dari platform ke input manager)

---

### 4. Implementasi Input yang Presisi & Agnostik
Refactor sistem input di level platform (khususnya Win32) untuk menghindari *implicit state* dan meningkatkan transparansi data:

- **Penggunaan Timestamp (GetMessageTime):** Simpan waktu kejadian pesan dari OS menggunakan `unsigned long` (DWORD). Gunakan aritmatika pengurangan langsung untuk mendapatkan durasi/selisih antar input. Mekanisme *two's complement* menjamin hasil tetap akurat meskipun terjadi *overflow/rollover* (setiap 49 hari), selama selisih waktu tidak melebihi ~24 hari.
- **Ekstraksi Data Eksplisit:** Manfaatkan `wParam` untuk identitas tombol. Gunakan `lParam` bit ke-30 untuk membedakan antara "tekanan pertama" (*fresh press*) dan "tekanan berulang" (*auto-repeat*).
- **Agnostic Event System:** Platform layer bertugas sebagai "penerjemah". Data mentah Win32 (`wParam`, `lParam`, `time`) harus dikonversi ke dalam struct `InputEvent` yang netral (hanya berisi enum internal dan tipe data primitif) sebelum dikirim ke `InputManager`.
- **Efisiensi State:** Hindari penggunaan fungsi *query* OS seperti `GetKeyState` secara berulang di dalam message loop untuk mencegah *overhead* pemanggilan API sistem. State keyboard harus dikelola secara mandiri di memori lokal aplikasi.

---

### 5. Etika Resource & Loop Management
Mencegah penggunaan CPU yang berlebihan dan menjamin responsivitas:

- **Message Coalescing Awareness:** Sadari bahwa Windows dapat menggabungkan beberapa pesan input ke dalam satu `lParam` (*repeat count*) jika CPU terlalu sibuk. 
- **Frame Rate Limiting:** Implementasikan mekanisme *capping* (V-Sync atau manual Sleep) agar `PeekMessage` loop tidak memakan 100% penggunaan satu core CPU secara sia-sia.
- **Input Safety (Focus Handling):** Tangani pesan `WM_KILLFOCUS` untuk mereset seluruh state input. Ini krusial untuk mencegah bug "tombol nyangkut" saat user melakukan *Alt-Tab* atau kehilangan fokus window.

---

### 6. Abstraksi Render Resource & Command Streaming
Mengoptimalkan komunikasi antara CPU dan GPU dengan memisahkan penyimpanan data (Static Data) dari instruksi eksekusi (Command):

- **Resource-ID Abstraction (Handle System):** Hindari mengirim data vertex mentah langsung ke dalam `DrawCommand` di setiap frame. Implementasikan sistem **Renderer Resource** di mana data geometri (seperti VAO/VBO pada OpenGL) dimuat sekali ke memori GPU saat inisialisasi. `DrawCommand` cukup membawa **Resource ID** (Handle) sebagai referensi, sehingga beban bandwidth CPU-ke-GPU tetap minimal.
- **State Change Minimization (Command Sorting):** Lakukan pengurutan (*sorting*) pada `std::vector<DrawCommand>` sebelum proses eksekusi di Renderer. Kelompokkan perintah berdasarkan `ShaderID` atau `ResourceID` yang sama. Tujuannya adalah meminimalkan *overhead* pergantian *state* pada API (seperti binding resource), yang merupakan *bottleneck* performa pada driver grafis.
- **Instancing Awareness:** Untuk render objek yang identik dalam jumlah banyak (seperti ratusan kotak UI atau model 3D yang sama), gunakan satu `DrawCommand` yang berisi referensi ke satu Resource, namun membawa array data transformasi (*Instance Data*). Ini memungkinkan penggunaan fungsi *Instanced Drawing* untuk mengurangi jumlah *draw calls*.
- **Agnostic Stream Ordering:** Pastikan `RenderManager` tetap menjaga urutan (*ordering*) yang konsisten sesuai urutan input (FIFO) saat memproses `DrawCommand`. Hal ini sangat krusial untuk menjaga *z-order* pada UIElement dan transparansi objek agar tidak terjadi *flickering* atau salah urutan layering.