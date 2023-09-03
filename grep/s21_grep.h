#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <regex.h>

#define BUFF 1000

typedef struct bank_flags {
    int flag_e;
    int flag_i;
    int flag_v;
    int flag_c;
    int flag_l;
    int flag_n;
    int flag_h;
    int flag_s;
    int flag_f;
    int flag_o;
    int file_num;
    int number[100];
} t_flags;

typedef struct list {
    char data[1000];
    struct list *ptr;
} spis;

void output_instruction(char **argv);
void input_processing(int argc, char *argv[]);
void init_flags(t_flags *info);
void parsing_e_f(int argc, char **argv, t_flags *info);
void flag_e_f(char *argv, t_flags *info);
spis *input_parsing(int argc, char **argv, t_flags *info, spis *lst, spis *lst_file, spis *f_lst);
spis *flag_parsing(char *grep, char *argv, t_flags *info, spis *lst, int *marker, spis **f_lst1);
void file_open(spis *lst_file, spis *lst, t_flags *info);
void file_read(FILE *f, char *lst_file, spis *lst, t_flags *info, int file_n);
void kread(spis *tmp_lst, char *str, t_flags *info, char *n_f, int *l_n, int *count,
                                                int *mar_v, int *mar_l, int file_n);
int keyword_search(char *keyword, char *str, t_flags *info);
void print_if_flag_o(char *keyword, char *str, t_flags *info);
void keyw_from_file(spis **lst, char *argv[], spis *f_lst);
spis *init(char *template);
spis *addelem(spis *lst, char *template);
spis *delete_list(spis *head);
int count_file(spis *head);

#endif  // SRC_GREP_S21_GREP_H_
