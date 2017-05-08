#ifndef BEHAVIORGENERATOR_H
#define BEHAVIORGENERATOR_H

#include "gamefield.h"
#include "state.h"
#include "behavior.h"
#include <time.h>
#include <thread>
#include <mutex>

#define MAX_GENERATION 500
#define GENERATION_SIZE 500
#define MUTATION_PROBABILITY 30

class BehaviorGenerator {
public:
    BehaviorGenerator(GameField g, int startR, int startC);

    Behavior findBehavior();
private:

    std::recursive_mutex lock;
    std::vector<std::thread> threads;
    int startRow, startCol;

    bool isFound;
    Behavior fitBehavior;
    GameField gameField;
    QVector<Behavior> currentGeneration;
    int generationNumber;
    int maxFitness;
    void generate();


    void fitness(Behavior &b);
    void initFitness();


    void mutation1(Behavior& b);
    void mutation2(Behavior& b);
    void mutation3(Behavior& b);
    void mutation4(Behavior& b);

    void crossover(Behavior & parent1, Behavior & parent2, int position);
    void crossoverAll();


    void mutate(Behavior &mutated);
    void mutateAll();

    void selection();
    void algorithmIteration();





};

struct compare
{
    inline bool operator() (const Behavior& b1, const Behavior& b2){
        return (b1.fitness > b2.fitness);
    }
};

#endif // BEHAVIORGENERATOR_H
