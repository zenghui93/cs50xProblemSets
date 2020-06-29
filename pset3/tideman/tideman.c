#include <cs50.h>
#include <string.h>
#include <stdio.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    bool ballot = false;
    for (int i = 0; i < candidate_count; i++)
    {
        if (!strcmp(candidates[i], name))
        {
            ranks[rank] = i;
            ballot = true;
            
        }
    }
   
    return ballot;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j <= candidate_count - 1; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
        
        
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    int votes_first, votes_second;
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j <= candidate_count - 1; j++)
        {
            votes_first = preferences[i][j];
            votes_second = preferences[j][i];
            if (votes_first > votes_second)
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            if (votes_first < votes_second)
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
             
             
        }
        
        
    }
    return;
}

//Compare whether pairs[i+1]. is greater than pairs[i] or no.
bool compare(int i)
{
    bool greater = false;
    if (preferences[pairs[i + 1].winner][pairs[i + 1].loser] > preferences[pairs[i].winner][pairs[i].loser])
    {
        greater = true;
    }
    return greater;
}//compare

//This function will be called if pairs[i+1] is greater than pairs[i] in order to switch their position. 
void get_changed(int i)
{
    pair temp;
    temp.winner = pairs[i].winner;
    temp.loser = pairs[i].loser;
    pairs[i].winner = pairs[i + 1].winner;
    pairs[i].loser = pairs[i + 1].loser;
    pairs[i + 1].winner = temp.winner;
    pairs[i + 1].loser = temp.loser;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int greater_count;
    do
    {
        greater_count = 0;
        for (int i = 0; i < pair_count - 1; i++)
        {
            if (compare(i))
            {
                greater_count++;
            }
        }//for
        if (greater_count != 0)
        {
            for (int i = 0; i < pair_count - 1; i++)
            {
                if (compare(i))
                {
                    get_changed(i);
                }
            }//for
        }
    }
    while (greater_count != 0);
   
   
    return;
}

// Check whether there is any edges pointing at the candidate i.
bool check(int j)
{
    bool checked = false;
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[i][j])
        {
            checked = true;
        }
    }
    return checked;
    
}
//Check whether there is a circle in the array pairs.
void check_circle(int index)
{
    for (int i = index; i < pair_count - 2; i++)
    {
        if (pairs[i + 1].loser == pairs[index].winner)
        {
            locked[pairs[i + 1].winner][pairs[i + 1].loser] = false;
        }
    }
    if (pairs[pair_count - 1].loser == pairs[index].winner)
    {
        locked[pairs[pair_count - 1].winner][pairs[pair_count - 1].loser] = false;
    }
}
// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    
    for (int i = 0; i < pair_count; i++)
    {
        locked[pairs[i].winner][pairs[i].loser] = true;
    }
    for (int i = 0; i < pair_count - 2; i++)
    {
        check_circle(i);
    }
    
    int edges = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (check(i))
        {
            edges++;
            
        }
    }//for
    
    if (edges == candidate_count)
    {
        //Set last pair of pairs to false.
        locked[pairs[pair_count - 1].winner][pairs[pair_count - 1].loser] = false;
    }
    
    
    
    
    
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (!check(i))
        {
            printf("%s\n", candidates[i]);
            
        }
    }//for
    return;
}

