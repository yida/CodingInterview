/* http://jakeboxer.com/blog/2009/12/13/the-knuth-morris-pratt-algorithm-in-my-own-words/ */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int partial_match_table(char *str, int *table, int size) { 
    int fix_len = 0, idx = 0;
    char *prefixp = NULL, *suffixp = NULL;
    for (fix_len = 1; fix_len < size; fix_len ++) {
        for (idx = fix_len; idx < size; idx ++) {
            prefixp = str;
            suffixp = str + idx - fix_len + 1;
            if (!strncmp(prefixp, suffixp, fix_len))
                table[idx] = fix_len;
        }
    }
    return 0;
}

int kmp_search(char *orig_str, char *match_str) {
    int match_len = strlen(match_str);
    int orig_len = strlen(orig_str);
    if (match_len > orig_len) return -1;

    /* init partial match table */
    int *pmt = (int *)malloc(match_len * sizeof(int));
    memset(pmt, 0, match_len);
    partial_match_table(match_str, pmt, match_len);

    int idx = 0, sub_idx = 0;
    /* if not matched, shift partial match table number */
    for (; sub_idx < match_len && idx <= (orig_len - match_len);
            idx = (sub_idx != 0)? idx + (sub_idx - pmt[sub_idx - 1]) : idx + 1)
        /* element-wise compare */
        for (sub_idx = 0; (strncmp(orig_str + idx + sub_idx, match_str + sub_idx, 1) == 0)
                && sub_idx < match_len; sub_idx++);
    free(pmt);
    if (sub_idx == match_len)
        return idx - sub_idx;
    else 
        return -1;
}

int main(void) {
    char *orig_str = "BBC ABCDAB ABCDABCDABDE";
    char *match_str = "ABCDABD";

    int ret = kmp_search(orig_str, match_str);
    printf("found %d\n", ret);

    return 0;
}
