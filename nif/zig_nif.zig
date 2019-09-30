const c = @cImport({
    @cInclude("/home/ityonemo/code/nif_test/nif/zig_nif_z.h");
});

extern fn zig_compare(env: ?*c.ErlNifEnv, argc: c_int, argv: [*c] const u64) u64 {
    var a: c_int = 0;
    var b: c_int = 0;
    var res: c_int = 0;

    res = c.enif_get_int(env, argv[0], &a);
    res = c.enif_get_int(env, argv[1], &b);

    var result: c_int = 0;
    
    if (a > b) {
        result = 1; 
    } else if (a <  b) {
        result = -1;
    }

    return c.enif_make_int(env, result);
}

var exported_nifs = [1] c.ErlNifFunc{
    c.ErlNifFunc{
        .name = c"zig_compare",
        .arity = 2,
        .fptr = zig_compare,
        .flags = 0,
    }
};

const entry = c.ErlNifEntry{
    .major = 2,
    .minor = 15,
    .name = c"Elixir.ZigNifTest",
    .num_of_funcs = 1,
    .funcs = &(exported_nifs[0]),
    .load = null,
    .reload = null,
    .upgrade = null,
    .unload = null,
    .vm_variant = c"beam.vanilla",
    .options = 1,
    .sizeof_ErlNifResourceTypeInit = 24,
    .min_erts = c"erts-10.4"
};

export fn nif_init() *const c.ErlNifEntry{
    return &entry;
}