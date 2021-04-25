# soal-shift-sisop-modul-2-E05-2021

## Anggota Kelompok  
1. Nur hidayati 05111940000028
2. Adrian 05111940000130
3. Ahmad Aunul 05111940000164

### Soal no 1
Soal ini meminta kami untuk membantu Steven membuat program sebagai berikut:
**(a)** Membuat beberapa folder dengan nama folder-foldernya adalah **Musyik** untuk mp3, **Fylm** untuk mp4, dan **Pyoto** untuk JPG.
**(b)** **Mendownload** folder dari masing-masing link yang telah disediakan.
**(c)** Setiap folder tidak boleh berisikan zip sehingga harus **di-extract** setelah didownload.
**(d)** Kemudian **memindahkan** file dari masing-masing folder yang telah diextract ke dalam folder yang telah dibuat.
**(e)** Semua proses berjalan otomatis 6 jam sebelum 9 April pukul 22.22 WIB.
**(f)** Lalu, pada 9 April pukul 22.22 WIB, semua folder akan **di-zip** dengan nama **Lopyu_Stevany.zip** dan semua folder akan **di-delete** sehingga hanya menyisakan .zip.

Pertama yang harus kita lakukan yaitu membuat kerangka daemon prosesnya terlebih dahulu karena semua program berjalan secara otomatis. Berikut kodenya:
```
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <stdbool.h>
#include <wait.h>
#include <dirent.h>
#include <time.h>

...

int main() 
{
    pid_t pid, sid;    // Variabel untuk menyimpan PID

    pid = fork();     // Menyimpan PID dari Child Process

    /* Keluar saat fork gagal
    * (nilai variabel pid < 0) */
    if (pid < 0) 
    {
        exit(EXIT_FAILURE);
    }

    /* Keluar saat fork berhasil
    * (nilai variabel pid adalah PID dari child process) */
    if (pid > 0) 
    {
        exit(EXIT_SUCCESS);
    }

    umask(0);

    sid = setsid();
    if (sid < 0) 
    {
        exit(EXIT_FAILURE);
    }

    if ((chdir("/home/nur/sisop/Modul2/Praktikum/")) < 0) 
    {
        exit(EXIT_FAILURE);
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    bool done = false;

    while(1)
    {
    
    	...
	
	sleep(1);
    }
}
```

Selanjutnya kita lakukan percabangan pada program utama dengan menggunakan ```if``` agar proses berjalan 6 jam sebelum 9 April pukul 22.22 WIB, yaitu pada 9 April pukul 16.22 WIB. Berikut kodenya:
```
if(t->tm_mday==9 && t->tm_mon+1==4 && t->tm_hour==16 && t->tm_min==22)
{
    pid_t cid1, cid2, cid3;
    int stat1, stat2, stat3;

    cid1 = fork();

    if (cid1 < 0)
    {
	exit(EXIT_FAILURE); // jika gagal membuat proses baru, maka program akan berhenti
    }
    if(cid1 == 0)
    {
	cid2 = fork();

	if(cid2 < 0)
	{
	    exit(EXIT_FAILURE);
	}
	if(cid2 == 0)
	{
	    cid3 = fork();

	    if(cid3 < 0)
	    {
		exit(EXIT_FAILURE);
	    }
	    if(cid3 == 0)
	    {
		//make directory
		char *argv[] = {"mkdir", "-p", "Pyoto", "Musyik", "Fylm", NULL};
		forkExecWait("/bin/mkdir", argv);
		_exit(1);
	    }

	    ...

	}

	...

    }

    ...

}
```

Fungsi ```forkExecWait``` berisi rangkaian perintah ```fork```, ```exec```, dan ```wait``` yang berjalan bersama. Berikut kodenya:
```
void forkExecWait(char *cmd, char *arg[]) 
{
    pid_t child_id;
    int status;

    child_id = fork();

    if (child_id < 0) {
        exit(EXIT_FAILURE); 
    }

    if (child_id == 0) {
        execv(cmd, arg);
    } else {
        while ((wait(&status)) > 0);
        return;
    }
}
```

