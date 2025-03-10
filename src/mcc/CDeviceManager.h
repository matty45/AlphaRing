#pragma once

#include "CInputDevice.h"

inline static const char key_map_list[] = {
        '\x1B', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '{', '|', '}', '~', '\xC0',
        '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
        '\xBD', '\xBB',
        '8', '9', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
        '\xDB', '\xDD', '\xDC', '\x14',
        'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
        '\xBA', '\xDE', '\x0D', '\xA0',
        'Z', 'X', 'C', 'V', 'B', 'N', 'M',
        '\xBC', '\xBE', '\xBF', '\xA1', '\xA2',
        '[', '\xA4', ' ', '\xA5', '\\', ']', '\xA3',
        '&', '(', '%', '\'', '-', '$', '!', '.', '#', '"',
        '\x90', 'o', 'j', '`', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'm', 'k', '\x0D', 'n',
        '\x00', '\x00', '\x00', '\x00'
};

struct input_data_t {
    int un;
    bool keyState[sizeof(key_map_list)]; // 0x4
    char buffer[0x94];
    struct mouse_t {
        float mouse_delta_x;//0x104
        float mouse_delta_y;//0x108
        float pos_x; // 0x10C
        float pos_y; // 0x110
        float un1; // 0x114
        float constant_1; // 0x118
    } mouse;
    char buffer1[20];
};

static_assert(sizeof(input_data_t) == 0x130);

struct CDeviceManager {
public:
    static bool Initialize(CDeviceManager** mng);

public:
    struct FunctionTable {
        void* pf0;
        char (__fastcall* get_status)(CDeviceManager* self, DWORD index, input_data_t* p_input_device, bool a4);
        char (__fastcall* update_time)(CDeviceManager* self, int a2, __int64 a3);
        void (__fastcall* set_vibration)(CDeviceManager* self, DWORD index, XINPUT_VIBRATION *a3);
        void (__fastcall* reset_device)(CDeviceManager* self);
        void* pf3;
        int (__fastcall* add_new_device)(CDeviceManager* self, int device_index);
        void (__fastcall* update_state)(CDeviceManager* self, __int64 a2, __int64 a3, bool a4);
    };

    static FunctionTable ppOriginal;
    FunctionTable* table;
    CInputDevice* p_input_device[5];
    char buffer[0x90];
    HWND hwnd; // 0xC0
    LARGE_INTEGER qpc; // 0xC8
};

extern CDeviceManager** g_ppDeviceManager;
inline CDeviceManager* DeviceManager() { return *g_ppDeviceManager; }
