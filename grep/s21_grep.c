#include "s21_grep.h"

int main(int argc, char *argv[]) {
    if (argc == 1) {
        output_instruction(argv);
    } else if (argc >= 2) {
        input_processing(argc, argv);
    }
    return 0;
}

void output_instruction(char **argv) {
    printf("usage: %s [-abcDEFGHhIiJLlmnOoqRSsUVvwxZ] [-A num] [-B num] [-C[num]]\n", argv[0]);
    printf("\t[-e pattern] [-f file] [--binary-files=value] [--color=when]\n");
    printf("\t[--context[=num]] [--directories=action] [--label] [--line-buffered]\n");
    printf("\t[--null] [pattern] [file ...]\n");
}

void input_processing(int argc, char *argv[]) {
    spis *lst = init(argv[0]);
    spis *lst_file = init(argv[0]);
    spis *f_lst = init(argv[0]);
    t_flags info;
    init_flags(&info);
    parsing_e_f(argc, argv, &info);
    spis *tmp_lst = input_parsing(argc, argv, &info, lst, lst_file, f_lst);
    if (info.flag_f)
        keyw_from_file(&tmp_lst, argv, f_lst);
    file_open(lst_file, lst, &info);
    delete_list(lst);
    delete_list(lst_file);
    delete_list(f_lst);
}

void init_flags(t_flags *info) {
    info->flag_e = 0;
    info->flag_i = 0;
    info->flag_v = 0;
    info->flag_c = 0;
    info->flag_l = 0;
    info->flag_n = 0;
    info->flag_h = 0;
    info->flag_s = 0;
    info->flag_f = 0;
    info->flag_o = 0;
}

void parsing_e_f(int argc, char **argv, t_flags *info) {
    for (int i = 1; i < argc; i++) {
         if (*argv[i] == '-')
            flag_e_f(argv[i], info);
    }
}

void flag_e_f(char *argv, t_flags *info) {
    argv++;
    while (*argv) {
        if (*argv == 'e') {
            info->flag_e = 1;
            break;
        } else if (*argv == 'f') {
            info->flag_f = 1;
            break;
        } else if (*argv == 'i' || *argv == 'v' || *argv == 'c' || *argv == 'l') {
            argv++;
            continue;
        } else if (*argv == 'n'|| *argv == 'h' || *argv == 's' || *argv == 'o') {
            argv++;
            continue;
        } else {
            break;
        }
        argv++;
    }
}

spis *input_parsing(int argc, char **argv, t_flags *info, spis *lst, spis *lst_file, spis *f_lst) {
    int marker = 0, marker_for_key = 1;
    spis *f_lst1 = f_lst;
    for (int i = 1; i < argc; i++) {
        if (marker == 3) {
            break;
        }
        if (marker == 1) {
            lst = addelem(lst, argv[i]);
            marker = 0;
            continue;
        }
        if (marker == 2) {
            f_lst1 = addelem(f_lst1, argv[i]);
            marker = 0;
            continue;
        }
        if (*argv[i] == '-') {
            lst = flag_parsing(argv[0], argv[i], info, lst, &marker, &f_lst1);
        } else if (!info->flag_e && !info->flag_f) {
            if (marker_for_key) {
                lst = addelem(lst , argv[i]);
                marker_for_key = 0;
            } else {
                lst_file = addelem(lst_file, argv[i]);
            }
        } else {
            lst_file = addelem(lst_file, argv[i]);
        }
    }
    return lst;
}

spis *flag_parsing(char *grep, char *argv, t_flags *info, spis *lst, int *marker, spis **f_lst1) {
    argv++;
    while (*argv) {
        if (*argv == 'e') {
            info->flag_e = 1;
            argv++;
            if (*argv) {
                lst = addelem(lst, argv);
                break;
            } else {
                *marker = 1;
                break;
            }
        } else if (*argv == 'i') {
            info->flag_i = 1;
        } else if (*argv == 'v') {
            info->flag_v = 1;
        } else if (*argv == 'c') {
            info->flag_c = 1;
        } else if (*argv == 'l') {
            info->flag_l = 1;
        } else if (*argv == 'n') {
            info->flag_n = 1;
        } else if (*argv == 'h') {
            info->flag_h = 1;
        } else if (*argv == 's') {
            info->flag_s = 1;
        } else if (*argv == 'f') {
            info->flag_f = 1;
            argv++;
            if (*argv) {
                *f_lst1 = addelem(*f_lst1, argv);
                break;
            } else {
                *marker = 2;
                break;
            }
        } else if (*argv == 'o') {
            info->flag_o = 1;
        } else {
            printf("%s: Invalid argument\n", grep);
            *marker = 3;
            break;
        }
        argv++;
    }
    return lst;
}

void file_open(spis *lst_file, spis *lst, t_flags *info) {
    lst_file = lst_file->ptr;
    int file_n = count_file(lst_file);
    while (lst_file) {
        FILE *f;
        if ((f = fopen(lst_file->data, "r")) == NULL) {
            if (!info->flag_s)
                printf("%s: %s\n", lst_file->data, strerror(errno));
            exit(1);
        } else {
            file_read(f, lst_file->data, lst, info, file_n);
            fclose(f);
        }
        lst_file = lst_file->ptr;
    }
}

