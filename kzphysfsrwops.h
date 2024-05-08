/*****************************************************************************\ 
| Copyright(C) 2019-2024 KZGAMES. All Rights Reserved.                        |
| Author: Zachary T Harris                                                    |
| 																			  |
| File: kzphysfsrwops.h 					                 	   	          |
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
#ifndef __KZPHYSFSRWOPS_H__
#define __KZPHYSFSRWOPS_H__

#include <sdl.h>
#ifdef __cplusplus
extern "C" {
#endif

    
#define KZ_RWOPS_READONLY 0
#define KZ_RWOPS_WRITABLE 1

/** utility function. 
    Uses Physfs to create a SDL_RWops struct.
    The returned SDL_RWops must be freed with SDL_RWclose(),
    SDL library functions have a flag to perform that call
    automatically. [Do not use 'delete' or 'free()' on it]
    See: https://wiki.libsdl.org/SDL_RWclose

	@param filename: filename
	@param flag: make the rwops writable(1) or read-only(0)*/
extern SDL_RWops*
KZ_PhysfsToRwops(const char* filename, int flag); 


#ifdef __cplusplus
}
#endif
/*****************************************************************************/  
#endif//EOF                                                                   |
/*****************************************************************************/