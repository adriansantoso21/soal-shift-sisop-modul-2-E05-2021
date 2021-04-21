#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <wait.h>
#include <time.h>

void createKillerExecutable(char *argv) {
    FILE *killer_bash = fopen("killer.sh", "w");

    fprintf(killer_bash, "#!/bin/bash\n");
    if (strcmp(argv, "-z") == 0) {
        char *kill_code = 
            "killall -9 ./soal3\n";
        fprintf(killer_bash, kill_code);
    } else if (strcmp(argv, "-x") == 0) {
        char *kill_code = 
            "kill %d\n";
        fprintf(killer_bash, kill_code, getpid());
    }

    fclose(killer_bash);
}

void forkExitFailure(pid_t pid) {
    if (pid < 0) {
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) {
    
    // Return 1 (error) argumen salah
    if (argc != 2 || (strcmp(argv[1], "-z") != 0 && strcmp(argv[1], "-x") != 0)) {
        printf("error!\n");
        return 1;
    }


    pid_t pid, sid,
        child_id, child_id2, child_id3, child_id4;   // Variabel untuk menyimpan PID

    pid = fork();     // Menyimpan PID dari Child Process

    /* Keluar saat fork gagal
    * (nilai variabel pid < 0) */
    if (pid < 0) {
        exit(EXIT_FAILURE);
    }

    /* Keluar saat fork berhasil
    * (nilai variabel pid adalah PID dari child process) */
    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    createKillerExecutable(argv[1]);

    umask(0);

    sid = setsid();
    if (sid < 0) {
        exit(EXIT_FAILURE);
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    while (1) {

        time_t rawtime;
        time(&rawtime);
        struct tm *timeinfo  = localtime(&rawtime);
        char folderName[100];
        strftime(folderName, 100, "%Y-%m-%d_%H-%M-%S", timeinfo);
        
        child_id = fork();
        forkExitFailure(child_id);

        // child 1
        if (child_id == 0) {
            char *argv[] = {"mkdir", folderName, NULL};
            execv("/bin/mkdir", argv);
        }

        // parent 1
        // while (wait(NULL) > 0);
        child_id2 = fork();
        forkExitFailure(child_id2);

        // child 2
        if (child_id2 == 0) {
            for(int i = 0; i < 10; i++) {
                
                child_id3 = fork();
                forkExitFailure(child_id3);
                
                // child 3
                if (child_id3 == 0) {
                    char pictName[100], pictPath[200], link[100];
                    
                    time(&rawtime);
                    timeinfo = localtime(&rawtime);
                    strftime(pictName, 100, "%Y-%m-%d_%H-%M-%S", timeinfo);

                    sprintf(pictPath, "%s/%s", folderName, pictName);
                    sprintf(link, "https://picsum.photos/%ld", (rawtime % 1000) + 50);

                    char *argv[] = {"wget", "-q", "-O", pictPath, link, NULL};
                    execv("/usr/bin/wget", argv);
                }

                // parent 3
                sleep(5);
            }

            child_id4 = fork();
            forkExitFailure(child_id4);

            // child 4
            if (child_id4 == 0) {
                char message[100] = "Download Success", zipName[100], txtPath[200];
                
                for (int j = 0; j < strlen(message); j++) {
                    if (message[j] >= 'a' && message[j] <= 'z') {
                        message[j] = message[j] - 'a';
                        message[j] = (message[j] + 5) % 26;
                        message[j] = message[j] + 'a';
                    }

                    else if (message[j] >= 'A' && message[j] <= 'Z') {
                        message[j] = message[j] - 'A';
                        message[j] = (message[j] + 5) % 26;
                        message[j] = message[j] + 'A';
                    }
                }

                sprintf(txtPath, "%s/%s", folderName, "status.txt");
                
                FILE *txt = fopen(txtPath, "w");
                fputs(message, txt);
                fclose(txt);

                sprintf(zipName, "%s.zip", folderName);
                
                char *argv[] = {"zip", "-q", "-r", zipName, folderName, NULL};
                execv("/usr/bin/zip", argv);
                
            } else {

                // parent 4
                while (wait(NULL) > 0);
            
                char *argv[] = {"rm", "-r", folderName, NULL};
                execv("/bin/rm", argv);
            }
        } 
        
        // parent 2
        sleep(40);
    }
}