Setelah folder berhasil dibuat selanjutnya program akan memproses film yang meliputi men-download folder, melakukan unzip, lalu memindahkannya ke folder yang telah dibuat (Fylm). Berikut kodenya:
```
if(t->tm_mday==9 && t->tm_mon+1==4 && t->tm_hour==16 && t->tm_min==22)
{
    pid_t cid1, cid2, cid3;
    int stat1, stat2, stat3;

    cid1 = fork();

    if (cid1 < 0)
    {
	exit(EXIT_FAILURE); // jika gagal membuat proses baru, maka program akan berhenti
    }
    if(cid1 == 0)
    {
	cid2 = fork();

	if(cid2 < 0)
	{
	    exit(EXIT_FAILURE);
	}
	if(cid2 == 0)
	{
	    cid3 = fork();

	    if(cid3 < 0)
	    {
		exit(EXIT_FAILURE);
	    }
	    if(cid3 == 0)
	    {
		//make directory
		...
	    }
	    else 
	    {
		// memproses film
		while ((wait(&stat1)) > 0);
		pid_t child_id1, child_id2;
		int status1, status2;

		child_id1 = fork();

		if (child_id1 < 0)
		{
		    exit(EXIT_FAILURE);
		}
		if (child_id1 == 0)
		{
		    child_id2 = fork();

		    if (child_id2 < 0)
		    {
			exit(EXIT_FAILURE);
		    }
		    if (child_id2 == 0)
		    {
			// download
			char *arg1[] = {"wget", "-q", "--no-check-certificate", "https://drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download", "-O", "Film_for_Stevany.zip", NULL};
			execv("/bin/wget", arg1);
		    }
		    else
		    {
			// unzip
			while ((wait(&status1)) > 0);
			sleep(5);
			char *arg2[] = {"unzip", "-oq", "Film_for_Stevany.zip", NULL};
			execv("/bin/unzip", arg2);
		    }
		}
		else
		{
		    // move
		    while ((wait(&status2)) > 0);
		    moveFiles("FILM", "Fylm");
		}
		_exit(1);
	    }
	}

	...

    }

    ...

}
```

Kode tersebut berisi serangkaian perintah yang pertama adalah mendownload folder film dari link yang telah disediakan, kemudian melakukan unzip folder hasil download. Pad proses ini terdapat ```sleep(5)``` yang berguna untuk men-delay proses unzip dikarenakan harus menunggu proses download selesai terlebih dahulu. Lalu, untuk memindahkan folder hasil unzip ke folder yang telah dibuat menggunakn fungsi ```moveFiles```. Fungsi tersebut memiliki variabel ```basePath``` yang digunakan untuk menyimpan path dari folder hasil extraxct dan variabel ```dest``` yang digunakan untuk menyimpan path dari folder yang telah dibuat sebelumnya. Berikut kodenya:
```
void moveFiles(char *basePath, char *dest)
{
    char path[1000];
    struct dirent *dp;
    DIR *dir = opendir(basePath);

    if (!dir)
        return;

    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {
            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name);

            char *argv[] = {"mv", path, dest, NULL};
            forkExecWait("/bin/mv", argv);
        }
    }
    closedir(dir);
}
```

Setelah proses film selesai dilakukan, selanjutnya program akan memproses musik. Proses yang dilakukan sama dengan proses untuk memproses film yaitu men-download folder musik, melakukan extract terhadap folder yang telah didownload kemudian memindahkannya ke folder yang telah dibuat (Musyik). Berikut kodenya:
```
if(t->tm_mday==9 && t->tm_mon+1==4 && t->tm_hour==16 && t->tm_min==22)
{
    pid_t cid1, cid2, cid3;
    int stat1, stat2, stat3;

    cid1 = fork();

    if (cid1 < 0)
    {
	exit(EXIT_FAILURE); // jika gagal membuat proses baru, maka program akan berhenti
    }
    if(cid1 == 0)
    {
	cid2 = fork();

	if(cid2 < 0)
	{
	    exit(EXIT_FAILURE);
	}
	if(cid2 == 0)
	{
	    cid3 = fork();

	    if(cid3 < 0)
	    {
		exit(EXIT_FAILURE);
	    }
	    if(cid3 == 0)
	    {
		//make directory
		...
	    }
	    else 
	    {
		// memproses film
		...
	    }
	}
	else
	{
	    // memproses musik
	    while ((wait(&stat2)) > 0);
	    pid_t child_id3, child_id4;
	    int status3, status4;

	    child_id3 = fork();

	    if (child_id3 < 0)
	    {
		exit(EXIT_FAILURE);
	    }
	    if (child_id3 == 0)
	    {
		child_id4 = fork();

		if (child_id4 < 0)
		{
		    exit(EXIT_FAILURE);
		}
		if (child_id4 == 0)
		{
		    // download
		    char *arg3[] = {"wget", "-q", "--no-check-certificate", "https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download", "-O", "Musik_for_Stevany.zip", NULL};
		    execv("/bin/wget", arg3);
		}
		else
		{
		    // unzip
		    while ((wait(&status3)) > 0);
		    sleep(5);
		    char *arg4[] = {"unzip", "-oq", "Musik_for_Stevany.zip", NULL};
		    execv("/bin/unzip", arg4);
		}
	    }
	    else
	    {
		// move
		while ((wait(&status4)) > 0);
		moveFiles("MUSIK", "Musyik");
	    }
	    _exit(1);
	}
    }
}
```

