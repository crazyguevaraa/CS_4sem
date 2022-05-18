#include <assert.h>
#include <stdlib.h>
#include "../include/bit_array.h"
#include "test.h"

void run_all (){
    void test_create            ();
    void test_setup_all         ();
    void test_check_setup_all   ();
    void test_setup             ();
    void test_find              ();
    void test_err               ();
}

void test_err (){
    bitset_t bitset = bit_ctor (128);

    assert (bitset != NULL);
    assert (bit_set_all (bitset) == OK);
    assert (bit_unset_all (bitset) == OK);
    assert (bit_set_val_all (bitset, -1) == INV_VAL);
    assert (bit_set_val_all (bitset, SET) == OK);
    assert (bit_check_set_all (bitset) == 1);
    assert (bit_set_val_all (bitset, UNSET) == OK);
    assert (bit_check_set_all (bitset) == 0);
    assert (bit_check_set_any (bitset) == 0);
    assert (bit_rvs (bitset) == OK);
    assert (bit_check_set_any (bitset) == 1); 
    assert (bit_set (bitset, -128) == INV_POS);
    assert (bit_set (bitset, 129) == INV_POS);
    assert (bit_unset (bitset, 64) == OK);
    assert (bit_unset (bitset, -128) == INV_POS);
    assert (bit_unset (bitset, 129) == INV_POS);
    assert (bit_set_val (bitset, 64, UNSET) == OK);
    assert (bit_set_val (bitset, -1, SET) == INV_POS);
    assert (bit_set_val (bitset, 129, SET) == INV_POS);
    assert (bit_set_val (bitset, 64, -1) == INV_VAL);
    assert (bit_get (bitset, -1) == INV_POS);
    assert (bit_get (bitset, 164) == INV_POS); 

    assert (bit_dtor (bitset) == OK);
    
    
}

void test_create (){
    bitset_t bitset = bit_ctor (0);

    assert (bitset == NULL);
    assert (bit_dtor (bitset) == INV_SET);

    bitset = bit_ctor (128);
    assert (bit_cap (bitset) == 128);
    assert (bit_dtor (bitset) != INV_ARR);
    
    bitset = bit_ctor (68);
    assert (bit_cap (bitset) > 68);
    bit_dtor (bitset);
}

void test_setup_all (){
    bitset_t bitset = bit_ctor (128);
    
    assert (bit_set_all (bitset) == OK);
    for (size_t i = 0; i < bitset->cap / ELEM; i++){
            assert (bitset->set[i]);
    }
    
    assert (bit_unset_all (bitset) == OK);
    for (size_t i = 0; i < bitset->cap / ELEM; i++){
        assert (!bitset->set[i]);
    }

    assert (bit_set_val_all (bitset, SET) == OK);
    for (size_t i = 0; i < bitset->cap / ELEM; i++){
            assert (bitset->set[i]);
    }
    
    assert (bit_set_val_all (bitset, UNSET) == OK);
    for (size_t i = 0; i < bitset->cap / ELEM; i++){
        assert (!bitset->set[i]);
    }

    assert (bit_rvs (bitset) == OK);
    for (size_t i = 0; i < &bitset->cap / ELEM; i++){
            assert (bitset->set[i]);
    }

    assert (bit_rvs (bitset) == OK);
    for (size_t i = 0; i < bitset->cap / ELEM; i++){
            assert (!bitset->set[i]);
    }  

    bit_dtor (bitset);
}

void test_setup (){
    bitset_t bitset = bit_ctor (128);


}

void test_check_setup_all (){

}

void test_find (){

    bitset_t bitset = bit_ctor (10);

    assert (bit_find_set (NULL, 0, 3) == FAIL);
    assert (bit_find_unset (NULL, 0, 3) == FAIL);

    bit_unset_all (bitset);

    bit_set (bitset, 4);
    bit_set (bitset, 6);
    assert (bit_find_set (bitset, 0, 6) == 4);
    assert (bit_find_set (bitset, 3, 7) == 4);
    
    bit_rvs (bitset);
    assert (bit_find_unset (bitset, 0, 5) == 4);
    assert (bit_find_unset (bitset, 3, 7) == 4); 

    bit_dtor (bitset);


}