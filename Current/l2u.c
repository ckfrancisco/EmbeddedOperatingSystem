#include "ucode.c"

char capitalize(char c)
{
    if(c >= 97 && c <= 122)
        return c - 32;
    return c;
}

main(int argc, char *argv[])
{
    int fdi, fdo;
    char tty[16], c;
    STAT ttystat, instat;

    fdi = 0;
    fdo = 1;

    if(argc > 1)
    {
        fdi = open(argv[1], O_RDONLY);
        if(fdi < 0)
        {
            printf("Error: %s does not exist\n\r", argv[1]);
            exit(0);
        }
    }

    if(argc > 2)
    {
        printf("    OPENING TO WRITE\n\r");
        fdo = open(argv[2], O_WRONLY | O_CREAT);
        if(fdo < 0)
        {
            printf("Error: %s does not exist\n\r", argv[2]);
            exit(0);
        }
    }

    gettty(tty);
    stat(tty, &ttystat);
    fstat(fdo, &instat);
        
    if(ttystat.st_dev == instat.st_dev && ttystat.st_ino == instat.st_ino)
        while(read(fdi, &c, 1))
        {
            c = capitalize(c);
            mputc(c);
            if(c == '\r')
                mputc('\n');
        }

    else
        while(read(fdi, &c, 1))
        {
            c = capitalize(c);
            write(fdo, &c, 1);
        }
}