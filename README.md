# soal-shift-sisop-modul-2-E05-2021

## Anggota Kelompok  
1. Nur hidayati 05111940000028
2. Adrian 05111940000130
3. Ahmad Aunul 05111940000164

### Soal no 1

### Soal no 2
Loba bekerja di sebuah petshop terkenal, suatu saat dia mendapatkan zip yang berisi banyak sekali foto peliharaan dan Ia diperintahkan untuk mengkategorikan foto-foto peliharaan tersebut. Loba merasa kesusahan melakukan pekerjaanya secara manual, apalagi ada kemungkinan ia akan diperintahkan untuk melakukan hal yang sama. Kamu adalah teman baik Loba dan Ia meminta bantuanmu untuk membantu pekerjaannya.

**(a)** Pertama-tama program perlu mengextract zip yang diberikan ke dalam folder “/home/[user]/modul2/petshop”. Karena bos Loba teledor, dalam zip tersebut bisa berisi folder-folder yang tidak penting, maka program harus bisa membedakan file dan folder sehingga dapat memproses file yang seharusnya dikerjakan dan menghapus folder-folder yang tidak dibutuhkan.

### Penjelasan 2a  
Pertama, kita perlu membuat folder nya terlebih dahulu dengan kode dibawah ini :
```
char *argv[] = {"mkdir", "-p", "/home/adr01/modul2/petshop", NULL};
execv("/bin/mkdir", argv);
```  
Kemudian, kita melakukan unzip pets.zip dari direktori tempat kita menyimpan file nya menuju direktori yang telah kita buat sebelumnya   
```
while ((wait(&status)) > 0);
char *argv2[] = {"unzip", "/home/adr01/Documents/SesiLab2/Soal Praktikum/pets.zip", "-d","/home/adr01/modul2/petshop/",NULL};
execv("/usr/bin/unzip", argv2);
exit(0);
```
Kemudian, untuk menghapus folder pada hasil file unzip, pertama kita perlu memindahkan lokasi kita ke direktorinya terlebih dahulu ```chdir("/home/adr01/modul2/petshop/");```  
Kita cek terlebih dahulu apakah isi direktori nya kosong atau tidak ```if (dp != NULL) ```  
Kemudian kita membaca satu per satu isi dari foldernya dan jika tipenya adalah folder maka kita akan membuat child baru untuk remove folder tersebut
```
while ((ep = readdir (dp))) {
    if(ep->d_type == DT_DIR && strcmp(ep->d_name, ".") != 0 && strcmp(ep->d_name, "..") != 0) {
      child_id3 = fork();
      if (child_id3==0){
        chdir("/home/adr01/modul2/petshop/");
        char *argv[] = {"rm", "-R",ep->d_name, NULL};
      execv("/bin/rm", argv);
      }
    }
}
```


**(b)** Foto peliharaan perlu dikategorikan sesuai jenis peliharaan, maka kamu harus membuat folder untuk setiap jenis peliharaan yang ada dalam zip. Karena kamu tidak mungkin memeriksa satu-persatu, maka program harus membuatkan folder-folder yang dibutuhkan sesuai dengan isi zip.
Contoh: Jenis peliharaan kucing akan disimpan dalam “/petshop/cat”, jenis peliharaan kura-kura akan disimpan dalam “/petshop/turtle”.

### Penjelasan 2b
Pertama, kita baca satu per satu  isi folder nya seperti soal 2a
```
if (dp != NULL) {
    while ((ep = readdir (dp))) {
        if(ep->d_type != DT_DIR && strcmp(ep->d_name, ".") != 0 && strcmp(ep->d_name, "..") != 0){
```
Untuk mendapat jenis dari hewan, kita menggunakan fungsi strtok yang berarti kita mengambil suatu kata hingga delimiter yang kita tentukan dimana di soal menggunakan ; dengan kode berikut ```token = strtok(ep->d_name, a);```  
Untuk jenis pertama, maka kita akan langsung memasukkan ke dalam array 
```
if(itrpendek==-1) {
  itrpendek++;
  strcpy(pendek[itrpendek], token);
}
```
Tetapi jika sudah terdapat item dalam array maka kita akan mengecek apakah sudah ada jenis tersebut dalam array, jika sudah ada maka kita abaikan sedangkan jika belum ada maka kita langsung tambahkan jenis hewan ke dalam array
```
else {
      for(i=0; i<=itrpendek; i++) {
        if(strcmp(token, pendek[i]) == 0) flag = 1;
      }
						
      if(flag == 0) {
        itrpendek++;
        strcpy(pendek[itrpendek], token);
      }    
      flag = 0;	
}
```
Kemudian, kita melakukan iterasi dari array dan kita fork child untuk membuat direktorinya 
```
for(flag=0; flag<=itrpendek; flag++){
    child_id4 = fork();
    if (child_id4 == 0) {
      char name[100];
      strcpy(name, "/home/adr01/modul2/petshop/");
      strcat(name,pendek[flag]);
            char *argv[] = {"mkdir", "-p", name, NULL};
      execv("/bin/mkdir", argv);
    }
}
```


