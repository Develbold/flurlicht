#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "pigpio::pigpio" for configuration "Release"
set_property(TARGET pigpio::pigpio APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(pigpio::pigpio PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libpigpio.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS pigpio::pigpio )
list(APPEND _IMPORT_CHECK_FILES_FOR_pigpio::pigpio "${_IMPORT_PREFIX}/lib/libpigpio.a" )

# Import target "pigpio::pigpiod_if" for configuration "Release"
set_property(TARGET pigpio::pigpiod_if APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(pigpio::pigpiod_if PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libpigpiod_if.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS pigpio::pigpiod_if )
list(APPEND _IMPORT_CHECK_FILES_FOR_pigpio::pigpiod_if "${_IMPORT_PREFIX}/lib/libpigpiod_if.a" )

# Import target "pigpio::pigpiod_if2" for configuration "Release"
set_property(TARGET pigpio::pigpiod_if2 APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(pigpio::pigpiod_if2 PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libpigpiod_if2.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS pigpio::pigpiod_if2 )
list(APPEND _IMPORT_CHECK_FILES_FOR_pigpio::pigpiod_if2 "${_IMPORT_PREFIX}/lib/libpigpiod_if2.a" )

# Import target "pigpio::pig2vcd" for configuration "Release"
set_property(TARGET pigpio::pig2vcd APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(pigpio::pig2vcd PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/pig2vcd"
  )

list(APPEND _IMPORT_CHECK_TARGETS pigpio::pig2vcd )
list(APPEND _IMPORT_CHECK_FILES_FOR_pigpio::pig2vcd "${_IMPORT_PREFIX}/bin/pig2vcd" )

# Import target "pigpio::pigpiod" for configuration "Release"
set_property(TARGET pigpio::pigpiod APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(pigpio::pigpiod PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/pigpiod"
  )

list(APPEND _IMPORT_CHECK_TARGETS pigpio::pigpiod )
list(APPEND _IMPORT_CHECK_FILES_FOR_pigpio::pigpiod "${_IMPORT_PREFIX}/bin/pigpiod" )

# Import target "pigpio::pigs" for configuration "Release"
set_property(TARGET pigpio::pigs APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(pigpio::pigs PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/pigs"
  )

list(APPEND _IMPORT_CHECK_TARGETS pigpio::pigs )
list(APPEND _IMPORT_CHECK_FILES_FOR_pigpio::pigs "${_IMPORT_PREFIX}/bin/pigs" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
