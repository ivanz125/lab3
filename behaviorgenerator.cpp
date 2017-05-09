#include "behaviorgenerator.h"
#include "ant.h"

BehaviorGenerator::BehaviorGenerator(GameField g, int startR, int startC) :
    gameField(g), fitBehavior(STATE_COUNT), isFound(false), startRow(startR), startCol(startC)
 {
     srand(time(NULL));
     generationNumber = 0;
     currentGeneration.reserve(GENERATION_SIZE * 2);
 }



Behavior BehaviorGenerator::findBehavior()
{
    generate();
    while (!isFound) algorithmIteration();
    return fitBehavior;
    //return currentGeneration.front();
}

void BehaviorGenerator::generate()
{
    // Initialize first population with random values
    for (int i = 0; i < 2 * GENERATION_SIZE; i++){
        Behavior item = Behavior(STATE_COUNT);
        for (int state = 0; state < item.states.size(); state++){
            Transit food(rand() % STATE_COUNT, (Action)(rand() % 3));
            Transit noFood(rand() % STATE_COUNT, (Action)(rand() % 3));
            item.states[state] = State(food, noFood);
        }
        item.currentState = item.states.front();
        currentGeneration.push_back(item);
    }
}

void BehaviorGenerator::fitness(Behavior& b)
{
    lock.lock();
    //GameField g = gameField;
    GameField g(0, 0, b);
    b.currentState = b.states.front();
    Ant ant(&g, b, startRow, startCol);
    lock.unlock();
    int steps = 0;
    for (;steps < 200; steps++){
        if (ant.eatenApplesCount() == APPLES_COUNT) break;
        ant.move();
    }
    b.fitness = ant.eatenApplesCount() + (200 - steps);
}

void BehaviorGenerator::initFitness()
{
    for (int i = 0; i < currentGeneration.size(); i++){
        if (currentGeneration[i].fitness < 0){
            //fitness(currentGeneration[i]);
            threads.push_back(std::thread([=] {fitness(currentGeneration[i]);}));
        }
    }
    for (unsigned int i = 0; i < threads.size(); i++) threads[i].join();
    threads.clear();
}



void BehaviorGenerator::mutation1(Behavior & b)
{
    int randomState = rand() % b.states.size();
    while (b.currentState == b.states[randomState])
        randomState = rand() % b.states.size();
    b.currentState = b.states[randomState];
}

void BehaviorGenerator::mutation2(Behavior & b)
{
    int randomState = rand() % b.states.size();
    bool randomTranslation = rand() % 2;
    Action randomAction = (Action)(rand() % 3);
    if (randomTranslation)
        b.states[randomState].foodTransit.action = randomAction;
    else
        b.states[randomState].noFoodTransit.action = randomAction;
}

void BehaviorGenerator::mutation3(Behavior & b)
{
    int randomState = rand() % b.states.size();
    bool randomTranslation = rand() % 2;
    int randomArrState = rand() % b.states.size();
    if (randomTranslation)
        b.states[randomState].foodTransit.toState = randomArrState;
    else
        b.states[randomState].noFoodTransit.toState = randomArrState;
}

void BehaviorGenerator::mutation4(Behavior & b)
{
    int randomState = rand() % b.states.size();
    Transit temp = b.states[randomState].foodTransit;
    b.states[randomState].foodTransit = b.states[randomState].noFoodTransit;
    b.states[randomState].noFoodTransit = temp;
}

void BehaviorGenerator::crossover(Behavior & parent1, Behavior & parent2, int position)
{
    Behavior child1(STATE_COUNT);
    Behavior child2(STATE_COUNT);
    int randomTransit;
    State childState1, childState2;
    QVector<Transit> pool;
    // Randomly swap states and transits
    for (int i = 0; i < STATE_COUNT; i++){
        pool.clear();
        pool.push_back(parent1.states[i].foodTransit);
        pool.push_back(parent1.states[i].noFoodTransit);
        pool.push_back(parent2.states[i].foodTransit);
        pool.push_back(parent2.states[i].noFoodTransit);

        randomTransit = rand() % pool.size();
        childState1.foodTransit = pool[randomTransit];
        pool.erase(pool.begin() + randomTransit);

        randomTransit = rand() % pool.size();
        childState1.noFoodTransit = pool[randomTransit];
        pool.erase(pool.begin() + randomTransit);

        randomTransit = rand() % pool.size();
        childState2.foodTransit = pool[randomTransit];
        pool.erase(pool.begin() + randomTransit);

        randomTransit = rand() % pool.size();
        childState2.noFoodTransit = pool[randomTransit];

        child1.states[i] = childState1;
        child2.states[i] = childState2;
    }

    child1.currentState = child1.states.front();
    child2.currentState = child2.states.front();

    lock.lock();
    (currentGeneration[position]) = child1;
    (currentGeneration[position + 1]) = child2;
    lock.unlock();
}

void BehaviorGenerator::crossoverAll()
{
    QVector<int> parents;
    parents.reserve(currentGeneration.size() / 2);
    int i = 0;
    for (; i < currentGeneration.size() / 2; i++) parents.push_back(i);

    while (!parents.empty()){
        int parent1 = rand() % parents.size();
        parents.erase(parents.begin() + parent1);
        if (parents.empty()) break;

        int parent2 = rand() % parents.size();
        parents.erase(parents.begin() + parent2);

        crossover(currentGeneration[parent1], currentGeneration[parent2], i);
        i += 2;
    }
}

void BehaviorGenerator::mutate(Behavior & mutatedBehavior)
{
    mutatedBehavior.fitness = -1;
    int mutation = rand() % 4;
    switch (mutation){
        case 0: mutation1(mutatedBehavior); break;
        case 1: mutation2(mutatedBehavior); break;
        case 2: mutation3(mutatedBehavior); break;
        case 3: mutation4(mutatedBehavior); break;
    }
}

void BehaviorGenerator::mutateAll()
{
    for (int i = 0; i < currentGeneration.size(); i++){
        if (rand() % 100 < MUTATION_PROBABILITY) mutate(currentGeneration[i]);
    }
}


void BehaviorGenerator::selection()
{
    initFitness();
    std::sort(currentGeneration.begin(), currentGeneration.end(), compare());

    if (currentGeneration.front().fitness >= APPLES_COUNT || generationNumber >= MAX_GENERATION){
        fitBehavior = currentGeneration.front();
        isFound = true;
        return;
    }

    maxFitness = currentGeneration.front().fitness;
}

void BehaviorGenerator::algorithmIteration()
{
    crossoverAll();
    selection();
    if (isFound) return;
    //mutateAll();
    generationNumber++;
}
