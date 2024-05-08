# kzphysfsrwops

simple utility function for creating a SDL_Rwops struct that uses Physfs 

/*Example usage (with SDL_image):
-----------------------------------------------------------------*/

SDL_Surface* LoadSurfaceFromFile(const char* filename) {
    SDL_Surface* surface;
    SDL_RWops*   rwops;
    
    rwops = KZ_PhysfsToRwops(filename, KZ_RWOPS_READONLY); 
    surface = IMG_Load_RW(rwops, 1); 
    SDL_RWclose(rwops); 
    
    return surface; 
}
