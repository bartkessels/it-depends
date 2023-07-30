cmake_minimum_required(VERSION 3.15 FATAL_ERROR)
include(FetchContent)

#-----------------------
# JSON parsing library
FetchContent_Declare(
        json_library

        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG         v3.10.5
)
FetchContent_MakeAvailable(json_library)

if (NOT packaging)

    #-----------------------
    # Mocking library
    FetchContent_Declare(
            mocking_library

            GIT_REPOSITORY  https://github.com/rollbear/trompeloeil.git
            GIT_TAG         v42
    )
    FetchContent_MakeAvailable(mocking_library)

    #-----------------------
    # Testing library
    FetchContent_Declare(
            testing_library

            GIT_REPOSITORY  https://github.com/catchorg/Catch2.git
            GIT_TAG         v2.13.9
    )
    FetchContent_MakeAvailable(testing_library)

endif()
