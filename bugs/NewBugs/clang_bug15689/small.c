#include "uthash.h"

//Ambiguous

struct module {
    UT_hash_handle hh;
} *modules = NULL;

int main()
{
    struct module *mod1, *mod2;
    HASH_REPLACE_STR(modules, hh, mod1, mod2);
}
