#include "../include/bit_array.h"


struct bitset{
    int*           set;
    unsigned long  cap;
}; 


err_t check_bitset (bitset_t* bitset){
    if (bitset == NULL) return INV_SET;

    if (bitset->set == NULL){
        free (bitset);
        return INV_ARR;
    }

    if (bitset->cap % ELEM) return INV_CAP;
    if (bitset->cap < 1)    return INV_CAP;

    return OK;
}

bitset_t* bit_ctor (unsigned long cap){
    if (cap < 1) return NULL;

    unsigned long num = 0; 
    bitset_t* bitset = (bitset_t*) calloc (1, sizeof (bitset_t));

    if (bitset == NULL) return NULL;

    if (cap % ELEM == 0) num = cap / ELEM;

    else num = cap / ELEM + 1;

    int* set = (int*) calloc (num, sizeof (int));

    if (set == NULL) {
        free (bitset);
        return NULL;
    }

    bitset->set = set;
    bitset->cap = num * ELEM;

    return bitset;
}

err_t bit_dtor (bitset_t* bitset){
    if (bitset == NULL) return INV_SET;
    if (bitset->set == NULL){
        free (bitset);
        return INV_ARR;
    }

    free (bitset->set);
    bitset->set = NULL;
    bitset->cap = 0;
    free (bitset);

    return OK;
}

unsigned long bit_cap (bitset_t* bitset){
    err_t err = OK;
    if ((err = check_bitset (bitset)) != OK) return err;

    return bitset->cap; 
}

err_t bit_set_all (bitset_t* bitset){
    err_t err = OK;
    if ((err = check_bitset (bitset)) != OK) return err; 

    for (unsigned long i = 0; i < bitset->cap / ELEM; i++){
        bitset->set[i] = ULONG_MAX;
    }

    return OK;
}

err_t bit_unset_all (bitset_t* bitset){
    err_t err = OK;
    if ((err = check_bitset (bitset)) != OK) return err; 

    for (unsigned long i = 0; i < bitset->cap / ELEM; i++){
        bitset->set[i] = UNSET;
    }

    return OK;
}

err_t bit_set_val_all (bitset_t* bitset, bit_t val){
    err_t err = OK;
    if ((err = check_bitset (bitset)) != OK) return err;  

    if (val == SET) return bit_set_all (bitset);

    else if (val == UNSET) return bit_unset_all (bitset);

    else return INV_VAL;
}

err_t bit_check_set_all (bitset_t* bitset){
    err_t err = OK;
    if ((err = check_bitset (bitset)) != OK) return err;

    for (unsigned long i = 0; i < bitset->cap / ELEM; i++){
        if (bitset->set[i] != ULONG_MAX) return 0;
    }
    
    return 1;
}

err_t bit_check_unset_all (bitset_t* bitset){
    err_t err = OK;
    if ((err = check_bitset (bitset)) != OK) return err;

    for (unsigned long i = 0; i < bitset->cap / ELEM; i++){
        if (bitset->set[i]) return 0;
    }
    
    return 1; 
}

err_t bit_check_set_any (bitset_t* bitset){
    err_t err = OK;
    if ((err = check_bitset (bitset)) != OK) return err;

    for (unsigned long i = 0; i < bitset->cap / ELEM; i++){
        if (bitset->set[i]) return 1;
    }
    
    return 0;
}

err_t bit_rvs (bitset_t* bitset){
    err_t err = OK;
    if ((err = check_bitset (bitset)) != OK) return err;

    for (unsigned long i = 0; i < bitset->cap / ELEM; i++){
        bitset->set[i] = ~bitset->set[i];
    }

    return OK;
}

err_t bit_set (bitset_t* bitset, int pos){
    if (pos < 0 || pos >= bitset->cap) return INV_POS;

    err_t err = OK;
    if ((err = check_bitset (bitset)) != OK) return err; 

    int* ptr = bitset->set + pos / ELEM;
    int bit = 1;
    bit = bit << (pos % ELEM);
    *ptr = *ptr | bit;

    return OK;
}

err_t bit_unset (bitset_t* bitset, int pos){
    if (pos < 0 || pos >= bitset->cap) return INV_POS;

    err_t err = OK;
    if ((err = check_bitset (bitset)) != OK) return err; 

    int* ptr = bitset->set + pos / ELEM;
    int  bit = 1;
    
    bit = bit << (pos % ELEM); 
    bit = ~bit;
    *ptr = *ptr & bit;

    return OK;
}

err_t bit_set_val (bitset_t* bitset, int pos, bit_t val){
    if (pos < 0 || pos >= bitset->cap) return INV_POS;

    err_t err = OK;
    if ((err = check_bitset (bitset)) != OK) return err; 

    if (val == SET) return bit_set (bitset, pos);
    
    else if (val == UNSET) return bit_unset (bitset, pos);

    else return INV_VAL;
}

int bit_get (bitset_t* bitset, int pos){
    if (pos < 0 || pos >= bitset->cap) return INV_POS;

    err_t err = OK;
    if ((err = check_bitset (bitset)) != OK) return err; 

    int bit = 1;
    bit = bit << pos % ELEM;

    if (bitset->set[pos / ELEM] & bit) return SET;

    return UNSET;
}

int bit_count (bitset_t* bitset){
    err_t err = OK;
    if ((err = check_bitset (bitset)) != OK) return err;

    int res = 0;

    for (unsigned long i = 0; i < bitset->cap / ELEM; i++){
        if (!bitset->set[i]) continue;

        for (int j = 0; j < ELEM; j++){
            if (bitset->set[i] & (1 << j)) res++;
        }
    }

    return res;
}

int bit_find_first_set (bitset_t* bitset){
    err_t err = OK;
    if ((err = check_bitset (bitset)) != OK) return err; 
    
    for (;;){

    }
}

int bit_find_fisrt_unset (bitset_t* bitset){
    err_t err = OK;
    if ((err = check_bitset (bitset)) != OK) return err;

    for (;;){

    }
}

int bit_find_last_set (bitset_t* bitset){
    err_t err = OK;
    if ((err = check_bitset (bitset)) != OK) return err;

    for (;;){

    }
}

int bit_find_last_unset (bitset_t* bitset){
    err_t err = OK;
    if ((err = check_bitset (bitset)) != OK) return err;

    for (;;){

    }
}

err_t dump_bitset (bitset_t* bitset, const char* path){
    err_t err = OK;
    if ((err = check_bitset (bitset)) != OK) return err;

}
