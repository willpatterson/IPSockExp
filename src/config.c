/* Functions for parsing the tcpsproxy config */

#include "include/config.h"

FILE * get_cfg_fd(char * fpath) {
    FILE * file = fopen(fpath, "r");
    return file;
}

void parse_cfg_file(LIST * frontends, LIST * backends, char * cfg_path) {
    int i;

    char * line = NULL;
    size_t len = 0;
    size_t read;
    char * token;
    char * subtoken;

    char * buffer1;
    char * buffer2;

    FILE * cfg_file = fopen(cfg_path, "r");
    //printf("%d", cfg_file);
    if (cfg_file == NULL)
        exit(1);

    while ((read = getline(&line, &len, cfg_file)) != -1) {
        token = strtok_r(line, " ", &buffer1);
        //printf("%s\n", token);
        if (strcmp(token, DEFAULT_KEYWORD) == 0) {}
        else if (strcmp(token, FRONTEND_KEYWORD) == 0) {
            subtoken = strtok_r(buffer1, " ", &buffer2);
            printf("%s\n", subtoken);
        }
        else if (strcmp(token, BACKEND_KEYWORD) == 0) {}
        else {} //Deal with commends and empty lines
    }

    fclose(cfg_file);
    free(line);
    //free(buffer);
}

int main(int argc, char *argv[]) {
    char * test_cfg = "./test/test_cfg";
    parse_cfg_file(FRONTENDS, BACKENDS, test_cfg);
}
