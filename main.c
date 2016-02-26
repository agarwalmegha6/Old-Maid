//  ECE 175 Final Project

//  Created by Megha Agarwal and Josh Marks on 12/1/14.

#include <stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

FILE *wins;
int i = 0,j=0,shuffle = 0,store = 0,min =1,max =51,k=0,l=0,c=0,pos = 0,n=0,d=0,e=0,num=0;
char s;
char username[] = "Player";
double frac =0.0;
typedef struct cards{//structure for card
    char suit[52];
    int face[52];
}cards;
cards deck;
cards user;
cards comp;

int myrand(int min, int max){//function to find random number
    double frac;
    double index;
    frac= (double)rand()/((double)RAND_MAX+1);
    index=min+floor((max-min+1)*(frac));
    return index;
    fflush(stdin);
}

void CreateDeck()//function that creates deck of cards in order from 1-13 with 4 suits
{
    for(i=0;i<4;i++)//loop for suits
    {
        for( j=1;j<=13;j++)//loop for numbers
        {
            if(i==0)
                deck.suit[j+(i*13)] = 'H';//hearts
            if(i==1)
                deck.suit[j+(i*13)] = 'D';//diamonds
            if(i==2)
                deck.suit[j+(i*13)] = 'C';//clubs
            if(i==3)
                deck.suit[j+(i*13)] = 'S';//spades
            deck.face[j+(i*13)] = j;
            printf("%c%d ",deck.suit[j+(i*13)],deck.face[j+(i*13)]);
        }
    }
    printf("\n\n");
}
void ShuffleDeck()//function to shuffle deck
{
    for(i=0;i<4;i++)
    {
        for (j = 1; j <=13; j++)
        {
            store = deck.face[j+(i*13)];//
            shuffle = myrand(min,max);//store rand num in shuffle
            deck.face[j+(i*13)] = deck.face[shuffle];//stores random number inside array
            deck.face[shuffle] = store;
            s = deck.suit[j+(i*13)];
            deck.suit[j+(i*13)] = deck.suit[shuffle];
            deck.suit[shuffle] = s;//swap function for s and deck.suit
        }
    }
    printf("Deck of cards after shuffling!\n\n");
    for(i=0;i<4;i++)
    {
        for( j=1;j<=13;j++)
        {
            printf("%c%d ",deck.suit[j+(i*13)],deck.face[j+(i*13)]);//for loop for printing shuffled cards (face and suit)
        }
    }
    printf("\n\n");
    fflush(stdin);
}
void DealCards()
{
    for(i=0;i<4;i++)
    {
        for( j=1;j<=13;j++)//for loops for suit and face
        {
            if(deck.face[j+(i*13)]!=0)
            {
                if((j+(i*13))%2==0)//deals even numbers to user
                {
                    user.face[k]=deck.face[j+(i*13)];
                    user.suit[k]=deck.suit[j+(i*13)];
                    k++;
                }
                if((j+(i*13))%2!=0)//deals odd numbers to computer
                {
                    comp.face[l]=deck.face[j+(i*13)];
                    comp.suit[l]=deck.suit[j+(i*13)];
                    l++;
                }
            }
        }
    }
    printf("Dealing Cards:\n\n");
    printf("%s's hand\n",username);
    for(i=0;i<k;i++)
        printf("%c%d ",user.suit[i],user.face[i]);//prints users hand
    printf("\n\n");
    printf("Computer's hand\n");
    for(i=0;i<l;i++)
        printf("%c%d ",comp.suit[i],comp.face[i]);//prints computers hand
    printf("\n\n");
    fflush(stdin);
}
void RemovePairs()
{
    for(i=0;i<k;i++)
    {
        c=0;
        for(j=0;j<k;j++)
        {
            if(user.face[i]==user.face[j])//if its a pair
            {
                pos = j;//stores j as the position
                c++;//c is counter
            }
            if(c==2)
                break;
        }
        if(c==2)
        {
            if(user.face[i]!=0)
                printf("Removing a pair: %c%d and %c%d\n",user.suit[i],user.face[i],user.suit[pos],user.face[pos]);// prints pair that is being removed
            user.face[i] = 0;
            user.face[pos] = 0;
            user.suit[i] = NULL;
            user.suit[pos] = NULL;
        }
    }
    printf("\n%s's hand after removing pairs\n",username);//prints hand after pair is removed
    for(i=0;i<k;i++)
    {
        if(user.face[i]!= 0)//only ones that are = 0
            printf("%c%d ",user.suit[i],user.face[i]);
    }
    printf("\n\n");
    
    for(i=0;i<k;i++)//same loop except for checking for computer pairs this time
    {
        c=0;
        for(j=0;j<k;j++)
        {
            if(comp.face[i]==comp.face[j])
            {
                pos = j;
                c++;
            }
            if(c==2)
                break;
        }
        if(c==2)
        {
            if(comp.face[i]!=0)
                printf("Removing a pair: %c%d and %c%d\n",comp.suit[i],comp.face[i],comp.suit[pos],comp.face[pos]);
            comp.face[i] = 0;
            comp.face[pos] = 0;
            comp.suit[i] = NULL;
            comp.suit[pos] = NULL;
        }
    }
    printf("\nComputer's hand after removal of pairs\n");
    for(i=0;i<l;i++)
    {
        if(comp.face[i]!=0)
            printf("%c%d ",comp.suit[i],comp.face[i]);
    }
    printf("\n\n");
    fflush(stdin);
}
void PairSearch()
{
    c=2;
    while(c>1)
    {
        c=0;
        e=0;
        for(i=0;i<l;i++)
        {
            if(comp.face[i]!=0)//checks for number of elements in comp.face (how many cards comp has
                e++;
        }
        printf("Computer has %d cards\n", e);
        printf("Which card do you want to choose?\n");
        printf("Enter a number between 1 and %d\n", e);
        scanf("%d", &n);
        fflush(stdin);
        d=0;
        for(i=0;i<l;i++)
        {
            if(comp.face[i]!=0)//checks computers card at selected location
                d++;
            if(d==n)
            {
                user.face[k] = comp.face[i];
                user.suit[k] = comp.suit[i];//transfers chosen card to users hand
                comp.face[i]=0;
                k++;
                break;
            }
        }
        RemovePairs();//removes pairs
        for (j = 0; j <k; j++)//shuffles cards again
        {
            store = user.face[j];
            shuffle = myrand(0,k);
            user.face[j] = user.face[shuffle];
            user.face[shuffle] = store;
            s = user.suit[j];
            user.suit[j] = user.suit[shuffle];
            user.suit[shuffle] = s;
        }
        c=0;
        for(i=0;i<26;i++)
        {
            if(user.face[i]!=0||comp.face[i]!=0)//if a match in either counter updates
                c++;
        }
        if(c==1)//if theres a match
            break;
        c=0;
        e=0;
        for(i=0;i<k;i++)
        {
            if(user.face[i]!=0)//if user match e updates
                e++;
        }
        d=0;
        printf("User has %d cards\n", e);
        num = myrand(1,e);
        printf("Computer chooses %d", num);//same as before except for computer
        for(i=0;i<k;i++)
        {
            if(user.face[i]!=0)
                d++;
            if(d==num)
            {
                comp.face[l] = user.face[i];
                comp.suit[l] = user.suit[i];
                user.face[i]=0;
                l++;
                break;
            }
        }
        RemovePairs();
        for (j = 0; j <l; j++)
        {
            store = comp.face[j];
            shuffle = myrand(0,l);
            comp.face[j] = comp.face[shuffle];
            comp.face[shuffle] = store;
            s = comp.suit[j];
            comp.suit[j] = comp.suit[shuffle];
            comp.suit[shuffle] = s;
        }
        c=0;
        for(i=0;i<26;i++)
        {
            if(user.face[i]!=0||comp.face[i]!=0)
                c++;
        }
        if(c==1)
            break;
    }
    fflush(stdin);
}
int main(int argc, const char * argv[])
{
    int game = 0;
    char ch,response;
    while(game==0)//continues until user choses not to continue anymore
    {
        printf("Do you want a new name? (Y or N)");
        scanf("%c",&ch);//scans for whether new name or not
        fflush(stdin);
        if(ch=='Y'||ch=='y')
        {
            printf("Enter new name: ");
            scanf("%s",username);//scans for new name
            fflush(stdin);
        }
        printf("\n\nGame begins between Computer and %s\n\n",username);
        srand((int)time(NULL));
        printf("Deck of Cards\n\n");
        CreateDeck();
        for(i=1;i<=4;i++)
        {
            for(j=1;j<=13;j++)
            {
                if(deck.suit[j+(i*13)] == 'C' && deck.face[j+(i*13)]== 12)//removes queen of clubs
                {
                    deck.suit[j+(i*13)] = NULL;
                    deck.face[j+(i*13)] = 0;
                }
            }
        }
        printf("Deck of Cards after one queen is removed\n\n");
        for(i=0;i<4;i++)
        {
            for( j=1;j<=13;j++)
            {
                if(deck.face[j+(i*13)]!=0)
                    printf("%c%d ",deck.suit[j+(i*13)],deck.face[j+(i*13)]);//prints new deck without C12
            }
        }
        printf("\n\n");
        ShuffleDeck();//calls shuffle deck function
        DealCards();//calls deal cards function
        RemovePairs();//calls remove pairs function
        PairSearch();//calls pair search function
        c=0;
        wins=fopen("wins.txt","w");//opens wins.txt for writing
        for(i=0;i<k;i++)
        {
            if(user.face[i]!=0)//if user has a card c updates
                c++;
        }
        if(c==0)
        {
            fprintf(wins,"%s\tWins\n",username);//prints name	 wins in wins.txt
            printf("Computer loses. %s Win!!!\n\n",username);//prints computer loses and player wins in program
        }
        else
        {
            fprintf(wins,"%s\tLoses\n",username);
            printf("%s loses. Computer Wins!!!\n\n",username);
        }
        fclose(wins);
        printf("Would you like to play again?(Y or N)");//asks if want to play again
        scanf("%c", &response);
        if(response== 'Y'||response=='y')//if yes stays in while loop
        {
            game=0;
        }
        else//if no exits while loop
        {
            game =1;
        }
        fflush(stdin);
    }
    return 0;
}
