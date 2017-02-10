# Commmon build settings across all AlexaClientSDK modules.

# Append custom CMake modules.
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

# Disallow out-of-source-builds.
include(DisallowOutOfSourceBuilds)

# Setup default build options, like compiler flags and build type.
include(BuildOptions)