Selanjutnya program akan memproses foto. Proses yang dilakukan sama dengan proses untuk memproses film dan musik yaitu men-download folder foto, melakukan extract terhadap folder yang telah didownload kemudian memindahkannya ke folder yang telah dibuat (Pyoto). Berikut kodenya:
```
if(t->tm_mday==9 && t->tm_mon+1==4 && t->tm_hour==16 && t->tm_min==22)
{
    pid_t cid1, cid2, cid3;
    int stat1, stat2, stat3;

    cid1 = fork();

    if (cid1 < 0)
    {
	exit(EXIT_FAILURE); // jika gagal membuat proses baru, maka program akan berhenti
    }
    if(cid1 == 0)
    {
	cid2 = fork();

	if(cid2 < 0)
	{
	    exit(EXIT_FAILURE);
	}
	if(cid2 == 0)
	{
	    cid3 = fork();

	    if(cid3 < 0)
	    {
		exit(EXIT_FAILURE);
	    }
	    if(cid3 == 0)
	    {
		//make directory
		...
	    }
	    else 
	    {
		// memproses film
		...
	    }
	}
	else
	{
	    // memproses musik
	    ...
	}
    }
    else
    {
	// memproses foto
	while ((wait(&stat3)) > 0);
	pid_t child_id5, child_id6;
	int status5, status6;

	child_id5 = fork();

	if (child_id5 < 0)
	{
	    exit(EXIT_FAILURE);
	}
	if (child_id5 == 0)
	{
	    child_id6 = fork();

	    if (child_id6 < 0)
	    {
		exit(EXIT_FAILURE);
	    }
	    if (child_id6 == 0)
	    {
		// download
		char *arg5[] = {"wget", "-q", "--no-check-certificate", "https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download", "-O", "Foto_for_Stevany.zip", NULL};
		execv("/bin/wget", arg5);
	    }
	    else
	    {
		// unzip
		while ((wait(&status5)) > 0);
		sleep(5);
		char *arg6[] = {"unzip", "-oq", "Foto_for_Stevany.zip", NULL};
		execv("/bin/unzip", arg6);
	    }
	}
	else
	{
	    // move
	    while ((wait(&status6)) > 0);
	    moveFiles("FOTO", "Pyoto");
	}  
    }
}
```
	  
