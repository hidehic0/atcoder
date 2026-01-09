{lib,rustPlatform,fetchFromGitHub,...}:
let 
version = "0.3.1";
in
  rustPlatform.buildRustPackage {
    pname = "pahcer";
    version = "v${version}";
    src = fetchFromGitHub{
      owner = "terry-u16";
      repo= "pahcer";
      tag = "v${version}";
      hash = "sha256-LNQsmAvoAbWipdI9MZfeZfQ8826Dz0EzwjvHiICfFec";
    };
    cargoHash="sha256-kcDBrcEkx+ouxB9wQZsQ7bGplaYQ56c7LS186DRCXDs";
    meta =  {
      description= "A tool to run tests for AtCoder Heuristic Contest (AHC)";
      homepage = "https://github.com/terry-u16/pahcer";
      license = with lib.licenses; [
        mit
        asl20
      ];
    };
  }
