#include <inttypes.h>
#include <stdlib.h>

#define ERL_NIF_MAJOR_VERSION 2
#define ERL_NIF_MINOR_VERSION 15
#define ERL_NIF_VM_VARIANT "beam.vanilla" 
#define ERL_NIF_MIN_ERTS_VERSION "erts-10.4"

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

static ErlNifTerm
fast_compare(ErlNifEnv *env, int argc, const ErlNifTerm argv[]) {
  // cool stuff here

  int a, b;
  // Fill a and b with the values of the first two args
  enif_get_int(env, argv[0], &a);
  enif_get_int(env, argv[1], &b);

  // Usual C unreadable code because this way is more true
  int result = a == b ? 0 : (a > b ? 1 : -1);

  return enif_make_int(env, result);
}

// Let's define the array of ErlNifFunc beforehand:
static ErlNifFunc nif_funcs[] = {
  // {erl_function_name, erl_function_arity, c_function}
  {"fast_compare", 2, fast_compare}
};

typedef int ErlNifEvent;
typedef struct
{
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

ErlNifEntry* nif_init(void);
ErlNifEntry* nif_init(void){
  static ErlNifEntry entry = {
    ERL_NIF_MAJOR_VERSION,
    ERL_NIF_MINOR_VERSION,
    "Elixir.NifTest",
    sizeof(nif_funcs) / sizeof(*nif_funcs),
    nif_funcs,
    NULL, NULL, NULL, NULL,
    ERL_NIF_VM_VARIANT,
    1,                             
    sizeof(ErlNifResourceTypeInit),
    ERL_NIF_MIN_ERTS_VERSION       
  };                                
  return &entry;
}
