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
    // double mark;
    int id;
    vector<double> marks;
};

int indexOf(vector<string> array, string item)
{
    for (int i = 0; i < array.size(); i++)
    {
        if (array[i] == item)
        {
            return i;
        }
    }
}

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

void printStudents(vector<Student> students, vector<string> subjects)
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
        << "Last Name";
    for (int i = 0; i < subjects.size(); i++)
    {
        cout << left
             << setw(10)
             << subjects[i];
    }
    cout << endl;

    cout << "----------------------------------";

    for (int i = 0; i < subjects.size(); i++)
    {
        cout << "----------";
    }

    cout << endl;

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
            << students[i].lastName;

        // print out the marks
        for (int j = 0; j < students[i].marks.size(); j++)
        {
            cout << left
                 << setw(10)
                 << students[i].marks[j];
        }
        cout << endl;
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

void printSubjects(vector<string> subjects)
{
    cout << "Subjects: ";

    for (int i = 0; i < subjects.size(); i++)
    {
        if (i == 0)
        {
            cout << subjects[i];
        }
        else
        {
            cout << ", " << subjects[i];
        }
    }
    cout << "\n\n\n\n\n"
         << endl;
}

void printStudentManagementGuide()
{
    cout << "Add new student          ->   ADD \"First Name\" \"Last Name\" " << endl
         << "Set one's mark           ->   SET \"First Name\" \"Last Name\" \"Mark\" " << endl
         << "Delete a student         ->   DEL \"First Name\" \"Last Name\" " << endl
         << "Delete a student's mark  ->   CLR \"First Name\" \"Last Name\" " << endl
         << "Back to menu             ->   BACK" << endl;
}

void printAverageMarksGuide()
{
    cout << "Show the average  ->   CAL" << endl
         << "Back to menu      ->   BACK" << endl;
}

void printSubjectManagementGuide()
{
    cout << "Add new subject          ->   ADD \"Title\" " << endl
         << "Delete a subject         ->   DEL \"Title\" " << endl
         << "Back to menu             ->   BACK" << endl;
}

void subjectManagement(vector<Student> &students, vector<string> &subjects)
{
    system("CLS");

    printSubjects(subjects);

    // input, inputWords and students variables
    string input;
    vector<string> inputWords;

    printSubjectManagementGuide();

    // get input and store it in input
    cout << "\n\n> ";
    getline(cin, input);
    // split input to words and store it in inputWords
    inputWords = splitToWords(input);

    if (inputWords[0] == "ADD")
    {
        // check if the subject already exists otherwise add it
        if (find(subjects.begin(), subjects.end(), inputWords[1]) == subjects.end())
        {
            if (inputWords.size() == 2)
            {
                subjects.push_back(inputWords[1]);
            }
        }
        else
        {
            cout << "Subject already exists!" << endl;

            Sleep(1000);
        }
    }
    else if (inputWords[0] == "DEL")
    {
        if (inputWords.size() == 2)
        {
            // get title of the subject and delete it from the vector
            string title = inputWords[1];

            for (int i = 0; i < subjects.size(); i++)
            {
                if (subjects[i] == title)
                {
                    subjects.erase(subjects.begin() + i);

                    // erase every student's mark with the subject
                    for (int j = 0; j < students.size(); j++)
                    {
                        students[j].marks.erase(students[j].marks.begin() + i);
                    }
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

// void averageMarks(vector<Student> &students)
// {
//     // input, inputWords and students variables
//     string input;
//     vector<string> inputWords;

//     if (print == false)
//     {
//         printAverageMarksGuide();
//         print = true;
//     }

//     // get input and store it in input
//     cout << "> ";
//     getline(cin, input);
//     // split input to words and store it in inputWords
//     inputWords = splitToWords(input);

//     double average = 0;
//     double sum = 0;

//     if (inputWords[0] == "CAL")
//     {
//         if (students.size() == 0)
//         {
//             cout << "\nNo students!\n";
//         }
//         else if (students.size() >= 1)
//         {
//             for (int i = 0; i < students.size(); i++)
//             {
//                 sum += students[i].mark;
//             }
//             average = sum / students.size();
//             cout << "\nThe average is " << average << "\n";
//         }
//     }
//     else if (inputWords[0] == "BACK")
//     {
//         ended = true;
//     }
//     else if (inputWords[0] != "")
//     {
//         cout << "Wrong input!";

//         Sleep(2000);
//         system("CLS");
//     }
// }

void studentManagement(vector<Student> &students, vector<string> &subjects)
{
    printStudents(students, subjects);

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
        // add the student to the vector
        if (inputWords.size() == 3)
        {
            // make newStudent object then set first name and last name
            Student newStudent;
            newStudent.firstName = inputWords[1];
            newStudent.lastName = inputWords[2];
            newStudent.id = (students.size() + 1) * 10 + rand() % 10 + 1;
            // set all marks to 0
            for (int i = 0; i < subjects.size(); i++)
            {
                newStudent.marks.push_back(0);
            }
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
        if (inputWords.size() == 4)
        {
            // get id of the student and set mark
            int id = stoi(inputWords[1]);
            string subject = inputWords[2];
            double mark = stod(inputWords[3]);

            for (int i = 0; i < students.size(); i++)
            {
                if (students[i].id == id)
                {
                    students[i].marks[indexOf(subjects, subject)] = mark;
                }
            }
        }
    }
    else if (inputWords[0] == "CLR")
    {
        if (inputWords.size() == 3)
        {
            // get id of the student and clear mark
            int id = stoi(inputWords[1]);
            string subject = inputWords[2];

            for (int i = 0; i < students.size(); i++)
            {
                if (students[i].id == id)
                {
                    students[i].marks[indexOf(subjects, subject)] = 0;
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
    vector<string> subjects = {"Math", "Physics", "Chemistry"};

    while (true)
    {
        printStudents(students, subjects);

        cout << "[1] Student Management\n[2] Subject Management\n[3] Average Student Marks\n[4] Exit The Program\n\n";
        cout << "Please enter your choice: (Number Only) ";

        string input;
        cin >> input;

        print = false;
        ended = false;

        if (input == "1")
        {
            system("CLS");

            while (ended != true)
            {
                studentManagement(students, subjects);
            }
        }

        else if (input == "2")
        {
            system("CLS");

            while (ended != true)
            {
                subjectManagement(students, subjects);
            }
        }

        else if (input == "3")
        {
            system("CLS");

            printStudents(students, subjects);

            while (ended != true)
            {
                // averageMarks(students);
            }
        }

        else if (input == "4")
        {
            system("CLS");
            exit(10);
        }

        else
        {
            cout << "\nWrong input!!";

            Sleep(1000);
        }
    }

    return 0;
}
