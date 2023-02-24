#build

# paho.mqtt.c 1.3.0编译 https://github.com/eclipse/paho.mqtt.c.git
git clone https://github.com/eclipse/paho.mqtt.c.git
git checkout v1.3.0
# 修改 cmakelist
SET(PAHO_BUILD_STATIC TRUE CACHE BOOL "Build static library")
cmake -Bbuild -H. -DPAHO_BUILD_STATIC=TRUE -DCMAKE_INSTALL_PREFIX=./build/_install
cmake -Bbuild -H. -DCMAKE_INSTALL_PREFIX=./build/_install
cmake --build build/ --config Release --target install