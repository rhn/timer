# Find the rqbg executable
#
# Defines the following variables
#  rqbg_FOUND      - True if the rqbg executable was found
#  rqbg_EXECUTABLE - path of the rqbg executable
#  rqbg_VERSION    - version number of rqbg

#=============================================================================
# Copyright 2017 Friedrich W. H. Kossebau <kossebau@kde.org>
# Copyright 2018-2020 rhn <gihu.rhn@porcupinefactory.org>
# Distributed under the OSI-approved BSD License (the "License");
# see accompanying file Copyright.txt for details.
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the License for more information.
#=============================================================================

include(FindPackageHandleStandardArgs)
find_program(rqbg_EXECUTABLE rq_bindgen)
if (rqbg_EXECUTABLE)
    execute_process(COMMAND "${rqbg_EXECUTABLE}" --version
        OUTPUT_VARIABLE rqbg_VERSION_OUTPUT
        ERROR_VARIABLE rqbg_VERSION_ERROR
        RESULT_VARIABLE rqbg_VERSION_RESULT
    )
    if(NOT ${rqbg_VERSION_RESULT} EQUAL 0)
        message(SEND_ERROR "Command \"${rqbg_EXECUTABLE} --version\" failed with output:\n${rqbg_VERSION_ERROR}")
    else()
        # TODO: support also nightly
        string(REGEX MATCH "[0-9]+\\.[0-9]+\\.[0-9]+"
            rqbg_VERSION "${rqbg_VERSION_OUTPUT}"
        )
    endif()
endif()
find_package_handle_standard_args(rqbg
    REQUIRED_VARS rqbg_EXECUTABLE)
mark_as_advanced(rqbg_EXECUTABLE)
