#include <stddef.h>
#include <stdio.h>

static char buf[80] = {0};

char *strcpy(char *dest, const char *src) {

        if (src && dest && (src != dest)) {
                char *p;
                size_t n;
                for (p=(char*)src, n=0; *p; p++, n++);

                if (src < dest) {
                        if (dest - src < n + 1) {
                                printf("Source and destination buffers overlap.\n");
                                return NULL;
                        }
                } else if (src - dest < n + 1) {
                        printf("Source and destination buffers overlap.\n");
                        return NULL;
                }

                for (p=dest; n; n--, src++, p++)
                        *p = *src;

                *p = 0;
        }
        return dest;
}

int main(int argc, char **stdarg) {

        if (strcpy(buf, "Copy this string to this destination."))
                printf("Destination buffer contains \"%s\"\n", buf);
        else
                printf("strcpy failed.\n");

        if (strcpy(buf, buf))
                printf("Destination buffer contains \"%s\"\n", buf);
        else
                printf("strcpy failed.\n");

        if (strcpy(buf, &buf[10]))
                printf("Destination buffer contains \"%s\"\n", buf);
        else
                printf("strcpy failed.\n");

        if (strcpy(&buf[10], buf))
                printf("Destination buffer contains \"%s\"\n", buf);
        else
                printf("strcpy failed.\n");

        while (argc--) {
                strcpy(buf, *stdarg++);
                printf("Destination buffer contains \"%s\"\n", buf);
        }
        return 0;
}
