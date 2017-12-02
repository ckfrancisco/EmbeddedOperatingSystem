/****************** Algorithm of login *******************/
// login.c : Upon entry, argv[0]=login, argv[1]=/dev/5X #include "ucode.c"

#include "ucode.c"

int mytokenize(int fd, char *buf, char token, int position)
{
    int nbytes = 0;
    char *cp = buf;

    lseek(fd, position, 0);

    while(read(fd, cp, 1) > 0)
    {
        nbytes++;
        if(*cp == token)
            break;
        cp++;
    }

    buf[nbytes - 1] = 0;

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
    int count = 0;

    while(*(s1++) == *(s2++) && *s1 && *s2);

    if(!(*s1 || *s2))
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

    int count = 0;
    int nbytes = 0;
    
    close(0); close(1); close(2);
    in  = open(argv[1], O_RDONLY); 
    out = open(argv[1], O_WRONLY);
    err = open(argv[1], O_WRONLY);

    fixtty(argv[1]);                        // set tty name string in PROC.tty

    passwd = open("/etc/passwd", O_RDONLY); // open /etc/passwd file for READ;

    while(1){
        printf("login:");
        gets(name);
        printf("password:");
        gets(password);

        line = position = 0;

        while(mytokenize(passwd, buf1, '\r', line))
        {
            //printf("FILE=%s\n", buf1);

            position += mytokenize(passwd, buf1, ':', position);
            //printf("NAME=%s\n", buf1);

            position += mytokenize(passwd, buf2, ':', position);
            //printf("PASSWORD=%s\n", buf2);

            if(mystrcmp(name, buf1) && mystrcmp(password, buf2))
            {
                position += mytokenize(passwd, buf1, ':', position);
                //printf("UID=%s\n", buf1);

                position += mytokenize(passwd, buf2, ':', position);
                //printf("GID=%s\n", buf2);

                uid = myatoi(buf1); gid = myatoi(buf2);
                //printf("UID=%d GID=%d\n", uid, gid);
                chuid(uid, gid);

                position += mytokenize(passwd, buf1, ':', position);
                position += mytokenize(passwd, buf1, ':', position);
                //printf("DIR=%s\n", buf1);
                chdir(buf1);

                position += mytokenize(passwd, buf1, '\n', position);
                //printf("CMD=%s\n", buf1);

                close(passwd);

                exec(buf1);

                close(in); close(out); close(err); close(passwd);
                return;
            }

            position = line += mytokenize(passwd, buf1, '\n', line);
        }

        printf("login failed, try again\n\r");
    }
}