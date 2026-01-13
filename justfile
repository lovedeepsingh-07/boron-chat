BINARY := "boron"

[working-directory: "server"]
build-server:
	@just build

[working-directory: "client"]
build-client:
	@just build

build: build-server build-client
	@mkdir -p build
	@cp -r ./server/target/x86_64-pc-windows-gnu/release/{{BINARY}}_server.exe ./build/
	@cp -r ./client/build/windows/{{BINARY}}_client.exe ./build/
	@cp -r ./client/assets ./build/

[working-directory: "build"]
run component: build
	@./{{BINARY}}_{{component}}.exe

[working-directory: "build"]
runw component: build
	@wine ./{{BINARY}}_{{component}}.exe

[working-directory: "client"]
setup:
	@nix run .#setup

gen:
	@mkdir -p common/src/generated client/include/generated
	@flatc -o ./client/include/generated/ ./data/packet.fbs --cpp --filename-suffix _
	@flatc -o ./common/src/generated ./data/packet.fbs --rust --filename-suffix _

fmt:
	alejandra .
