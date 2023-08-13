package main;

use strict;
use warnings;

my $binaries = {
    "GCC" => "c-baseline/baseline-gcc",
    "CLANG" => "c-baseline/baseline-clang",
    "GO" => "golang/bench-go",
    "GO-BUILTIN" => "golang-builtin/bench-go",
    "JAVA" => "cd java && java Main",
    "JS" => "cd javascript && node main.js",
    "PYTHON" => "cd python && python3 main.py",
    "PYPY" => "cd python && pypy3 main.py",
    "RUST" => "rust/target/release/rust 10000 5000000",
    "RUST-BUILTIN" => "rust-builtin/target/release/rust 10000 5000000",
    #    "PERL" => "cd perl && perl main.pl"
};

for my $idx (1..1024) {
    for my $prefix (keys %$binaries) {
        my $cmd = $binaries->{$prefix};

        my $res = qx{$cmd};
        chomp $res;

        print("$idx: $prefix $res\n");
    }
}