**(c)** Setelah folder kategori berhasil dibuat, programmu akan memindahkan foto ke folder dengan kategori yang sesuai dan di rename dengan nama peliharaan.
Contoh: “/petshop/cat/joni.jpg”.  
**(d)** Karena dalam satu foto bisa terdapat lebih dari satu peliharaan maka foto harus di pindah ke masing-masing kategori yang sesuai. Contoh: foto dengan nama “dog;baro;1_cat;joni;2.jpg” dipindah ke folder “/petshop/cat/joni.jpg” dan “/petshop/dog/baro.jpg”.  
**(e)** Di setiap folder buatlah sebuah file "keterangan.txt" yang berisi nama dan umur semua peliharaan dalam folder tersebut. Format harus sesuai contoh.   
```
nama : joni
umur  : 3 tahun

nama : miko
umur  : 2 tahun
```

### Penjelasan 2c, 2d, dan 2e  
Pertama, kita baca satu per satu isi folder nya seperti soal 2a dan 2b dan kita akan mencari yang tipe nya bukan folder / direktori
```
if (dp != NULL) {
    while ((wait(&status4)) > 0);
      while ((ep = readdir (dp))) {
        if(ep->d_type != DT_DIR && strcmp(ep->d_name, ".") != 0 && strcmp(ep->d_name, "..") != 0){
```
Kemudian kita menyalin nama dari file ke dalam string dengan syntax ```strcpy(panjang, ep->d_name);```  
Selanjutnya, kita akan memanggil fungsi hewan untuk mencari jenis hewan, nama untuk mencari nama hewan ,dan umur untuk mencari umur dari hewan. Kita memasukkan parameter 0 pada fungsi hewan karena pembacaan file mulai dari index ke-0.
```
strcpy(panjang, ep->d_name);
int animaltype = hewan(0);
int animalname = nama(animaltype);
int animalage = umur(animalname);
```

Berikut ini adalah fungsi hewan yang menerima parameter index untuk posisi awal karakter dalam membaca jenis hewan. ```strcpy(jenishewan,"");``` untuk mengosongkan nilai dari hewan. Kemudian kita akan masuk ke dalam perulangan untuk menyalin karakter dari string nama file ke dalam array jenis hewan. Jika sudah menemui ; maka kita sudah mendapatkan jenis hewan dan fungsi akan mengembalikan index untuk parameter fungsi umur. 
```
int hewan(int mulai){
	int b; 
	int countc = -1;
	strcpy(jenishewan,"");
	for(b=mulai; b<strlen(panjang); b++){
		if(panjang[b]==';') {
			countc++;
			jenishewan[b]='\0';
			b +=1;
			return b;
		}
		else{
			countc++;
			jenishewan[countc] = panjang[b];
		} 
	}
}
```  
Berikut ini adalah fungsi nama yang menerima parameter index untuk posisi awal karakter dalam membaca nama hewan. ```strcpy(namahewan,"");``` untuk mengosongkan nilai dari namahewan. Kemudian kita akan masuk ke dalam perulangan untuk menyalin karakter dari string nama file ke dalam array nama hewan. Jika sudah menemui ; maka kita sudah mendapatkan nama hewan dan fungsi akan mengembalikan index untuk parameter fungsi nama. 
```
int nama(int mulai){
	int count=-1;
	int c;
	strcpy(namahewan,"");
	for(c=mulai; c<strlen(panjang); c++){
		if(panjang[c]==';'){
			count++;
			namahewan[count]='\0';
			c +=1;
			return c;
		}
		else{
			count++;
			namahewan[count] = panjang[c];
		}
	}
}
```
Berikut ini adalah fungsi umur yang mempunyai cara kerja hampir sama dengan fungsi hewan dan nama di atas. Perbedaannya hanya di bagian perulangan yang akan dihentikan jika menemukan simbol _ karena terdapat beberapa file yang terdiri dari 2 jenis hewan dan dipisahkan oleh simbol _. Serta perulangan hanya sampai ```d<strlen(panjang)-4``` karena .jpg tidak akan dibaca. Fungsi ini akan mengembalikan index akhir dari pembacaan string yang digunakan untuk parameter fungsi changename. 
```  
int umur(int mulai){
	int counta=-1;
	int is_= 1;
	int d;
	strcpy(umurhewan,"");

	for(d=mulai; d<strlen(panjang)-4; d++){
		if(panjang[d] == '_'){
			break;
		}
		else{
			counta++;
			umurhewan[counta] = panjang[d];
		}
	}

	counta++;
	umurhewan[counta]='\0';
	d+=1;
	return d;
}
```
Terakhir, kita akan memanggil fungsi changename untuk memindahkan file tersebut ke dalam folder nama hewan yang sesuai.   
```
char *argv[] = {"mv", namafile, namafolder, NULL};
execv("/bin/mv", argv);
```
Di sini akan masuk kondisional, jika karakter yang dibaca berupa _ maka pada akhirnya akan ditambahkan code untuk mulai membaca lagi string hewan dari awal karena terdapat hewan kedua setelah _. 
```
while ((wait(&status7)) > 0);
mulai +=1;

int hewan_ = hewan(mulai);
int nama_ = nama(hewan_);
int umur_ = umur(nama_);
changename(umur_-1);
```
Terakhir, terdapat fungsi untuk menuliskan ke dalam file keterangan.txt menurut format yang ada
```
fp = fopen(keterangan, "a+");
fprintf(fp, "nama : %s\numur : %s\n\n",namahewan, umurhewan);
fclose(fp);
 ```
### Soal no 3
