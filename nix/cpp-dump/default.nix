{
  lib,
  stdenv,
  fetchFromGitHub,
  ...
}:
stdenv.mkDerivation {
  name = "cpp-dump";
  src = fetchFromGitHub {
    owner = "philip82148";
    repo = "cpp-dump";
    rev = "aabd98dd8a4b5ae3f62cf12387a68a9f6591197e";
    hash = "sha256-VRHbY34BL602BmseXcF4jvqx3Ni+07ZSH/U6JO15LGo=";
  };
  installPhase = ''
    mkdir -p $out/include/cpp-dump
    cp cpp-dump.hpp $out/include/cpp-dump
    cp -r cpp-dump $out/include/cpp-dump
  '';

  meta = {
    description = "A C++ library for debugging purposes that can print any variable, even user-defined types.";
    homepage = "https://github.com/philip82148/cpp-dump";
    license = lib.licenses.mit;
  };
}
