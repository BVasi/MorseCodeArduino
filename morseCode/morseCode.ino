#include <Arduino.h>

const int emitterPin = 7;
const int receiverPin = 3;
const int DELAY_BETWEEN_LETTERS = 300;
const int DELAY_BETWEEN_WORDS = 700;
const int DELAY_IN_LETTER = 100;
const int DOT_DISPLAY_TIME = 100;
const int LINE_DISPLAY_TIME = 300;
const int CORRECTION = 1;
unsigned long signalStart;
unsigned long signalStop;
bool hasReceivedSignal = false;
String morseCodeOfTheLetter = "";
String output = "";
String letterToPrint = "";

void displayMorseOfTheLetter()
{
  for (const char& morseLetter : morseCodeOfTheLetter)
  {
    if (morseLetter == '.')
    {
      PORTD |= (1 << emitterPin);
      delay(DOT_DISPLAY_TIME);
      PORTD &= ~(1 << emitterPin);
    }
    else if (morseLetter == '-')
    {
      PORTD |= (1 << emitterPin);
      delay(LINE_DISPLAY_TIME);
      PORTD &= ~(1 << emitterPin);
    }
    delay(DELAY_IN_LETTER);
  }
}

void convertSentenceToMorseCode(const String& sentence)
{
  for(const char& letter : sentence)
  {
    morseCodeOfTheLetter = "";
    if (letter != ' ')
    {
      convertLetterToMorse(letter);
      displayMorseOfTheLetter();
      delay(DELAY_BETWEEN_LETTERS);
    }
    else
    {
      delay(DELAY_BETWEEN_WORDS);
    }
  }
}

void printLetterInBuffer()
{
  letterToPrint += convertMorseToLetter(output);
  Serial.print(letterToPrint);
  letterToPrint = ""; 
  output = "";
}

void translateMorseSignal()
{
  unsigned long signalDuration = signalStop - signalStart;
  unsigned long pauseDuration = signalStart - signalStop;
  if (signalDuration < pauseDuration) //deoarece se da overflow, normal trebuia semnul invers
  {
    if (signalDuration >= (DELAY_IN_LETTER - CORRECTION) && signalDuration <= (DOT_DISPLAY_TIME + CORRECTION))
    {
      output += ".";
    }
    else if (signalDuration >= (DOT_DISPLAY_TIME - CORRECTION) && signalDuration <= (LINE_DISPLAY_TIME + CORRECTION))
    {
      output += "-";
    }
  }
  else
  {
    if (pauseDuration >= (DELAY_IN_LETTER - CORRECTION) && pauseDuration <= (DELAY_BETWEEN_LETTERS + CORRECTION)) //sunt in aceeasi litera astept sa intre iar in if ca sa am tot ce trebuie in output
    {
      return;
    }
    printLetterInBuffer();
    if (pauseDuration >= (DELAY_BETWEEN_WORDS - CORRECTION))
    {
      Serial.print(" ");
    }
  }
}

char convertMorseToLetter(const String& morseLetter)
{
  if (morseLetter == ".-")
  {
    return 'A';
  }
  else if (morseLetter == "-...")
  {
    return 'B';
  }
  else if (morseLetter == "-.-.")
  {
    return 'C';
  }
  else if (morseLetter == "-..")
  {
    return 'D';
  }
  else if (morseLetter == ".")
  {
    return 'E';
  }
  else if (morseLetter == "..-.")
  {
    return 'F';
  }
  else if (morseLetter == "--.")
  {
    return 'G';
  }
  else if (morseLetter == "....")
  {
    return 'H';
  }
  else if (morseLetter == "..")
  {
    return 'I';
  }
  else if (morseLetter == ".---")
  {
    return 'J';
  }
  else if (morseLetter == "-.-")
  {
    return 'K';
  }
  else if (morseLetter == ".-..")
  {
    return 'L';
  }
  else if (morseLetter == "--")
  {
    return 'M';
  }
  else if (morseLetter == "-.")
  {
    return 'N';
  }
  else if (morseLetter == "---")
  {
    return 'O';
  }
  else if (morseLetter == ".--.")
  {
    return 'P';
  }
  else if (morseLetter == "--.-")
  {
    return 'Q';
  }
  else if (morseLetter == ".-.")
  {
    return 'R';
  }
  else if (morseLetter == "...")
  {
    return 'S';
  }
  else if (morseLetter == "-")
  {
    return 'T';
  }
  else if (morseLetter == "..-")
  {
    return 'U';
  }
  else if (morseLetter == "...-")
  {
    return 'V';
  }
  else if (morseLetter == ".--")
  {
    return 'W';
  }
  else if (morseLetter == "-..-")
  {
    return 'X';
  }
  else if (morseLetter == "-.--")
  {
    return 'Y';
  }
  else if (morseLetter == "--..")
  {
    return 'Z';
  }
}

