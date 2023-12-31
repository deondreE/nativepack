# Clean for pushing to GitHub.
cd ../
# builds
rm -rf ./main
# ninja
rm -rf .ninja_deps .ninja_log build.ninja
# cmake
rm -rf cmake_install.cmake CMakeCache.txt CMakeFiles/ .cmake/ Testing/

# github
git add -A
