#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <bits/stdc++.h>
#include <Windows.h>

using namespace std;

bool ended, print;

class Student
{
public:
    string firstName;
    string lastName;
    double mark;
    int id;
};

vector<string> splitToWords(string text)
{
    string word = "";
    vector<string> words;

    for (int x = 0; x < text.size(); x++)
    {
        if (text[x] == ' ')
        {
            words.push_back(word);
            word = "";
        }
        else
        {
            word += text[x];
        }
    }
    words.push_back(word);

    return words;
}

void printStudents(vector<Student> students)
{
    system("CLS");

    cout
        << left
        << setw(5)
        << "Id"
        << left
        << setw(15)
        << "First Name"
        << left
        << setw(15)
        << "Last Name"
        << left
        << setw(10)
        << "Marks"
        << endl;
    cout << "----------------------------------------------------" << endl;

    for (int i = 0; i < students.size(); i++)
    {
        cout
            << left
            << setw(5)
            << students[i].id
            << left
            << setw(15)
            << students[i].firstName
            << left
            << setw(15)
            << students[i].lastName
            << left
            << setw(15)
            << students[i].mark
            << endl;
    }

    if (students.size() < 10)
    {
        for (int n = 0; n < 10 - students.size(); n++)
        {
            cout << "\n";
        }
    }
    else
    {
        cout << "\n";
    }
}

void printStudentManagementGuide()
{
    cout << "Add new student          ->   ADD \"First Name\" \"Last Name\"" << endl
         << "Set one's mark           ->   SET \"Id\" \"Mark\" " << endl
         << "Delete a student         ->   DEL \"Id\" " << endl
         << "Delete a student's mark  ->   CLR \"Id\" " << endl
         << "Back to menu             ->   BACK" << endl;
}

void printAverageMarksGuide()
{
    cout << "Show the average  ->  CAL" << endl
         << "Back to menu      ->  BACK" << endl;
}

void averageMarks(vector<Student> &students)
{
    // input, inputWords and students variables
    string input;
    vector<string> inputWords;

    if (print == false)
    {
        printAverageMarksGuide();
        print = true;
    }

    // get input and store it in input
    cout << "> ";
    getline(cin, input);
    // split input to words and store it in inputWords
    inputWords = splitToWords(input);

    double average = 0;
    double sum = 0;

    if (inputWords[0] == "CAL")
    {
        if (students.size() == 0)
        {
            cout << "\nNo students!\n";
        }
        else if (students.size() >= 1)
        {
            for (int i = 0; i < students.size(); i++)
            {
                sum += students[i].mark;
            }
            average = sum / students.size();
            cout << "\nThe average is " << average << "\n";
        }
    }

    else if (inputWords[0] == "BACK")
    {
        ended = true;
    }

    else if (inputWords[0] != "")
    {
        cout << "Wrong input!";

        Sleep(2000);
        system("CLS");
    }
}

void studentManagement(vector<Student> &students)
{
    printStudents(students);

    // input, inputWords and students variables
    string input;
    vector<string> inputWords;

    printStudentManagementGuide();

    // get input and store it in input
    cout << "\n\n> ";
    getline(cin, input);
    // split input to words and store it in inputWords
    inputWords = splitToWords(input);

    if (inputWords[0] == "ADD")
    {
        if (inputWords.size() == 3)
        {
            // make newStudent object then set first name and last name
            Student newStudent;
            newStudent.firstName = inputWords[1];
            newStudent.lastName = inputWords[2];
            newStudent.id = (students.size() + 1) * 10 + rand() % 10 + 1;
            newStudent.mark = 0;
            students.push_back(newStudent);
        }
    }
    else if (inputWords[0] == "DEL")
    {
        if (inputWords.size() == 2)
        {
            // get id of the student and delete it from the vector
            int id = stoi(inputWords[1]);

            for (int i = 0; i < students.size(); i++)
            {
                if (students[i].id == id)
                {
                    students.erase(students.begin() + i);
                }
            }
        }
    }
    else if (inputWords[0] == "SET")
    {
        if (inputWords.size() == 3)
        {
            // get id of the student and set mark
            int id = stoi(inputWords[1]);
            double mark = stod(inputWords[2]);

            for (int i = 0; i < students.size(); i++)
            {
                if (students[i].id == id)
                {
                    students[i].mark = mark;
                }
            }
        }
    }
    else if (inputWords[0] == "CLR")
    {
        if (inputWords.size() == 2)
        {
            // get id of the student and clear mark
            int id = stoi(inputWords[1]);

            for (int i = 0; i < students.size(); i++)
            {
                if (students[i].id == id)
                {
                    students[i].mark = 0;
                }
            }
        }
    }

    else if (inputWords[0] == "BACK")
    {
        ended = true;

        // clear the screen
        system("CLS");
    }

    else if (inputWords[0] != "")
    {
        cout << "Wrong input!";

        Sleep(2000);
        system("CLS");
    }
}

int main()
{
    vector<Student> students;

    while (true)
    {
        printStudents(students);

        cout << "[1] Student Management\n[2] Average Student Marks\n[3] Exit The Program\n\n";
        cout << "Please enter your choice: (Number Only) ";

        int num;
        cin >> num;

        print = false;
        ended = false;

        if (num == 1)
        {
            system("CLS");

            while (ended != true)
            {
                studentManagement(students);
            }
        }

        else if (num == 2)
        {
            printStudents(students);

            while (ended != true)
            {
                averageMarks(students);
            }
        }

        else if (num == 3)
        {
            system("CLS");
            exit(10);
        }

        else
        {
            cout << "\nWrong input!!";

            Sleep(2000);
        }
    }

    return 0;
}
