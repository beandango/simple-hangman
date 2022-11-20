#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <vector>
#include <cctype>

#define ascii "ascii.txt"
#define PIC1 "pic1.txt"
#define PIC2 "pic2.txt"
#define PIC3 "pic3.txt"
#define PIC4 "pic4.txt"
#define PIC5 "pic5.txt"
#define PIC6 "pic6.txt"
#define PIC7 "pic7.txt"
#define THANKS "thanks.txt"

std::ifstream fin, hangpic1, hangpic2, hangpic3, hangpic4, hangpic5, hangpic6, hangpic7, thanks;

std::string animals[64] = {"ant", "baboon" , "badger", "bat", "bear", "beaver", "camel",
"cat", "cobra","cougar","coyote","crow","deer","dog","donkey","duck","eagle","ferret",
"fox","frog","goat","goose","hawk","lion","lizard","llama","mole","monkey","moose","mouse","mule","newt",
"otter","owl","panda","parrot","pigeon","python","rabbit","ram","rat","raven","rhino","salmon","seal",
"shark","sheep","skunk","sloth","snake","spider","stork","swan","tiger","toad","trout","turkey",
"turtle","weasel","whale","wolf"};

std::string memes[11] = {"chungus","cunny", "memes", "hatsunemiku", "poggers",
"ugandanknuckles", "amogus","sus","sussy","bingchilling","baka"};

std::string words[64];


void header(std::ifstream& fin);
void generateWord(int);
void generateHangedPic(int misses);
void gameLoop(std::string themeChoice);
void display(std::vector<char> incorrect, std::string filledIn);
void end(std::string filledIn, std::string codeword, int misses);
void clear();
std::string  theme(int choice);


std::string theme(int choice)
{

    std::string themeChoice;
    if(choice == 1)
    {
        for(int i = 0; i < 65; i++)
        {
            words[i] = animals[i];
            themeChoice = "Animals";
        }
    }
    else if (choice == 2)
    {
        for(int i = 0; i < 65; i++)
        {
            words[i] = memes[i];
            themeChoice = "Memes";
        }
    }

    return themeChoice;

}

int main()
{
    
    std::srand(std::time(nullptr));
    char yn;
    bool again = true;

    while(again)
    {
        int choice;
        bool flag = true;

    // choosing theme
        do
        {
            std::cout<<"Choose a theme: \n\n";
            std::cout<<"1. Animals\n2. Memes\n\n";
            std::cin >> choice;
            if(!std::cin || choice > 2)
            {
                std::cout<<"\nInvalid input\n";
            }
            else
            {
                flag = false;
            }
        } while (flag);

        std::string themeChoice = theme(choice);
    
        bool flag2 = true;
        gameLoop(themeChoice);
        do
        {
            std::cout<<"\n Do you want to play again? (y/n)\n";
            std::cin>>yn;
            int result = isalpha(yn);

            if(!std::cin || result == 0 || (( yn != 'n') && (yn != 'y' )))
            {
                std::cout<<"\nOops, invalid input\n";
            }
            else
            {
                flag2 = false;
            }

        } while (flag2);
        
        
        if(yn=='n' || yn == 'N')
        {
            again = false;
        }
    }
    

    system("pause");

    return 0;
}


void clear()
{
    std::cout<<"\n\n\n\n\n\n";
}

void gameLoop(std::string themeChoice)
{
    int range = 64;
    int random_num = 1 + (rand() % range);
    std::string codeword = words[random_num];
    std::string filledIn = "_";
    int wordLength = codeword.length();

    for(int i = 0; i < wordLength-1; i++) // get correct number of blanks for chosen word
    {
        filledIn +="_";
    }
    
    std::vector<char> incorrect;           

    
    int misses = 0;
    char input;
    bool guess = false;

    while(misses < 6 && filledIn != codeword)
    {
        clear();
        header(fin);
        generateHangedPic(misses);
        display(incorrect, filledIn);
        bool flag = true;

        do
        {
            std::cout<<"\nGuess a letter! Theme: "<<themeChoice<<std::endl;
            clear();
            std::cin>>input;
            int result = isalpha(input);
            if(!std::cin || result == 0)
            {
                std::cout<<"\nOops! Only enter one letter please\n";
            }
            else
            {
                flag = false;
            }
        } while (flag);
        
        

        for(int i = 0; i < filledIn.length(); i++)
        {
            if(codeword[i] == input)
            {
                filledIn[i] = input;
                guess = true;
            }
        }
        if(!guess)
        {
            incorrect.push_back(input);
            misses++;
        }
        else if(guess)
        {
            generateHangedPic(misses);
        }
        guess = false;
    }
    end(filledIn, codeword, misses);
}

void end(std::string filledIn, std::string codeword, int misses)
{
    clear();
    clear();
    thanks.open(THANKS);
    std::string line;
    while(!thanks.eof())
    {
        getline(thanks, line);
        std::cout<<line<<std::endl;
    }
    thanks.close();

    std::cout<<"\nThe word was: "<<codeword<<std::endl;

    if(filledIn == codeword)
    {
        std::cout<<"\nYay!!! You saved Bob from being hanged!!!\n"
                 <<"He can see his family again!!!\n\n";
    }
    else
    {
        std::cout<<"\nOh no! Bob is dead :(\n"
                 <<"Now his family will be sad\n\n";
    }
}

void display(std::vector<char> incorrect, std::string filledIn)
{
    std::cout<<"Incorrect guesses: \n";

    for(int i = 0; i < incorrect.size(); i++)
    {
        std::cout<<incorrect[i]<<" ";
    }

    std::cout<<"\nWord: \n";

    for(int i = 0; i < filledIn.length(); i++)
    {
        std::cout<<filledIn[i]<<" ";
    }
}

void header(std::ifstream& fin)
{
    fin.open(ascii);
    std::string line;
    while(!fin.eof())
    {
        getline(fin, line);
        std::cout<<line<<std::endl;
    }
    fin.close();
}

void generateHangedPic(int misses)
{
    std::string line;
    switch(misses)
    {
        case 0:
            hangpic1.open(PIC1);
            while(!hangpic1.eof())
            {
                getline(hangpic1, line);
                std::cout<<line<<std::endl;
            }
            hangpic1.close();
            break;
        case 1:
            hangpic2.open(PIC2);
            while(!hangpic2.eof())
            {
                getline(hangpic2, line);
                std::cout<<line<<std::endl;
            }
            hangpic2.close();
            break;
        case 2:
            hangpic3.open(PIC3);
            while(!hangpic3.eof())
            {
                getline(hangpic3, line);
                std::cout<<line<<std::endl;
            }
            hangpic3.close();
            break;
        case 3:
            hangpic4.open(PIC4);
            while(!hangpic4.eof())
            {
                getline(hangpic4, line);
                std::cout<<line<<std::endl;
            }
            hangpic4.close();
            break;
        case 4:
            hangpic5.open(PIC5);
            while(!hangpic5.eof())
            {
                getline(hangpic5, line);
                std::cout<<line<<std::endl;
            }
            hangpic5.close();
            break;
        case 5:
            hangpic6.open(PIC6);
            while(!hangpic6.eof())
            {
                getline(hangpic6, line);
                std::cout<<line<<std::endl;
            }
            hangpic6.close();
            break;
        case 6:
            hangpic7.open(PIC7);
            while(!hangpic7.eof())
            {
                getline(hangpic7, line);
                std::cout<<line<<std::endl;
            }
            hangpic7.close();
            break;
        default:
            std::cout<<misses<<" something went wrong";
    }

}