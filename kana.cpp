//Kana.cpp

#include <iostream>
#include <string>
#include <vector>
#include <random>

using namespace std;

const string kana =
//Hiragana
	"あいうえお"
	"かきくけこ"
	"さしすせそ"
	"たちつてと"
	"なにぬねの"
	"はひふへほ"
	"まみむめも"
	"やゆよ"
	"らりるれろ"
	"わを"
	"ん"
//Hiragana Accents
	"がぎぐげご"
	"ざじずぜぞ"
	"だぢづでど"
	"ぱぴぷぺぽ"
	"ばびぶべぼ"
//Katakana
	"アイウエオ"
	"カキクケコ"
	"サシスセソ"
	"タチツテト"
	"ナニヌネノ"
	"ハヒフヘホ"
	"マミムメモ"
	"ヤユヨ"
	"ラリルレロ"
	"ワヲ"
	"ン"
//Katakana Accents
	"ガギグゲゴ"
	"ザジズゼゾ"
	"ダヂヅデド"
	"パピプペポ"
	"バビブベボ"
;
const int numKana = 46;
const int numKanaAccents = 25;
const vector<string> romanji = {
//Romanji
	"a", "i", "u", "e", "o",
	"ka", "ki", "ku", "ke", "ko",
	"sa", "shi", "su", "se", "so",
	"ta", "chi", "tsu", "te", "to",
	"na", "ni", "nu", "ne", "no",
	"ha", "hi", "fu", "he", "ho",
	"ma", "mi", "mu", "me", "mo",
	"ya", "yu", "yo",
	"ra", "ri", "ru", "re", "ro",
	"wa", "wo",
	"n",
//Romanji Accents
	"ga", "gi", "gu", "ge", "go",
	"za", "ji", "zu", "ze", "zo",
	"da", "ji", "zu", "de", "do",
	"pa", "pi", "pu", "pe", "po",
	"ba", "bi", "bu", "be", "bo"
};

int main(int argc, char *argv[]) {
	bool running = true;
	char charsetChoice = '\0';
	char accentChoice = '\0';
	bool useHiragana = false;
	bool useKatakana = false;
	bool useAccents = false;
	int numChars = 0;
	int alphabetSize = 0;
	vector<int> key;
	string input = "";
	int numCorrect = 0;

	//Character set choice
	if(argc == 4) {
		charsetChoice = *argv[1];
	} else {
		cout << "(H)iragana, (K)atakana, or (B)oth? ";
		cin >> charsetChoice;
	}
	switch(charsetChoice) {
		case 'h':
		case 'H':
			useHiragana = true;
			useKatakana = false;
			break;
		case 'k':
		case 'K':
			useHiragana = false;
			useKatakana = true;
			break;
		case 'b':
		case 'B':
			useHiragana = true;
			useKatakana = true;
			break;
		default:
			cout << "Invalid input!" << endl;
			running = false;
			break;
	}

	//Accent choice
	if(argc == 4) {
		accentChoice = *argv[2];
	} else {
		cout << "Include accents (y/n)? ";
		cin >> accentChoice;
	}
	switch(accentChoice) {
		case 'y':
		case 'Y':
			useAccents = true;
			break;
		case 'n':
		case 'N':
			useAccents = false;
			break;
		default:
			cout << "Invalid input!" << endl;
			running = false;
			break;
	}

	//Alphabet size
	if(useHiragana) {
		alphabetSize += numKana;
		if(useAccents) {
			alphabetSize += numKanaAccents;
		}
	}
	if(useKatakana) {
		alphabetSize += numKana;
		if(useAccents) {
			alphabetSize += numKanaAccents;
		}
	}

	//Number of characters
	if(argc == 4) {
		numChars = stoi(argv[3]);
	} else {
		cout << "How many characters would you like to study? ";
		cin >> numChars;
	}

	//Output kana
	random_device rd;
	cout << "Kana: ";
	for(int i = 0; i < numChars; i++) {
		//Get random number
		int num = rd() % alphabetSize;
		
		//Account for gaps in alphabet
		if(!useHiragana) {
			num += numKana + numKanaAccents;
		}
		if(!useAccents) {
			if(num > numKana && num < numKana + numKanaAccents) {
				num += numKanaAccents;
			}
		}

		//Find character, output the kana, and store the romanji
		key.push_back(num);
		cout << kana.at(num * 3);	//UTF-8 Japanese characters are 3 chars wide
		cout << kana.at(num * 3 + 1);
		cout << kana.at(num * 3 + 2);
	}
	cout << endl;

	cout << "Translate: ";

	for(int i = 0; i < numChars; i++) {
		//Shift katakana to hiragana
		if(key.at(i) > numKana + numKanaAccents) {
			key.at(i) -= numKana + numKanaAccents;
		}

		//Compare inputs with key
		cin >> input;
		if(romanji.at(key.at(i)).compare(input) == 0) {
			numCorrect++;
			cout << ". " << kana.at(key.at(i)*3) << kana.at(key.at(i)*3+1) << kana.at(key.at(i)*3+2) << endl;
		} else {
			cout << romanji.at(key.at(i)) << " " << kana.at(key.at(i)*3) << kana.at(key.at(i)*3+1) << kana.at(key.at(i)*3+2) << endl;
		}
	}

	cout << "Number correct: " << numCorrect << " (" << (numCorrect*100)/numChars << "%)" << endl;

	return 0;
}
