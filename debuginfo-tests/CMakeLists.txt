# Debug Info tests.  These tests invoke clang to generate programs with
# various types of debug info, and then run those programs under a debugger
# such as GDB or LLDB to verify the results.

set(DEBUGINFO_TESTS_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(DEBUGINFO_TESTS_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})

set(DEBUGINFO_TEST_DEPS
  clang
  FileCheck
  count
  llvm-objdump
  not
  )

# The Windows builder scripts pass -fuse-ld=lld.
if (WIN32)
  set(DEBUGINFO_TEST_DEPS ${DEBUGINFO_TEST_DEPS} lld)
endif()

if (NOT DEFINED PYTHON_EXECUTABLE)
  message(FATAL_ERROR "Cannot run debuginfo-tests without python")
elseif(PYTHON_VERSION_MAJOR LESS 3)
  message(FATAL_ERROR "Cannot run debuginfo-tests without python 3")
else()
   configure_lit_site_cfg(
    ${CMAKE_CURRENT_SOURCE_DIR}/lit.site.cfg.py.in
    ${CMAKE_CURRENT_BINARY_DIR}/lit.site.cfg.py
    MAIN_CONFIG
    ${CMAKE_CURRENT_SOURCE_DIR}/lit.cfg.py
    )

  add_lit_testsuite(check-debuginfo "Running debug info integration tests"
    ${CMAKE_CURRENT_BINARY_DIR}
    DEPENDS ${DEBUGINFO_TEST_DEPS}
    )
  set_target_properties(check-debuginfo PROPERTIES FOLDER "Debug info tests")
endif()
