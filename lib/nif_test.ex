defmodule NifTest do

  @on_load :load_nifs

  def load_nifs do
    File.rm_rf!("priv/nif/fast_compare.so")
    File.mkdir_p("/tmp/nif")
    File.cp("nif/my_nif.c", "/tmp/nif/my_nif.c")
    System.cmd("cc", ~w(-fPIC -shared -I/usr/lib/erlang/erts-10.4.4/include/ -dynamiclib -undefined -dynamic_lookup -o fast_compare.so my_nif.c), cd: "/tmp/nif")
    File.cp("/tmp/nif/fast_compare.so", "priv/nif/fast_compare.so")
    Process.sleep(100)
    :erlang.load_nif('priv/nif/fast_compare', 0)
  end

  def fast_compare(_a, _b) do
    raise "NIF fast_compare/2 not implemented"
  end

end
