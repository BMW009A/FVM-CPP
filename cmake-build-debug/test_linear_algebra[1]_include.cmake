if(EXISTS "C:/Users/QCZ/CLionProjects/Project-02-FVM/cmake-build-debug/test_linear_algebra[1]_tests.cmake")
  include("C:/Users/QCZ/CLionProjects/Project-02-FVM/cmake-build-debug/test_linear_algebra[1]_tests.cmake")
else()
  add_test(test_linear_algebra_NOT_BUILT test_linear_algebra_NOT_BUILT)
endif()