/* Easy2Use, Helper Functions for Reversers
 * 
 * This file is not part of Extended Module player. 
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <process.h>

#include "common.h"
#include "commonp.h"
#include "unistd.h"
#include "list.h"
#include "sound.h"
#include "xmp.h"

#define MAX_DRV_PARM 20

static struct sound_driver* sound;
static unsigned int foreground_in, foreground_out;
static int refresh_status;

unsigned char pauseState = 0;
HANDLE hOynat;
HANDLE hThread;

void usleep(__int64 usec)
{
	HANDLE timer;
	LARGE_INTEGER ft;

	// Convert to 100 nanosecond interval, negative value indicates relative time
	ft.QuadPart = -(10 * usec);

	timer = CreateWaitableTimer(NULL, TRUE, NULL);
	SetWaitableTimer(timer, &ft, 0, NULL, NULL, 0);
	WaitForSingleObject(timer, INFINITE);
	CloseHandle(timer);
}

static void check_pause(
	xmp_context xc,
	struct control* ctl,
	struct xmp_module_info* mi,
	struct xmp_frame_info* fi
)
{
	if (ctl->pause) {
		sound->pause();

		while (ctl->pause) {
			usleep(100000);
			ctl->pause = pauseState;
		}

		sound->resume();
	}
}



// Pauses and resumes xm music
void SCT_XMduraklat(
	unsigned char state
)
{
	pauseState = state;
}


// Plays xm music
unsigned char
SCT_XMOynat(
	void* lpXM,
	void* param,
	int fwFlags
)
{
	xmp_context xc;
	struct xmp_module_info mi;
	struct xmp_frame_info fi;
	struct options opt, save_opt;
	struct control control;

	int optind = 1;//getopt'dan geliyor

	int first;
	int skipprev;
	int val, lf_flag;
	int flags;
	int played;

	//
	// We're playing XM music from applications resource 
	//
	HRSRC rc = FindResource(NULL, MAKEINTRESOURCE(lpXM), RT_RCDATA);
	DWORD size = SizeofResource(NULL, rc);
	if (size == 0) {
		DWORD errrr = GetLastError();
	}
	HGLOBAL rcData = LoadResource(NULL, rc);
	if (rcData == NULL) {
		//report("[-]Error");
	}

	init_sound_drivers();

	memset(&opt, 0, sizeof(struct options));
	memset(&control, 0, sizeof(struct control));

	/* set defaults */
	opt.verbose = 0;
	opt.rate = 44100;
	opt.mix = -1;
	opt.defpan = 50;
	opt.numvoices = 128;
	opt.driver_id = NULL;
	opt.interp = XMP_INTERP_SPLINE;
	opt.dsp = XMP_DSP_LOWPASS;
	opt.player_mode = XMP_MODE_AUTO;
	opt.amplify = 1;
	opt.loop = 1; // play the xm in a loop
	control.pause = pauseState;

	sound = select_sound_driver(&opt);
	if (sound == NULL) {
		// TODO: handle error
	}


	xc = xmp_create_context();
	if (xc == NULL) {
		// TODO: handle the error if xc is NULL
	}

	skipprev = 0;
	lf_flag = 0;
	memcpy(&save_opt, &opt, sizeof(struct options));

	control.loop = opt.loop;
	control.explore = opt.explore;
	control.amiga = opt.amiga;
	first = optind;	//optind data comes from getopt and it is 1
	

	for (played = 0; optind < 2; optind++) {
		memcpy(&opt, &save_opt, sizeof(struct options));

		/* these must be set before loading the module */
		xmp_set_player(xc, XMP_PLAYER_DEFPAN, opt.defpan);

		//
		// Our module is XM music and it is from applications memory
		//
		val = xmp_load_module_from_memory(xc, rcData, (unsigned int)size);

		if (val < 0) {
			//hata
		}

		xmp_get_module_info(xc, &mi);

		/* these must be set before xmp_start_player() */
		xmp_set_player(xc, XMP_PLAYER_VOICES, opt.numvoices);

		if (opt.sequence) {
			//bizimki hep 0
		}
		control.sequence = opt.sequence;

		skipprev = 0;
		control.time = 0.0;

		/* Play module */

		if (xmp_start_player(xc, opt.rate, opt.format) == 0) {
			xmp_set_player(xc, XMP_PLAYER_INTERP, opt.interp);
			xmp_set_player(xc, XMP_PLAYER_DSP, opt.dsp);
			// player mode auto bizim

			played = 1;

			xmp_set_player(xc, XMP_PLAYER_AMP, opt.amplify);

			xmp_set_position(xc, opt.start);

			// no mute channel
			// no set flags, we are gonna play xm
			flags = xmp_get_player(xc, XMP_PLAYER_CFLAGS);
			xmp_set_player(xc, XMP_PLAYER_CFLAGS, flags);

			/* Play sequence */
			refresh_status = 1;
			//info_frame_init();
			fi.loop_count = 0;
		//play_sequence:
			while (!opt.info && xmp_play_frame(xc) == 0) {
				int old_loop = fi.loop_count;
				xmp_get_frame_info(xc, &fi);
				control.mixer_type = xmp_get_player(
					xc, XMP_PLAYER_MIXER_TYPE);

				/* Check loop */

				if (old_loop != fi.loop_count) {
					if (control.loop == 1) {
						//info_message("Loop sequence %d", control.sequence);
					}
					else {
						break;
					}
				}

				foreground_in = foreground_out = 1;
				if (foreground_out && opt.verbose > 0) {
					//info_frame(&mi, &fi, &control, refresh_status);
					refresh_status = 0;
				}
				control.time += 1.0 * fi.frame_time / 1000;

				sound->play(fi.buffer, fi.buffer_size);

				//if (foreground_in && !opt.nocmd) {
					//plays single by single
					//read_command(xc, &mi, &control);
				//}
				control.pause = pauseState;
				check_pause(xc, &control, &mi, &fi);

				opt.start = 0;
			}
			xmp_end_player(xc);
		}
		xmp_release_module(xc);
	}
	sound->flush();

