#include "ucode.c"

main(int argc, char *argv[])
{
    int fd, out;
    char tty[16], c;
    STAT ttystat, instat, outstat;

    if(argc > 1)
    {
        fd = open(argv[1], O_RDONLY);
        if(fd < 0)
        {
            printf("Error: %s does not exist\n\r", argv[2]);
            exit(1);
        }

        dup2(fd, 0); 
    }

    gettty(tty);
    stat(tty, &ttystat);
    fstat(0, &instat);
    fstat(1, &outstat);
    out = open(tty, O_WRONLY);
        
    if(ttystat.st_dev == instat.st_dev && ttystat.st_ino == instat.st_ino)
        while(read(0, &c, 1))
        {
            if(ttystat.st_dev == outstat.st_dev && ttystat.st_ino == outstat.st_ino)
            {
                write(1, &c, 1);
                if(c == '\r')
                {
                    c = '\n';
                    write(out, &c, 1);
                }
            }
            else
            {
                write(1, &c, 1);
                write(out, &c, 1);

                if(c == '\r')
                {
                    c = '\n';
                    write(out, &c, 1);
                }
            }
        }

    else
        while(read(0, &c, 1))
        {
            if(ttystat.st_dev == outstat.st_dev && ttystat.st_ino == outstat.st_ino)
                mputc(c);
            else
                write(1, &c, 1);
            
                
        }

    exit(0);
}