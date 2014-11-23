/*
  writes a message in morse code
  (adapted from the "Blink" example - Louis O'Callaghan Jan 2013)
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int output = 13;

// dots and dashes as per the international standard
// http://en.wikipedia.org/wiki/Morse_code

// this determines the keying speed
int unit = 200;

int dot = unit;
int dash = unit * 3;
int keySpace = unit;
int charSpace = unit * 3;
int wordSpace = charSpace * 2;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(output, OUTPUT);     
}

// the loop routine runs over and over again forever:
void loop() {
  keyMessage("0 1 2 3 4 hello out there");
}

// supply a string and the program keys it to output in morse
void keyMessage(char *message)
{
  int i = 0;
  while (message[i] != '\0')
  {
    char next = message[i + 1];
    if (message[i] == ' ')
    {
      delay(wordSpace);
    }
    else
    {
      
      char* morseString;
      getMorse(message[i], morseString);
      keyLetter(morseString);
      // if a non-whitespace character is next then wait a bit
      if (next != '\0' && next != ' ')
        delay(charSpace);
    }
    i++;
  }
}

// takes a string representation of a morse letter and keys it
// (periods and dashes only, like this: "-.-" for 'K')
void keyLetter(char *letter)
{
  char* morseString;
  getMorse(letter, morseString);


  int i = 0;
  while (letter[i] != '\0')
  {
    if (letter[i] == '.')
    {
      key(dot);
    }
    else if (letter[i] == '-')
    {
      key(dash);
    }
    // if this isn't end of string then wait a bit
    if (letter[++i] != '\0')
      delay(keySpace);
  }
}

// key on for some time period
void key(int milliseconds)
{
  digitalWrite(output, HIGH);
  delay(milliseconds);
  digitalWrite(output, LOW);
}

// converts a character to a string of morse dots and dashes
// ignores case and anything that's not 0-9 and a-z and space
void getMorse(char character, char *morseString)
{
  if (character > 47 && character < 58)
  {
    getMorseNumber(character, morseString);
    return;
  }
    
  // toLower
  if (character > 64 && character < 91)
    character += 32;
  
  switch(character)
  {
    case 'a':
      morseString = ".-";
      break;
    case 'b':
      morseString = "-...";
      break;
    case 'c':
      morseString = "-.-.";
      break;
    case 'd':
      morseString = "-..";
      break;
    case 'e':
      morseString = ".";
      break;
    case 'f':
      morseString = "..-.";
      break;
    case 'g':
      morseString = "--.";
      break;
    case 'h':
      morseString = "....";
      break;
    case 'i':
      morseString = "..";
      break;
    case 'j':
      morseString = ".---";
      break;
    case 'k':
      morseString = "-.-";
      break;
    case 'l':
      morseString = ".-..";
      break;
    case 'm':
      morseString = "--";
      break;
    case 'n':
      morseString = "-.";
      break;
    case 'o':
      morseString = "---";
      break;
    case 'p':
      morseString = ".--.";
      break;
    case 'q':
      morseString = "--.-";
      break;
    case 'r':
      morseString = ".-.";
      break;
    case 's':
      morseString = "...";
      break;
    case 't':
      morseString = "-";
      break;
    case 'u':
      morseString = "..-";
      break;
    case 'v':
      morseString = "...-";
      break;
    case 'w':
      morseString = ".--";
      break;
    case 'x':
      morseString = "-..-";
      break;
    case 'y':
      morseString = "-.--";
      break;
    case 'z':
      morseString = "--..";
      break;
    case ' ':
      morseString = " ";
      break;
    default:
      morseString = "";
      break;
  }
}

// trying to be clever and produce the pattern algorythmically
void getMorseNumber(char number, char *morseNumber)
{
    if (number < 48 || number > 57)
      return;
      
    for (int i = 0; i < 5; i++)
      morseNumber[i] = 45 + (((number - i > 48) && (number - i < 54)) ? 1 : 0);

    morseNumber[5] = '\0';
}

