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

void forkExecWait(char *cmd, char *arg[]) 
{
    pid_t child_id;
    int status;

    child_id = fork();

    if (child_id < 0) {
        exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
    }

    if (child_id == 0) {
        // this is child
        execv(cmd, arg);
    } else {
        // this is parent
        while ((wait(&status)) > 0);
        return;
    }
}

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
            //printf("%s\n", dp->d_name);

            // Construct new path from our base path
            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name);

            char *argv[] = {"mv", path, dest, NULL};
            forkExecWait("/bin/mv", argv);
        }
    }

    closedir(dir);
}

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
        // Tulis program kalian di sini

        //char buffer[100]; // Mendeklarasikan array text berukuran 100 dengan tipe char
        time_t now = time(NULL); // inisialisasi variabel now bertipe time dengan fungsi time dg parameter NULL
        struct tm *t = localtime(&now); // inisialisasi pointer t bertipe struct tm dg fungsi localtime berparameter now(alamat memmori now)
        //strftime(buffer, sizeof(buffer)-1, "%d-%m_%H:%M", t); // nge-breakdown format tipe waktu tm sesuai format yg dispesifikasikan 

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
                    else 
                    {
                        // film
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
                else
                {
                    // musik
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
            else
            {
                // foto
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