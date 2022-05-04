#pragma once 
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>

enum SIZE {
    DEFAULT = 2,
    EXTRA   = 2,
    ELEM    = 64
};

struct bitset{
    int*           set;
    unsigned long  cap;
}; 
typedef struct bitset bitset_t;

typedef enum BIT {
    SET   = 1,
    UNSET = 0
} bit_t;

typedef enum ERR {
    OK          =  0,
    NO_MATCH    = -1,
    ALLOC_ERR   = -2,
    REALLOC_ERR = -3,
    UNKNOWN_ERR = -4,
    INV_SIZE    = -5,
    INV_ARR     = -6,
    INV_CAP     = -7,
    INV_NUM     = -8,
    INV_POS     = -9,
    INV_BITARR  = -10,
    INV_VAL     = -11,
    INV_SET     = -12
} err_t;

unsigned long    bit_cap               (bitset_t *bitset);
bitset_t*        bit_ctor              (unsigned long cap);
err_t            bit_dtor              (bitset_t *bitset);
err_t            bit_set_all           (bitset_t *bitset);
err_t            bit_unset_all         (bitset_t *bitset);
err_t            bit_set_val_all       (bitset_t *bitset, bit_t val);
err_t            bit_check_set_all     (bitset_t *bitset);
err_t            bit_check_unset_all   (bitset_t *bitset);
err_t            bit_check_set_any     (bitset_t *bitset);
err_t            bit_rvs               (bitset_t *bitset);
err_t            bit_set               (bitset_t *bitset, int pos);
err_t            bit_unset             (bitset_t *bitset, int pos);
err_t            bit_set_val           (bitset_t *bitset, int pos, bit_t val);
err_t            check_bitset          (bitset_t *bitset);
err_t            dump_bitset           (bitset_t *bitset, const char *path);
int              bit_get               (bitset_t *bitset, int pos);
int              bit_count             (bitset_t *bitset);
int              bit_find_first_set    (bitset_t *bitset);
int              bit_find_first_unset  (bitset_t *bitset);
int              bit_find_last_set     (bitset_t *bitset);
int              bit_find_last_unset   (bitset_t *bitset);



