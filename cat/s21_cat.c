#include "s21_cat.h"

int main(int argc, char **argv) {
    if (argc == 1) {
        repeat_input();
    } else if (argc >= 2) {
        start_cat(argc, argv);
    }
    return 0;
}

void repeat_input() {
    char c;
    while ((c = getchar()) != EOF) {
        printf("%c", c);
    }
}

void start_cat(int argc, char **argv) {
    t_storage_flags info;
    init_struct(&info);
    int i = 1, marker = 0;
    while (i < argc) {
        if (argv[i][0] == '-') {
            flags(argv[i], &info);
            i++;
            if ((marker = output_error(&info, argv)) == 1)
                break;
        } else {
            break;
        }
    }
    if (!marker) {
        for (int j = i; j < argc; j++) {
            output_files(argv, argv[j], &info);
        }
    }
}

void init_struct(t_storage_flags *info) {
    info->flag_b = 0;
    info->flag_e = 0;
    info->flag_n = 0;
    info->flag_s = 0;
    info->flag_t = 0;
    info->flag_v = 0;
    info->flag_error = 0;
    info->flag_sym = 0;
    strcpy(info->flag_word, "");
}

void flags(char *argv, t_storage_flags *info) {
    if (argv[1] == '-') {
        flags_gnu(argv, info);
    } else {
        int lenght = strlen(argv);
        for (int i = 1; i < lenght; i++) {
            if (argv[i] == 'b') {
                info->flag_b = 1;
            } else if (argv[i] == 'e') {
                info->flag_e = 1;
                info->flag_v = 1;
            } else if (argv[i] == 'E') {
                info->flag_e = 1;
            } else if (argv[i] == 'n') {
                info->flag_n = 1;
            } else if (argv[i] == 's') {
                info->flag_s = 1;
            } else if (argv[i] == 't') {
                info->flag_t = 1;
                info->flag_v = 1;
            } else if (argv[i] == 'T') {
                info->flag_t = 1;
            } else if (argv[i] == 'v') {
                info->flag_v = 1;
            } else {
                info->flag_error = 2;
                info->flag_sym = argv[i];
                break;
            }
        }
    }
}

void flags_gnu(char *argv, t_storage_flags *info) {
    if ((strcmp(argv, "--number-")) == 0) {
        info->flag_b = 1;
    } else if ((strcmp(argv, "--number")) == 0) {
        info->flag_n = 1;
    } else if ((strcmp(argv, "--squeeze-blank")) == 0) {
        info->flag_s = 1;
    } else {
        info->flag_error = 2;
        strcpy(info->flag_word, argv);
    }
}

void output_files(char **argv, char *path, t_storage_flags *info) {
    FILE *f;
    if ((f = fopen(path, "r")) == NULL) {
        printf("%s: %s: %s\n", argv[0], path, strerror(errno));
        exit(1);
    } else {
    int count = 0, number = 1, new_line = '\n';
    char x = '$';
    while (1) {
        int sym = fgetc(f);
        if (sym == EOF)
            break;
        if (sym != '\n' && info->flag_b && new_line == '\n')
            printf("%6d\t", number++);
        if (info->flag_s && sym == '\n' && new_line == '\n')
            count++;
        if (count == 2) {
            count--;
            continue;
        }
        if (!info->flag_b && info->flag_n && new_line == '\n')
            printf("%6d\t", number++);
        if (sym == '\n' && info->flag_e)
            printf("%c", x);
        if (info->flag_t && sym == '\t') {
            printf("^I");
            new_line = sym;
            continue;
        }
        if (info->flag_v == 1) {
            if (sym >= 0 && sym <= 31 && sym != 9 && sym != 10) {
                printf("^");
                sym += 64;
            }
            if (sym >= 127 && sym <= 159) {
                if (sym == 127)
                    printf("^");
                else
                    printf("M-^");
                sym -= 64;
            }
        }
        printf("%c", sym);
        new_line = sym;
        if (new_line != '\n')
            count = 0;
    }
    fclose(f);
    }
}

int output_error(t_storage_flags *info, char **argv) {
    int marker = 0;
    if (info->flag_error == 1) {
        printf("%s: illegal option -- %c\n", argv[0], info->flag_sym);
        printf("usage: cat [-benstuv] [file ...]\n");
        marker = 1;
    }
    if (info->flag_error == 2) {
        printf("%s: illegal option -- %s\n", argv[0], info->flag_word);
        printf("usage: cat [-benstuv] [file ...]\n");
        marker = 1;
    }
    return marker;
}
