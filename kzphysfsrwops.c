/*****************************************************************************\ 
| Copyright(C) 2019-2024 KZGAMES. All Rights Reserved.                        |
| Author: Zachary T Harris                                                    |
| 																			  |
| File: kzphysfsrwops.c     				                 	   	          |
| Desc: utility function. uses Physfs to implement a SDL_RWops struct         |
|     																		  |
| This program is free software: you can redistribute it and/or modify		  |
| it under the terms of the GNU General Public License as published by		  |
| the Free Software Foundation, either version 3 of the License, or			  |
| (at your option) any later version.										  |
| 																			  |
| This program is distributed in the hope that it will be useful,			  |
| but WITHOUT ANY WARRANTY; without even the implied warranty of			  |
| MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the				  |
| GNU General Public License for more details.								  |
| 																			  |
| You should have received a copy of the GNU General Public License			  |
| along with this program.  If not, see <http://www.gnu.org/licenses/>.		  |
******************************************************************************/
#include <physfs/physfs.h>  
#include "kzphysfsrwops.h"

typedef PHYSFS_sint64 Int64;


static Int64 CB_Size(SDL_RWops* rwops) {
	PHYSFS_File* file;
    file = (PHYSFS_File*)rwops->hidden.unknown.data1;
	return PHYSFS_fileLength(file);
}


static Int64 CB_Seek(SDL_RWops* rwops, Int64 offset, int whence) {
    int          result;
	PHYSFS_File* file;

    file = (PHYSFS_File*)rwops->hidden.unknown.data1;
	 
	switch (whence) {
	case RW_SEEK_SET:
		result = PHYSFS_seek(file, offset);
		break;
	case RW_SEEK_CUR:
		result = PHYSFS_seek(file, PHYSFS_tell(file) + offset);
		break;
	case RW_SEEK_END:
		result = PHYSFS_seek(file, PHYSFS_fileLength(file) + offset);
		break;
	default:
		result = 0; // NOLINT
		assert(0);
		break;
	}
	if (result == 0) { 
		return -1;
	}
	return (Int64)(PHYSFS_tell(file));
}


static size_t CB_Read(SDL_RWops* rwops, void* data, size_t size, size_t maxnum) {
    Int64 result;
	PHYSFS_File* file; 
    file = (PHYSFS_File*)rwops->hidden.unknown.data1; 
	result = PHYSFS_readBytes(file, data, size * maxnum);
	return result < 0 ? 0 : (size_t)(result / size);
}


static size_t CB_Write(SDL_RWops* rwops, const void* data, size_t size, size_t num) {
    Int64 result;
	PHYSFS_File* file; 
    file = (PHYSFS_File*)rwops->hidden.unknown.data1;
	result = PHYSFS_writeBytes(file, data, size * num); 
	return result < 0 ? 0 : (size_t)(result / size);
}


static int CB_Close(SDL_RWops* rwops) {
	PHYSFS_File *file;
    file = (PHYSFS_File*)rwops->hidden.unknown.data1;
	PHYSFS_close(file);
	SDL_FreeRW(rwops);
	return 0;
}


SDL_RWops* KZ_PhysfsToRwops(const char* filename, int flag) {
	PHYSFS_File* file;
    SDL_RWops*   rwops;

	if (!filename) { 
		return NULL;
	}
	if (flag == KZ_RWOPS_WRITABLE)
		file = PHYSFS_openWrite(filename);
	else file = PHYSFS_openRead(filename);

	if (!file) { 
		return NULL;
	} 
    rwops = SDL_AllocRW();
    if (!rwops) {
        return NULL;
    } 
	rwops->size  = CB_Size;
	rwops->seek  = CB_Seek;
	rwops->read  = CB_Read;
	rwops->write = CB_Write;
	rwops->close = CB_Close;
	rwops->type  = SDL_RWOPS_UNKNOWN;
	rwops->hidden.unknown.data1 = file; 

    return rwops;
}  
/*****************************************************************************/  
//EOF                                                                         |
/*****************************************************************************/