SET(THREE_PART_VERSION_REGEX "[0-9]+\\.[0-9]+\\.[0-9]+")
# Breaks up a string in the form n1.n2.n3 into three parts and stores
# them in major, minor, and patch.  version should be a value, not a
# variable, while major, minor and patch should be variables.
MACRO(THREE_PART_VERSION_TO_VARS version major minor patch)
  IF(${version} MATCHES ${THREE_PART_VERSION_REGEX})
    STRING(REPLACE "." " " version_list ${version})
    SEPARATE_ARGUMENTS(version_list)
    LIST(GET version_list 0 ${major})
    LIST(GET version_list 1 ${minor})
    LIST(GET version_list 2 ${patch})
  ELSE(${version} MATCHES ${THREE_PART_VERSION_REGEX})
    MESSAGE("MACRO(THREE_PART_VERSION_TO_VARS ${version} ${major} ${minor} ${patch}")
    MESSAGE(FATAL_ERROR "Problem parsing version string, I can't parse it properly.")
  ENDIF(${version} MATCHES ${THREE_PART_VERSION_REGEX})
ENDMACRO(THREE_PART_VERSION_TO_VARS)