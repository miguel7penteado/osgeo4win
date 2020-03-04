@echo off
REM setup from svn

REM extract above toplevel:
REM http://www.bzip.org/1.0.6/bzip2-1.0.6.tar.gz
REM http://downloads.sourceforge.net/project/libpng/zlib/1.2.8/zlib-1.2.8.tar.gz

if "%1"=="x86" (
	set OSGEO4W_ROOT=C:\OSGeo4W
	set A=x86
	set VCARCH=x86
	set CMAKEGEN=Visual Studio 10
) else if "%1"=="x86_64" (
	set OSGEO4W_ROOT=C:\OSGeo4W64
	set A=x86_64
	set VCARCH=x64
	set CMAKEGEN=Visual Studio 10 Win64
) else (
	echo usage: package.cmd [x86^|x86_64]
	exit /b 1
)

set P=setup
set V=1.0.7
set B=16
set CONF=MinSizeRel

set R=..\..\..\%A%\release\%P%
if not exist %R% mkdir %R%

set pf=%ProgramFiles(x86)%
if "%pf%"=="" set pf=%ProgramFiles%
call "%pf%\Microsoft Visual Studio 10.0\VC\vcvarsall.bat" %VCARCH%
echo on
path %ProgramFiles%\CMake\bin;%pf%\Microsoft Visual Studio 10.0\Common7\IDE;%PATH%;c:\cygwin\bin

if not exist build-%A% mkdir build-%A%
if exist skipbuild goto skipbuild
cd build-%A%

cmake -G "%CMAKEGEN%" ^
	../..
if errorlevel 1 (echo cmake error & goto error)

if not exist ..\noclean devenv osgeo4w-setup.sln /Project ALL_BUILD /Clean %CONF%
if errorlevel 1 (echo build error & goto error)

devenv osgeo4w-setup.sln /Project ALL_BUILD /Build %CONF%
if errorlevel 1 (echo build error & goto error)

cd ..
:skipbuild

copy ..\setup.hint %R%\setup.hint
copy ..\COPYING %R%\%P%-%V%-%B%.txt

if exist install-%A% rmdir /s /q install-%A%
for %%i in (bin etc\postinstall etc\preremove) do mkdir install-%A%\%%i

if exist OSGeo_DigiCert_Signing_Cert.p12 (
	if exist OSGeo_DigiCert_Signing_Cert.pass (
		osslsigncode sign ^
			-pkcs12 OSGeo_DigiCert_Signing_Cert.p12 ^
			-readpass OSGeo_DigiCert_Signing_Cert.pass ^
			-n "OSGeo4W Installer" ^
			-h sha256 ^
			-i http://osgeo4w.osgeo.org ^
			-t http://timestamp.digicert.com ^
			-in build-%A%\%CONF%\osgeo4w-setup-%A%.exe ^
			install-%A%\bin\osgeo4w-setup.exe
		if errorlevel 1 (echo sign error & goto error)
	)
)

copy install-%A%\bin\osgeo4w-setup.exe ..\..\..\osgeo4w-setup-%A%.exe

copy ..\postinstall.bat install-%A%\etc\postinstall\%P%.bat
copy ..\preremove.bat install-%A%\etc\preremove\%P%.bat
copy ..\setup.bat install-%A%\bin\%P%.bat.tmpl
copy ..\setup-test.bat install-%A%\bin\%P%-test.bat.tmpl

tar -C install-%A% -cjvvf %R%\%P%-%V%-%B%.tar.bz2 bin etc
if errorlevel 1 (echo tar error & goto error)

exit /b 0

:error
exit /b 1
