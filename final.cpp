#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
using namespace std;

class Student
{
private:
    string rollNo;
    string name;
    float marks1, marks2, marks3;
    float total, average, percentage;
    string grade;
    string result;

public:

    // Set student basic information
    void setBasicData(string r, string n)
    {
        rollNo = r;
        name = n;
    }

    // Get and validate marks
    float getValidMarks(string message)
    {
        float marks;

        while (true)
        {
            cout << message;
            cin >> marks;

            if (cin.fail())
            {
                cout << "Invalid input! Please enter a number.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else if (marks < 0 || marks > 100)
            {
                cout << "Marks must be between 0 and 100.\n";
            }
            else
            {
                return marks;
            }
        }
    }

    // Get marks
    void getMarks()
    {
        marks1 = getValidMarks("Enter Marks in c++: ");
        marks2 = getValidMarks("Enter Marks in python: ");
        marks3 = getValidMarks("Enter Marks in DBMS: ");
    }

    // Calculate result
    void calculateResult()
    {
        total = marks1 + marks2 + marks3;
        average = total / 3.0;
        percentage = (total / 300.0) * 100;

        // If any subject is below 35, student fails
        if (marks1 < 35 || marks2 < 35 || marks3 < 35)
        {
            grade = "F";
            result = "FAIL";
        }
        else
        {
            result = "PASS";

            if (average >= 90)
                grade = "O";
            else if (average >= 80)
                grade = "A+";
            else if (average >= 70)
                grade = "A";
            else if (average >= 60)
                grade = "B";
            else
                grade = "C";
        }
    }

    // Display complete result
    void display()
    {
        cout << "\n================================================";
        cout << "\nRoll Number : " << rollNo;
        cout << "\nName        : " << name;

        cout << "\n------------------------------------------------";

        cout << "\nc++      : "
             << fixed << setprecision(0) << marks1;

        cout << "\npython   : "
             << fixed << setprecision(0) << marks2;

        cout << "\nDBMS     : "
             << fixed << setprecision(0) << marks3;

        cout << "\n------------------------------------------------";

        cout << "\nTotal Marks : "
             << fixed << setprecision(0)
             << total << " / 300";

        cout << "\nAverage     : "
             << fixed << setprecision(2)
             << average;

        cout << "\nPercentage  : "
             << fixed << setprecision(2)
             << percentage << "%";

        cout << "\nGrade       : " << grade;
        cout << "\nResult      : " << result;

        cout << "\n================================================\n";
    }

    // Display short failed-student details
    void displayFailedStudent()
    {
        cout << "\n-----------------------------------------------";
        cout << "\nRoll Number : " << rollNo;
        cout << "\nName        : " << name;
        cout << "\nAverage     : "
             << fixed << setprecision(2) << average;
        cout << "\nGrade       : " << grade;
        cout << "\nResult      : " << result;
        cout << "\n-----------------------------------------------";
    }

    // Get roll number
    string getRollNo()
    {
        return rollNo;
    }

    // Get average
    float getAverage()
    {
        return average;
    }

    // Check whether student failed
    bool isFailed()
    {
        return result == "FAIL";
    }
};


// Check duplicate roll number
bool rollNumberExists(Student students[], int count, string rollNo)
{
    for (int i = 0; i < count; i++)
    {
        if (students[i].getRollNo() == rollNo)
        {
            return true;
        }
    }

    return false;
}


int main()
{
    Student students[50];

    int count = 0;
    int choice;

    do
    {
        cout << "\n\n===============================================";
        cout << "\n              STUDENT RESULT SYSTEM";
        cout << "\n===============================================";
        cout << "\n1. Add Student";
        cout << "\n2. Display All Results";
        cout << "\n3. Search Student";
        cout << "\n4. Display Topper(s)";
        cout << "\n5. Display Failed Students";
        cout << "\n6. Exit";
        cout << "\n===============================================";

        cout << "\nEnter your choice: ";
        cin >> choice;

        // Validate menu input
        if (cin.fail())
        {
            cout << "\nInvalid input! Please enter a number from 1 to 6.";

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            continue;
        }


        switch (choice)
        {

            // =====================================
            // 1. ADD STUDENT
            // =====================================

            case 1:
            {
                if (count >= 50)
                {
                    cout << "\nMaximum student limit reached!";
                    break;
                }

                string rollNo;
                string name;

                cout << "\nEnter Roll Number: ";
                cin >> rollNo;

                // Check duplicate roll number
                if (rollNumberExists(students, count, rollNo))
                {
                    cout << "\nError: Roll Number already exists!";
                    break;
                }

                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Enter Student Name: ";
                getline(cin, name);

                // Store basic details
                students[count].setBasicData(rollNo, name);

                // Get marks
                students[count].getMarks();

                // Calculate result
                students[count].calculateResult();

                count++;

                cout << "\nStudent record added successfully!";

                break;
            }


            // =====================================
            // 2. DISPLAY ALL RESULTS
            // =====================================

            case 2:
            {
                if (count == 0)
                {
                    cout << "\nNo student records available!";
                }
                else
                {
                    cout << "\n\n=========== ALL STUDENT RESULTS ===========";

                    for (int i = 0; i < count; i++)
                    {
                        students[i].display();
                    }
                }

                break;
            }


            // =====================================
            // 3. SEARCH STUDENT
            // =====================================

            case 3:
            {
                if (count == 0)
                {
                    cout << "\nNo student records available!";
                    break;
                }

                string searchRoll;

                cout << "\nEnter Roll Number to Search: ";
                cin >> searchRoll;

                bool found = false;

                for (int i = 0; i < count; i++)
                {
                    if (students[i].getRollNo() == searchRoll)
                    {
                        students[i].display();

                        found = true;

                        break;
                    }
                }

                if (!found)
                {
                    cout << "\nStudent not found!";
                }

                break;
            }


            // =====================================
            // 4. DISPLAY TOPPER(S)
            // =====================================

            case 4:
            {
                if (count == 0)
                {
                    cout << "\nNo student records available!";
                    break;
                }

                // Find highest average
                float highestAverage = students[0].getAverage();

                for (int i = 1; i < count; i++)
                {
                    if (students[i].getAverage() > highestAverage)
                    {
                        highestAverage = students[i].getAverage();
                    }
                }

                cout << "\n\n============== TOPPER(S) ==============";

                cout << "\nHighest Average : "
                     << fixed << setprecision(2)
                     << highestAverage;

                // Display all students with highest average
                for (int i = 0; i < count; i++)
                {
                    if (students[i].getAverage() == highestAverage)
                    {
                        students[i].display();
                    }
                }

                break;
            }


            // =====================================
            // 5. DISPLAY FAILED STUDENTS
            // =====================================

            case 5:
            {
                if (count == 0)
                {
                    cout << "\nNo student records available!";
                    break;
                }

                int failedCount = 0;

                cout << "\n\n============== FAILED STUDENTS ==============";

                for (int i = 0; i < count; i++)
                {
                    if (students[i].isFailed())
                    {
                        students[i].displayFailedStudent();

                        failedCount++;
                    }
                }

                if (failedCount == 0)
                {
                    cout << "\n\nNo students have failed.";
                }
                else
                {
                    cout << "\n\nTotal Failed Students : "
                         << failedCount;
                }

                break;
            }


            // =====================================
            // 6. EXIT
            // =====================================

            case 6:
            {
                cout << "\nThank you for using Student Result System!";

                break;
            }


            // =====================================
            // INVALID CHOICE
            // =====================================

            default:
            {
                cout << "\nInvalid choice! Please select 1 to 6.";

                break;
            }
        }

    } while (choice != 6);

    return 0;
}
