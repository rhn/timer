CARGO_TARGET_DIR=$(pwd)
cd $1/rust
CARGO_TARGET_DIR=${CARGO_TARGET_DIR} cargo build
