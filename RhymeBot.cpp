#include "RhymeBot.h"
#include <iostream>
#include <map>
#include <vector>

using namespace std;



/** Inserting Words **/

void RhymeBot::insertWithPronunciation(string word, vector<Sound> pronunciation){
    std::map<string, vector<Sound>>::iterator it;
    // The following lines should be removed. They are here to show what is being added to you data structures
    it = wordNsounds.begin();
    wordNsounds.insert( std::pair<string, vector<Sound>>(word, pronunciation) );


   /* for (it; it != wordNsounds.end(); it++){
        cout << it->first<<": ";
        vector<Sound> value =  it->second;
        for(int i = 0; i<value.size(); i++){
            cout << value.at(i)<<" ";
        }
        cout<<endl;
    }*/


    /*cout << word << ": ";
    for(int i=0; i<pronunciation.size(); i++){
        cout << pronunciation.at(i) << " ";
    }
    cout << endl;
*/
}

void RhymeBot::addPartOfSpeech(string word, PART_OF_SPEECH partOfSpeech){
    std::map<string, PART_OF_SPEECH>::iterator it = wordNpartsOfSpeech.begin();
    //string theWord = wordNsounds.find(word);
    if(wordNsounds.find(word) == wordNsounds.end()){

    }else{


        if(wordNpartsOfSpeech.find(word)!= wordNpartsOfSpeech.end()){

           //cout << word << "Overwritten" << endl;
           wordNpartsOfSpeech.erase(wordNpartsOfSpeech.find(word));
        }

     wordNpartsOfSpeech.insert( std::pair<string, PART_OF_SPEECH>(word, partOfSpeech) );
       //wordNpartsOfSpeech[word] = partOfSpeech;
    }


    //it2 = wordNpartsOfSpeech.begin();

    /*for (it2; it2 != wordNpartsOfSpeech.end(); it2++){
        cout << it2->first<<": ";
        int value =  it2->second;
        cout<<value<< " but should be: "<<partOfSpeech<<endl;
    }*/

    // The following line should be removed. They are here to show what is being added to you data structures
   // cout << word << ": " << partOfSpeech << endl;

}


/** Helper Functions **/

// returns the number of syllables in word
int RhymeBot::countSyllables(string word){
    int counter = 0;

   vector<Sound> theSounds = wordNsounds.find(word)->second;

    for(int i = 0; i<theSounds.size(); i++){
    if(theSounds.at(i).isVowel()){
    counter = counter + 1;
    }
}

return counter;
}



// returns the number of rhyming syllables in the two words. This is defined as the number of vowel sounds in the
//  largest rhyming suffix.
//
// Words are considered a rhyme if they have the same last vowel sound as well as the same sounds following
//  the last vowel. Note: These are syllabic rhymes since the matching vowels might not both be stressed
int RhymeBot::rhymingSyllables(string word1, string word2){
    //cout<<"word1: "<<word1<<endl;
    //cout<<"word2: "<<word2<<endl;

    int counter = 0;

    vector<Sound> pronun1 = wordNsounds.find(word1)->second;
    /*cout<<"vec: ";
    for(int a = 0; a < pronun1.size(); a++){
       cout <<pronun1.at(a)<<" ";
    }
    cout<<endl;*/

    vector<Sound> pronun2 = wordNsounds.find(word2)->second;
    /*cout<<"vec: ";
    for(int b = 0; b < pronun2.size(); b++){
        cout<<pronun2.at(b)<<" ";
    }
    cout<<endl;*/

    vector<Sound> alikeSounds;


            int i = pronun1.size()-1;
            int j = pronun2.size()-1;

        while(i >= 0 && j >= 0){

            if(pronun1.at(i) == pronun2.at(j)){
                alikeSounds.push_back( pronun1.at(i) );


            }else if(pronun1.at(i) != pronun2.at(j)){
                break;
            }

                i--;
                j--;

        }


    for(int x = 0; x < alikeSounds.size(); x++){
            if(alikeSounds.size() == 0){
          //          cout<<"No Rhyming Syls"<<endl;
                return 0;
            }
        else if(alikeSounds.at(x).isVowel()){
            counter = counter + 1;
        }
    }
    //cout<<"# of rhyming syls: "<<counter<<endl;
    return counter;
}

// returns the number of identical sounds in the largest matching prefix of the two words.
//
// Words are considered an alliteration if they have the same first sound
int RhymeBot::alliterationSounds(string word1, string word2){

    vector<Sound> pronun1 = wordNsounds.find(word1)->second;

    vector<Sound> pronun2 = wordNsounds.find(word2)->second;

    vector<Sound> alikeSounds;

           int i = 0;
           int j = 0;

        while(i < pronun1.size() && j < pronun2.size()){
            if(pronun1.at(i) == pronun2.at(j)){
                alikeSounds.push_back( pronun1.at(i) );

            }else if(pronun1.at(i) != pronun2.at(j)){
                    break;
            }
                i++;
                j++;
        }

    return alikeSounds.size();
}


