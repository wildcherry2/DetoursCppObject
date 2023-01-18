#header-only library
vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO wildcherry2/DetoursCppObject
	HEAD_REF master
    SHA512 0
	AUTHORIZATION_TOKEN <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>
)

vcpkg_cmake_configure(
    SOURCE_PATH "${SOURCE_PATH}"
	WINDOWS_USE_MSBUILD
)

vcpkg_cmake_install()
vcpkg_cmake_config_fixup()
vcpkg_fixup_pkgconfig()
vcpkg_copy_pdbs()

file(INSTALL "${SOURCE_PATH}/LICENSE.txt" DESTINATION "${CURRENT_PACKAGES_DIR}/share/${PORT}" RENAME license)