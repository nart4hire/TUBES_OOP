# Tugas Besar 1 IF2210 Pemrograman Berorientasi Objek 2021/2022

K03 Kelompok 11

- 13520129 / Nathanael Santoso
- 13520024 / Hilya Fadhilah Imania
- 13520162 / Daffa Romyz Aufa
- 13519210 / Dwi Kalam Amal Tauhid
- 13517129 / Panawar Hasibuan

## Deskripsi Singkat

Program ini adalah tiruan sederhana dari mekanisme inventory dan crafting
pada permainan Minecraft. Daftar item dan resep dari item yang bisa di-craft
dapat dispesifikasikan melalui konfigurasi, yang contohnya terdapat pada
direktori `config`.

## Install dan Run

Program ditulis dalam bahasa C++ standar 2017. Kompilasi dilakukan dengan
`g++` dan `makefile`. Platform yang disupport adalah Linux (bisa dengan WSL).
Untuk mengkompilasi dan menjalankan program dengan config default, jalankan
perintah berikut pada direktori utama:

```
$ make
$ ./main
```

- Program dapat menerima satu buah argumen berupa direktori dimana file config
  berada. Diasumsikan nama file config untuk daftar item adalah `item.txt` dan
  direktori resep adalah `recipe`.
  ```
  $ ./main config
  ```
- Program dapat menerima dua buah argumen berupa path file daftar item dan path
  direktori resep.
  ```
  $ ./main config/item.txt config/recipe
  ```

## Unit Testing

Untuk melakukan unit test, buat file unit test pada direktori `test`.
Kemudian jalankan perintah `make unit-test` dengan variabel `MODULE`
diset sesuai nama modul (nama file pada direktori `test`). Contoh:

```
$ make unit-test MODULE=inventory
```
