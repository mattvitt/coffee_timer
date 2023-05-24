#include <stdlib.h>
#include <string.h>
#include <storage/storage.h>
#include <flipper_format/flipper_format_i.h>
#include "../coffeetimer.h"

#define COFFEETIMER_SETTINGS_FILE_VERSION 1
#define CONFIG_FILE_DIRECTORY_PATH EXT_PATH("apps_data/coffeetimer")
#define coffeetimer_SETTINGS_SAVE_PATH CONFIG_FILE_DIRECTORY_PATH "/coffeetimer.conf"
#define COFFEETIMER_SETTINGS_SAVE_PATH_TMP COFFEETIMER_SETTINGS_SAVE_PATH ".tmp"
#define COFFEETIMER_SETTINGS_HEADER "Coffeetimer Config File"
#define COFFEETIMER_SETTINGS_KEY_HAPTIC "Haptic"
#define COFFEETIMER_SETTINGS_KEY_LED "Led"
#define COFFEETIMER_SETTINGS_KEY_SPEAKER "Speaker"
#define COFFEETIMER_SETTINGS_KEY_SAVE_SETTINGS "SaveSettings"

void coffeetimer_save_settings(void* context);
void coffeetimer_read_settings(void* context);