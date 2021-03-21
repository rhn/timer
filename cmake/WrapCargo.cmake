# Set all necessary path variables to make Cargo cooperate with the rest
# Avoid building Rust stuff inside sources
SET(CARGO_TARGET_DIR "${CMAKE_BINARY_DIR}/rust")

string(TOUPPER "${CMAKE_BUILD_TYPE}" CMAKE_BUILD_TYPE_UPPER)
if(CMAKE_BUILD_TYPE_UPPER STREQUAL RELEASE)
    set(RUST_TARGET_DIR "release/")
    set(RUST_BUILD_FLAG "--release")
else()
    set(RUST_TARGET_DIR "debug/")
    set(RUST_BUILD_FLAG "")
endif()

SET(RUST_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
SET(RUST_BIN_DIR "${CARGO_TARGET_DIR}/${RUST_TARGET_DIR}")


# needs RUST_LIB and RUST_DIR
function(add_cargo_build _ OUTPUT _ RUST_BUILD_FLAG _ DEPENDS)
    add_custom_command(
      OUTPUT "${RUST_LIB}"
      COMMAND env CARGO_TARGET_DIR="${CARGO_TARGET_DIR}" "${Cargo_EXECUTABLE}" build "${RUST_BUILD_FLAG}"
      DEPENDS "${DEPENDS}"
      WORKING_DIRECTORY "${RUST_DIR}"
    )
endfunction()
