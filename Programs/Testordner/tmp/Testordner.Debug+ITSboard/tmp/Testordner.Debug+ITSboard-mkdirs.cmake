# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/Users/yildirim/Desktop/ITSBoard/ITS-BRD-VSC/Programs/Testordner/tmp/Testordner.Debug+ITSboard"
  "/Users/yildirim/Desktop/ITSBoard/ITS-BRD-VSC/Programs/Testordner/tmp/1"
  "/Users/yildirim/Desktop/ITSBoard/ITS-BRD-VSC/Programs/Testordner/tmp/Testordner.Debug+ITSboard"
  "/Users/yildirim/Desktop/ITSBoard/ITS-BRD-VSC/Programs/Testordner/tmp/Testordner.Debug+ITSboard/tmp"
  "/Users/yildirim/Desktop/ITSBoard/ITS-BRD-VSC/Programs/Testordner/tmp/Testordner.Debug+ITSboard/src/Testordner.Debug+ITSboard-stamp"
  "/Users/yildirim/Desktop/ITSBoard/ITS-BRD-VSC/Programs/Testordner/tmp/Testordner.Debug+ITSboard/src"
  "/Users/yildirim/Desktop/ITSBoard/ITS-BRD-VSC/Programs/Testordner/tmp/Testordner.Debug+ITSboard/src/Testordner.Debug+ITSboard-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/yildirim/Desktop/ITSBoard/ITS-BRD-VSC/Programs/Testordner/tmp/Testordner.Debug+ITSboard/src/Testordner.Debug+ITSboard-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/yildirim/Desktop/ITSBoard/ITS-BRD-VSC/Programs/Testordner/tmp/Testordner.Debug+ITSboard/src/Testordner.Debug+ITSboard-stamp${cfgdir}") # cfgdir has leading slash
endif()
