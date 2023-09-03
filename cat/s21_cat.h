#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define SIZE 100

typedef struct storage_flags {
    int flag_b;
    int flag_e;
    int flag_n;
    int flag_s;
    int flag_t;
    int flag_v;
    int flag_error;
    char flag_sym;
    char flag_word[SIZE];
} t_storage_flags;

void repeat_input();
void output_files(char **argv, char *path, t_storage_flags *info);
void start_cat(int argc, char **argv);
void init_struct(t_storage_flags *info);
void flags(char *argv, t_storage_flags *info);
void flags_gnu(char *argv, t_storage_flags *info);
int output_error(t_storage_flags *info, char **argv);

#endif  // SRC_CAT_S21_CAT_H_
