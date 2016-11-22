// **************************************************************
//     Filename: Tsunami.h
// Date Created: 11/22/2016
//
//     Comments: Robertsonics Tsunami serial control library
//
// Programmers: Jamie Robertson, info@robertsonics.com
//
// **************************************************************
//
// Revision History
//
// Date      Description
// --------  -----------
//
// 10/15/16  First version created.

#ifndef _20161015_TSUNAMI_H_
#define _20161015_TSUNAMI_H_

#define TSUNAMI_NUM_OUTPUTS	4

// ==================================================================
// The following defines are used to control which serial class is
//  used. Uncomment only the one you wish to use. If all of them are
//  commented out, the library will use Hardware Serial
#define __TSUNAMI_USE_SERIAL1__
//#define __TSUNAMI_USE_SERIAL2__
//#define __TSUNAMI_USE_SERIAL3__
//#define __TSUNAMI_USE_ALTSOFTSERIAL__
// ==================================================================

#define CMD_GET_VERSION				1
#define CMD_GET_SYS_INFO			2
#define CMD_TRACK_CONTROL			3
#define CMD_STOP_ALL				4
#define CMD_MASTER_VOLUME			5
#define CMD_TRACK_VOLUME			8
#define CMD_TRACK_FADE				10
#define CMD_RESUME_ALL_SYNC			11
#define CMD_SAMPLERATE_OFFSET		12
#define	CMD_SET_REPORTING			13

#define TRK_PLAY_SOLO				0
#define TRK_PLAY_POLY				1
#define TRK_PAUSE					2
#define TRK_RESUME					3
#define TRK_STOP					4
#define TRK_LOOP_ON					5
#define TRK_LOOP_OFF				6
#define TRK_LOAD					7

#define	RSP_VERSION_STRING			129
#define	RSP_SYSTEM_INFO				130
#define	RSP_STATUS					131
#define	RSP_TRACK_REPORT			132

#define MAX_MESSAGE_LEN				32
#define MAX_NUM_VOICES				18
#define VERSION_STRING_LEN			22

#define SOM1	0xf0
#define SOM2	0xaa
#define EOM		0x55


#ifdef __TSUNAMI_USE_ALTSOFTSERIAL__
#include "../AltSoftSerial/AltSoftSerial.h"
#else
#include <HardwareSerial.h>
#ifdef __TSUNAMI_USE_SERIAL1__
#define TsunamiSerial Serial1
#define __TSUNAMI_SERIAL_ASSIGNED__
#endif
#ifdef __TSUNAMI_USE_SERIAL2__
#define TsunamiSerial Serial2
#define __TSUNAMI_SERIAL_ASSIGNED__
#endif
#ifdef __TSUNAMI_USE_SERIAL3__
#define TsunamiSerial Serial3
#define __TSUNAMI_SERIAL_ASSIGNED__
#endif
#ifndef __TSUNAMI_SERIAL_ASSIGNED__
#define TsunamiSerial Serial
#endif
#endif

class Tsunami
{
public:
	Tsunami() {;}
	~Tsunami() {;}
	void start(void);
	void update(void);
	void flush(void);
	void setReporting(bool enable);
	bool getVersion(char *pDst, int len);
	int getNumTracks(void);
	bool isTrackPlaying(int trk);
	void masterGain(int out, int gain);
	void stopAllTracks(void);
	void resumeAllInSync(void);
	void trackPlaySolo(int trk, int out, bool lock);
	void trackPlayPoly(int trk, int out, bool lock);
	void trackLoad(int trk, int out, bool lock);
	void trackStop(int trk);
	void trackPause(int trk);
	void trackResume(int trk);
	void trackLoop(int trk, bool enable);
	void trackGain(int trk, int gain);
	void trackFade(int trk, int gain, int time, bool stopFlag);
	void samplerateOffset(int out, int offset);

private:
	void trackControl(int trk, int code, int out, int flags);

#ifdef __TSUNAMI_USE_ALTSOFTSERIAL__
	AltSoftSerial TsunamiSerial;
#endif

	uint16_t voiceTable[MAX_NUM_VOICES];
	uint8_t rxMessage[MAX_MESSAGE_LEN];
	char version[VERSION_STRING_LEN];
	uint16_t numTracks;
	uint8_t numVoices;
	uint8_t rxCount;
	uint8_t rxLen;
	bool rxMsgReady;
	bool versionRcvd;
	bool sysinfoRcvd;
};

#endif