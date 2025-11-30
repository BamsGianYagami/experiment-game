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

### 2. Refactor Platform & Surface
Karena `Surface` dan `PlatformLayer` sebenarnya satu kesatuan (window + native handle), maka lakukan:

- satukan `Surface` ke dalam `PlatformLayer`
- pindahkan logic `createSurface` / window handle ke `PlatformLayer`
- renderer mengambil native handle langsung dari platform  
  `platform->getNativeWindowHandle()`

---

### 3. Bersihkan Cross-Reference
Pastikan dependency tersusun rapi:

- `PlatformLayer` **tidak tahu** apa pun tentang `InputManager`  
  (hanya menyimpan function callback / event hook)
- `InputManager` **tidak tergantung** implementasi platform
- `GameEngine` menjadi penghubung yang bersih  
  (inject callback dari platform ke input manager)
