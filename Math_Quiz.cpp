#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

// Enumeration to define difficulty levels
enum enLevel
{
    Easy = 1,
    Med = 2,
    Hard = 3,
    Mix = 4
};

// Enumeration to define math operation types
enum enOperation_Type
{
    Add = 1,
    Sub = 2,
    Mult = 3,
    Div = 4,
    mix = 5
};

// Struct to define number range based on level
struct stNumber_Of_Degree_Level
{
    short From;
    short To;
};

// Struct to store all information about a math equation/question
struct stInfo_Of_Equation
{
    short How_Many_Rounds;
    enLevel Level;
    enOperation_Type Operations;
    short First_Number_Of_Equation;
    char Operation_Of_Equation;
    short Second_Number_Of_Equation;
    short Answer_By_User;
    int Result = 0;
    short Count_Right_Answer = 0;
    short Count_Wrong_Answer = 0;
};

// Struct to represent one round of quiz
struct stInfo_Of_Round
{
    stInfo_Of_Equation Info_Of_Round;
};

// Function to ask the user for a number greater than a certain limit
int Ask_And_Read_From_User(string Message, short limit)
{
    short Number;
    do
    {
        cout << Message << endl;
        cin >> Number;
    } while (Number <= limit);
    return Number;
}

// Function to ask the user to select a difficulty level
enLevel Ask_User_about_Level()
{
    short Level;
    do
    {
        cout << "Enter Questions level [1]Easy, [2]Med, [3]Hard, [4]Mix ?\n";
        cin >> Level;
    } while (Level > 4 || Level < 1);
    return (enLevel)Level;
}

// Function to ask the user to select a math operation type
enOperation_Type Ask_User_about_Operation_Type()
{
    short Operation_Type;
    do
    {
        cout << "Enter Operation_Type [1]Add, [2]Sub, [3]Mul, [4]Div ,[5]Mix ?\n";
        cin >> Operation_Type;
    } while (Operation_Type > 5 || Operation_Type < 1);
    return (enOperation_Type)Operation_Type;
}

// Function to generate a random number within a range
short Random_Number(short From, short To)
{
    int Number;
    Number = rand() % (To - From + 1) + From;
    return Number;
}

// Converts the difficulty level enum to a string for display
string Convert_EnLevel_To_String(stInfo_Of_Round Info)
{
    string Name_Of_Level[4] = {"Easy", "Med", "Hard", "Mix"};
    return Name_Of_Level[Info.Info_Of_Round.Level - 1];
}

// Converts the operation type enum to a string for display
string Convert_EnOperatio_To_String(stInfo_Of_Round Info)
{
    string Name_Of_Level[5] = {"Add", "Sub", "Mult", "Div", "Mix"};
    return Name_Of_Level[Info.Info_Of_Round.Operations - 1];
}

// Function to set the number range based on selected level
stNumber_Of_Degree_Level Degree_Of_Level(enLevel Input, stNumber_Of_Degree_Level &Number)
{
    switch (Input)
    {
    case Easy:
        Number.From = 1;
        Number.To = 10;
        break;
    case Med:
        Number.From = 11;
        Number.To = 50;
        break;
    case Hard:
        Number.From = 51;
        Number.To = 100;
        break;
    default:
        Number.From = 1;
        Number.To = 100;
        break;
    }
    return Number;
}

// Function to determine the operation symbol based on type or randomly if "Mix"
char Operation(enOperation_Type Input)
{
    char Operation[4] = {'+', '-', '*', '/'};
    if (Input >= 1 && Input <= 4)
        return Operation[Input - 1];
    else
        return Operation[Random_Number(0, 3)];
}

// Prints the current question number
void Print_Count_Questions(short Input, short Count)
{
    cout << "\nQuestions [" << 0 + Count << "/" << Input << "]" << endl;
}

// Prints the math equation in a formatted way
void Print_Equation(stInfo_Of_Equation Info_Of_Equation)
{
    cout << Info_Of_Equation.First_Number_Of_Equation << endl;
    cout << Info_Of_Equation.Second_Number_Of_Equation << "\t" << Info_Of_Equation.Operation_Of_Equation << endl;
    cout << "__________" << endl;
}

// Calculates the correct answer based on the operator
stInfo_Of_Equation Right_Answer(stInfo_Of_Equation &Info_Of_Equation)
{
    switch (Info_Of_Equation.Operation_Of_Equation)
    {
    case '+':
        Info_Of_Equation.Result = Info_Of_Equation.First_Number_Of_Equation + Info_Of_Equation.Second_Number_Of_Equation;
        break;
    case '-':
        Info_Of_Equation.Result = Info_Of_Equation.First_Number_Of_Equation - Info_Of_Equation.Second_Number_Of_Equation;
        break;
    case '*':
        Info_Of_Equation.Result = Info_Of_Equation.First_Number_Of_Equation * Info_Of_Equation.Second_Number_Of_Equation;
        break;
    default:
        Info_Of_Equation.Result = Info_Of_Equation.First_Number_Of_Equation / Info_Of_Equation.Second_Number_Of_Equation;
        break;
    }
    return Info_Of_Equation;
}

