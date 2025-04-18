ROOT=$PWD
BUILD_DIR="${ROOT}/cmake-build"
mkdir -p "${BUILD_DIR}"

cd "${BUILD_DIR}" && cmake -G "Unix Makefiles" ${ROOT}
echo "Workspace generated."
# echo " 'cd ${ROOT}/cmake-build && make install -j12' to compile"
echo " 'make install -C ${ROOT}/cmake-build -j12' to compile"