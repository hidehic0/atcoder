{
  lib,
  stdenv,
  ...
}:
let
  version = "0.19.5";
  src = builtins.fetchTarball {
    url = "https://github.com/exaloop/codon/releases/download/v${version}/codon-linux-x86_64.tar.gz";
    sha256 = "sha256:05b7gp571bwwjsd96gvfxzvg20708272cw1srxws83gb5z162scq";
  };
in
stdenv.mkDerivation {
  name = "codon";
  version = version;
  src = src;
  installPhase = ''
    mkdir -p $out
    cp -r bin $out/bin
    cp -r include $out/include
    cp -r lib $out/lib
    cp -r lib64 $out/lib64
  '';
  meta = {
    description = "High-performance, zero-overhead, extensible Python compiler using LLVM";
    homepage = "https://docs.exaloop.io/codon";
    maintainers = [ ];
    license = lib.licenses.asl20;
    platforms = [ "x86_64-linux" ];
  };
}
