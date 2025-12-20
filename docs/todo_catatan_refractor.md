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
