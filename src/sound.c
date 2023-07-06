/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * main.c - Sample to demonstrate proper use of the mp3 library
 *
 * Copyright (c) 2008 Alexander Berl <raphael@fx-world.org>
 *
 * $Id: $
 */
#include <pspkernel.h>
#include <stdio.h>
#include <pspaudio.h>
#include <pspmp3.h>
#include <psputility.h>
#include "sound.h"

static int isrunning = 1;

// Input and Output buffers
char	mp3Buf[16*1024]  __attribute__((aligned(64)));
short	pcmBuf[16*(1152/2)]  __attribute__((aligned(64)));

int fillStreamBuffer( int fd, int handle )
{
	char* dst;
	int write;
	int pos;
	// Get Info on the stream (where to fill to, how much to fill, where to fill from)
	int status = sceMp3GetInfoToAddStreamData( handle, &dst, &write, &pos);
	if (status<0)
	{
	}

	// Seek file to position requested
	status = sceIoLseek32( fd, pos, SEEK_SET );
	if (status<0)
	{
	}
	
	// Read the amount of data
	int read = sceIoRead( fd, dst, write );
	if (read < 0)
	{
	}
	
	if (read==0)
	{
		// End of file?
		return 0;
	}
	
	// Notify mp3 library about how much we really wrote to the stream buffer
	status = sceMp3NotifyAddStreamData( handle, read );
	if (status<0)
	{
	}
	
	return (pos>0);
}

/* main routine */
int playing(const char* MP3FILE)
{
	// Load modules
	int status = sceUtilityLoadModule(PSP_MODULE_AV_AVCODEC);
	if (status<0)
	{
	}
	
	status = sceUtilityLoadModule(PSP_MODULE_AV_MP3);
	if (status<0)
	{
	}
	
	// Open the input file
	int fd = sceIoOpen( MP3FILE, PSP_O_RDONLY, 0777 );
	if (fd<0)
	{
	}
	
	// Init mp3 resources
	status = sceMp3InitResource();
	if (status<0)
	{
	}
	
	// Reserve a mp3 handle for our playback
	SceMp3InitArg mp3Init;
	mp3Init.mp3StreamStart = 0;
	mp3Init.mp3StreamEnd = sceIoLseek32( fd, 0, SEEK_END );
	mp3Init.unk1 = 0;
	mp3Init.unk2 = 0;
	mp3Init.mp3Buf = mp3Buf;
	mp3Init.mp3BufSize = sizeof(mp3Buf);
	mp3Init.pcmBuf = pcmBuf;
	mp3Init.pcmBufSize = sizeof(pcmBuf);
	
	int handle = sceMp3ReserveMp3Handle( &mp3Init );
	if (handle<0)
	{
	}
	
	// Fill the stream buffer with some data so that sceMp3Init has something to work with
	fillStreamBuffer( fd, handle );
	
	status = sceMp3Init( handle );
	if (status<0)
	{
	}
	
	int channel = -1;
	int samplingRate = sceMp3GetSamplingRate( handle );
	int numChannels = sceMp3GetMp3ChannelNum( handle );
	int lastDecoded = 0;
	int volume = PSP_AUDIO_VOLUME_MAX;
	int numPlayed = 0;
	int paused = 0;
	int loop = 0;
	while (isrunning)
	{
			// Check if we need to fill our stream buffer
			if (sceMp3CheckStreamDataNeeded( handle )>0)
			{
				fillStreamBuffer( fd, handle );
			}

			// Decode some samples
			short* buf;
			int bytesDecoded;
			int retries = 0;
			// We retry in case it's just that we reached the end of the stream and need to loop
			for (;retries<1;retries++)
			{
				bytesDecoded = sceMp3Decode( handle, &buf );
				if (bytesDecoded>0)
					break;
				
				if (sceMp3CheckStreamDataNeeded( handle )<=0)
					break;
				
				if (!fillStreamBuffer( fd, handle ))
				{
					numPlayed = 0;
				}
			}
			if (bytesDecoded<0 && bytesDecoded!=0x80671402)
			{
			}
			
			// Nothing more to decode? Must have reached end of input buffer
			if (bytesDecoded==0 || bytesDecoded==0x80671402)
			{
				paused = 1;
				sceMp3ResetPlayPosition( handle );
				numPlayed = 0;
			}
			else
			{
				// Reserve the Audio channel for our output if not yet done
				if (channel<0 || lastDecoded!=bytesDecoded)
				{
					if (channel>=0)
						sceAudioSRCChRelease();
					
					channel = sceAudioSRCChReserve( bytesDecoded/(2*numChannels), samplingRate, numChannels );
				}
				// Output the decoded samples and accumulate the number of played samples to get the playtime
				numPlayed += sceAudioSRCOutputBlocking( volume, buf );
			}
            				status = sceMp3SetLoopNum( handle, loop );
				if (status<0)
				{
				}
    }
    
 return 0;
}
