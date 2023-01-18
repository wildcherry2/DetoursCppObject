vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO wildcherry2/DetoursCppObject
	HEAD_REF master
)

vcpkg_install_msbuild(
	SOURCE_PATH ${SOURCE_PATH}
	PROJECT_SUBPATH DetoursCppObject.sln
	INCLUDES_SUBPATH DetoursCppObject
	LICENSE_SUBPATH "LICENSE.txt"
	PLATFORM "x64"
	RELEASE_CONFIGURATION "Release"
	DEBUG_CONFIGURATION "Debug"
	USE_VCPKG_INTEGRATION
	ALLOW_ROOT_INCLUDES
)

file(RENAME "${CURRENT_PACKAGES_DIR}/include" "${CURRENT_PACKAGES_DIR}/includeTemp")
file(MAKE_DIRECTORY "${CURRENT_PACKAGES_DIR}/include")
file(RENAME "${CURRENT_PACKAGES_DIR}/includeTemp" "${CURRENT_PACKAGES_DIR}/include/DetoursCppObject")

file(REMOVE "${CURRENT_PACKAGES_DIR}/include/DetoursCppObject/DetoursCppObject.vcxproj")
file(REMOVE "${CURRENT_PACKAGES_DIR}/include/DetoursCppObject/DetoursCppObject.vcxproj.filters")

file(INSTALL "${SOURCE_PATH}/LICENSE.txt" DESTINATION "${CURRENT_PACKAGES_DIR}/share/${PORT}" RENAME license)