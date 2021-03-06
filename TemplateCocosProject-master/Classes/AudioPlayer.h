#pragma once
#include <Windows.h>
#include<string>
#include<iostream>
//#pragma comment(lib,"winmm.lib")
using namespace std;
class AudioPlayer
{
public:
	/****Constructors & Destructor****/

	AudioPlayer();

	//see setAudio();
	AudioPlayer(std::string audio);

	~AudioPlayer();

	/****Member Functions****/

	//Sets the audio player's audio file directory	
	void setAudio(std::string audio);
	
	/*
	creates a new instance of sound that can run beside
	other instances of the same sound. can be set to 
	repeat ONLY IF AUDIO IS NOT A .wav FILE
	*/
	void play(bool repeat = false);

	/*
	Mutes and un-mutes audio. audio is muted
	or unmuted based on it's current state
	*/
	void mute();

	/*
	Pauses the latest instance of a running audio file.
	paused audio can be resumed by using resume();
	*/
	void pause();

	/*
	Resumes the latest instance of a paused audio file.
	Continues to play from the last point it was paused.
	*/
	void resume();

	/*
	Stops the latest instance of the audio file.
	When audio is stoped it can not be resumed
	only restarted by play.
	*/
	void stop();

	/*
	Stops all instances of playing audio.
	When audio is stoped it can not be resumed
	only restarted by play.
	*/
	void stopAll();
	 	
	//Depriciated, will be fixed in a latter build	
	bool isPlaying();

	/*
	Prints the amount of open instances of the class, 
	the name of the stream and if it is playing,
	has stoped, or is paused 
	*/
	void info();

	/*
	Sets the volume of the audio.
	Lowest volume 0.0f
	Highest volume 1.0f
	*/
	void setVolume(float = 1);

private:
	/****Utility Functions****/
	void cleanUp();

	/****Utility Variables****/
	std::string* audio = new std::string("");
	static bool printError(int);
	static int inst;	
};

