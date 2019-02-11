#include <iostream>
#include <thread>
using namespace std;

#include "math.h"
#include "olcNoiseMaker.h"
#include "pch.h"
#include "Square.h"
#include "Sine.h"
#include "Triangle.h"
#include "Saw.h"
#include "MelodyGenerator.h"

int BPMtoSixteenth(int bpm)
{
	return 0;
}

struct Envelope
{
	double AttackTime;
	double DecayTime;
	double ReleaseTime;

	double Sustain;

	double StartAmplitude;
	double TriggerOn;
	double TriggerOff;

	bool NoteOn;

	Envelope()
	{
		AttackTime = 0.01;
		DecayTime = 0.05;
		ReleaseTime = 0.05;

		Sustain = 0.8;

		StartAmplitude = 1.0;
		TriggerOn = 0.0;
		TriggerOff = 0.0;
		NoteOn = false;
	}

	void NoteOnTrigger(double dTimeOn)
	{
		TriggerOn = dTimeOn;
		NoteOn = true;
	}

	void NoteOffTrigger(double dTimeOff)
	{
		TriggerOff = dTimeOff;
		NoteOn = false;
	}

	double GetAmplitude(double dTime)
	{
		double Amplitude = 0.0;
		double lifeTime = dTime - TriggerOn;

		if (NoteOn)
		{
			if (lifeTime <= AttackTime)
			{
				Amplitude = (lifeTime / AttackTime) * StartAmplitude;
			}

			if (lifeTime > AttackTime && lifeTime <= (AttackTime + DecayTime))
			{
				Amplitude = ((lifeTime - AttackTime) / DecayTime) * (Sustain - StartAmplitude) + StartAmplitude;
			}

			if (lifeTime > (AttackTime + DecayTime))
			{
				Amplitude = Sustain;
			}
		}
		else
		{
			Amplitude = ((dTime - TriggerOff) / ReleaseTime) * (0.0 - Sustain) + Sustain;
		}

		if (Amplitude >= 1)
		{
			Amplitude = 1;
		}
		if (Amplitude <= 0.0001)
		{
			Amplitude = 0.0;
		}

		return Amplitude;
	}

};

double counter;
double dTime;


Envelope envelope;
Envelope envelope2;
Sine sine(dTime);
Square square(dTime);
Saw saw(dTime);
Triangle triangle(dTime);

Oscillator* osc;


double render(double dTime)
{
	return (osc->calculate(dTime) * envelope.GetAmplitude(dTime) * 0.5);
}

int main()
{
	string q0;
	cout << "Give waveform for Ocs1\n";
	cin >> q0;
	
	if (q0 == "square")
	{
		osc = &square;
	}

	else if (q0 == "sine")
	{
		osc = &sine;
	}

	else if (q0 == "triangle")
	{
		osc = &triangle;
	}

	else if (q0 == "saw")
	{
		osc = &saw;
	}

	int q1;
	cout << "What's your bpm?\n";
	cin >> q1;

	int q2;
	cout << "\nHow many notes should be in your melody?\n";
	cin >> q2;

	string q3;
	cout << "\nWhat do you want your root to be? (a - as)\n";
	cin >> q3;

	string q4;
	cout << "\nWhat scale do you want to use? You can choose between: \n- major \n- minor \n- phrygian \n- lydian \n- harmonicminor \n- dorian#4 - Kayas Favorite :D\n";
	cin >> q4;

	MelodyGenerator melody(q1, q2, q3, q4);
	melody.generate();
	

	vector<wstring> devices = olcNoiseMaker<short>::Enumerate();

	for (auto d : devices) wcout << "Output Devices:" << d << "\n";

	olcNoiseMaker<short> sound(devices[0], melody.samplerate, 1, 16, 512);

	sound.SetUserFunction(render);

	double preresidue = melody.pitch[0] - 69;
	double pred = preresidue / 12;
	double prefCalc = pow(2, pred) * 440;
	osc->setFrequency(prefCalc);

	for (int f = 0; f < q2 - 1;)
	{
		if (counter == melody.noteLength[f] * melody.eighth)
		{
			envelope.NoteOffTrigger(sound.GetTime());
			cout << melody.pitch[f] << "\n";
			double residue = melody.pitch[f + 1] - 69;
			double d = residue / 12;
			double fCalc = pow(2, d) * 440;
			cout << fCalc << "\n";
			osc->setFrequency(fCalc);
			envelope.NoteOnTrigger(sound.GetTime());
			f++;
			counter = 0;
		}

		else 
		{
			cout << counter << "\n";
			counter++;
		}
	}

	system("cls");
	envelope.NoteOffTrigger(sound.GetTime());
	cout << "You can now play a melody with your computer keyboard, using the z, s, x, c, f, v, g, b, n, j, m and k keys." << "\n";


	double BaseFrequency = 110;
	double calculateNote = pow(2.0, 1.0 / 12.0);

	int CurrentKey = -1;
	bool running = true;
	while (running)
	{

		bool KeyPressed = false;
		for (int k = 0; k < 15; k++)
		{
			if (GetAsyncKeyState((unsigned char)("ZSXCFVGBNJMK\xbcL\xbe"[k])) & 0x8000)
			{
				if (CurrentKey != k)
				{
					double FrequencyOut = BaseFrequency * pow(calculateNote, k);
					osc->setFrequency(FrequencyOut);
					envelope.NoteOnTrigger(sound.GetTime());
					wcout << "\rNote On : " << sound.GetTime() << "s " << FrequencyOut << "Hz";
					CurrentKey = k;
				}

				KeyPressed = true;

			}

		}

		if (!KeyPressed)
		{
			if (CurrentKey != -1)
			{
				wcout << "\rNote Off: " << sound.GetTime() << "s                        ";
				envelope.NoteOffTrigger(sound.GetTime());
				CurrentKey = -1;
			}
		}


	}

	return 0;
}

