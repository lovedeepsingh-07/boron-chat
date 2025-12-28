[working-directory: "client"]
setup:
	@nix run .#setup

gen:
	@mkdir -p common/src/generated client/include/generated
	@flatc -o ./client/include/generated/ ./data/packet.fbs --cpp --filename-suffix _
	@flatc -o ./common/src/generated ./data/packet.fbs --rust --filename-suffix _
