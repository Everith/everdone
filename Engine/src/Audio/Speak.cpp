#include "speak.h"

namespace speak {
    bool speak (const wchar_t *text) {
        ISpVoice * pVoice = NULL;
        if (FAILED (CoInitialize (NULL))) {
            return FALSE;
        }
        HRESULT hr = CoCreateInstance (CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void **)&pVoice);
        if (SUCCEEDED (hr)) {
            pVoice->SetRate (3);
            pVoice->Speak (text, 0, NULL);
            pVoice->Release ();
            pVoice = NULL;
        }
        CoUninitialize ();
        return TRUE;
    }
}