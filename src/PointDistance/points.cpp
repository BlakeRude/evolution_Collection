/* Author: Blake Rude
 * 
 * Uses Evolutionary Strategy optimization
 * technique to determine maximum distance
 * between a supplied number of points
 * 
 * Number of points is given in stdin
 * during runtime
 *
 * V 1.0 - 12 November 2020
 */

#include "rand.cpp"
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <bitset>
#include <time.h>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
using namespace std;
static double myPI = 3.141592653589793238462643383279502884197;
static int MAX_GENERATIONS = 20000;
static int tSize = 3;
class Gene
{
public:
    int np;
    vector<double> r;     // [0,1]
    vector<double> theta; // [0, 360]
    double fitness;

    bool operator<(const Gene &other)
    {
        return other.fitness < fitness;
    }
public:
    void setNP(int Points)
    {
        np = Points;
    }
    void print();
    void init()
    {
        for (int i = 0; i < np; i++)
        {
            if (i == 0)
            {
                r.push_back(1);
                theta.push_back(0);
            }
            else
            {
                r.push_back(((double)rand() / (RAND_MAX + 1.))); // rand 0-1.0
                theta.push_back(randMod(360));                   // in Degrees, convert to radians later
            }
        }
    } // end of init()
    void calcFitness()
    {
        double minD = 100.0;
        double temp = 100.0;
        for (int i = 0; i < np; i++)
        {
            for (int j = 0; j < np; j++)
            {
                if (i != j)
                {
                    temp = (((r[i] * r[i]) + (r[j] * r[j])) - (2 * r[i] * r[j] * cos(((theta[i]*myPI)/180) - ((theta[j]*myPI)/180))));
                    if (temp < minD)
                    {
                        minD = temp;
                    }
                    temp = 100.0;
                }
            }
        }
        fitness = minD;
    }
    void mutate()
    {
        double Pm = 1;
        Pm = Pm/np;
        for(int i=1; i<np; i++)
        {
            if(((double)rand() / (RAND_MAX + 1.)) < Pm)
            {
                double randy = randNorm(0.1);
                r[i] += randy;
                if(r[i] > 1.0){ r[i] = 1.0; }
                if(r[i] < 0.0)
                { 
                    if(randy < 0)
                    {
                        r[i] = r[i] + (randy*-1);
                    }
                    else{r[i] = r[i] + (randy);}
                }

                randy = randNorm(10);
                theta[i] += randy;
                if(theta[i] > 360){ theta[i] = 360; }
                if(theta[i] < 0){ theta[i] = 0; }
            }
        }
    }
};
int main(int argc, char *argv[])
{
    initRand();
    int Points = -1;
    if (argc < 2)
    {
        cout << "Please Provide a point value.\n";
        cout << "Try: ./points 5\n";
        exit(EXIT_FAILURE);
    }
    else
    {
        Points = atoi(argv[1]);
    }
    /* Variables */
    //ES(7+49)
    int mu = 7;
    int lambda = 49;
    int nGenerations = 1;

    //Initialize a vector of type Gene.
    vector<Gene> Genes;
    vector<Gene> lambdaPop;
    for (int i = 0; i < mu; i++)
    {
        Gene newGene;
        newGene.setNP(Points);
        newGene.init();
        newGene.calcFitness();
        Genes.push_back(newGene);
    }
    sort(Genes.begin(), Genes.end());
    int rr = 0;
    double s = 0.0;
    double bestS = -1.0;
    int t = -1.0;
    while (nGenerations <= MAX_GENERATIONS)
    {
        for (int i = 0; i < lambda; i++)
        {
            Gene newGene;
            //Tournament Selection
            for (int j = 0; j < tSize; j++)
            {
                rr = rand() % mu;
                s = Genes[rr].fitness;
                if (s > bestS)
                {
                    bestS = s;
                    t = rr;
                }
            }
            //tournament over
            newGene = Genes[t];
            t = -1.0;
            rr = 0;
            bestS = -1.0;
            s = 0.0;
            newGene.mutate();
            newGene.calcFitness();
            
            lambdaPop.push_back(newGene);
        }

        for(int i=0; i<mu; i++)// add Genes<> to lambdapop<> (functionally making mu + lambda)
        {
            lambdaPop.push_back(Genes[i]);
        }
        sort(lambdaPop.begin(), lambdaPop.end());
        
        for(int i=0; i<mu; i++)
        {
            Genes[i] = lambdaPop[i];

        }
        nGenerations++;
        lambdaPop.clear();
    }
    cout << setprecision(6) << fixed;
    for(int i=0; i<Points; i++)
    {
        cout << Genes[0].r[i];
        cout << " " ;
        cout << (Genes[0].theta[i]*PI)/180;
        cout << "\n";
    }
    cout << "Fitness: " << sqrt(Genes[0].fitness )<< "\n";
    cout << setprecision(2) << fixed;
    vector<double> sig;
    for(int i=0; i < Points; i++)
    {
        for(int j=0; j < Points; j++)
        {
            if(i!=j){
            sig.push_back((((Genes[0].r[i] * Genes[0].r[i]) + (Genes[0].r[j] * Genes[0].r[j])) - (2 * Genes[0].r[i] * Genes[0].r[j] * cos(((Genes[0].theta[i]*PI)/180) - ((Genes[0].theta[j]*PI)/180)))));
            }
        }
    }
    sort(sig.begin(), sig.end());
    int iterate = 0;
    for (int i = sig.size()-1; i >= 0; i=i-2)
    {
        cout << "** " << iterate << " " << sqrt(sig[i]) << endl;
        iterate++;
    }
}