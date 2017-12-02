/****************** Algorithm of login *******************/
// login.c : Upon entry, argv[0]=login, argv[1]=/dev/5X #include "ucode.c"

#include "ucode.c"

int tokenize(int fd, char *buf, char token, int position)
{
    int nbytes = 0;

    while(read(fd, buf, 1) > 0 && *buf != token)
        nbytes++;

    lseek(fd, position, 0);

    read(fd, buf, nbytes);
    buf[nbytes] = 0;

    return nbytes;
}

int myatoi(char *buf)
{
    int result = 0;

    while(*buf)
    {
        result += (*buf - '0');

        if(*(buf++))
            result *= 10;
    }
}

int mystrcmp(char *s1, char *s2)
{
    while(*(s1++) == *(s2++) && *s1 && *s2);

    if(!(*s1 && *s2))
        return 1;
    return 0;
}

main(int argc, char *argv[])
{
    int in, out, err, passwd;
    char name[128], password[128];

    int line, position;
    char buf1[256], buf2[256];
    int uid, gid;

    int test = 0;
    

    close(0); close(1);
    in  = open(argv[1], O_RDONLY); 
    out = open(argv[1], O_WRONLY);
    err = open(argv[1], O_WRONLY);

    fixtty(argv[1]);                    // set tty name string in PROC.tty

    passwd = open("/etc/passwd", O_RDONLY);  // open /etc/passwd file for READ;

    while(1){
        printf("login:");
        gets(name);
        printf("password:");
        gets(password);

        line = position = 0;

        while(tokenize(passwd, buf1, '\r', position))
        {
            lseek(passwd, position, 0);
            printf("line=%d position=%d test=%d buf=%s\n\r", line, position, test++, buf1);

            line = tokenize(passwd, buf1, '\n', position);
            printf("line=%d position=%d test=%d buf=%s\n\r", line, position, test++, buf1);

            printf("%d %s\n\r", test++, buf1);
            position = line;
            position += tokenize(passwd, buf1, ':', position);
            position += tokenize(passwd, buf2, ':', position);

            if(mystrcmp(name, buf1) && mystrcmp(password, buf2))
            {
                position += tokenize(passwd, buf1, ':', position);
                position += tokenize(passwd, buf2, ':', position);
                uid = myatoi(buf1); gid = myatoi(buf2);
                chuid(uid, gid);

                position += tokenize(passwd, buf1, ':', position);
                chdir(buf1);

                close(passwd);

                position += tokenize(passwd, buf1, '\n', position);
                exec(buf1);

                return;
            }
        }

        printf("login failed, try again\n");
    }
}