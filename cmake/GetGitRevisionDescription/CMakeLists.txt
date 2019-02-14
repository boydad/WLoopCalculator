# Make a version file containing the current version from git.
#
include(GetGitRevisionDescription.cmake)
git_describe(VERSION --tags --dirty=-dirty)

#parse the version information into pieces.
string(REGEX REPLACE "^v([0-9]+)\\..*" "\\1" VERSION_MAJOR "${VERSION}")
string(REGEX REPLACE "^v[0-9]+\\.([0-9]+).*" "\\1" VERSION_MINOR "${VERSION}")
string(REGEX REPLACE "^v[0-9]+\\.[0-9]+\\.([0-9]+).*" "\\1" VERSION_PATCH "${VERSION}")
string(REGEX REPLACE "^v[0-9]+\\.[0-9]+\\.[0-9]+(.*)" "\\1" VERSION_SHA1 "${VERSION}")
set(VERSION_SHORT "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}" CACHE INTERNAL "" FORCE)

#add TRAVIS_BUILD_NUMBER if on travis machine
if($ENV{TRAVIS_BUILD_NUMBER})
  set(VERSION_SHORT "${VERSION_SHORT}.$ENV{TRAVIS_BUILD_NUMBER}" CACHE INTERNAL "" FORCE)
endif($ENV{TRAVIS_BUILD_NUMBER})

configure_file(version.cpp.in
               ${CMAKE_CURRENT_BINARY_DIR}/version.cpp)
set(version_file "${CMAKE_CURRENT_BINARY_DIR}/version.cpp")
