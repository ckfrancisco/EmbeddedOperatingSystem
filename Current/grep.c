#include "ucode.c"

int substring(char *pattern, char *s)
{
    char *p = pattern;

    while(*s)
    {
        if(*s == *p)
        {
            while(*s++ && *p++)
            {
                if(*p == '\0')
                    return 1;
                
                if(*s != *p)
                    break;
            }

            p = pattern;
        }
        s++;
    }

    return 0;
}

main(int argc, char *argv[])
{
    int in, fd;
    char buf[256];

    if(argc < 2)
        return;

    if(argc < 3)
    {
        while(gets(buf))
        {
            if(substring(argv[1], buf))
                printf("%s\n\r", buf);
        }
    }

    else
    {
        fd = open(argv[2], O_RDONLY);
        if(fd < 0)
        {
            printf("Error: %s does not exist\n\r", argv[1]);
        }

        in = dup(0);
        dup2(fd, 0);

        while(getline(buf))
        {
            if(substring(argv[1], buf))
                printf("%s", buf);
        }

        dup2(in, 0);
        close(in); close(fd);
    }
}