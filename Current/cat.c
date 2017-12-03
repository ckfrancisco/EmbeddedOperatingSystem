#include "ucode.c"

main(int argc, char *argv[])
{
    int fd;
    char c;

    fd = open(argv[1], O_RDONLY);

    while(read(fd, &c, 1) > 0)
        mputc(c);

    close(fd);
}