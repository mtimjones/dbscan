#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define FEATURES	16

#define CLASSES		 7

#define UNDEFINED        0
#define CLASS_1          1
#define CLASS_2          2
#define CLASS_3          3
#define CLASS_4          4
#define CLASS_5          5
#define CLASS_6          6
#define CLASS_7          7
#define NOISE            8

typedef struct dataset_t {
   char *name;
   int  features[ FEATURES ];
   int  class;
   int  label;
} dataset_t;

typedef struct neighbors_t {
   int neighbor_count;
   int neighbor[ OBSERVATIONS ];
} neighbors_t;

#define EPSILON        1.0
#define MINPTS         3

#define OBSERVATIONS	100

// Features are:
//    [ 0] hair
//    [ 1] feathers 
//    [ 2] eggs 
//    [ 3] milk
//    [ 4] airborne
//    [ 5] aquatic
//    [ 6] predator
//    [ 7] toothed
//    [ 8] backbone
//    [ 9] breathes
//    [10] venomous
//    [11] fins
//    [12] legs
//    [13] tail
//    [14] domestic
//    [15] catsize

// Classes are [1] Mammal, [2] Bird, [3] Reptile, [4] Fish
//             [5] Amphibian, [6] Bug, [7] Invertebrate.

dataset_t dataset[ OBSERVATIONS ] = 
{
//  Name        Features                           Class
   {"aardvark", {1,0,0,1,0,0,1,1,1,1,0,0,4,0,0,1}, 1, 0, 0},
   {"antelope", {1,0,0,1,0,0,0,1,1,1,0,0,4,1,0,1}, 1, 0, 0},
   {"bass",     {0,0,1,0,0,1,1,1,1,0,0,1,0,1,0,0}, 4, 0, 0},
   {"bear",     {1,0,0,1,0,0,1,1,1,1,0,0,4,0,0,1}, 1, 0, 0},
   {"boar",     {1,0,0,1,0,0,1,1,1,1,0,0,4,1,0,1}, 1, 0, 0},
   {"buffalo",  {1,0,0,1,0,0,0,1,1,1,0,0,4,1,0,1}, 1, 0, 0},
   {"calf",     {1,0,0,1,0,0,0,1,1,1,0,0,4,1,1,1}, 1, 0, 0},
   {"carp",     {0,0,1,0,0,1,0,1,1,0,0,1,0,1,1,0}, 4, 0, 0},
   {"catfish",  {0,0,1,0,0,1,1,1,1,0,0,1,0,1,0,0}, 4, 0, 0},
   {"cavy",     {1,0,0,1,0,0,0,1,1,1,0,0,4,0,1,0}, 1, 0, 0},
   {"cheetah",  {1,0,0,1,0,0,1,1,1,1,0,0,4,1,0,1}, 1, 0, 0},
   {"chicken",  {0,1,1,0,1,0,0,0,1,1,0,0,2,1,1,0}, 2, 0, 0},
   {"chub",     {0,0,1,0,0,1,1,1,1,0,0,1,0,1,0,0}, 4, 0, 0},
   {"crab",     {0,0,1,0,0,1,1,0,0,0,0,0,4,0,0,0}, 7, 0, 0},
   {"crayfish", {0,0,1,0,0,1,1,0,0,0,0,0,6,0,0,0}, 7, 0, 0},
   {"crow",     {0,1,1,0,1,0,1,0,1,1,0,0,2,1,0,0}, 2, 0, 0},
   {"deer",     {1,0,0,1,0,0,0,1,1,1,0,0,4,1,0,1}, 1, 0, 0},
   {"dogfish",  {0,0,1,0,0,1,1,1,1,0,0,1,0,1,0,1}, 4, 0, 0},
   {"dolphin",  {0,0,0,1,0,1,1,1,1,1,0,1,0,1,0,1}, 1, 0, 0},
   {"dove",     {0,1,1,0,1,0,0,0,1,1,0,0,2,1,1,0}, 2, 0, 0},
   {"duck",     {0,1,1,0,1,1,0,0,1,1,0,0,2,1,0,0}, 2, 0, 0},
   {"elephant", {1,0,0,1,0,0,0,1,1,1,0,0,4,1,0,1}, 1, 0, 0},
   {"flamingo", {0,1,1,0,1,0,0,0,1,1,0,0,2,1,0,1}, 2, 0, 0},
   {"flea",     {0,0,1,0,0,0,0,0,0,1,0,0,6,0,0,0}, 6, 0, 0},
   {"frog",     {0,0,1,0,0,1,1,1,1,1,0,0,4,0,0,0}, 5, 0, 0},
   {"frog",     {0,0,1,0,0,1,1,1,1,1,1,0,4,0,0,0}, 5, 0, 0},
   {"fruitbat", {1,0,0,1,1,0,0,1,1,1,0,0,2,1,0,0}, 1, 0, 0},
   {"giraffe",  {1,0,0,1,0,0,0,1,1,1,0,0,4,1,0,1}, 1, 0, 0},
   {"girl",     {1,0,0,1,0,0,1,1,1,1,0,0,2,0,1,1}, 1, 0, 0},
   {"gnat",     {0,0,1,0,1,0,0,0,0,1,0,0,6,0,0,0}, 6, 0, 0},
   {"goat",     {1,0,0,1,0,0,0,1,1,1,0,0,4,1,1,1}, 1, 0, 0},
   {"gorilla",  {1,0,0,1,0,0,0,1,1,1,0,0,2,0,0,1}, 1, 0, 0},
   {"gull",     {0,1,1,0,1,1,1,0,1,1,0,0,2,1,0,0}, 2, 0, 0},
   {"haddock",  {0,0,1,0,0,1,0,1,1,0,0,1,0,1,0,0}, 4, 0, 0},
   {"hamster",  {1,0,0,1,0,0,0,1,1,1,0,0,4,1,1,0}, 1, 0, 0},
   {"hare",     {1,0,0,1,0,0,0,1,1,1,0,0,4,1,0,0}, 1, 0, 0},
   {"hawk",     {0,1,1,0,1,0,1,0,1,1,0,0,2,1,0,0}, 2, 0, 0},
   {"herring",  {0,0,1,0,0,1,1,1,1,0,0,1,0,1,0,0}, 4, 0, 0},
   {"honeybee", {1,0,1,0,1,0,0,0,0,1,1,0,6,0,1,0}, 6, 0, 0},
   {"housefly", {1,0,1,0,1,0,0,0,0,1,0,0,6,0,0,0}, 6, 0, 0},
   {"kiwi",     {0,1,1,0,0,0,1,0,1,1,0,0,2,1,0,0}, 2, 0, 0},
   {"ladybird", {0,0,1,0,1,0,1,0,0,1,0,0,6,0,0,0}, 6, 0, 0},
   {"lark",     {0,1,1,0,1,0,0,0,1,1,0,0,2,1,0,0}, 2, 0, 0},
   {"leopard",  {1,0,0,1,0,0,1,1,1,1,0,0,4,1,0,1}, 1, 0, 0},
   {"lion",     {1,0,0,1,0,0,1,1,1,1,0,0,4,1,0,1}, 1, 0, 0},
   {"lobster",  {0,0,1,0,0,1,1,0,0,0,0,0,6,0,0,0}, 7, 0, 0},
   {"lynx",     {1,0,0,1,0,0,1,1,1,1,0,0,4,1,0,1}, 1, 0, 0},
   {"mink",     {1,0,0,1,0,1,1,1,1,1,0,0,4,1,0,1}, 1, 0, 0},
   {"mole",     {1,0,0,1,0,0,1,1,1,1,0,0,4,1,0,0}, 1, 0, 0},
   {"mongoose", {1,0,0,1,0,0,1,1,1,1,0,0,4,1,0,1}, 1, 0, 0},
   {"moth",     {1,0,1,0,1,0,0,0,0,1,0,0,6,0,0,0}, 6, 0, 0},
   {"newt",     {0,0,1,0,0,1,1,1,1,1,0,0,4,1,0,0}, 5, 0, 0},
   {"octopus",  {0,0,1,0,0,1,1,0,0,0,0,0,8,0,0,1}, 7, 0, 0},
   {"opossum",  {1,0,0,1,0,0,1,1,1,1,0,0,4,1,0,0}, 1, 0, 0},
   {"oryx",     {1,0,0,1,0,0,0,1,1,1,0,0,4,1,0,1}, 1, 0, 0},
   {"ostrich",  {0,1,1,0,0,0,0,0,1,1,0,0,2,1,0,1}, 2, 0, 0},
   {"parakeet", {0,1,1,0,1,0,0,0,1,1,0,0,2,1,1,0}, 2, 0, 0},
   {"penguin",  {0,1,1,0,0,1,1,0,1,1,0,0,2,1,0,1}, 2, 0, 0},
   {"pheasant", {0,1,1,0,1,0,0,0,1,1,0,0,2,1,0,0}, 2, 0, 0},
   {"pike",     {0,0,1,0,0,1,1,1,1,0,0,1,0,1,0,1}, 4, 0, 0},
   {"piranha",  {0,0,1,0,0,1,1,1,1,0,0,1,0,1,0,0}, 4, 0, 0},
   {"pitviper", {0,0,1,0,0,0,1,1,1,1,1,0,0,1,0,0}, 3, 0, 0},
   {"platypus", {1,0,1,1,0,1,1,0,1,1,0,0,4,1,0,1}, 1, 0, 0},
   {"polecat",  {1,0,0,1,0,0,1,1,1,1,0,0,4,1,0,1}, 1, 0, 0},
   {"pony",     {1,0,0,1,0,0,0,1,1,1,0,0,4,1,1,1}, 1, 0, 0},
   {"porpoise", {0,0,0,1,0,1,1,1,1,1,0,1,0,1,0,1}, 1, 0, 0},
   {"puma",     {1,0,0,1,0,0,1,1,1,1,0,0,4,1,0,1}, 1, 0, 0},
   {"pussycat", {1,0,0,1,0,0,1,1,1,1,0,0,4,1,1,1}, 1, 0, 0},
   {"raccoon",  {1,0,0,1,0,0,1,1,1,1,0,0,4,1,0,1}, 1, 0, 0},
   {"reindeer", {1,0,0,1,0,0,0,1,1,1,0,0,4,1,1,1}, 1, 0, 0},
   {"rhea",     {0,1,1,0,0,0,1,0,1,1,0,0,2,1,0,1}, 2, 0, 0},
   {"scorpion", {0,0,0,0,0,0,1,0,0,1,1,0,8,1,0,0}, 7, 0, 0},
   {"seahorse", {0,0,1,0,0,1,0,1,1,0,0,1,0,1,0,0}, 4, 0, 0},
   {"seal",     {1,0,0,1,0,1,1,1,1,1,0,1,0,0,0,1}, 1, 0, 0},
   {"sealion",  {1,0,0,1,0,1,1,1,1,1,0,1,2,1,0,1}, 1, 0, 0},
   {"seasnake", {0,0,0,0,0,1,1,1,1,0,1,0,0,1,0,0}, 3, 0, 0},
   {"seawasp",  {0,0,1,0,0,1,1,0,0,0,1,0,0,0,0,0}, 7, 0, 0},
   {"skimmer",  {0,1,1,0,1,1,1,0,1,1,0,0,2,1,0,0}, 2, 0, 0},
   {"skua",     {0,1,1,0,1,1,1,0,1,1,0,0,2,1,0,0}, 2, 0, 0},
   {"slowworm", {0,0,1,0,0,0,1,1,1,1,0,0,0,1,0,0}, 3, 0, 0},
   {"slug",     {0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0}, 7, 0, 0},
   {"sole",     {0,0,1,0,0,1,0,1,1,0,0,1,0,1,0,0}, 4, 0, 0},
   {"sparrow",  {0,1,1,0,1,0,0,0,1,1,0,0,2,1,0,0}, 2, 0, 0},
   {"squirrel", {1,0,0,1,0,0,0,1,1,1,0,0,2,1,0,0}, 1, 0, 0},
   {"starfish", {0,0,1,0,0,1,1,0,0,0,0,0,5,0,0,0}, 7, 0, 0},
   {"stingray", {0,0,1,0,0,1,1,1,1,0,1,1,0,1,0,1}, 4, 0, 0},
   {"swan",     {0,1,1,0,1,1,0,0,1,1,0,0,2,1,0,1}, 2, 0, 0},
   {"termite",  {0,0,1,0,0,0,0,0,0,1,0,0,6,0,0,0}, 6, 0, 0},
   {"toad",     {0,0,1,0,0,1,0,1,1,1,0,0,4,0,0,0}, 5, 0, 0},
   {"tortoise", {0,0,1,0,0,0,0,0,1,1,0,0,4,1,0,1}, 3, 0, 0},
   {"tuatara",  {0,0,1,0,0,0,1,1,1,1,0,0,4,1,0,0}, 3, 0, 0},
   {"tuna",     {0,0,1,0,0,1,1,1,1,0,0,1,0,1,0,1}, 4, 0, 0},
   {"vampire",  {1,0,0,1,1,0,0,1,1,1,0,0,2,1,0,0}, 1, 0, 0},
   {"vole",     {1,0,0,1,0,0,0,1,1,1,0,0,4,1,0,0}, 1, 0, 0},
   {"vulture",  {0,1,1,0,1,0,1,0,1,1,0,0,2,1,0,1}, 2, 0, 0},
   {"wallaby",  {1,0,0,1,0,0,0,1,1,1,0,0,2,1,0,1}, 1, 0, 0},
   {"wasp",     {1,0,1,0,1,0,0,0,0,1,1,0,6,0,0,0}, 6, 0, 0},
   {"wolf",     {1,0,0,1,0,0,1,1,1,1,0,0,4,1,0,1}, 1, 0, 0},
   {"worm",     {0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0}, 7, 0, 0},
   {"wren",     {0,1,1,0,1,0,0,0,1,1,0,0,2,1,0,0}, 2, 0, 0},
};


