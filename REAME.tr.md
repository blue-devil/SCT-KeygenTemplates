# SCT Keygen Taslakları

**ÖNEMLİ AÇIKLAMA**

Bu depoda warez vb. içerik bulunmamaktadır. Bu taslaklar, eğlenmek, sanat ve müziği bölüşmek içindir.

Taslaklar WinAPI C ile Visual Studio ile yazıldı. İlk amaç 64 bir keygende XM müzik çalışmaktı. Sağolsunlar [libxmp](https://github.com/libxmp/libxmp) kitaplığı sayesinde platfom bağımsız XM/MOD müziklerini çalabiliyoruz.

Eskiden uFMOD vardı, anımsıyor musun? Ben de eski günlerdeki gibi libxmp kitaplığından bir statik kitaplık yarattım. Artık XM/MOD müziklerini 64 uygulamanda kolaylıkla çalabilirsin.

## Derleme
* Visual Studio 2017 ya da üstü

Proje özellikleri altında aşağıdaki özellikleri kullanıyorum:

| Configuration Properties | General                                  |
|--------------------------|------------------------------------------|
| Windows SDK Version      | 10.0.17134.0                             |
| Platform Toolset         | Visual Studio 2015 (v140)                |

### Uyarılar
* Statik kitaplık derlerken `C/C++ -> General -> Debug Information Format` altında derleme parametresi olarak `/Z7` seçilirse, statik kitaplığı kullanan proje statik kitaplık ve eş PDB dosyasını yanyana göremediği için ağlayıp şu hatayı vermez: `warning LNK4099: PDB...`

## XM müziği çalmak

Statik kitaplığı ve başlık dosyasını projene ekle. XM dosyanı da `resource` yani kaynak olarak ekle. Sonra da aşağıdaki APIleri kullanarak XM müziğini çal:

```c
	// Müziği durdurur
	void SCT_XMstop();

	// Müziği duraklatır.
	// state = 0 -> müziği devam ettirir.
	// state = 1 -> müziği duraklatır
	void SCT_XMpause(unsigned char state);

	// XM müziği yürütür.
  // Ben aşağıda ufmod'daki aynı işlevselliği bıraktım.
  // Bu nedenle aslında gerek olmasada son iki parametre
  // şimdilik rezerve durumunda. Oralara NULL verilebilir.
	void SCT_XMplay(
		void* lpXM,	// resource/kaynak olarak projeye eklenmiş olan XM müzik dosyası
		void* param,// rezerve
		int fwFlags // rezerve
	);
```

## Özellikler
* Saydamlık
* XM müzik
* Müzik açma/kapama

## Yapılacaklar
* Resim olarak gif eklenecek
* C++ taslaklar hazırlanacak
* C# taslaklar hazırlanacak

## Kaynaklar
**Belgeler**
* [Libxmp is a library that renders module files to PCM data.][web-github-libxmp]
* [Microsoft Visual C++ Static and Dynamic Libraries][web-codeproject-sta-dyn-lib]
* [Static Library Example][web-instructure-sta-lib]
* [RahulSreedharan / Win32-GUI-Programming-in-C][web-github-RahulSreedharan-Win32-GUI-Programming-in-C]
* [ZetCode - Windows API tutorial][web-zetcode-winapi-tut]
* [theForger's Win32 API Programming Tutorial][web-theforgers-winapi]
* [microsoft / Windows-classic-samples][web-github-microsoft-win-classic]
* [Rohitab - Win32 GUI Example Programs -C][web-rohitab-winapi]
* [Riptutorial - Getting started with Win32 API][web-riptutorial-winapi]

**Muzik**
* [Modarchive][web-modarchive]
* [KeyGen Music][web-kgmusic]
* [DualTrax][web-dualtrax]
* [Un4seen - xmplay][web-un4seen]
* [NAudio - Audio and MIDI library for .NET][web-naudio]
* [Soundtracker Module music player in C#][web-sharpmod]
* [How To Add XM or MOD chiptune in C# SharpDevelop][web-yt-howtoaddxmtodotnet]

**GFX/Sanat**
* [Defacto2][web-defacto2]
* [Pouet][web-pouet]

**Text/ASCII/ANSI**
* [AnsiLove][web-ansilove]

## İleri Okuma
* [Transmissionzero - Building Win32 Apps with Mingw][web-transmissionzero-winapi-mingw]
* [TransmissionZero / MinGW-Win32-Application][web-github-transmissionzero-winapi-mingw]
* [Using GCC with MinGW][web-vscode-gcc-mingw-usage]

## Lisans
Bu proje GPLv3 lisansı ile lisanslanmıştır.

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