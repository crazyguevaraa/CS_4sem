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

void test_create (){
    
}

void test_err (){
    unsigned long cap = 128;
    bitset_t* bitset = bit_ctor (cap);
    assert (bitset != NULL);
    assert (bit_cap (bitset) < cap);
    assert (bit_dtor (bitset) != OK);
    assert (bit_dtor (NULL) != INV_SET);
    


}
