// Copyright (c) 2010  Sundog Software, LLC All rights reserved worldwide.

/**
    \file ResourceLoader.h
    \brief A class for loading SilverLining's resources from mass storage, which you may extend.
 */

#ifndef RESOURCE_LOADER_H
#define RESOURCE_LOADER_H

#if defined(WIN32) || defined(WIN64)
#pragma warning (disable: 4786)
#endif

#include <vector>
#include <string>

namespace SilverLining
{
/** This class is used whenever SilverLining needs to load textures, data files, or shaders from mass storage; you may
   extend this class to override our default use of POSIX filesystem calls with your own resource management if you wish.
   If you have your own system of packed files, you can include SilverLining's resources directory into it and implement your
   own ResourceLoader to access our resources within your pack files.

   Custom ResourceLoader classes should be passed into Atmosphere::SetResourceLoader() after constructing the Atmosphere
   class. The Atmosphere maintains a static instance of ResourceLoader that is shared across all Atmosphere objects.

   If you choose to implement your own resource management scheme, you'll need to take care with the rendering DLL's found
   under the VC6, VC7, VC8, and VC9 directories of the SilverLining resource folder. Windows can only load DLL's directly from
   a file, so you'll need to exclude these DLL's from your pack files and leave them loose in the resources directory. Alternately,
   you may eliminate the DLL's by statically linking the renderer you want into the SilverLining libraries themselves. See the
   "Overview of SilverLining" section of the documentation for more information.
 */
class ResourceLoader
{
public:
/// Constructor.
ResourceLoader() : resourcePath(0) {
}

/// Virtual destructor; frees the memory of the resource path string.
virtual ~ResourceLoader();

/// Sets the path to the SilverLining resources folder, which will be pre-pended to all resource filenames
/// passed into LoadResource(). This path is also used to locate the renderer DLL's inside the SilverLining
/// resources folder. It should be called after constructing the ResourceLoader and before calling LoadResource().
void SetResourceDirPath(const char *path);

/// Retrieves the path set by SetResourceDirPath().
const char *GetResourceDirPath() const {
    return resourcePath;
}

/** Load a resource from mass storage; the default implementation uses the POSIX functions fopen(), fread(), and fclose()
   to do this, but you may override this method to load resources however you wish. The caller is responsible for calling
   FreeResource() when it's done consuming the resource data in order to free its memory.

   \param pathName The path to the desired resource, relative to the location of the resources folder previously specified
   in SetResourceDirPath().
   \param data A reference to a char * that will return the resource's data upon a successful load.
   \param dataLen A reference to an unsigned int that will return the number of bytes loaded upon a successful load.
   \param text True if the resource is a text file, such as a shader. If true, a terminating null character will be appended
   to the resulting data and the file will be opened in text mode.
   \return True if the resource was located and loaded successfully, false otherwise.

   \sa SetResourceDirPath
 */
virtual bool LoadResource(const char *pathName, char*& data, unsigned int& dataLen, bool text);

/** Frees the resource data memory that was returned from LoadResource(). The data pointer will be invalid following
   this call. */
virtual void FreeResource(char *data);

/** Retrieves a list of file names within the directory path specified (relative to the resource path specified
   with SetResourceDirPath().
   \param pathName The path to the directory underneath the resources directory. The path to the resources directory will
   be pre-pended to this path.
   \param dirContents A reference that will receive a vector of strings of the file names found inside this path, if any.
   \return True if the path was found and scanned successfully, false otherwise.
 */
bool GetFilesInDirectory(const char *pathName, std::vector<std::string>& dirContents);

protected:
char *resourcePath;
};
}

#endif