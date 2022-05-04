#include <assert.h>
#include "test.h"
#include "stdlib.h"

int run_all (){
    int  run_all                ();
    void test_create            ();
    void test_setup_all         ();
    void test_check_setup_all   ();
    void test_setup             ();
    void test_find              ();
    void test_err               ();

    return 0;
}

void test_err (){
    bitset_t* bitset = bit_ctor (128);

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
    bitset_t* bitset = bit_ctor (0);
    assert (bitset == NULL);
    assert (bit_dtor (bitset) == INV_SET);
    bitset = bit_ctor (128);
    assert (bit_cap (bitset) == 128);
    assert (bit_dtor (bitset) != INV_ARR);




}