void convertLetterToMorse(const char& letter)
{
  switch(tolower(letter))
    {
      case ('a'):
      {
        morseCodeOfTheLetter = ".-";
        break;
      }
      case ('b'):
      {
        morseCodeOfTheLetter = "-...";
        break;
      }
      case ('c'):
      {
        morseCodeOfTheLetter = "-.-.";
        break;
      }
      case ('d'):
      {
        morseCodeOfTheLetter = "-..";
        break;
      }
      case ('e'):
      {
        morseCodeOfTheLetter = ".";
        break;
      }
      case ('f'):
      {
        morseCodeOfTheLetter = "..-.";
        break;
      }
      case ('g'):
      {
        morseCodeOfTheLetter = "--.";
        break;
      }
      case ('h'):
      {
        morseCodeOfTheLetter = "....";
        break;
      }
      case ('i'):
      {
        morseCodeOfTheLetter = "..";
        break;
      }
      case ('j'):
      {
        morseCodeOfTheLetter = ".---";
        break;
      }
      case ('k'):
      {
        morseCodeOfTheLetter = "-.-";
        break;
      }
      case ('l'):
      {
        morseCodeOfTheLetter = ".-..";
        break;
      }
      case ('m'):
      {
        morseCodeOfTheLetter = "--";
        break;
      }
      case ('n'):
      {
        morseCodeOfTheLetter = "-.";
        break;
      }
      case ('o'):
      {
        morseCodeOfTheLetter = "---";
        break;
      }
      case ('p'):
      {
        morseCodeOfTheLetter = ".--.";
        break;
      }
      case ('q'):
      {
        morseCodeOfTheLetter = "--.-";
        break;
      }
      case ('r'):
      {
        morseCodeOfTheLetter = ".-.";
        break;
      }
      case ('s'):
      {
        morseCodeOfTheLetter = "...";
        break;
      }
      case ('t'):
      {
        morseCodeOfTheLetter = "-";
        break;
      }
      case ('u'):
      {
        morseCodeOfTheLetter = "..-";
        break;
      }
      case ('v'):
      {
        morseCodeOfTheLetter = "...-";
        break;
      }
      case ('w'):
      {
        morseCodeOfTheLetter = ".--";
        break;
      }
      case ('x'):
      {
        morseCodeOfTheLetter = "-..-";
        break;
      }
      case ('y'):
      {
        morseCodeOfTheLetter = "-.--";
        break;
      }
      case ('z'):
      {
        morseCodeOfTheLetter = "--..";
        break;
      }
      default:
      {
        morseCodeOfTheLetter = "";
        break;
      }
    }
}

void handleInterrupt() 
{
  if (hasReceivedSignal == false)
  {
    signalStart = millis();
    hasReceivedSignal = true;
  }
  else
  {
    signalStop = millis();
    hasReceivedSignal = false;
  }
  translateMorseSignal();
}

String readFromSerial()
{
  String inputString = "";
  while (Serial.available())
  {
    inputString += (char)Serial.read();
  }

  return inputString;
}

void setup() 
{
  DDRD |= (1 << emitterPin);
  attachInterrupt(digitalPinToInterrupt(receiverPin), handleInterrupt, CHANGE);
  Serial.begin(9600);
}

void loop() 
{
  delay(1000);
  Serial.println("Introduceti textul care vreti sa fie codificat, iar mai apoi decodificat!");
  convertSentenceToMorseCode(readFromSerial());
  printLetterInBuffer();
}