# This initializes the core project from the users input. Then Creates an xcode project to go with that process to.
echo "initializing new project"
rm -rf test_dir/
mkdir test_dir/
cd test_dir/ ||
# TODO: Put the contents of this file inside the source.
touch project.yml
cp -a ../input/project.yml project.yml
# steps to this process.
mkdir src/ .build/
cd src/ || exit
mkdir views/ images/ fonts/
