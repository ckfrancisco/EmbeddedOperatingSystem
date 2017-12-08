#include "ucode.c"

int console;

// P1's code
int parent(int login[])
{
    int i, pid, status;

    while(1){
        printf("INIT : wait for ZOMBIE child\n\r");
        pid = wait(&status);

        i = 0;
        while(i < 3)
        {
            if(pid == login[i])
            {
                login[i] = fork();

                if(login[i])
                    continue;
                else
                {
                    if(i == 0)
                        exec("login /dev/tty0");
                    else if(i == 0)
                        exec("login /dev/ttyS0");
                    else if(i == 0)
                        exec("login /dev/ttyS1");
                }
            }

            i++;
        }
        
        printf("INIT: I just buried an orphan child proc %d\n\r", pid);
    }
}

main()
{
    int in, out, login[3];
    // STAT buf;

    // file descriptors for terminal I/O
    in = open("/dev/tty0", O_RDONLY); // file descriptor 0
    out = open("/dev/tty0", O_WRONLY); // for display to console

    // fstat(in, &buf);
    // printf("    IN DEV=%d INO=%d\n\r", buf.st_dev, buf.st_ino);
    // fstat(out, &buf);
    // printf("    IN DEV=%d INO=%d\n\r", buf.st_dev, buf.st_ino);
    
    printf("INIT: fork a login proc on console\n\r");
    login[0] = fork();
    if (login[0])
    {
        printf("INIT: fork a login proc on console\n\r");
        login[1] = fork();
        if (login[1])
        {
            printf("INIT: fork a login proc on console\n\r");
            login[2] = fork();
            if (login[2])
                parent(login);
            else
                exec("login /dev/ttyS1");
        }
        else
            exec("login /dev/ttyS0");
    }
    else
        exec("login /dev/tty0");
}