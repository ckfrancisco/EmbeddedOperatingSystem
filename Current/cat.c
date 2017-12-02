#include "ucode.c"

main(int argc, char *argv[])
{
    int file, nbytes;
    char buf[256];

    if(argc < 1)
        return;
    
    file = open(argv[1], O_RDONLY);

    while(nbytes = read(file, buf, 255))
    {
        buf[nbytes] = 0;
        printf("%s", buf);
    }

    close(file);
}