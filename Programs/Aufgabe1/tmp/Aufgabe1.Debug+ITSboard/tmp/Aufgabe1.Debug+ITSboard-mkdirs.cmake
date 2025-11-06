# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "/Users/ramin/Desktop/GS_Neu/ITS-BRD-VSC/Programs/Aufgabe1/tmp/Aufgabe1.Debug+ITSboard")
  file(MAKE_DIRECTORY "/Users/ramin/Desktop/GS_Neu/ITS-BRD-VSC/Programs/Aufgabe1/tmp/Aufgabe1.Debug+ITSboard")
endif()
file(MAKE_DIRECTORY
  "/Users/ramin/Desktop/GS_Neu/ITS-BRD-VSC/Programs/Aufgabe1/tmp/1"
  "/Users/ramin/Desktop/GS_Neu/ITS-BRD-VSC/Programs/Aufgabe1/tmp/Aufgabe1.Debug+ITSboard"
  "/Users/ramin/Desktop/GS_Neu/ITS-BRD-VSC/Programs/Aufgabe1/tmp/Aufgabe1.Debug+ITSboard/tmp"
  "/Users/ramin/Desktop/GS_Neu/ITS-BRD-VSC/Programs/Aufgabe1/tmp/Aufgabe1.Debug+ITSboard/src/Aufgabe1.Debug+ITSboard-stamp"
  "/Users/ramin/Desktop/GS_Neu/ITS-BRD-VSC/Programs/Aufgabe1/tmp/Aufgabe1.Debug+ITSboard/src"
  "/Users/ramin/Desktop/GS_Neu/ITS-BRD-VSC/Programs/Aufgabe1/tmp/Aufgabe1.Debug+ITSboard/src/Aufgabe1.Debug+ITSboard-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/ramin/Desktop/GS_Neu/ITS-BRD-VSC/Programs/Aufgabe1/tmp/Aufgabe1.Debug+ITSboard/src/Aufgabe1.Debug+ITSboard-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/ramin/Desktop/GS_Neu/ITS-BRD-VSC/Programs/Aufgabe1/tmp/Aufgabe1.Debug+ITSboard/src/Aufgabe1.Debug+ITSboard-stamp${cfgdir}") # cfgdir has leading slash
endif()
