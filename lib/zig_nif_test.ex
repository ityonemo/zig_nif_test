defmodule ZigNifTest do

  @on_load :load_nifs

  def load_nifs do
    System.cmd("zig", ~w(build-lib zig_nif.zig -dynamic --disable-gen-h), cd: "nif")
    File.cp("nif/libzig_nif.so.0.0.0", "priv/nif/fast_compare2.so")
    File.rm_rf!("nif/libzig_nif.so.0.0.0")
    Process.sleep(100)
    :erlang.load_nif('priv/nif/fast_compare2', 0)
  end

  def zig_compare(_a, _b) do
    raise "NIF zig_compare/2 not implemented"
  end

end