//end:
	xmp_free_context(xc);

	if (foreground_in)
		//reset_tty();

	sound->deinit();

	exit(EXIT_SUCCESS);

}

// Stops xm music
void
SCT_XMdurdur()
{
	CloseHandle(hOynat);
}

struct params {
	void* lpXM;
	void* reserved;
	int fwFlags;
};

// Player thread.
unsigned int __stdcall
SCT_PlayThread(void* data)
{
	struct params* argm;
	argm = (struct params*)data;
	void* lpXM = argm->lpXM;
	void* reserved = argm->reserved;
	int fwFlags = argm->fwFlags;

	SCT_XMOynat(lpXM, 0, 0);

	return 0;
}

// Plays xm music by calling a new thread.
void
SCT_Oynat(
	void* lpXM,
	void* param,
	int fwFlags
)
{
	struct params* argm;
	argm = (struct params*)malloc(sizeof(struct params*));
	argm->lpXM = lpXM;
	argm->reserved = 0;
	argm->fwFlags = 0;
	hThread = (HANDLE)_beginthreadex(0, 0, &SCT_PlayThread, (void *)argm, 0, hOynat);
	WaitForSingleObject(hOynat, INFINITE);
	CloseHandle(hOynat);
}


//
// Needed functions for my fellow reversers
//

                                                                               
// Plays xm music
// 2nd and 3rd parameters
void
SCT_XMplay(
	void* lpXM,				// xm resource
	void* param,			// reserved
	int fwFlags				// reserved
)
{
	SCT_Oynat(lpXM, param, fwFlags);
}

// Stops xm music
void
SCT_XMstop()
{
	SCT_XMdurdur();
}

// Pauses and resumes xm music
void SCT_XMpause(
	unsigned char state		// playing state of xm
							// 1 = pauses music
							// 0 = resumes music
)
{
	SCT_XMduraklat(state);
}

