PROJECT(osgeo4w-setup)

SET(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

SET(CMAKE_CXX_FLAGS_MINSIZEREL "/MT /O1 /Ob1 /D NDEBUG")
SET(CMAKE_CXX_FLAGS_RELEASE "/MT /O2 /Ob2 /D NDEBUG")
SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/MD /ZI /Od /D NDEBUG")
SET(CMAKE_SHARED_LINKER_FLAGS /MANIFEST:NO )
SET(CMAKE_EXE_LINKER_FLAGS /MANIFEST:NO)

SET(CMAKE_RC_COMPILER c:/cygwin/bin/windres.exe)

IF(CMAKE_SIZEOF_VOID_P MATCHES 8)
  SET(MANIFEST_ARCH "amd64")
  SET(SETUPNAME "osgeo4w-setup-x86_64")
  SET(RESDEFINE "-D__x86_64__=1")
ELSE(CMAKE_SIZEOF_VOID_P MATCHES 8)
  SET(MANIFEST_ARCH "x86")
  SET(SETUPNAME "osgeo4w-setup-x86")
ENDIF(CMAKE_SIZEOF_VOID_P MATCHES 8)

FILE(GLOB RCFILES *.rc *.manifest)
ADD_CUSTOM_COMMAND(
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/res.res
  COMMAND ${CMAKE_RC_COMPILER} -O res ${RESDEFINE} -I${CMAKE_BINARY_DIR} -o${CMAKE_CURRENT_BINARY_DIR}/res.res -i${CMAKE_SOURCE_DIR}/res.rc
  DEPENDS ${RCFILES}
)

#CONFIGURE_FILE(cmake/setup.exe.manifest ${CMAKE_BINARY_DIR}/setup.exe.manifest)

# TODO: retrieve from ChangeLog
FILE(WRITE ${CMAKE_BINARY_DIR}/setup_version.c "#define VERSION_PREFIX \"%%% setup-version\"\nstatic const char version_store[] = VERSION_PREFIX \" 2.579\";\nconst char *setup_version = version_store + sizeof (VERSION_PREFIX);\n")

INCLUDE(Flex)
FIND_FLEX()
IF (NOT FLEX_EXECUTABLE)
  MESSAGE(FATAL_ERROR "Couldn't find Flex")
ENDIF (NOT FLEX_EXECUTABLE)

INCLUDE(Bison)
FIND_BISON()

INCLUDE_DIRECTORIES(
  libgetopt++/include
  ../bzip2-1.0.6
  ../zlib-1.2.8
  ${CMAKE_SOURCE_DIR}
)

IF(MSVC)
  ADD_DEFINITIONS(
    -DNOMINMAX
    -D_CRT_SECURE_NO_WARNINGS
    -DHAVE_STRING_H
    -Dstrcasecmp=_stricmp
    -Dsnprintf=_snprintf
    -DOSGEO4W_MIRROR_URL="\\\"http://download.osgeo.org/osgeo4w/mirrors.lst\\\""
    -wd4996 # 'function': was declared deprecated
  )
  SET_SOURCE_FILES_PROPERTIES(PickView.cc
    PROPERTIES COMPILE_FLAGS -wd4355
    # C4355 'this' : used in base member initializer list
  )
  SET_SOURCE_FILES_PROPERTIES(../bzip2-1.0.6/bzlib.c ../bzip2-1.0.6/compress.c
    PROPERTIES COMPILE_FLAGS "-wd4267 -wd4244 -wd4996"
    # C4267 'var' : conversion from 'size_t' to 'type', possible loss of data
    # C4244 'conversion' conversion from 'type1' to 'type2', possible loss of data
    # C4996 'function': was declared deprecated
  )
ENDIF(MSVC)

SET(SRCS
  AntiVirus.cc
  archive.cc
  archive_tar.cc
  archive_tar_file.cc
  choose.cc
  compress.cc
  compress_bz.cc
  compress_gz.cc
  ConnectionSetting.cc
  ControlAdjuster.cc
  cygpackage.cc
  desktop.cc
  dialog.cc
  diskfull.cc
  download.cc
  Exception.cc
  express_package.cc
  filemanip.cc
  find.cc
  FindVisitor.cc
  fromcwd.cc
  geturl.cc
  ini.cc
  IniDBBuilderPackage.cc
  IniParseFeedback.cc
  IniParseFindVisitor.cc
  install.cc
  io_stream.cc
  io_stream_cygfile.cc
  io_stream_file.cc
  io_stream_memory.cc
  license.cc
  localdir.cc
  LogFile.cc
  LogSingleton.cc
  main.cc
  mkdir.cc
  mklink2.cc
  mount.cc
  msg.cc
  net.cc
  netio.cc
  nio-file.cc
  nio-ftp.cc
  nio-http.cc
  nio-ie5.cc
  package_db.cc
  package_meta.cc
  package_source.cc
  package_version.cc
  PackageSpecification.cc
  PickCategoryLine.cc
  PickPackageLine.cc
  PickView.cc
  postinstall.cc
  postinstallresults.cc
  prereq.cc
  proppage.cc
  propsheet.cc
  root.cc
  ScanFindVisitor.cc
  script.cc
  simpsock.cc
  source.cc
  SourceSetting.cc
  splash.cc
  state.cc
  site.cc
  String++.cc
  threebar.cc
  UserSettings.cc
  win32.cc
  window.cc

  ${CMAKE_BINARY_DIR}/setup_version.c

  libgetopt++/src/BoolOption.cc
  libgetopt++/src/StringOption.cc
  libgetopt++/src/StringArrayOption.cc
  libgetopt++/src/GetOption.cc
  libgetopt++/src/OptionSet.cc
  libgetopt++/src/Option.cc

  csu_util/MD5Sum.cc
  csu_util/rfc1738.cc
  csu_util/version_compare.cc

  libmd5-rfc/md5.c

  ../bzip2-1.0.6/bzlib.c
  ../bzip2-1.0.6/crctable.c
  ../bzip2-1.0.6/blocksort.c
  ../bzip2-1.0.6/compress.c
  ../bzip2-1.0.6/crctable.c
  ../bzip2-1.0.6/decompress.c
  ../bzip2-1.0.6/huffman.c
  ../bzip2-1.0.6/randtable.c
  ../bzip2-1.0.6/unzcrash.c

  ../zlib-1.2.8/adler32.c
  ../zlib-1.2.8/compress.c
  ../zlib-1.2.8/crc32.c
  ../zlib-1.2.8/deflate.c
  ../zlib-1.2.8/gzclose.c
  ../zlib-1.2.8/gzlib.c
  ../zlib-1.2.8/gzread.c
  ../zlib-1.2.8/gzwrite.c
  ../zlib-1.2.8/infback.c
  ../zlib-1.2.8/inffast.c
  ../zlib-1.2.8/inflate.c
  ../zlib-1.2.8/inftrees.c
  ../zlib-1.2.8/trees.c
  ../zlib-1.2.8/uncompr.c
  ../zlib-1.2.8/zutil.c

  ${CMAKE_CURRENT_BINARY_DIR}/res.res
)

ADD_BISON_FILES(SRCS iniparse.yy)
ADD_FLEX_FILES(SRCS inilex.ll)

ADD_EXECUTABLE(${SETUPNAME} WIN32 ${SRCS})

TARGET_LINK_LIBRARIES(${SETUPNAME} wsock32 shlwapi comctl32 ole32 wsock32 wininet comdlg32 gdi32)
