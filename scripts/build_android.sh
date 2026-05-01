#!/bin/bash
set -e

if [ -z "$ANDROID_NDK_HOME" ]; then
  echo "ANDROID_NDK_HOME is not set"
  exit 1
fi

ABIS=("arm64-v8a" "armeabi-v7a" "x86_64")

for ABI in "${ABIS[@]}"; do
  BUILD_DIR=build/android-$ABI

  cmake -G "Ninja" -B $BUILD_DIR \
    -DCMAKE_TOOLCHAIN_FILE=$ANDROID_NDK_HOME/build/cmake/android.toolchain.cmake \
    -DANDROID_ABI=$ABI \
    -DANDROID_PLATFORM=android-26 \
    -DBUILD_TESTS=OFF \
    -DBUILD_SHARED_LIBS=ON

  cmake --build $BUILD_DIR

  mkdir -p dist/android/$ABI
  cp $BUILD_DIR/libcounter.so dist/android/$ABI/
done

echo "=== VERIFY ==="
ls dist/android/*/libcounter.so