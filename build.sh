#!/usr/bin/env bash
# Fetch the latest version of the library
fetch() {
if [ -d "plibsys" ]; then return; fi
URL="https://github.com/saprykin/plibsys/archive/refs/tags/0.0.5.zip"
ZIP="plibsys-0.0.5.zip"
DIR="${ZIP%.zip}"
mkdir -p .build
cd .build

# Download the release
if [ ! -f "$ZIP" ]; then
  echo "Downloading $ZIP from $URL ..."
  curl -L "$URL" -o "$ZIP"
  echo ""
fi

# Unzip the release
if [ ! -d "$DIR" ]; then
  echo "Unzipping $ZIP to .build/$DIR ..."
  cp "$ZIP" "$ZIP.bak"
  unzip -q "$ZIP"
  rm "$ZIP"
  mv "$ZIP.bak" "$ZIP"
  echo ""
fi
cd ..

# Copy the libs to the package directory
echo "Copying libs to plibsys/ ..."
rm -rf plibsys
mkdir -p plibsys
cp -rf ".build/$DIR/src"/*.c  plibsys/
cp -rf ".build/$DIR/src"/*.h  plibsys/
cp -rf ".build/$DIR/src"/*.in plibsys/
echo ""
}


# Test the project
test() {
echo "Running 01-thread-creation.c ..."
clang -I. -o 01.exe examples/01-thread-creation.c      && ./01.exe && echo -e "\n"
echo "Running 02-mutex-locking.c ..."
clang -I. -o 02.exe examples/02-mutex-locking.c        && ./02.exe && echo -e "\n"
echo "Running 03-condition-variables.c ..."
clang -I. -o 03.exe examples/03-condition-variables.c  && ./03.exe && echo -e "\n"
}


# Main script
if [[ "$1" == "test" ]]; then test
elif [[ "$1" == "fetch" ]]; then fetch
else echo "Usage: $0 {fetch|test}"; fi
