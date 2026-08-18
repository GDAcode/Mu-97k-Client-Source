#pragma once
// Config.h - Configuration loading
//
// Config_Load      @ 0x0041E0A0  - reads registry + config.ini
// Config_ReadServerAddr @ 0x0041E800  - reads IP/port from config.ini

#include "stdafx.h"

// Load all config (registry + config.ini).
// Registry key: HKCU\SOFTWARE\Webzen\Mu\Config
//   SoundOnOff  -> g_SoundOn
//   MusicOnOff  -> g_MusicOn
//   Resolution  -> sets g_ScreenW / g_ScreenH:
//     0=640x480  1=800x600  2=1024x768  3=1280x1024  4=1600x1200
//   TextOut     -> g_TextOut
// config.ini [LOGIN] Version=
// Returns 1 on success, 0 on failure.
// @ 0x0041E0A0
int  Config_Load(void);

// Read server IP and port from config.ini.
// Stores results in PTR_s_connect_muonline_co_kr_005615b8 and DAT_005615bc.
// @ 0x0041E800
int  Config_ReadServerAddr(void* pConfig, char* lpCmdLine, char* outIP, unsigned short* outPort);

// Known globals (set by Config_Load):
//
// 2026-08-18: g_ScreenW / g_ScreenH SON DAT_0056156c / DAT_00561570 — el mismo
// global del binario (verificado en OpenInitFile @0x0041E388..0x0041E3EA: el
// switch de Resolution escribe directo a 0x0056156C / 0x00561570).  Hasta hoy
// el port tenia DOS memorias distintas: Config_Load escribia g_ScreenW y la
// ventana, el ortho y el viewport leian DAT_0056156c, que se quedaba en 640x480
// para siempre.  Por eso cambiar Resolution no hacia nada visible, y por eso
// _DAT_055c9b70 (que sale de g_ScreenW) quedaba desincronizado del ortho — la
// desincronizacion que documentan FUN_0040f610 y stubs_game.cpp:7492.
// Misma unificacion por #define que ya se hizo con m_dwTextColor/DAT_00559c78.
extern DWORD DAT_0056156c;
extern DWORD DAT_00561570;
#define g_ScreenW  DAT_0056156c
#define g_ScreenH  DAT_00561570
extern DWORD g_SoundOn;    // lpData_055c9fe8  (1 = sound on)
// g_MusicOn es un ALIAS del unico global del binario, m_MusicOnOff @ 0x055C9E3C
// (definido en globals.cpp). No declarar una variable propia aca: hasta 2026-08-17
// habia dos memorias distintas — esta se escribia y la de Music.cpp se leia — y
// por eso PlayMp3 salia siempre por el early-return.
extern DWORD m_MusicOnOff;
#define g_MusicOn m_MusicOnOff   // 0x055C9E3C  (0 = musica apagada)
extern DWORD g_Resolution; // lpData_055c9e38 (0-4)
extern DWORD g_TextOut;    // lpData_055ca044
