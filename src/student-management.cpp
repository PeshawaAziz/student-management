#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <bits/stdc++.h>
#include <windows.h>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

class Student
{
public:
    int id;
    string firstName;
    string lastName;
    double avgMark = 0;
    vector<double> marks;
};

bool isEmpty(std::ifstream &pFile)
{
    return pFile.peek() == std::ifstream::traits_type::eof();
}

string toLowerCase(string s)
{
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] >= 'A' && s[i] <= 'Z')
        {
            s[i] = tolower(s[i]);
        }
    }
    return s;
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

void getSubjects(vector<string> &subjects)
{
    // get subjects from json file
    json j;
    ifstream file("subjects.json");
    vector<string> _subjects;

    if (isEmpty(file))
    {
        j["subjects"] = {};
    }
    else
    {
        file >> j;
    }

    for (int x = 0; x < j["subjects"].size(); x++)
    {
        string subject = j["subjects"][x];
        _subjects.push_back(subject);
    }
    subjects = _subjects;

    file.close();
}

void setSubjects(vector<string> subjects)
{
    // set subjects to the json file
    json j;
    ofstream file("subjects.json");

    j["subjects"] = subjects;

    file << j;
    file.close();
}

void getStudents(vector<Student> &students)
{
    // get students from json file
    json j;
    ifstream file("students.json");
    vector<Student> _students;

    if (isEmpty(file))
    {
        j["students"] = {};
    }
    else
    {
        file >> j;
    }

    for (int x = 0; x < j["students"].size(); x++)
    {
        Student student;
        student.id = j["students"][x]["id"];
        student.firstName = j["students"][x]["firstName"];
        student.lastName = j["students"][x]["lastName"];

        for (int y = 0; y < j["students"][x]["marks"].size(); y++)
        {
            double mark = j["students"][x]["marks"][y];
            student.marks.push_back(mark);
        }

        _students.push_back(student);
    }

    students = _students;
    file.close();
}

void setStudents(vector<Student> students)
{
    // set students to the json file
    json j;
    ofstream file("students.json");

    j["students"] = j.array();

    for (int x = 0; x < students.size(); x++)
    {
        j["students"][x] = j.object();
        j["students"][x]["id"] = students[x].id;
        j["students"][x]["firstName"] = students[x].firstName;
        j["students"][x]["lastName"] = students[x].lastName;
        j["students"][x]["marks"] = students[x].marks;
    }

    file << j;
    file.close();
}

void writeData(vector<Student> students, vector<string> subjects)
{
    setSubjects(subjects);
    setStudents(students);
}

void readData(vector<Student> &students, vector<string> &subjects)
{
    getSubjects(subjects);
    getStudents(students);
}

int indexOf(vector<string> array, string item)
{
    for (int i = 0; i < array.size(); i++)
    {
        if (array[i] == item)
        {
            return i;
        }
    }

    return -1;
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
             << setw(15)
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
                 << setw(15)
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
    cout << "Add new student          ->   ADD \"First Name\" \"Last Name\"" << endl
         << "Set one's mark           ->   SET \"Id\" \"Subject\" \"Mark\"" << endl
         << "Delete a student's mark  ->   CLR \"Id\" \"Subject\"" << endl
         << "Delete a student         ->   DEL \"Id\"" << endl
         << "Back to menu             ->   BACK" << endl;
}

void printSubjectManagementGuide()
{
    cout << "Add new subject          ->   ADD \"Subject\"" << endl
         << "Delete a subject         ->   DEL \"Subject\"" << endl
         << "Back to menu             ->   BACK" << endl;
}

void printResetDataGuide()
{
    cout << "Remove all students      ->   REM students" << endl
         << "Remove all subjects      ->   REM subjects" << endl
         << "Back to menu             ->   BACK" << endl;
}

void printSearchStudentsGuide()
{
    cout << "Search for a student     ->   SEARCH \"First Name\"" << endl
         << "                         ->   SEARCH \"Last Name\"" << endl
         << "                         ->   SEARCH \"First Name\" \"Last Name\"" << endl
         << "Back to menu             ->   BACK" << endl;
}

