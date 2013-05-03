#include <stdio.h>
#include <string.h>
#include <stdlib.h>

inline char max(char a, char b) {
    return (a > b)? a : b;
}

int boyer_moore(char *orig, char *match, char *bad_char, char *good_suffix) {
    int orig_len = strlen(orig);
    int match_len = strlen(match);
    if (orig_len < match_len) return -1;
    
    int idx = match_len - 1; /* left alignment and start with the end of match str */
    int sub_idx = idx; /* idx on match str */
    int idx_shift = 0;

    while (idx < orig_len && sub_idx >= 0) {
        for (; (orig[idx] == match[sub_idx]) && (sub_idx >= 0); sub_idx --, idx--);
        /* shift = bad char position - last occurance in match str */
        if (sub_idx < (match_len - 1)) {
            /* good suffix */
            idx_shift = max(sub_idx - bad_char[orig[idx]], 
            sub_idx - good_suffix[match_len - sub_idx - 1]);
            sub_idx = match_len - 1;
        } else {
            idx_shift = sub_idx - bad_char[orig[idx]];
            idx += (idx_shift); 
        }
        if (idx_shift == 0)
            return idx;
    }


    return 0;
}

void gen_bad_char_table(char *match, char *table) {
    int str_len = strlen(match);
    int i = 0;
    for (i = str_len - 1; i >= 0; i--) {
        if (table[match[i]] == -1)
            table[match[i]] = i;
    }
}

void gen_good_suffix_table(char *match, char *table) {
    int len = strlen(match);
    int i = 0, j = 0;
    char * suffixp = NULL;
    char * posp = NULL;
    /* iterate suffix length */
    for (i = 1; i < len; i++) {
        suffixp = match + len - i; 
        for (j = (len - i - 1); j >= 0; j--) {
            posp = match + j;
            if (strncmp(suffixp, posp, i) == 0) {
                table[i - 1] = j;
                break;
            }
        }
    }
}

int main(void) {
    char *orig = "HERE IS A SIMPLE EXAMPLE";
    char *match = "EXAMPLE";
    /* ASCII 127 Chararcters */
    char *bad_char_table = malloc(127 * sizeof(char));
    memset(bad_char_table, -1, 127);
    char *good_suffix_table = malloc(strlen(match) * sizeof(char));
    memset(good_suffix_table, -1, strlen(match));

    gen_bad_char_table(match, bad_char_table);
    gen_good_suffix_table(match, good_suffix_table);
    int ret = boyer_moore(orig, match, bad_char_table, good_suffix_table);
    printf("result %d\n", ret);

    free(bad_char_table);
    free(good_suffix_table);
    return 0;
}
