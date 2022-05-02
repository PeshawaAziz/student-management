#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <bits/stdc++.h>
#include <Windows.h>
#include <map>
#include <algorithm>

using namespace std;

bool ended, print;

class Student
{
public:
    string firstName;
    string lastName;
    int id;
    double sortSubject;
    double avgMark = 0;
    map<string, double> marks = {{"math", 0}, {"science", 0}, {"chemistry", 0}};
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

string convertStrToLower(string str)
{
	string res = str;
	
	for (int i=0; i<res.size(); i++)
	{
		res[i] = tolower(res[i]);
	}
	
	return res;
}

vector<string> convertVecToLower(string str, vector<string> vec)
{
	vector<string> res = vec;
	
	if (str == "firstOne" && res.size() > 0)
	{
		for (int i=0; i<res[0].size(); i++)
		{
			res[0][i] = tolower(res[0][i]);
		}
	}
	else if (str == "all" && res.size() > 0)
	{
		for (int i=0; i<vec.size(); i++)
		{
			for (int j=0; j<vec[i].size(); j++)
			{
				res[i][j] = tolower(res[i][j]);
			}
		}
	}
	
	return res;
}

void averageMark(vector<Student> &students, vector<string> &subjects)
{
	double num;
	
	for (int i=0; i<students.size(); i++)
	{
		num = 0;
		
		for (int j=0; j<subjects.size(); j++)
		{
			num += students[i].marks[subjects[j]];
		}
		
		students[i].avgMark = num / (subjects.size());
	}
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
    
    cout << left
    	 << setw(10)
    	 << "average mark";
    
    cout << endl;

    cout << "----------------------------------";

    for (int i = 0; i < subjects.size(); i++)
    {
        cout << "----------";
    }

    cout << "-------------" << endl;
    
    // set the new average marks
    averageMark(students, subjects);

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
        for (int j = 0; j < subjects.size(); j++)
        {
            cout << left
                 << setw(10)
                 << students[i].marks[subjects[j]];
        }
        cout << left
        	 << setw(10)
        	 << students[i].avgMark;
        
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

void printShowStudentsInOrderGuide()
{
    cout << "Arrange students by average mark  ->  SORT AVG" << endl
         << "Back to menu                      ->   BACK" << endl;
}

void printSubjectManagementGuide()
{
    cout << "Add new subject          ->   ADD \"Title\" " << endl
         << "Delete a subject         ->   DEL \"Title\" " << endl
         << "Back to menu             ->   BACK" << endl;
}

void printSearchStudentsGuide()
{
	cout << "Search for a student -> SEARCH \"first name\"" << endl
		 << "                     -> SEARCH \"last name\"" << endl
		 << "                     -> SEARCH \"first name\" \"last name\"" << endl
		 << "Back to menu         -> BACK" << endl;
}

void subjectManagement(vector<Student> &students, vector<string> &subjects) // finish!!!
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
    inputWords = convertVecToLower("firstOne", splitToWords(input));

    if (inputWords[0] == "add")
    {
        // check if the subject already exists otherwise add it
        vector<string> subj = subjects;
        if (find(subj.begin(), subj.end(), convertStrToLower(inputWords[1])) == subjects.end())
        {
            if (inputWords.size() == 2)
            {
                subjects.push_back(inputWords[1]);
                for (auto i: students)
                {
                	i.marks.insert({convertStrToLower(inputWords[1]), 0});
				}
            }
        }
        else
        {
            cout << "Subject already exists!" << endl;

            Sleep(1000);
        }
    }
    else if (inputWords[0] == "del")
    {
        if (inputWords.size() == 2)
        {
            // get title of the subject and delete it from the vector
            string title = convertStrToLower(inputWords[1]);

            for (int i = 0; i < subjects.size(); i++)
            {
                if (convertStrToLower(subjects[i]) == title)
                {
                    subjects.erase(subjects.begin() + i);

                    // erase every student's mark with the subject
                    for (int j = 0; j < students.size(); j++)
                    {
                        students[j].marks.erase(title);
                    }
                }
            }
        }
    }
    else if (inputWords[0] == "back")
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

void studentManagement(vector<Student> &students, vector<string> &subjects) // wududi finish!!!
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
    if (convertStrToLower(inputWords[0]) != "add")
    {
    	inputWords = convertVecToLower("all", inputWords);
	}

    if (convertStrToLower(inputWords[0]) == "add")
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
            string subject;
            for (int i = 0; i < subjects.size(); i++)
            {
            	subject = convertStrToLower(subjects[i]);
            	newStudent.marks.insert({subject, 0});
            }
            students.push_back(newStudent);
        }
    }
    else if (inputWords[0] == "del")
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
    else if (inputWords[0] == "set")
    {
    	if (inputWords.size() == 4)
    	{
    		int id = stod(inputWords[1]);
    		string subject = inputWords[2];
    		double mark = stod(inputWords[3]);
    		
    		for (int i=0; i<students.size(); i++)
    		{
    			if (students[i].id == id)
    			{
    				students[i].marks[subject] = mark;
				}
			}
		}
	}
    else if (inputWords[0] == "clr")
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
                	students[i].marks[subject] = 0;
                }
            }
        }
    }
    else if (inputWords[0] == "back")
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