void printSortStudentsGuide()
{
    cout << "Sort students by average mark   ->   SORT AVG" << endl
         << "Sort students by subject mark   ->   SORT \"Subject\"" << endl;
}

void resetData(vector<Student> &students, vector<string> &subjects, bool &ended)
{
    system("CLS");

    printSubjects(subjects);
    printStudents(students, subjects);

    // input, inputWords
    string input;
    vector<string> inputWords;

    printResetDataGuide();

    // get input and store it in input
    cout << "\n\n> ";
    getline(cin, input);
    // split input to words and store it in inputWords
    inputWords = splitToWords(input);

    if (inputWords[0] == "REM")
    {
        if (inputWords[1] == "students")
        {
            string sure = "";
            cout << "Are you sure you want to remove all students? (YES / NO): ";
            cin >> sure;

            if (sure == "YES")
            {
                students.clear();
            }
            else if (sure == "NO")
            {
                cout << "Cancelled" << endl;
            }

            Sleep(1000);
            system("CLS");
        }
        else if (inputWords[1] == "subjects")
        {
            string sure = "";
            cout << "Are you sure you want to remove all students? (YES / NO): ";
            cin >> sure;

            if (sure == "YES")
            {
                subjects.clear();
            }
            else if (sure == "NO")
            {
                cout << "Cancelled" << endl;
            }

            Sleep(1000);
            system("CLS");
        }
    }
    else if (inputWords[0] == "BACK")
    {
        ended = true;

        system("CLS");
    }
    else if (inputWords[0] != "")
    {
        cout << "Wrong input!";

        Sleep(2000);
        system("CLS");
    }

    writeData(students, subjects);
}

void subjectManagement(vector<Student> &students, vector<string> &subjects, bool &ended)
{
    system("CLS");
    printSubjects(subjects);

    // input, inputWords
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
        vector<string> _subjects;
        for (int x = 0; x < _subjects.size(); x++)
        {
            _subjects[x] = toLowerCase(subjects[x]);
        }

        // check if the subject already exists otherwise add it
        if (find(_subjects.begin(), _subjects.end(), toLowerCase(inputWords[1])) == subjects.end() && inputWords.size() == 2)
        {
            subjects.push_back(inputWords[1]);

            vector<double> _marks;

            // Add the subject to all the students
            for (int i = 0; i < subjects.size(); i++)
            {
                _marks.push_back(0);
            }

            for (int i = 0; i < students.size(); i++)
            {
                students[i].marks = _marks;
            }
        }
        else
        {
            cout << "Subject already exists!" << endl;

            Sleep(1000);
        }
    }
    else if (inputWords[0] == "DEL" && inputWords.size() == 2)
    {
        // get title of the subject and delete it from the vector
        string title = inputWords[1];

        for (int i = 0; i < subjects.size(); i++)
        {
            if (subjects[i] == title)
            {
                subjects.erase(subjects.begin() + i);

                // erase every student's mark for that subject
                for (int j = 0; j < students.size(); j++)
                {
                    students[j].marks.erase(students[j].marks.begin() + i);
                }
            }
        }
    }
    else if (inputWords[0] == "BACK")
    {
        ended = true;

        system("CLS");
    }
    else if (inputWords[0] != "")
    {
        cout << "Wrong input!";

        Sleep(2000);
        system("CLS");
    }

    writeData(students, subjects);
}

