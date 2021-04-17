#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>

char panjang[55];
char jenishewan[55];
char namahewan[55];
char umurhewan[55];
char namafile[75];
char namafolder[75];
char keterangan[75];
struct dirent *ep;
int hewan(int mulai);
int nama(int mulai);
int umur(int mulai);
pid_t child_id6, child_id7;
int status5,status6,status7;
void changename(int mulai);
FILE *fp;

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

int umur(int mulai){
	int counta=-1;
	int is_= 1;
	int d;
	strcpy(umurhewan,"");
	int pjg = strlen(panjang);

	for(d=mulai; d<strlen(panjang)-4; d++){
		if(panjang[d] == '_'){
			is_=0;
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

void changename (int mulai){
	if(panjang[mulai] == '.'){
		child_id6=fork();
		if(child_id6==0){
			while ((wait(&status5)) > 0);
			keterangan[75];
			
			strcat(namafile,"/home/adr01/modul2/petshop/");
			strcat(namafile,panjang);
			strcat(namafolder, "/home/adr01/modul2/petshop/");
			strcat(namafolder, jenishewan);
			strcat(namafolder, "/");
			strcat(keterangan, namafolder);
			strcat(keterangan, "keterangan.txt");
			strcat(namafolder, namahewan);
			strcat(namafolder, ".jpg");
			
			//Soal 2e
			fp = fopen(keterangan, "a+");
			fprintf(fp, "nama : %s\numur : %s\n\n",namahewan, umurhewan);
			fclose(fp);
			
			char *argv[] = {"mv", namafile, namafolder, NULL};
			execv("/bin/mv", argv);
		}
		
	}
	else if(panjang[mulai] == '_'){
		child_id7=fork();
		if(child_id7==0){
			while ((wait(&status6)) > 0);
			keterangan[75];
			
			strcat(namafile,"/home/adr01/modul2/petshop/");
			strcat(namafile,panjang);
			strcat(namafolder, "/home/adr01/modul2/petshop/");
			strcat(namafolder, jenishewan);
			strcat(namafolder, "/");
			strcat(keterangan, namafolder);
			strcat(keterangan, "keterangan.txt");
			strcat(namafolder, namahewan);
			strcat(namafolder, ".jpg");
			
			//Soal 2e
			fp = fopen(keterangan, "a+");
			fprintf(fp, "nama : %s\numur : %s\n\n",namahewan, umurhewan);
			fclose(fp);
			
			char *argv[] = {"cp", namafile, namafolder, NULL};
			execv("/bin/cp", argv);
		}
		else {
			while ((wait(&status7)) > 0);
			mulai +=1;
			
			int hewan_ = hewan(mulai);
			int nama_ = nama(hewan_);
			int umur_ = umur(nama_);
			changename(umur_-1);
		}
	}
}

int main() {
  pid_t child_id, child_id1, child_id2, child_id3, child_id4, child_id5;
  int status, status1, status2,status3,status4;
  DIR *dp;
  struct dirent *ep;

  //Soal 2a
  child_id = fork();

  if (child_id < 0) {
    exit(EXIT_FAILURE);
  }

  if (child_id == 0) {	
	child_id1 = fork();
	
	if(child_id1 == 0) {
		child_id2 = fork();
		
		if(child_id2 == 0) {
			char *argv[] = {"mkdir", "-p", "/home/adr01/modul2/petshop", NULL};
	    		execv("/bin/mkdir", argv);
	    		exit(0);
		}
		else {
			while ((wait(&status)) > 0);
			char *argv2[] = {"unzip", "/home/adr01/Documents/SesiLab2/Soal Praktikum/pets.zip", "-d","/home/adr01/modul2/petshop/",NULL};
	    		execv("/usr/bin/unzip", argv2);
	    		exit(0);
		}
	}
	else {
		while ((wait(&status1)) > 0);
	    	dp = opendir("/home/adr01/modul2/petshop/");
	    	chdir("/home/adr01/modul2/petshop/");
	    	if (dp != NULL) {
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

		      (void) closedir (dp);
		}
	    	exit(0);
	}
  }
  
	//Soal 2b
	else {
	  	while ((wait(&status3)) > 0);
		int itrpanjang=-1, itrpendek=-1,flag=0,i;
	    	char a[2] = ";";
	    	char b[2] = "_";
	    	char pendek[55][55];
	    	char *token;
	    	char *token2;
	    	char *folder;
	    	char *namafile;
	    	
	    	dp = opendir("/home/adr01/modul2/petshop/");
	    	if (dp != NULL) {
		      while ((ep = readdir (dp))) {
		      		if(ep->d_type != DT_DIR && strcmp(ep->d_name, ".") != 0 && strcmp(ep->d_name, "..") != 0){
		      			itrpanjang++;   	
				      	
				      	token = strtok(ep->d_name, a);
				      	if(itrpendek==-1) {
				      		itrpendek++;
				      		strcpy(pendek[itrpendek], token);
				      	}
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
		      		}
			}
			(void) closedir (dp);
		}	
		
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

		//Soal 2c dan 2d

		dp = opendir("/home/adr01/modul2/petshop/");
	    	if (dp != NULL) {
	    		while ((wait(&status4)) > 0);
		        while ((ep = readdir (dp))) {
		      		if(ep->d_type != DT_DIR && strcmp(ep->d_name, ".") != 0 && strcmp(ep->d_name, "..") != 0){
		      			strcpy(panjang, ep->d_name);
		      			int animaltype = hewan(0);
		      			int animalname = nama(animaltype);
		      			int animalage = umur(animalname);
		      			changename(animalage-1); 
		      		}	
		      }
		}
		(void) closedir (dp);
	}		
}