Setelah semua proses pada 9 April pukul 16.22 WIB selesai dilakukan, selanjutnya program akan memproses hasilnya pada 9 April pukul 22.22 WIB. Proses tersebut meliputi melakukan zip terhadap folder Pyoto, Musyik, dan Fylm. Kemudian akan menghapus folder kosong (folder hasil extract yang isinya telah di pindahkan ke folder yang dibuat). Berikut kodenya:
```
int main() 
{
    pid_t pid, sid;    // Variabel untuk menyimpan PID

    pid = fork();     // Menyimpan PID dari Child Process

    /* Keluar saat fork gagal
    * (nilai variabel pid < 0) */
    if (pid < 0) 
    {
        exit(EXIT_FAILURE);
    }

    /* Keluar saat fork berhasil
    * (nilai variabel pid adalah PID dari child process) */
    if (pid > 0) 
    {
        exit(EXIT_SUCCESS);
    }

    umask(0);

    sid = setsid();
    if (sid < 0) 
    {
        exit(EXIT_FAILURE);
    }

    if ((chdir("/home/nur/sisop/Modul2/Praktikum/")) < 0) 
    {
        exit(EXIT_FAILURE);
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    bool done = false;

    while(1)
    {
        time_t now = time(NULL); // inisialisasi variabel now bertipe time dengan fungsi time dg parameter NULL
        struct tm *t = localtime(&now); // inisialisasi pointer t bertipe struct tm dg fungsi localtime berparameter now(alamat memmori now)

        ...
	
        else if(t->tm_mday==9 && t->tm_mon+1==4 && t->tm_hour==22 && t->tm_min==22)
        {
            pid_t child1;
            int statuss;

            child1 = fork();
            
            if(child1 < 0)
            {
                exit(EXIT_FAILURE);
            }
            if(child1 == 0)
            {
                char *argc[] = {"zip", "-rq", "Lopyu_Stevany.zip", "Pyoto", "Musyik", "Fylm", NULL};
                execv("/usr/bin/zip", argc);
            }
            else
            {
                while((wait(&statuss)) > 0);
                char *ag[] = {"find", "/home/nur/sisop/Modul2/Praktikum/", "-mindepth", "1", "-type", "d", "-exec", "rm", "-r", "{}", "+", NULL};
                if(execv("/usr/bin/find", ag) == -1)
                    exit(EXIT_FAILURE);
            }
        }
        sleep(1);
    }
}
```
Untuk menghapus folder pada path, kami menggunakan ```find``` untuk mencari semua yang bertipe ```folder (d)``` kecuali folder path dengan menambahkan argumen ```-mindepth``` dan ```-type```. Kemudian, untuk menghapus folder yang telah ditemukan, kami menambahkan argumen ```-exec``` yang akan akan mengeksekusi ```rm``` secara rekursif.

Hasil yang didapat saat proses 9 April pukul 16.22 WIB selesai dijalankan:
![image](https://drive.google.com/uc?export=view&id=1g_uosAxSrxpHKOcg_b04PQ1aRPay6Ab8)

Hasil yang didapat saat proses 9 April pukul 22.22 WIB selesai dijalankan:
![image](https://drive.google.com/uc?export=view&id=1RzJdYPc8u3tgruVYDFnQZGe01e6CnbGn)

Kendala yang dialami saat menyelesaikan soal 1 yaitu:
- Kesalahan pengimplementasian saat akan mencocokkan tanggal dan waktu sesuai permintaan soal.
- Kesulitan saat menjalankan banyak child sekaligus.
- Mengalamai beberapa kesalahan saat mengimplementasikan penggunakaan library ```dirent.h```.

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
Gambar bahwa unzip berhasil :

![gambar 2a (unzip)](https://user-images.githubusercontent.com/65168221/115965800-ffa87c80-a554-11eb-8aeb-f91c95ac63e5.jpg)


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

Gambar bahwa membuat folder dengan nama jenis hewan :

![gambar 2b (bikin folder)](https://user-images.githubusercontent.com/65168221/115965917-79406a80-a555-11eb-8b24-0c3cdf890e6b.jpg)


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

Gambar memasukkan gambar ke dalam folder :

![gambar 2c 2d (masukkan gambar ke folder)](https://user-images.githubusercontent.com/65168221/115965975-9ecd7400-a555-11eb-9557-204e322199d4.jpg)


Terakhir, terdapat fungsi untuk menuliskan ke dalam file keterangan.txt menurut format yang ada
```
fp = fopen(keterangan, "a+");
fprintf(fp, "nama : %s\numur : %s\n\n",namahewan, umurhewan);
fclose(fp);
 ```
 
 Gambar hasil keterangan.txt :
 
 ![gambar 2e (keterangan txt)](https://user-images.githubusercontent.com/65168221/115965992-c02e6000-a555-11eb-8613-d905adaca159.jpg)

 Kendala yang dialami : 
 - Kesusahan saat menjalankan banyak child sekaligus
 - Kesusahan saat mengatasi nama file yang mengandung _ (gambar yang terdiri dari 2 hewan)
 - Kesusahan saat membaca nama file dimana saya sebelumnya menggunakna strtok dan tidak berhasil sehingga harus membuat fungsi secara manual

### Soal no 3
