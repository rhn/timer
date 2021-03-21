cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(timer-controls)

set(QT_MIN_VERSION "5.6.0")
set(KF5_MIN_VERSION "5.2.0")

LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
find_package(ECM 1.0.0 NO_MODULE)
if (ECM_FOUND)
    LIST(APPEND CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR})
    include(KDEInstallDirs)
    include(KDECMakeSettings)
    include(KDECompilerSettings NO_POLICY_SCOPE)
    include(ECMPoQmTools)
else()
    cmake_policy(SET CMP0063 NEW)
    cmake_policy(SET CMP0071 NEW)
    enable_testing()
    set(CMAKE_AUTOMOC ON)
endif()

set(CMAKE_AUTOUIC ON)

include(FeatureSummary)

find_package(Cargo REQUIRED)
find_package(Rust REQUIRED)
find_package(rqbg "0.5.0" REQUIRED)
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
find_package(Threads REQUIRED)

# Runtime information library -- dl on Debian, execinfo on FreeBSD.
# This quiets a warning from rustc about linking to native artifacts.
if (CMAKE_SYSTEM MATCHES "FreeBSD")
    set(NEED_DL_LIBRARY true)
    find_library(DL_LIBRARY execinfo)
elseif (DEFINED CMAKE_DL_LIBS)
    set(NEED_DL_LIBRARY true)
    find_library(DL_LIBRARY ${CMAKE_DL_LIBS})
endif()

# It would be neater to use set_package_properties() here and to
# rely on feature_summary(), below, but that entails using find_package()
# and moving this whole thing into a Find-module, which is over-wrought.
if (NEED_DL_LIBRARY AND NOT DL_LIBRARY)
    message(FATAL_ERROR "No runtime information library (-ldl or -lexecinfo)")
endif()

# Find Qt modules
find_package(Qt5 ${QT_MIN_VERSION} CONFIG
    REQUIRED COMPONENTS
        Core
        Qml
        Quick
        Widgets
)
find_package(Qt5QuickControls2 EXACT ${Qt5Core_VERSION})

find_package(SQLite3)
#find_package(KF5Kirigami2)

include(WrapCargo)

SET(RUST_DIR "${CMAKE_CURRENT_SOURCE_DIR}/rust")
set(RUST_LIB "${RUST_BIN_DIR}/librust.a")

set(RQBG_GENERATED_DIR "${CMAKE_CURRENT_BINARY_DIR}")

add_custom_command(
  OUTPUT "${CARGO_TARGET_DIR}/src/interface.rs" "${RQBG_GENERATED_DIR}/bindings.h" "${RQBG_GENERATED_DIR}/bindings.cpp"
  COMMAND "${rqbg_EXECUTABLE}" --destination . --cargo-toml "${RUST_DIR}/Cargo.toml" "${CMAKE_CURRENT_SOURCE_DIR}/bindings.yaml"
  DEPENDS bindings.yaml
  WORKING_DIRECTORY "${RQBG_GENERATED_DIR}"
)

set(RUST_DEPS
    rust/src/database.rs
    rust/src/implementation.rs
    rust/src/interface.rs
    rust/src/lib.rs
    rust/src/schema.rs
    rust/Cargo.toml
    rust/Cargo.lock
    "${CARGO_TARGET_DIR}/src/interface.rs"
)

add_cargo_build(
    OUTPUT "${RUST_LIB}"
    FLAG "${RUST_BUILD_FLAG}"
    DEPENDS "${RUST_DEPS}"
)
add_custom_target(rust_lib DEPENDS "${RUST_LIB}")

set(SRCS
  main.cpp
  #entrymodel.cpp
  stopwatch.cpp
  "${RQBG_GENERATED_DIR}/bindings.cpp"
  "${RQBG_GENERATED_DIR}/bindings.h"
)
add_executable(timer-controls ${SRCS})

add_dependencies(timer-controls rust_lib)

list(APPEND Libs "${RUST_LIB}")
list(APPEND Libs Qt5::Core Qt5::Quick Qt5::Widgets ${CMAKE_DL_LIBS} pthread sqlite3)
target_link_libraries(timer-controls ${Libs})
target_include_directories(timer-controls PRIVATE "${RQBG_GENERATED_DIR}")
target_include_directories(timer-controls PRIVATE "${CMAKE_INCLUDE_PATH}")
target_include_directories(timer-controls PRIVATE "${CMAKE_INCLUDE_PATH}/date")

set_target_properties(timer-controls PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

install(TARGETS timer-controls)

if (ECM_FOUND)
    install(FILES org.kde.rq_bindgen.appdata.xml
            DESTINATION ${KDE_INSTALL_METAINFODIR})
endif()

# Data

include(GNUInstallDirs)

set(INSTALL_DATADIR "${CMAKE_INSTALL_DATADIR}/timer-controls")
add_compile_definitions(QML_DIR="${CMAKE_INSTALL_PREFIX}/${INSTALL_DATADIR}/ui")

install(FILES
  ui/main.qml
  ui/EditableCell.qml
  DESTINATION "${INSTALL_DATADIR}/ui"
)