void clear_labels( void )
{
   for ( int i = 0 ; i < OBSERVATIONS ; i++ )
   {
      dataset[ i ].label = UNDEFINED;
   }

   return;
}


double distance( int i, int j )
{
   double sum = 0.0;

   for ( feature = 0 ; feature < FEATURES ; feature++ )
   {
      sum += SQR( ( dataset[ i ].features[ feature ] - dataset[ j ].features[ feature ] ) );

   }

   return sqrt( sum );
}


neighbor_t *find_neighbors( int observation )
{
   neighbors_t *neighbor = ( neighbors_t )malloc( sizeof( neighbors_t ) );

   bzero( (void *)neighbor_t, sizeof( neighbor_t ) );

   for ( int i = 0 ; i < OBSERVATIONS ; i++ )
   {
      if ( i = observation ) continue;

      if ( distance( observation, i ) < EPSILON )
      {
         neighbor->neighbor[ i ] = 1;
         neighbor->neighbor_count++;
      }
   }

   return;
}


void free_neighbors( neighbors_t *neighbors )
{
   free( neighbors );

   return;
}

void fold_neighbors( neighbors_t *seed_set, neighbors_t *neighbors )
{
   for ( int i = 0 ; i < OBSERVATIONS ; i++ )
   {
      if ( neighbors->neighbor[ i ] )
      {
         seed_set->neighbor[ i ] = 1;
      }
   }

   return;
}

