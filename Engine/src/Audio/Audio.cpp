#include "audio.h"
namespace Sound {
    void playWAV (const wchar_t * filename) {
        PlaySoundW (filename, NULL, SND_FILENAME | SND_ASYNC);
    }

}