defmodule NifTestTest do
  use ExUnit.Case

  test "c nifs work" do
    assert NifTest.fast_compare(1, 2) == -1
    assert NifTest.fast_compare(1, 1) == 0
    assert NifTest.fast_compare(2, 1) == 1
  end

  test "zig nifs work" do
    assert ZigNifTest.zig_compare(1, 2) == -1
    assert ZigNifTest.zig_compare(1, 1) == 0
    assert ZigNifTest.zig_compare(2, 1) == 1
  end
end
