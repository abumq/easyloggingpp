#ifndef GETOPT_H
#define GETOPT_H

int optIndex;
char* currArg;

int getopt(int argc, char** argv, char* optstring) {
    static char *next = nullptr;
    if (optIndex == 0)
        next = nullptr;

    currArg = nullptr;

    if (next == nullptr || *next == '\0') {
        if (optIndex == 0)
            optIndex++;

        if (optIndex >= argc || argv[optIndex][0] != '-' || argv[optIndex][1] == '\0') {
            currArg = nullptr;
            if (optIndex < argc)
                currArg = argv[optIndex];
            return EOF;
        }

        if (strcmp(argv[optIndex], "--") == 0) {
            optIndex++;
            currArg = nullptr;
            if (optIndex < argc)
                currArg = argv[optIndex];
            return EOF;
        }

        next = argv[optIndex];
        ++next;
        ++optIndex;
    }

    char c = *next++;
    char* cp = strchr(optstring, c);

    if (cp == nullptr || c == ':')
        return '?';

    ++cp;
    if (*cp == ':') {
        if (*next != '\0') {
            currArg = next;
            next = nullptr;
        }
        else if (optIndex < argc) {
            currArg = argv[optIndex];
            ++optIndex;
        }
        else {
            return '?';
        }
    }

    return c;
}
#endif // GETOPT_H
