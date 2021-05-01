/* Author: Blake Rude
 *
 * To run the knapsack, need to have proper command line
 * arguments.
 * argv[1] Population Size
 * argv[2] Maximum Generations
 * argv[3] Tournament Selection Size
 * argv[4] Mutation Probability
 * argv[5] Crossover Probability
 * 
 * V 1.0 -  3 October 2020
 */

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <bitset>
#include <time.h>
#include <iomanip>
using namespace std;

double bestfit;
int b = -1;

/* Function Definitions */
double fitnessFunction(int solution[], double weights[], int j, int maxwt);
bool goodenough(double fitV[], int PopSize, int maxwt);
int best(double fitV[], int PopSize);
int secondbest(double fitV[], int PopSize, int best);

int main(int argc, char *argv[])
{
  cout << setprecision(6) << fixed;
  srand(time(NULL));
  /* Command Line Vars */
  int PopSize = atoi(argv[1]);
  int maxGenerations = atoi(argv[2]);
  int tSize = atoi(argv[3]);
  double Pm = atof(argv[4]);
  double Px = atof(argv[5]);
  /* stdin Vars */
  int maxwt;
  cin >> maxwt;
  int k;
  cin >> k;
  Pm = (Pm / k);
  double weights[k];
  for (int i = 0; i < k; i++)
  {
    cin >> weights[i];
  }
  /* Other Vars */
  int load;
  int solution[PopSize][k];
  int solutionprime[PopSize][k];
  double fitV[PopSize];

  int r;
  for (int i = 0; i < PopSize; i++)
  {
    for (int n = 0; n < k; n++)
    {
      r = rand() % 2;
      solution[i][n] = r;
      solutionprime[i][n] = -1;
    }
  }
  /* Initialize */
  int gencount = 1;
  int t, rd;
  int mask[k];
  int child[k];
  double S;
  double bestS = -999.0;
  for (int i = 0; i < PopSize; i++)
  {
    fitV[i] = fitnessFunction(solution[i], weights, k, maxwt);
  }
  while (not goodenough(fitV, PopSize, maxwt) && gencount <= maxGenerations)
  {
    t = best(fitV, PopSize);
    for (int i = 0; i < k; i++)
    {
      solutionprime[0][i] = solution[t][i];
    }
    t = secondbest(fitV, PopSize, t);
    for (int i = 0; i < k; i++)
    {
      solutionprime[1][i] = solution[t][i];
    }

    for (int i = 2; i <= PopSize; i += 2)
    {
      t = -999;
      // Selection
      for (int y = 0; y < tSize; y++)
      {
        rd = rand() % PopSize;
        S = fitV[rd];
        if (S > bestS)
        {
          bestS = S;
          t = rd;
        }
      }
      //Assign first Tournament Selection Winner
      for (int y = 0; y < k; y++)
      {
        solutionprime[i][y] = solution[t][y];
      }

      rd = -1;
      t = -999;
      bestS = -999.0;
      for (int y = 0; y < tSize; y++)
      {
        rd = rand() % PopSize;
        S = fitV[rd];
        if (S > bestS)
        {
          bestS = S;
          t = rd;
        }
      }
      bestS = -999;
      //Assign Second tournament Selection Winner
      for (int y = 0; y < k; y++)
      {
        solutionprime[i + 1][y] = solution[t][y];
      }
      // Tournament Selection Completed

      if (((double)rand() / (RAND_MAX + 1.)) < Px)
      {
        for (int p = 0; p < k; p++)
        {
          mask[p] = rand() % 2;
        }
        for (int p = 0; p < k; p++)
        {
          if (mask[p] == 0)
          {
            child[p] = solutionprime[i][p];
          }
          else
          {
            child[p] = solutionprime[i][p];
          }
        }
        for (int p = 0; p < k; p++)
        {
          solutionprime[i + 1][p] = child[p];
        }
      }
      
      for (int p = 0; p < k; p++)
      {
        if (solutionprime[i][p] == 0)
        {
          if (((double)rand() / (RAND_MAX + 1.)) < Pm)
          {
            solutionprime[i][p] = 1;
          }
        }
        if (solutionprime[i][p] == 1)
        {
          if (((double)rand() / (RAND_MAX + 1.)) < Pm)
          {
            solutionprime[i][p] = 0;
          }
        }
      }
      for (int p = 0; p < k; p++)
      {
        if (solutionprime[i + 1][p] == 0)
        {
          if (((double)rand() / (RAND_MAX + 1.)) < Pm)
          {
            solutionprime[i + 1][p] = 1;
          }
        }
        if (solutionprime[i + 1][p] == 1)
        {
          if (((double)rand() / (RAND_MAX + 1.)) < Pm)
          {
            solutionprime[i + 1][p] = 0;
          }
        }
      }
    }
    //Swap and compute fitness.
    for (int x = 0; x < PopSize; x++)
    {
      for (int y = 0; y < k; y++)
      {
        solution[x][y] = solutionprime[x][y];
      }
    }
    for (int x = 0; x < PopSize; x++)
    {
      fitV[x] = fitnessFunction(solution[x], weights, k, maxwt);
    }
    for (int x = 0; x < PopSize; x++)
    {
      for (int y = 0; y < k; y++)
      {
        solutionprime[x][y] = -1;
      }
    }

    gencount++;
  }

  // END OF WHILE LOOP
  if (gencount > maxGenerations)
  {
    cout << "FAILED "
         << "Gen " << gencount << endl;
  }
  else
  {
    for (int i = 0; i < PopSize; i++)
    {
      for (int j = 0; j < k; j++)
      {
        if (solution[i][j] == 0)
        {
          cout << ".";
        }
        else
        {
          cout << "X";
        }
      }
      cout << " " << fitV[i] << endl;
    }
    cout << "FOUND "
         << "Gen " << gencount << " : ";
    for (int i = 0; i < k; i++)
    {
      if (solution[b][i] == 0)
      {
        cout << ".";
      }
      else
      {
        cout << "X";
      }
    }
    cout << " " << bestfit << endl;
  }
}

int best(double fitV[], int PopSize)
{
  double highest = fitV[0];
  int n = 0;
  for (int i = 1; i < PopSize; i++)
  {
    if (fitV[i] > highest)
    {
      highest = fitV[i];
      n = i;
    }
  }
  return n;
}

int secondbest(double fitV[], int PopSize, int best)
{
  double secondhighest = -999;
  int m;
  for (int i = 0; i < PopSize; i++)
  {
    if ((fitV[i] > secondhighest) && (i != best))
    {
      secondhighest = fitV[i];
      m = i;
    }
  }
  return m;
}

bool goodenough(double fitV[], int PopSize, int maxwt)
{
  for (int i = 0; i < PopSize; i++)
  {
    if ((fitV[i] / maxwt) >= 0.99995)
    {
      bestfit = fitV[i];
      b = i;
      return true;
    }
  }
  return false;
}

double fitnessFunction(int solution[], double weights[], int j, int maxwt)
{
  double fitness;
  double load = 0;

  for (int i = 0; i < j; i++)
  {
    load = load + (weights[i] * solution[i]);
  }
  if (load > maxwt)
  {
    fitness = (load) - (2 * (load - maxwt));
  }
  else
  {
    fitness = load;
  }
  return fitness;
}
