#include <iostream>
#include <time.h>
#include <math.h>
#include "MelodyGenerator.h"

using namespace std;

// Constructor and destructor
MelodyGenerator::MelodyGenerator(int bpm, int noteAmount, string root, string scale) :
 bpm(bpm), noteAmount(noteAmount), root(root), scale(scale)
{

    // make your root a MIDI value:
    if(root == "a")
    {
      this->rootMidiValue = 57;
    }
    else if(root == "ais" || root == "bes")
    {
      this->rootMidiValue = 58;
    }
    else if(root == "b")
    {
      this->rootMidiValue = 59;
    }
    else if(root == "c")
    {
      this->rootMidiValue = 60;
    }
    else if(root == "cis" || root == "des")
    {
      this->rootMidiValue = 61;
    }
    else if(root == "d")
    {
      this->rootMidiValue = 62;
    }
    else if(root == "dis" || root == "es")
    {
      this->rootMidiValue = 63;
    }
    else if(root == "e")
    {
      this->rootMidiValue = 64;
    }
    else if(root == "f")
    {
      this->rootMidiValue = 65;
    }
    else if(root == "fis" || root == "ges")
    {
      this->rootMidiValue = 66;
    }
    else if(root == "g")
    {
      this->rootMidiValue = 67;
    }
    else if(root == "gis" || root == "as")
    {
      this->rootMidiValue = 68;
    }

  // Set your pitchList to the chosen scale, from a third below to a sixth above the chosen root:
  if (scale=="major")
  {
    pitchList = {-3, -1, 0, 2, 4, 5, 7, 9};
  }
  else if(scale=="minor")
  {
    pitchList = {-4, -2, 0, 2, 3, 5, 7, 8};
  }
  else if(scale=="phrygian")
  {
    pitchList = {-4, -2, 0, 1, 3, 5, 7, 8};
  }
  else if(scale=="lydian")
  {
    pitchList = {-3, -1, 0, 2, 4, 6, 7, 9};
  }
  else if(scale=="harmonic minor")
  {
    pitchList = {-4, -1, 0, 2, 3, 5, 7, 8};
  }
  else if(scale=="dorian#4")
  {
    pitchList = {-3, -2, 0, 2, 3, 6, 7, 9};
  }
  else
  {
    cout << "...How about minor? :D\n\n";
    pitchList = {-4, -2, 0, 2, 3, 5, 7, 8};
  }

  step = 2; //starting position in the vector; Start at chosen root.
  randomStep = rand() %3 -1;
  randomLength = rand() %3 +1;
}

MelodyGenerator::~MelodyGenerator()
{

}

// generate the melody:
void MelodyGenerator::generate()
{
  // get random seed:
  srand(time(0));

  // add initial pitch & length to the vectors:
  pitch.push_back(pitchList[step] + rootMidiValue);
  noteLength.push_back(2);

  for (int x=1; x <= (noteAmount-1); x++)
  {
    //decide next step:
    randomStep = rand() %3 -1;
    step += randomStep;
    if (step < 0)
    {
      step=1;
    }
    else if (step>7)
    {
      step=6;
    }

    // add new pitch according to step:
    pitch.push_back(pitchList[step] + rootMidiValue);
	Hertz.push_back(440.0 * pow(2.0, ((pitchList[step] + rootMidiValue) - 69) / 12));

    // decide length for the note:
    int randomLength = rand() %4 + 1;
    if(randomLength == 4)
    {
      randomLength=8;
    }

    // add length to the noteLength vector:
    noteLength.push_back(randomLength);
  } // ForLoop
} //generate