/** Search for Rhymes and Alliterations **/

// returns all words that rhyme at least 1 syllable with the input word
// returns the empty vector if no rhymes are found or if the given word is not in the dictionary
vector<string>* RhymeBot::getAllRhymes(string word){
    vector<string>* rhymingWords = new vector<string>;
    std::map<string, vector<Sound>>::iterator it;
    it = wordNsounds.begin();
    for(it; it != wordNsounds.end(); it++){
       string wordInDic = it->first;
        if(rhymingSyllables(word, wordInDic) > 0){
            rhymingWords->push_back( wordInDic );

        }
    }

    return rhymingWords;
}

// returns all words that form an alliteration of at least 1 sound with the input word
// returns the empty vector if no rhymes are found or the given word is not known
vector<string>* RhymeBot::getAllAlliterations(string word){
    vector<string>* alliterationWords = new vector<string>;
    std::map<string, vector<Sound>>::iterator it;
    it = wordNsounds.begin();
    for(it; it!= wordNsounds.end(); it++){
        string wordInDic = it->first;
         if(alliterationSounds(word, wordInDic) > 0){
            alliterationWords->push_back( wordInDic );
         }
    }

    return alliterationWords;
}


/** Finding the Perfect Word **/

// returns the best word with the specified number of syllables and part of speech that rhymes with the given word.
// Best is defined by the maximum number of rhyming syllables.
string RhymeBot::findBestRhyme(int numberOfSyllables, string rhymesWith){
    int largest = 0;
    string bestWord = "";
    vector<string>* rhymingWords = getAllRhymes(rhymesWith);
    for(int i = 0; i < rhymingWords->size(); i++){
        string wordInDic = rhymingWords->at(i);
        int numofSylsInDicWord = countSyllables(wordInDic);

    if(numofSylsInDicWord == numberOfSyllables){
        int rhymingSyls = rhymingSyllables(rhymesWith, wordInDic);
            if(rhymingSyls > largest){
                largest = rhymingSyls;
                bestWord = wordInDic;
            }
        }
    }

    return bestWord;
}
string RhymeBot::findBestRhyme(PART_OF_SPEECH pos, string rhymesWith){
     string bestWord = "";
     int largest = 0;
     vector<string>* rhymingWords = getAllRhymes(rhymesWith);
    for(int i = 0; i < rhymingWords->size(); i++){
        string wordInDic = rhymingWords->at(i);
        //cout<<"\" "<<wordInDic<<" \""<<" rhymes with (& is in rhym vec) "<<rhymesWith<<endl;
        if(wordNpartsOfSpeech.find(wordInDic) != wordNpartsOfSpeech.end()){
        PART_OF_SPEECH widPos = wordNpartsOfSpeech.at(wordInDic);
            if(widPos == pos){
     //cout<<"Part of Speech for this word is: \""<<widPos<<"\" But should be: \""<<pos<<"\""<<" and the word is: \" "<<wordInDic<<" \""<<endl;
            int rhymingSyls = rhymingSyllables(rhymesWith, wordInDic);
               // cout<<"Number of Rhyming Syls: "<<rhymingSyls<<endl;
            if(rhymingSyls > largest){
                largest = rhymingSyls;
                bestWord = wordInDic;
            }
        }
    }else{}
    }
        //cout<<"Best Word: "<<bestWord<<endl;
    return bestWord;
}
string RhymeBot::findBestRhyme(int numberOfSyllables, PART_OF_SPEECH pos, string rhymesWith){

    string bestWord = "";
    int largest = 0;
      vector<string>* rhymingWords = getAllRhymes(rhymesWith);
for(int i = 0; i < rhymingWords->size(); i++){
    string wordInDic = rhymingWords->at(i);
        int numofSylsInDicWord = countSyllables(wordInDic);
            PART_OF_SPEECH widPos = wordNpartsOfSpeech.find(wordInDic)->second;
    if(widPos == pos){
        if(numofSylsInDicWord == numberOfSyllables){
            int rhymingSyls = rhymingSyllables(rhymesWith, wordInDic);
                if(rhymingSyls > largest){
                    largest = rhymingSyls;
                    bestWord = wordInDic;
                }
            }
        }
    }
    return bestWord;
}

