if("master" STREQUAL "")
  message(FATAL_ERROR "Tag for git checkout should not be empty.")
endif()

set(run 0)

if("G:/SD_Engine/SDEngine/Assimp/binaries/test/gtest/src/gtest-stamp/gtest-gitinfo.txt" IS_NEWER_THAN "G:/SD_Engine/SDEngine/Assimp/binaries/test/gtest/src/gtest-stamp/gtest-gitclone-lastrun.txt")
  set(run 1)
endif()

if(NOT run)
  message(STATUS "Avoiding repeated git clone, stamp file is up to date: 'G:/SD_Engine/SDEngine/Assimp/binaries/test/gtest/src/gtest-stamp/gtest-gitclone-lastrun.txt'")
  return()
endif()

execute_process(
  COMMAND ${CMAKE_COMMAND} -E remove_directory "G:/SD_Engine/SDEngine/Assimp/binaries/test/gtest/src/gtest"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to remove directory: 'G:/SD_Engine/SDEngine/Assimp/binaries/test/gtest/src/gtest'")
endif()

set(git_options)

# disable cert checking if explicitly told not to do it
set(tls_verify "")
if(NOT "x" STREQUAL "x" AND NOT tls_verify)
  list(APPEND git_options
    -c http.sslVerify=false)
endif()

set(git_clone_options)

set(git_shallow "")
if(git_shallow)
  list(APPEND git_clone_options --depth 1 --no-single-branch)
endif()

# try the clone 3 times incase there is an odd git clone issue
set(error_code 1)
set(number_of_tries 0)
while(error_code AND number_of_tries LESS 3)
  execute_process(
    COMMAND "C:/Program Files/Git/cmd/git.exe" ${git_options} clone ${git_clone_options} --origin "origin" "https://github.com/google/googletest.git" "gtest"
    WORKING_DIRECTORY "G:/SD_Engine/SDEngine/Assimp/binaries/test/gtest/src"
    RESULT_VARIABLE error_code
    )
  math(EXPR number_of_tries "${number_of_tries} + 1")
endwhile()
if(number_of_tries GREATER 1)
  message(STATUS "Had to git clone more than once:
          ${number_of_tries} times.")
endif()
if(error_code)
  message(FATAL_ERROR "Failed to clone repository: 'https://github.com/google/googletest.git'")
endif()

execute_process(
  COMMAND "C:/Program Files/Git/cmd/git.exe" ${git_options} checkout master
  WORKING_DIRECTORY "G:/SD_Engine/SDEngine/Assimp/binaries/test/gtest/src/gtest"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to checkout tag: 'master'")
endif()

execute_process(
  COMMAND "C:/Program Files/Git/cmd/git.exe" ${git_options} submodule init 
  WORKING_DIRECTORY "G:/SD_Engine/SDEngine/Assimp/binaries/test/gtest/src/gtest"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to init submodules in: 'G:/SD_Engine/SDEngine/Assimp/binaries/test/gtest/src/gtest'")
endif()

execute_process(
  COMMAND "C:/Program Files/Git/cmd/git.exe" ${git_options} submodule update --recursive --init 
  WORKING_DIRECTORY "G:/SD_Engine/SDEngine/Assimp/binaries/test/gtest/src/gtest"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to update submodules in: 'G:/SD_Engine/SDEngine/Assimp/binaries/test/gtest/src/gtest'")
endif()

# Complete success, update the script-last-run stamp file:
#
execute_process(
  COMMAND ${CMAKE_COMMAND} -E copy
    "G:/SD_Engine/SDEngine/Assimp/binaries/test/gtest/src/gtest-stamp/gtest-gitinfo.txt"
    "G:/SD_Engine/SDEngine/Assimp/binaries/test/gtest/src/gtest-stamp/gtest-gitclone-lastrun.txt"
  WORKING_DIRECTORY "G:/SD_Engine/SDEngine/Assimp/binaries/test/gtest/src/gtest"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to copy script-last-run stamp file: 'G:/SD_Engine/SDEngine/Assimp/binaries/test/gtest/src/gtest-stamp/gtest-gitclone-lastrun.txt'")
endif()

