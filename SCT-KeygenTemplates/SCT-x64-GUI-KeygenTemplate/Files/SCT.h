#pragma once
#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "Files\\libxmp-lite4reversers.lib")
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#include <stdio.h>
#include <Windows.h>
#include <process.h>
#include <CommCtrl.h>
#include "..\Resources\resource.h"

HICON		hIcon;
HBRUSH		hBrush;
HCURSOR		hCursor;
HANDLE		hSerial;
HANDLE		hName;
HANDLE		hLink;
BOOL		isCursorOver;
COLORREF	colorStatic;
WNDPROC		lpOrgStaticProc;

HANDLE hOynat;

// 
// 0 = English
// 1 = Türkçe
//
static char lang = 0; 

//
// Function Prototypes
//
void GenerateSerial(HANDLE, HANDLE);
void TransparentDialog(HWND, BYTE);
LRESULT CALLBACK CursorLoader(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK MainDialogProc(HWND, UINT, WPARAM, LPARAM);

//
// Strings for About Message, in English and in Turkish
//
static wchar_t* strSCT = TEXT("SCT");
static wchar_t* strMsgTitle = TEXT("Hakkında");
static wchar_t* strBlueDeviLGithub = TEXT("https://github.com/blue-devil/");
static wchar_t* strMsgAbout = TEXT("[SCT]Keygen Taslağı v2.2 - 64 bit\n\n\
Esen!\n\
Keygen yazmayı hızlandırmak için bir taslak\n\n\
Özellikleri:\n\
Tamamen WinAPI C ile yazıldı, \n\
XM müzik çalma-durdurma eklendi,\n\
pencereye saydamlık eklendi,\n\
lang seçeneği eklendi.\n\n\
Yazar:\tBlue DeviL // SCT\n\
Tester:\tErrorInside // SCT\n\
Tarih:\t03.07.2022\n\
E-posta:\tbluedevil.SCT@gmail.com\n\n\
Esenlikler ve Teşekkürler:\n\
ErrorInside, Mr_Stop, Infexia\n\n\
[SCT] 2022");

static wchar_t* strMsgTitleENG = TEXT("About");
static wchar_t* strMsgAboutENG = TEXT("[SCT]Keygen Template v2.2 - 64 bit\n\n\
Hello!\n\
Keygen template to fasten things up!\n\n\
Specs:\n\
Written WinAPI C,\n\
XM music start-stop added,\n\
dialog transparency added,\n\
language option added.\n\n\
Author:\tBlue DeviL // SCT\n\
Tester:\tErrorInside // SCT\n\
Date:\t03.07.2022\n\
E-mail:\tbluedevil.SCT@gmail.com\n\n\
Greets and Thanks:\n\
ErrorInside, Mr_Stop, Infexia\n\n\
[SCT] 2022");

