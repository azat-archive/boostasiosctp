
cmake_minimum_required(VERSION 2.6)

find_package(Boost REQUIRED COMPONENTS system unit_test_framework test_exec_monitor)

include_directories("../../../")
add_definitions(-DBOOST_ASIO_HAVE_SCTP)

function(FindLibraryOrFatalError libraryName)
    unset(LIBRARY CACHE)
    find_library(LIBRARY NAMES ${libraryName})

    if(LIBRARY)
        message(STATUS "Looking for ${libraryName} - found")
    else(LIBRARY)
        message(FATAL_ERROR "Looking for ${libraryName} - not found")
    endif(LIBRARY)

    # In global scope
    set(LIBS ${LIBS} ${LIBRARY} PARENT_SCOPE)
endfunction(FindLibraryOrFatalError)

macro(FindLibrariesOrFatalError _libraries_string)
    string(REPLACE " " ";" _libraries ${_libraries_string})
    foreach(_library ${_libraries})
        FindLibraryOrFatalError("${_library}" _good)
    endforeach(_library)
endmacro(FindLibrariesOrFatalError)

FindLibrariesOrFatalError("boost_system boost_unit_test_framework sctp boost_test_exec_monitor")

list(APPEND SOURCES "is_write_buffered.cpp")
add_executable(is_write_buffered ${SOURCES})
target_link_libraries(is_write_buffered ${LIBS})
