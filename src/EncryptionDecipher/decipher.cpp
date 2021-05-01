/* Blake Rude
 *
 * Code to determine a cipher key
 * for an asymmetrically encrypted 
 * letter only key
 * a96 is a sample of input to supply
 * 
 * Does this by analyzing next letter probabilities
 * based on letter frequencies in the English language
 * 
 * V 1.0 - 18 October 2020
 */


#include "rand.cpp"
#include "Frequency.cpp"
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <bitset>
#include <time.h>
#include <iomanip>
#include <string>
using namespace std;

/* Function Definitions */
double sumFreq(double sum);
double Construct_contactTable(double sum, double EcontactTable[][26]);
int e(char i, char key[26]);
double fit(char key[26], double EcontactTable[][26], double CcontactTable[][26]);
/* Vars */
char alphabet[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

int main(int argc, char* argv[]){
  initRand();  
  double EcontactTable[26][26];
    int CCountTable[26][26];
    double CcontactTable[26][26];
    double sum = sumFreq(sum);
    int PopSize = 30;
    char key[PopSize][26];
    char keytemp[PopSize][26];
    double fitV[PopSize];
    char* ciphertextBUFFER = new char[10000];
    int cipherlen=0;
    Construct_contactTable(sum, EcontactTable);
    char c;
    int q = 0;
    for(int i=0; i<PopSize; i++){
      for(int j=0; j<26; j++){
	key[i][j] = (char)(j+97);
	keytemp[i][j] = key[i][j];
      }
    }
    while(cin >> c){
      if(c == 'a' || c == 'b' || c == 'c' || c == 'd' || c == 'e' || c == 'f' || c == 'g' || c == 'h' || c == 'i' || c == 'j' || c == 'k' || c == 'l' || c == 'm' || c == 'n' || c == 'o' || c == 'p' || c == 'q' || c == 'r' || c == 's' || c == 't' || c == 'u' || c == 'v' || c == 'w' || c == 'x' || c == 'y' || c == 'z')
	{
	  ciphertextBUFFER[q] = c;
	  q++;
	}
      else if(c == 'A' || c == 'B' || c == 'C' || c == 'D' || c == 'E' || c == 'F' || c == 'G' || c == 'H' || c == 'I' || c == 'J' || c == 'K' || c == 'L' || c == 'M' || c == 'N' || c == 'O' || c == 'P' || c == 'Q' || c == 'R' || c == 'S' ||c == 'T' || c == 'U' || c == 'V' || c == 'W' || c == 'X' || c == 'Y' || c == 'Z')
	{
	  ciphertextBUFFER[q] = tolower(c);
	  q++;
	}
    }
    cipherlen = q;
    char ciphertext[cipherlen];
    for(int i=0; i<cipherlen; i++){
      ciphertext[i] = ciphertextBUFFER[i];
    }
    delete[] ciphertextBUFFER;
    
    for(int i=0; i<26; i++){
      for(int j=0; j<26; j++){
	CCountTable[i][j] = 0;
      }
    }
    
    //Make cipher contact table, then normalize
    int ciphertextINT[cipherlen];
    for(int i=0; i<cipherlen; i++){
      ciphertextINT[i] = ((int)ciphertext[i]) - 97;
    }
    for(int i=0; i<cipherlen; i++){
      CCountTable[ciphertextINT[i]][ciphertextINT[i+1]] += 1;
    }
    sum = 0;
    
    for(int i=0; i<26; i++){
      for(int j=0; j<26; j++){
	sum = sum + CCountTable[i][j];
      }
    }
    for(int i=0; i<26; i++){
      for(int j=0; j<26; j++){
	CcontactTable[i][j] = ((CCountTable[i][j])/sum);
      }
    }  
    //START GA
    /* Initialize */
    int gencount = 1;
    int t, rd;
    int mask[26];
    int child[26];
    double tempfit = 0.0;
    double bestfit = -1.0;
    for(int i=0; i<PopSize; i++){
      int k;
      for(int j=26-1; j; j--){
	int tmp;
	k = randMod(j+1);
	tmp = key[i][j];
	key[i][j] = key[i][k];
	key[i][k] = tmp;
      }
    }
    for(int i=0; i<PopSize; i++){
      fitV[i] = fit(key[i], EcontactTable, CcontactTable);
    }

    double Px = 1.0;
    double Pm = 1.0;
    while(gencount <= 100000){
      int bestF = -1;
      int secondF = -1;
      double cBest = -100.0;
      for(int i=0; i<PopSize; i++){
	if(fitV[i] > cBest){
	  cBest = fitV[i];
	  bestF = i;
	}
      }
      cBest = -100.0;
      for(int i=0; i<PopSize; i++){
	if(fitV[i] > cBest && i != bestF){
	  cBest = fitV[i];
	  secondF = i;
	}
      }
      for(int i=0; i<26; i++){
	keytemp[0][i] = key[bestF][i];
      }
      for(int i=0; i<26; i++){
        keytemp[1][i] = key[secondF][i];
      }

      for(int i=2; i < PopSize; i++){
	if(((double)rand()/(RAND_MAX + 1.)) < Px){ 
	  char child[26];
	  int start = -1, end = -1;
	  int num_allele=0;
	  int usedIndex = 0;
	  char usedLetters[26];
	  
	  for(int j=0; j<26; j++){
	    if(rand() % 3 == 1){
	      start = j;
	      usedLetters[usedIndex] = key[i][j];
	      usedIndex++;
	      j++;
	      num_allele = 1;
	      for(int x=j; x<26; x++){
		if(((double)rand()/(RAND_MAX + 1.)) < 0.65){
		  usedLetters[usedIndex] = key[i][x];
		  usedIndex++;
		  num_allele++;
		}
		else{
		  end = x;
		  j = 30;
		  break;
		}
	      }
	    }
	    else{
	    }
	  }
	  bool isin = false;
	  for(int j=start; j<end+1;j++){
	    child[j] = key[i][j];
	  }
	  for(int j=0; j<26; j++){
	    isin = false;
	    if(j < start || j > end){
	      for(int x=0; x<num_allele; x++){
		if(usedLetters[x] == key[i+1][j]){
		  isin = true;
		}
	      }
	      if(! isin){
		child[j] = key[i+1][j];
		usedLetters[usedIndex] = child[j];
		num_allele++;
		usedIndex++;
	      }
	    }
	  }
	  isin = false;
	  for(int j=0; j<26; j++){
            isin = false;
	    if(1){
              for(int x=0; x<num_allele; x++){
                if(usedLetters[x] == key[i][j]){
                  isin = true;
                }
              }
              if(! isin){
                child[j] = key[i][j];
                usedLetters[usedIndex] = child[j];
                num_allele++;
		usedIndex++;
              }
            }
          }
	  for(int j=0; j<26; j++){
	    keytemp[i][j] = child[j];
	  }
	}
	if(((double)rand()/(RAND_MAX + 1.)) < Pm){
	  int ind1, ind2;
	  ind1= rand() % 26;
	  ind2= rand() % 26;
	  while(ind2 == ind1){
	    ind2= rand() % 26;
	  }
	  for(int j=0; j<26; j++){
	    if(j == ind1 || j == ind2){
	      keytemp[i][ind1] = key[i][ind2];
	      keytemp[i][ind2] = key[i][ind1];
 	    }
	    else{
	      keytemp[i][j] = key[i][j];
	    }
	  }
	}
      }
      for(int x=0; x<PopSize; x++){
	for(int y=0; y<26; y++){
	  key[x][y] = keytemp[x][y];
	}
      }
      
      for(int x=0; x<PopSize; x++){
	fitV[x] = fit(key[x], EcontactTable, CcontactTable);
      }
      
      for(int x=0; x<PopSize; x++){
        for(int y=0; y<26; y++){
          keytemp[x][y] = ' ';
        }
      }
      for(int i=0; i<PopSize; i++){
	for(int j=0; j<26; j++){
	}
      }
      gencount++;
    }
    cout << "** BlakeRude ";
    for(int i=0; i<26; i++){
      cout << key[0][i];
    }
    cout << " " << fitV[0] << endl;
}
//end of main, start of other functions

double sumFreq(double sum){
    sum = 0;
    for(int i=0; i<26; i++){
        for(int j=0; j<26; j++){
            sum = sum + english[i][j];
        }
    }
    return sum;
}
// End of sumFreq()

double Construct_contactTable(double sum, double EcontactTable[][26]){
  for(int i=0; i<26; i++){
    for(int j=0; j<26; j++){
      EcontactTable[i][j] = ((english[i][j])/sum);
    }
  }
}
//End of Construct_contactTable()

int e(int i, char key[26]){
  int index = 0;
  index = (char)(key[i] - 97);
  return index;
}
//End of e()

double fit(char key[26], double EcontactTable[][26], double CcontactTable[][26]){
  double sum = 0;
  double temp;
  for(int i=0; i<26; i++){
    for(int j=0; j<26; j++){
      temp = (EcontactTable[i][j]) - (CcontactTable[e(i,key)][e(j,key)]); 
      sum = sum + (temp*temp);;
    }
  }
  sum = sum*(-1);
  return sum;
}