void file_read(FILE *f, char *lst_file, spis *lst, t_flags *info, int file_n) {
    char str[BUFF];
    int count = 0, mar_l = 0, line_n = 0, mar_v_l = 0;
    while (fgets(str, BUFF - 1, f)) {
        line_n++;
        int mar_v = 1;
        spis *tmp_lst = lst;
        kread(tmp_lst, str, info, lst_file, &line_n, &count, &mar_v, &mar_l, file_n);
        if (!mar_v && !info->flag_v && info->flag_c && !info->flag_l) {
            (count)++;
        }
        if (mar_v && info->flag_v && !info->flag_c && !info->flag_l) {
            if (!info->flag_h && (file_n > 1))
                printf("%s:", lst_file);
            if (info->flag_n)
                    printf("%d:", line_n);
            printf("%s", str);
            if (strchr(str, '\n') == NULL)
                printf("\n");
        }
        if (mar_v && info->flag_v && info->flag_c && !info->flag_l) {
            count++;
        } else if (mar_v && info->flag_v && info->flag_c && info->flag_l) {
            if (count == 0)
                count++;
        }
        if (mar_v)
            mar_v_l = 1;
    }
    if (info->flag_c) {
        if (!info->flag_h && (file_n > 1))
            printf("%s:", lst_file);
        printf("%d\n", count);
    }
    if (info->flag_l && mar_l && !info->flag_v)
        printf("%s\n", lst_file);
    else if (info->flag_l && info->flag_v && mar_v_l)
        printf("%s\n", lst_file);
}

void kread(spis *tmp_lst, char *str, t_flags *info, char *n_f, int *l_n, int *count,
                                                int *mar_v, int *mar_l, int file_n) {
    tmp_lst = tmp_lst->ptr;
    while (tmp_lst != NULL) {
        int yes_no = keyword_search(tmp_lst->data, str, info);
        if (!yes_no) {
            *mar_v = 0;
            *mar_l = 1;
            if (info->flag_l && !info->flag_v)
                *count = 1;
        }
        if (!yes_no && !info->flag_v && !info->flag_c && !info->flag_l) {
            if (!info->flag_h && (file_n > 1))
                printf("%s:", n_f);
            if (info->flag_n)
                printf("%d:", *l_n);
            if (!info->flag_o) {
                printf("%s", str);
                if (strchr(str, '\n') == NULL)
                printf("\n");
            } else {
                print_if_flag_o(tmp_lst->data, str, info);
            }
            if (!info->flag_o) {
                break;
            }
        }
        tmp_lst = tmp_lst->ptr;
    }
}

int keyword_search(char *keyword, char *str, t_flags *info) {
    regex_t regex;
    int marker = 0;
    if (info->flag_i)
        marker = REG_EXTENDED|REG_ICASE;
    int return_value2 = 1;
    int return_value = regcomp(&regex, keyword, marker);
    if (!return_value) {
        return_value2 = regexec(&regex, str, 0, NULL, 0);
    }
    regfree(&regex);
    return return_value2;
}

void print_if_flag_o(char *keyword, char *str, t_flags *info) {
    regex_t regex;
    regmatch_t matchptr;
    size_t len = strlen(str);
    int marker = 0;
    if (info->flag_i)
        marker = REG_EXTENDED|REG_ICASE;
    int return_value = regcomp(&regex, keyword, marker);
    if (!return_value) {
        size_t nmatch = 1, offset = 0;
        while (regexec(&regex, str + offset, nmatch, &matchptr, 0) == 0) {
            matchptr.rm_so += offset;
            matchptr.rm_eo += offset;
            if (matchptr.rm_eo > (regoff_t)len)
                    break;
            if (matchptr.rm_eo <= (regoff_t)len) {
                for (int i = matchptr.rm_so; i < matchptr.rm_eo; i++) {
                    printf("%c", str[i]);
                }
                printf("\n");
            }
            offset = matchptr.rm_eo;
        }
    }
    regfree(&regex);
}

void keyw_from_file(spis **lst, char *argv[], spis *f_lst) {
    f_lst = f_lst->ptr;
    while (f_lst) {
        FILE *f;
        if ((f = fopen(f_lst->data, "r")) == NULL) {
            printf("%s: %s: %s\n", argv[0], f_lst->data, strerror(errno));
            exit(1);
        } else {
            char str[BUFF];
            while (fgets(str, BUFF - 1, f)) {
                if (strlen(str) > 2) {
                    if (str[strlen(str) - 1] == '\n')
                        str[strlen(str) - 1] = '\0';
                }
                *lst = addelem(*lst, str);
            }
            fclose(f);
        }
        f_lst = f_lst->ptr;
    }
}

spis *init(char *template) {
    struct list *lst;
    lst = (struct  list*)malloc(sizeof(struct list));
    strcpy(lst->data, template);
    lst->ptr = NULL;
    return(lst);
}

spis *addelem(spis *lst, char *template) {
    struct list *temp = init(template);
    lst->ptr = temp;
    return(lst->ptr);
}

spis *delete_list(spis *head) {
    while (head != NULL) {
        spis *p = head;
        head = head->ptr;
        free(p);
    }
    return NULL;
}

int count_file(spis *head) {
    int count = 0;
    while (head != NULL) {
        count++;
        head = head->ptr;
    }
    return count;
}
