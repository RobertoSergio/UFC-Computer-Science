{ pkgs }: {
	deps = [
		pkgs.valgrind
  pkgs.sudo
  pkgs.clang_12
		pkgs.ccls
		pkgs.gdb
		pkgs.gnumake
	];
}