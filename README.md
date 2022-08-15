# SCT Keygen Templates

**IMPORTANT NOTICE**

There is no warez stuff in this repo. These templates are only for fun and just to share art and music.

Templates are written in WinAPI C. The very first aim is to play XM music in 64 bit. Thankfully there are good people who created (libxmp)[https://github.com/libxmp/libxmp] XM Player Library. Anyone can plan XM/MOD music independent from platform by using libxmp.

Do you remember uFMOD? I have created a static library just like the old days. Now you can play your XM in a 64 bit windows application. 

## Building
* Visual Studio 2017 or above

Under project properties,  i was using those configurations:

| Configuration Properties | General                                  |
|--------------------------|------------------------------------------|
| Windows SDK Version      | 10.0.17134.0                             |
| Platform Toolset         | Visual Studio 2015 (v140)                |

## Playing XM music
Add the static library and header file to your project. Add your XM music as a resource. Then you can use the API below.

```c
	// Stops the music
	void SCT_XMstop();

	// Pauses the music
	// state = 0 -> resumes music
	// state = 1 -> pauses music
	void SCT_XMpause(unsigned char state);

	// Plays xm music
	// I have provide the same function prototype as it was in ufMod.
	// So the last two parameters are now in reserved state
	void SCT_XMplay(
		void* lpXM,	// Our XM music as resource
		void* param,// reserved
		int fwFlags // reserved
	);
```

## Features
* Transparency added
* XM music added
* Music on/off added

## TODO
* Add gif banner
* Add C++ templates
* Add C# templates

## Sources
**Documents/Tutorials**
* [Libxmp is a library that renders module files to PCM data.][web-github-libxmp]
* [Microsoft Visual C++ Static and Dynamic Libraries][web-codeproject-sta-dyn-lib]
* [Static Library Example][web-instructure-sta-lib]
* [RahulSreedharan / Win32-GUI-Programming-in-C][web-github-RahulSreedharan-Win32-GUI-Programming-in-C]
* [ZetCode - Windows API tutorial][web-zetcode-winapi-tut]
* [theForger's Win32 API Programming Tutorial][web-theforgers-winapi]
* [microsoft / Windows-classic-samples][web-github-microsoft-win-classic]
* [Rohitab - Win32 GUI Example Programs -C][web-rohitab-winapi]
* [Riptutorial - Getting started with Win32 API][web-riptutorial-winapi]

**Music**
* [Modarchive][web-modarchive]
* [KeyGen Music][web-kgmusic]
* [DualTrax][web-dualtrax]
* [Un4seen - xmplay][web-un4seen]
* [NAudio - Audio and MIDI library for .NET][web-naudio]
* [Soundtracker Module music player in C#][web-sharpmod]
* [How To Add XM or MOD chiptune in C# SharpDevelop][web-yt-howtoaddxmtodotnet]

**GFX/Art**
* [Defacto2][web-defacto2]
* [Pouet][web-pouet]

**Text/ASCII/ANSI**
* [AnsiLove][web-ansilove]

## Further Reading
* [Transmissionzero - Building Win32 Apps with Mingw][web-transmissionzero-winapi-mingw]
* [TransmissionZero / MinGW-Win32-Application][web-github-transmissionzero-winapi-mingw]
* [Using GCC with MinGW][web-vscode-gcc-mingw-usage]

## License
This project is licensed under GPLv3


[web-codeproject-sta-dyn-lib]: https://www.codeproject.com/Articles/85391/Microsoft-Visual-C-Static-and-Dynamic-Libraries
[web-instructure-sta-lib]: https://utah.instructure.com/courses/512907/pages/static-library-example
[web-github-libxmp]: https://github.com/libxmp/libxmp
[web-github-RahulSreedharan-Win32-GUI-Programming-in-C]: https://github.com/RahulSreedharan/Win32-GUI-Programming-in-C
[web-zetcode-winapi-tut]: https://zetcode.com/gui/winapi/
[web-theforgers-winapi]: http://www.winprog.org/tutorial/
[web-github-microsoft-win-classic]: https://github.com/microsoft/Windows-classic-samples
[web-rohitab-winapi]: http://www.rohitab.com/discuss/topic/36060-c-win32-gui-example-programs/
[web-riptutorial-winapi]: https://riptutorial.com/winapi
[web-transmissionzero-winapi-mingw]: https://www.transmissionzero.co.uk/computing/win32-apps-with-mingw/
[web-github-transmissionzero-winapi-mingw]: https://github.com/TransmissionZero/MinGW-Win32-Application
[web-vscode-gcc-mingw-usage]: https://code.visualstudio.com/docs/cpp/config-mingw
[web-modarchive]: https://modarchive.org
[web-kgmusic]: http://keygenmusic.net/
[web-dualtrax]: https://dualtrax.com/
[web-un4seen]: https://www.un4seen.com/
[web-naudio]: https://github.com/naudio/NAudio
[web-sharpmod]: https://github.com/jaredthirsk/sharpmod
[web-yt-howtoaddxmtodotnet]: https://www.youtube.com/watch?v=iPemidgUpHo
[web-defacto2]: https://defacto2.net/home
[web-pouet]: https://www.pouet.net/
[web-ansilove]: https://www.ansilove.org/