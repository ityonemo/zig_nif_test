# NifTest

**Just Testing Nifs in Zig**

Key files can be found in:

`nif/my_nif.c`  - demo nif in c

`nif/zig_nif.zig` - same nif in zig

`lib/nif_test.ex` - parameters for compiling the C nif

`lib/zig_nif_test.ex` - parameters for compiling the zig nif

`test/nif_test_test.exs` - tests on c and zig


Running it:

```
iex(1)> ZigNifTest.zig_compare(2, 1)
1
iex(2)> ZigNifTest.zig_compare(2, 2)
0
iex(3)> ZigNifTest.zig_compare(1, 2)
-1
```
