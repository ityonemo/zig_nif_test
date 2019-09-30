#ifndef ZIG_NIF_H
#define ZIG_NIF_H

#define ERL_NIF_MAJOR_VERSION 2
#define ERL_NIF_MINOR_VERSION 15
#define ERL_NIF_VM_VARIANT "beam.vanilla" 
#define ERL_NIF_MIN_ERTS_VERSION "erts-10.4"

typedef unsigned long long uint64_t;
typedef unsigned long long size_t;

struct enif_environment_t;
typedef struct enif_environment_t ErlNifEnv;
typedef uint64_t ErlNifTerm;

typedef struct enif_func_t
{
    const char* name;
    unsigned arity;
    ErlNifTerm (*fptr)(ErlNifEnv* env, int argc, const ErlNifTerm argv[]);
    unsigned flags;
}ErlNifFunc;

extern int enif_get_int(ErlNifEnv*, ErlNifTerm term, int* ip);
extern ErlNifTerm enif_make_int(ErlNifEnv* env, int i);

typedef int ErlNifEvent;

typedef struct {
    ErlNifTerm pid;  /* internal, may change */
} ErlNifPid;

typedef struct {
    unsigned char data[sizeof(void *)*4];
} ErlDrvMonitor;

typedef void ErlNifResourceDtor(ErlNifEnv*, void*);
typedef void ErlNifResourceStop(ErlNifEnv*, void*, ErlNifEvent, int is_direct_call);
typedef void ErlNifResourceDown(ErlNifEnv*, void*, ErlNifPid*, ErlDrvMonitor*);

typedef struct {
    ErlNifResourceDtor* dtor;
    ErlNifResourceStop* stop;  /* at ERL_NIF_SELECT_STOP event */
    ErlNifResourceDown* down;  /* enif_monitor_process */
} ErlNifResourceTypeInit;

typedef struct enif_entry_t
{
    int major;
    int minor;
    const char* name;
    int num_of_funcs;
    ErlNifFunc* funcs;
    int  (*load)   (ErlNifEnv*, void** priv_data, ErlNifTerm load_info);
    int  (*reload) (ErlNifEnv*, void** priv_data, ErlNifTerm load_info);
    int  (*upgrade)(ErlNifEnv*, void** priv_data, void** old_priv_data, ErlNifTerm load_info);
    void (*unload) (ErlNifEnv*, void* priv_data);

    /* Added in 2.1 */
    const char* vm_variant;

    /* Added in 2.7 */
    unsigned options;   /* Unused. Can be set to 0 or 1 (dirty sched config) */

    /* Added in 2.12 */
    size_t sizeof_ErlNifResourceTypeInit;

    /* Added in 2.14 */
    const char* min_erts;
}ErlNifEntry;

#endif