// Checks whether the user's answer is correct
bool Check_Answer(stInfo_Of_Equation Info_Of_Equation)
{
    return Info_Of_Equation.Answer_By_User == Info_Of_Equation.Result;
}

// Changes the screen color based on whether the answer is correct or not
void Set_Screen_Color(bool Result)
{
    if (Result==true)
        system("color 2F"); // Green for correct
    else
    {
        system("color 4F"); // Red for wrong
        cout << "\a"; // Beep sound
    }
}

// Displays the correct answer if the user was wrong
void Print_Right_Answer(stInfo_Of_Equation Info_Of_Equation)
{
    cout << "\nThe right Answer is " << Info_Of_Equation.Result << "\n"
         << endl;
}

// Main loop for all quiz rounds
stInfo_Of_Round Start_Rounds()
{
    stInfo_Of_Round Info;

    // User inputs
    Info.Info_Of_Round.How_Many_Rounds = Ask_And_Read_From_User("How many Questions do you want to answer?", 0);
    Info.Info_Of_Round.Level = Ask_User_about_Level();
    Info.Info_Of_Round.Operations = Ask_User_about_Operation_Type();

    // Determine number range
    stNumber_Of_Degree_Level Number;
    Degree_Of_Level(Info.Info_Of_Round.Level, Number);

    // Loop over each round/question
    for (short i = 0; i < Info.Info_Of_Round.How_Many_Rounds; i++)
    {
        Info.Info_Of_Round.First_Number_Of_Equation = Random_Number(Number.From, Number.To);
        Info.Info_Of_Round.Second_Number_Of_Equation = Random_Number(Number.From, Number.To);
        Info.Info_Of_Round.Operation_Of_Equation = Operation(Info.Info_Of_Round.Operations);

        Print_Count_Questions(Info.Info_Of_Round.How_Many_Rounds, i + 1);
        Print_Equation(Info.Info_Of_Round);
        Info.Info_Of_Round.Answer_By_User = Ask_And_Read_From_User("", -1);
        Right_Answer(Info.Info_Of_Round);

        // Check and give feedback
        if (Check_Answer(Info.Info_Of_Round))
        {
            Set_Screen_Color(true);
            cout << "Right Answer :-)\n" << endl;
            Info.Info_Of_Round.Count_Right_Answer++;
        }
        else
        {
            Set_Screen_Color(false);
            cout << "Worng Answer :-(";
            Print_Right_Answer(Info.Info_Of_Round);
            Info.Info_Of_Round.Count_Wrong_Answer++;
        }
    }

    return Info;
}

// Determines if the user passed the quiz
bool Final_Result(stInfo_Of_Equation Info)
{
    return Info.Count_Right_Answer >= Info.Count_Wrong_Answer;
}

// Prints the final result summary
void Print_Final_Result(stInfo_Of_Round Info)
{
    cout << "\n______________________________\n";
    cout << "Final Result is ";
    if (Final_Result(Info.Info_Of_Round))
        cout << "PASS :-)\n";
    else
        cout << "FAIL :-(\n";
    cout << "______________________________\n";
    cout << "Number of Questions: " << Info.Info_Of_Round.How_Many_Rounds << endl;
    cout << "Quetions Level     : " << Convert_EnLevel_To_String(Info) << endl;
    cout << "OpType             : " << Convert_EnOperatio_To_String(Info) << endl;
    cout << "Number Of Right Answers: " << Info.Info_Of_Round.Count_Right_Answer << endl;
    cout << "Number Of Worng Answers: " << Info.Info_Of_Round.Count_Wrong_Answer << endl;
    cout << "______________________________\n";
}

// Asks the user if they want to play again
bool Ask_User_Do_Play_Again()
{
    char Answer;
    do
    {
        cout << "Do You want play again? Y/N?" << endl;
        cin >> Answer;
    } while (Answer != 'Y' && Answer != 'N');

    return Answer == 'Y';
}

// Resets the console screen for a new game
void Reset_Play()
{
    system("cls");
    system("color 0F");
}

// Manages the entire game lifecycle
void Start_Game()
{
    bool Answer;
    Print_Final_Result(Start_Rounds());

    do
    {
        Answer = Ask_User_Do_Play_Again();
        if (Answer)
        {
            Reset_Play();
            Print_Final_Result(Start_Rounds());
        }
    } while (Answer);
}

// Program entry point
int main()
{
    srand((unsigned)time(NULL)); // Seed random number generator
    Start_Game(); // Start the math quiz game
    return 0;
}

