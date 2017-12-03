#include "ucode.c"

main(int argc, char *argv[])
{
    int fd;
    char buf[256];
    char c;

    if(argc < 2)
    {
        while(gets(buf))
        {
            printf("%s\n\r", buf);
        }
    }
    
    else
    {
        fd = open(argv[1], O_RDONLY);

        while(read(fd, &c, 1) > 0)
            mputc(c);
    }

    close(fd);
}