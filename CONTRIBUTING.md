# Melakukan Kontribusi

## [Kode Etik](CODE-OF-CONDUCT.md)

Kami memiliki kode etik yang **wajib** dipatuhi oleh semua partisipan atau kontributor. Klik [disini](CODE-OF-CONDUCT.md) sebelum melakukan kontribusi terhadap projek ini.

## Cara Berkontribusi

- Melalui issue
- Melalui pull request

### Cara Melakukan _Pull Request_

Projek ini memiliki 1 _branch_ utama, yaitu `main`. Jika ingin menambah fitur baru, silakan membuat _branch_ baru di _repository_ yang telah di-_fork_. Berikut adalah cara melakukan _pull request_.

1. _Fork_ _repository_ ini ke akun github anda dengan menekan _icon_ `🍴 | Fork`
2. _Clone repository_ yang telah di-_fork_ ke perangkat.
3. Modifikasi file yang terdapat di _folder_ tersebut. Modifikasi _file_ bisa berupa perbaikan bug, penambahan fitur, _code refactor_, dan masih banyak lagi. Sebelum melakukan modifikasi, baca aturan mengenai _style guide_ dalam melakukan modifikasi.
4. Masukkan file yang telah dimodfikasi ke _staging area_ dengan mengetik perintah `git add [nama_file]` (ganti [nama file] dengan . jika memasukkan semua file yang telah dimodifkasi ke _staging area_).
5. Lakukan _commit_ dengan memberikan pesan yang **singkat dan jelas** dengan mengetik perintah `git commit -m ["nama_pesan"]`
6. Kirimkan perubahan tadi ke _remote repository_ dengan mengetik perintah `git push origin main`
7. Kembali ke _repository_ yang telah di-_fork_ ke akun github anda. Akan muncul tulisan `This branch is x commit ahead`, klik tombol _Pull Request_ yang berada di samping tulisan tersebut.
8. Tunggu sampai kode kalian di-_review_ dan di-_merged_ ke _repository_ original.
9. Anda telah berhasil melakukan kontribusi untuk projek ini.

## _Style Guide_

- Kontributor **wajib** menggunakan [Prettier](https://prettier.io/) dalam menuliskan kode.
- Batas maksimum jumlah karakter dalam satu baris adalah **96** karakter

### _Naming Conventions_

- Penamaan _variable_ dan fungsi haruslah singkat dan eksplisit.
- Penamaan struct harus diawali dengan huruf kapital.
- Gunakan _camelCase_ dalam semua penamaan, baik _variable_ maupun fungsi.
- Penulisan _escape sequence_ (seperti `\n`, `\t`, dsb.) harus diawali spasi jika digunakan bersama _string_. (Contoh: `"Terima kasih. \n"`)