void process_neighbors( int initial_point, neighbors_t *seed_set )
{
   // Process every member in the seed set.
   for ( int i = 0 ; i < OBSERVATIONS ; i++ )
   {
      // Is this a neighbor?
      if ( seed_set->neighbor[ i ] )
      {
         if ( dataset[ i ].label == NOISE )
         {
            dataset[ i ].label = dataset[ initial_point ].label;
         }
         else if ( dataset[ i ].label == UNDEFINED )
         {
            continue;
         }
         else
         {
            dataset[ i ].label = dataset[ initial_point ].label;
         }

         neighbors_t *neighbors = find_neighbors( i );
         if ( neighbors->neighbor_count >= MINPTS )
         {
            fold_neighbors( seed_set, neighbors );
            i = 0;
         }
         free_neighbors( neighbors );
      }
   }

   return;
}


void dbscan( void )
{
   int cluster = 0;

   for ( int i = 0 ; i < OBSERVATIONS ; i++ )
   {
      if ( dataset[ i ].label != UNDEFINED ) continue;

      neighbors_t *neighbors = find_neighbors( i );

      if ( neighbors->neighbor_count < MINPTS )
      {
         dataset[ i ] = NOISE;
         free_neighbors( neighbors );
         continue;
      }

      cluster++;
      dataset[ i ].label = cluster;

      process_neighbors( i, neighbors  );
      free_neighbors( neighbors );
   }

   return;
}


int main( void )
{
   dbscan( );

   // emit classes
   for ( int class = 1 ; class <= CLASSES ; class++ )
   {

   }

   // Emit outliers (NOISE)

   return 0;
}