void searchStudents(vector<Student> &students, vector<string> &subjects, vector<Student> &search) // finish!!!
{	
	string input;
    vector<string> inputWords;
    
    printSearchStudentsGuide();
    
    cout << "\n\n> ";
    getline(cin, input);
    
    inputWords = convertVecToLower("all", splitToWords(input));
    
    if (inputWords[0] == "search")
	{
	    if (inputWords.size() == 2)
	    {
	    	search.clear();
	    	string fn, ln;
	    	
	    	for (int i=0; i<students.size(); i++)
	    	{
	    		fn = convertStrToLower(students[i].firstName);
				ln = convertStrToLower(students[i].lastName);
				
	    		if (fn == inputWords[1] || ln == inputWords[1])
	    		{
	    			search.push_back(students[i]);
				}
			}
		}
	
		else if (inputWords.size() == 3)
		{
			search.clear();
			string fn, ln;
			
			for (int i=0; i<students.size(); i++)
			{
				fn = convertStrToLower(students[i].firstName);
				ln = convertStrToLower(students[i].lastName);
				
				if (fn == inputWords[1] && ln == inputWords[2])
				{
					search.push_back(students[i]);
				}
			}
		}
	}
	
	else if (inputWords[0] == "back")
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

void showStudentsInOrder (vector<Student> &students, vector<string> subjects, vector<Student> &regStudents) // finish!!!
{
	printStudents(regStudents, subjects);
	printShowStudentsInOrderGuide();
	
	string input;
    vector<string> inputWords;
	
    cout << "\n\n> ";
    getline(cin, input);

    inputWords = convertVecToLower("all", splitToWords(input));
    subjects = convertVecToLower("all", subjects);
    
    if (inputWords[0] == "sort" && inputWords.size() == 2)
    {
    	regStudents = students;
    	
    	if (inputWords[1] == "avg")
    	{
    		averageMark(regStudents, subjects);
    		sort(regStudents.begin(), regStudents.end(), [](const Student &i1, const Student &i2) { return i1.avgMark > i2.avgMark; });
		}
		else
		{
			for (auto i: regStudents)
			{
				i.sortSubject = i.marks[inputWords[1]];
			}
			sort(regStudents.begin(), regStudents.end(), [](const Student &i1, const Student &i2) { return i1.sortSubject > i2.sortSubject; });
		}
	}
	
	else if (inputWords[0] == "back")
	{
		ended = true;
		
		system("CLS");
	}
	
	else if (input != "")
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

        cout << "[1] Student Management\n[2] Subject Management\n[3] Search\n[4] Show students in order\n[5] Exit The Program\n\n";
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
    		
    		vector<Student> search;
    		
        	while (ended != true)
        	{
        		searchStudents(students, subjects, search);
			}
		}
		
		else if (input == "4")
		{
			system("CLS");
			
			vector<Student> regStudents;
			
			while (ended != true)
			{
				showStudentsInOrder(students, subjects, regStudents);
			}
		}
		
        else if (input == "5")
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
