# Clean for pushing to GitHub.
cd ../
# builds
rm -rf ./main
# ninja
rm -rf .ninja_deps .ninja_log build.ninja bin/ build/
# cmake
rm -rf cmake_install.cmake CMakeCache.txt CMakeFiles/ .cmake/ Testing/ _deps/ lib/ tests[1]_include.cmake tests[1]_tests.cmake tests CTestTestfile.cmake
# testing

# github
git add -A