// returns the best word with the specified number of syllables and part of speech that forms an alliteration with
// the given word. Best is defined by the number of maximum number of alliterating sounds.
string RhymeBot::findBestAlliteration(int numberOfSyllables, string alliterationWith){
    int largest = 0;
    string bestWord = "";
    vector<string>* alliteratingWords = getAllAlliterations(alliterationWith);
    for(int i = 0; i < alliteratingWords->size(); i++){
        string wordInDic = alliteratingWords->at(i);
        int numofSylsInDicWord = countSyllables(wordInDic);

    if(numofSylsInDicWord == numberOfSyllables){
        int alliteratingSounds = alliterationSounds(alliterationWith, wordInDic);
            if(alliteratingSounds > largest){
                largest = alliteratingSounds;
                bestWord = wordInDic;
            }
        }
    }

    return bestWord;
}
string RhymeBot::findBestAlliteration(PART_OF_SPEECH pos, string alliterationWith){
     string bestWord = "";
     int largest = 0;
     vector<string>* alliteratingWords = getAllAlliterations(alliterationWith);
    for(int i = 0; i < alliteratingWords->size(); i++){
        string wordInDic = alliteratingWords->at(i);
        //cout<<"\" "<<wordInDic<<" \""<<" rhymes with (& is in rhym vec) "<<rhymesWith<<endl;
        if(wordNpartsOfSpeech.find(wordInDic) != wordNpartsOfSpeech.end()){
        PART_OF_SPEECH widPos = wordNpartsOfSpeech.at(wordInDic);
            if(widPos == pos){
     //cout<<"Part of Speech for this word is: \""<<widPos<<"\" But should be: \""<<pos<<"\""<<" and the word is: \" "<<wordInDic<<" \""<<endl;
            int alliteratingSounds = alliterationSounds(alliterationWith, wordInDic);
               // cout<<"Number of Rhyming Syls: "<<rhymingSyls<<endl;
            if(alliteratingSounds > largest){
                largest = alliteratingSounds;
                bestWord = wordInDic;
            }
        }
    }else{}
    }
        //cout<<"Best Word: "<<bestWord<<endl;
    return bestWord;
}
string RhymeBot::findBestAlliteration(int numberOfSyllables, PART_OF_SPEECH pos, string alliterationWith){
     string bestWord = "";
    int largest = 0;
      vector<string>* alliteratingWords = getAllAlliterations(alliterationWith);
for(int i = 0; i < alliteratingWords->size(); i++){
    string wordInDic = alliteratingWords->at(i);
    if(wordNpartsOfSpeech.find(wordInDic) != wordNpartsOfSpeech.end()){
        int numofSylsInDicWord = countSyllables(wordInDic);
            PART_OF_SPEECH widPos = wordNpartsOfSpeech.find(wordInDic)->second;
    if(widPos == pos){
        if(numofSylsInDicWord == numberOfSyllables){
            int alliteratingSounds = alliterationSounds(alliterationWith, wordInDic);
                if(alliteratingSounds > largest){
                    largest = alliteratingSounds;
                    bestWord = wordInDic;
                }
            }
        }
    }else{}
}
    return bestWord;
}

// Combine findBestRhyme and findBestAlliteration. Best is defined by the sum of the number of rhyming syllables
//  and the number of alliterating sounds.
string RhymeBot::findPerfectWord(int numberOfSyllables, PART_OF_SPEECH pos, string rhymesWith, string alliterationWith){

    int largest = 0;
    string perfectWord = "";
    vector<string>* alliteratingWords = getAllAlliterations(alliterationWith);
    vector<string>* rhymingWords = getAllRhymes(rhymesWith);
    vector<string>* shortenedList = new vector<string>;
     // vector<string>::iterator it2 = shortenedList->begin();
        for(int i = 0; i<alliteratingWords->size(); i++){
            string wordInDic = alliteratingWords->at(i);
            int numofSyls = countSyllables(wordInDic);
            PART_OF_SPEECH widPos = wordNpartsOfSpeech.find(wordInDic)->second;
          if(numofSyls == numberOfSyllables && widPos == pos){
            shortenedList->push_back(wordInDic);
          }
        }
        for(int j = 0; j<rhymingWords->size(); j++){
            string wordInDic2 = rhymingWords->at(j);
            int numofSyls2 = countSyllables(wordInDic2);
            PART_OF_SPEECH widPos2 = wordNpartsOfSpeech.find(wordInDic2)->second;
          if(numofSyls2 == numberOfSyllables && widPos2 == pos){
            shortenedList->push_back(wordInDic2);
          }
        }
        for(int k = 0; k<shortenedList->size(); k++){
            string wordInList = shortenedList->at(k);
            int numOfRhymSyls = rhymingSyllables(wordInList, rhymesWith);
            int numOfAlliSounds = alliterationSounds(wordInList, alliterationWith);
            int combo = numOfRhymSyls + numOfAlliSounds;
            if(combo > largest && numOfRhymSyls>0 && numOfAlliSounds>0){
                largest = combo;
                perfectWord = wordInList;
            }
        }

    return perfectWord;
}
