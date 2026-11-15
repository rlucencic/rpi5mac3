#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include "emu/emu.h"
#include "emu/log.h"
#include "rom_store.h"

static const char *TAG = "rom";

static const uint32_t sizes[] = { 512 * 1024, 1024 * 1024 };

/* A file in the data folder's roms/ of the model's ROM size whose checksum
 * names a ROM of that model
 */
bool rom_store_load(mac_model_t model, uint8_t *buf, uint32_t *size, const char **name)
{
    if (model > MAC_MODEL_LC3) {
        return false;
    }
    char folder[1200];
    snprintf(folder, sizeof(folder), "%s/roms", emu_data_dir());
    DIR *dir = opendir(folder);
    if (dir == NULL) {
        return false;
    }
    bool ok = false;
    struct dirent *e;
    while (!ok && (e = readdir(dir)) != NULL) {
        char path[1500];
        struct stat st;
        snprintf(path, sizeof(path), "%s/%s", folder, e->d_name);
        if (e->d_name[0] == '.' || stat(path, &st) != 0 || st.st_size != sizes[model]) {
            continue;
        }
        FILE *f = fopen(path, "rb");
        if (f == NULL) {
            continue;
        }
        mac_model_t found;
        ok = fread(buf, 1, sizes[model], f) == sizes[model] &&
             mac_rom_identify(buf, sizes[model], &found) != NULL && found == model;
        fclose(f);
        if (ok) {
            EMU_LOGI(TAG, "ROM from %s", path);
        }
    }
    closedir(dir);
    if (!ok) {
        return false;
    }
    *size = sizes[model];
    *name = mac_rom_identify(buf, *size, NULL);
    return true;
}
