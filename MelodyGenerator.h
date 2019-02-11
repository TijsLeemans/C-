#ifndef _MELODYGENERATOR_H_
#define _MELODYGENERATOR_H_
#include <iostream>
#include <vector>
#include "math.h"

class MelodyGenerator
{
public:
  //Constructor and destructor
  MelodyGenerator(int bpm, int noteAmount, std::string root, std::string scale);
  ~MelodyGenerator();

  int bpm;
  int noteAmount;
  std::string root;
  std::string scale;
  std::vector<int> pitch = {};
  std::vector<double> noteLength = {};
  std::vector<int> pitchList = {};
  std::vector<double> Hertz = {};
  int rootMidiValue;
  int step; //position of where you are in the scale
  int randomStep;
  int randomLength;
  int samplerate = 48000;

  // generate the melody:
  void generate();

  double sixteenth = (60.0 / bpm) / 4.0 * 1000;
  double eighth = (60.0 / bpm) / 2.0 * 1000;


};

#endif
