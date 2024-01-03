# This initializes the core project from the users input. Then Creates an xcode project to go with that process to.
echo "initializing new project"

rm -rf test_dir/
mkdir test_dir/
cd test_dir/ || exit
touch nativepack.json
cp ../input/nativepack.json nativepack.json
mkdir src/ .build/
cd src/ || exit
mkdir views/ images/ fonts/