void studentManagement(vector<Student> &students, vector<string> &subjects, bool &ended)
{
    printStudents(students, subjects);

    // input, inputWords
    string input;
    vector<string> inputWords;

    printStudentManagementGuide();

    // get input and store it in input
    cout << "\n\n> ";
    getline(cin, input);
    // split input to words and store it in inputWords
    inputWords = splitToWords(input);

    if (inputWords[0] == "ADD" && inputWords.size() == 3)
    {
        // make newStudent object
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
    else if (inputWords[0] == "DEL" && inputWords.size() == 2)
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
    else if (inputWords[0] == "SET" && inputWords.size() == 4)
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
    else if (inputWords[0] == "CLR" && inputWords.size() == 3)
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
    else if (inputWords[0] == "BACK")
    {
        ended = true;
        system("CLS");
    }
    else if (inputWords[0] != "")
    {
        cout << "Wrong input!";
        Sleep(2000);
        system("CLS");
    }

    writeData(students, subjects);
}

void searchStudents(vector<Student> &students, vector<string> &subjects, vector<Student> &search, bool &ended)
{
    string input;
    vector<string> inputWords;

    printSearchStudentsGuide();

    cout << "\n\n> ";
    getline(cin, input);

    inputWords = splitToWords(input);

    if (inputWords[0] == "SEARCH")
    {
        if (inputWords.size() == 2)
        {
            search.clear();
            string fn, ln;

            for (int i = 0; i < students.size(); i++)
            {
                fn = toLowerCase(students[i].firstName);
                ln = toLowerCase(students[i].lastName);

                if (fn == toLowerCase(inputWords[1]) || ln == toLowerCase(inputWords[1]))
                {
                    search.push_back(students[i]);
                }
            }
        }
        else if (inputWords.size() == 3)
        {
            search.clear();
            string fn, ln;

            for (int i = 0; i < students.size(); i++)
            {
                fn = toLowerCase(students[i].firstName);
                ln = toLowerCase(students[i].lastName);

                if (fn == inputWords[1] && ln == inputWords[2])
                {
                    search.push_back(students[i]);
                }
            }
        }
    }

    else if (inputWords[0] == "BACK")
    {
        ended = true;
    }

    else if (input != "")
    {
        cout << "Wrong input!";
        Sleep(2000);
    }

    printStudents(search, subjects);
}

void sortStudents(vector<Student> &students, vector<string> &subjects, bool &ended)
{
    printStudents(students, subjects);

    // input, inputWords
    string input;
    vector<string> inputWords;

    printSortStudentsGuide();

    // get input and store it in input
    cout << "\n\n> ";
    getline(cin, input);
    // split input to words and store it in inputWords
    inputWords = splitToWords(input);

    if (inputWords[0] == "SORT" && inputWords.size() == 2)
    {
        string sortType = inputWords[1];
        if (sortType == "AVG")
        {
            sort(students.begin(), students.end(), greater<double>());
        }
        for (int i = 0; i < subjects.size(); i++)
        {
            if (toLowerCase(sortType) == toLowerCase(subjects[i]))
            {
                sort(students.begin(), students.end(), greater<double>());
            }
        }
    }
    else if (inputWords[0] == "BACK")
    {
        ended = true;
        system("CLS");
    }
    else if (inputWords[0] != "")
    {
        cout << "Wrong input!";
        Sleep(2000);
        system("CLS");
    }

    writeData(students, subjects);
}

int main()
{
    bool ended, print;
    vector<Student> students;
    vector<string> subjects;

    while (true)
    {
        readData(students, subjects);
        printStudents(students, subjects);

        cout << "[1] Student Management\n[2] Subject Management\n[3] Reset Data\n[4] Search\n[5] Sort\n[6] Exit The Program\n\n";
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
                studentManagement(students, subjects, ended);
            }
        }

        else if (input == "2")
        {
            system("CLS");

            while (ended != true)
            {
                subjectManagement(students, subjects, ended);
            }
        }

        else if (input == "3")
        {
            system("CLS");

            while (ended != true)
            {
                resetData(students, subjects, ended);
            }
        }

        else if (input == "4")
        {
            system("CLS");

            vector<Student> search;

            while (ended != true)
            {
                searchStudents(students, subjects, search, ended);
            }
        }

        else if (input == "5")
        {
            system("CLS");

            while (ended != true)
            {
                sortStudents(students, subjects, ended);
            }
        }

        else if (input == "6")
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