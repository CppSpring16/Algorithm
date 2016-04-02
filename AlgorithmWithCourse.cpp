/* Alexander Gonzalez
 * Course and Section Classes
 */
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class Section{
private:
    //Member Variables
    string sectionNum;
    int days[10];
    int periods[10];
    
public:
    //Constructor (only one that worked with our conditions)
    void set(string sectionNum, string day[], string period[]){
        this->sectionNum = sectionNum;
        string temp;
        for(int i = 0; i < 10; i++){
            switch(day[i][0]){
                case 'M': days[i] = 0; break;
                case 'T': days[i] = 1; break;
                case 'W': days[i] = 2; break;
                case 'R': days[i] = 3; break;
                case 'F': days[i] = 4; break;
                default: days[i] = -1; break;
            }
            periods[i] = atoi(period[i].c_str()) - 1;

        }
    }
    
    //Setter methods
    void setSectionNum(string sectionNum){
        this->sectionNum = sectionNum;
    }
    void setDays(string day[]){
        for(int i = 0; i < 10; i++){
            switch(day[i][0]){
                case 'M': days[i] = 0; break;
                case 'T': days[i] = 1; break;
                case 'W': days[i] = 2; break;
                case 'R': days[i] = 3; break;
                case 'F': days[i] = 4; break;
                default: days[i] = -1; break;
            }
        }
    }
    void setPeriods(string period[]){
        for(int i = 0; i < 10; i++){
            periods[i] = atoi(period[i].c_str()) - 1;
        }
    }
    //Getter methods
    string getSectionNum(){
        return this->sectionNum;
    }
    int getDays(int index){
        return this->days[index];
    }
    int getPeriods(int index){
        return this->periods[index];
    }
};

class Course{
private:
    //Member Variables
    string courseName;
    string courseNum;
    Section section[10];
    bool priority;
    int credits;
    
public:
    void set(string courseName, string courseNum, Section section[],
             bool priority, int credits){
        this->courseName = courseName;
        this->courseNum = courseNum;
        this->priority = priority;
        this->credits = credits;
        for(int i = 0; i < 10; i++){
            this->section[i] = section[i];
        }
    }
    
    //Setter methods for each variable
    void setCourseName(string courseName){
        this->courseName = courseName;
    }
    void setCourseNum(string courseNum){
        this->courseNum = courseNum;
    }
    void setSection(Section section[]){
        for(int i = 0; i <= 10; i++){
            this->section[i] = section[i];
        }
    }
    void setPriority(bool priority){
        this->priority = priority;
    }
    void setCredits(int credits){
        this->credits = credits;
    }
    
    //Getter methods for each variable
    string getCourseName(){
        return this->courseName;
    }
    string getCourseNum(){
        return this->courseNum;
    }
    Section getSection(int index){
        return this->section[index];
    }
    bool getPriority(){
        return this->priority;
    }
    int getCredits(){
        return this->credits;
    }
};

//Convert user input for time availability to two arrays of days
//and corresponding periods
void processTimeAvbl(string timeAvbl, string *days, string *periods){
    //Delete white spaces and punctuation
    for(int n = 0; n < timeAvbl.length(); ++n){
        if(ispunct(timeAvbl[n]) || isspace(timeAvbl[n]))
            timeAvbl.erase(n--, 1);
    }
    //Variables
    int index = 0;
    string subString, subString2;
    //Go through each character of string
    for(int i = 0; i < timeAvbl.length(); i++){
        subString = timeAvbl[i];
        //If it's a letter
        if(!isdigit(timeAvbl[i])){
            days[index] = subString; //Add day to array
        }
        //If it's a number
        else if(isdigit(timeAvbl[i])){
            subString = timeAvbl[i];
            //Check if two consecutive numbers
            if(i != 0)
                subString2 = timeAvbl[i - 1];
            //Add period to array
            if(isdigit(timeAvbl[i - 1])){
                periods[index] = subString2 + subString;
            }
            else{
                periods[index] = subString;
            }
            index++; //Go to next column of both arrays
        }
    }
}

//Convert priority values to boolean
bool priorityCheck(string priority){
    if(priority == "yes")
        return true;
    else
        return false;
}

//Get course info and store it in array of Course objects
//All there is to do in main is:
//    Course course[10];
//    getCourseInfo(course); //Calling this function and passing array of Courses
//    then we can get info from object by:
//    course[0].getCourseName();
//See Main here for more details
void getCourseInfo(Course course[]){
    //Variables
    string courseName, courseNum, sect, priority, time;
    int numberOfSections, credits;
    bool prio;
    Section section[10];
    string sections[10];
    string days[10];
    string periods[10];
    string timeAvbl[10];
    
    //Getting input from user
    cout << "How many courses would you like to add?" << endl;
    int numberOfCourses;
    cin >> numberOfCourses;
    for(int i = 0; i < numberOfCourses; i++){
        cout << "Enter course name: ";
        cin >> courseName;
        cout << "\nEnter course number: ";
        cin >> courseNum;
        cout << "\nEnter \"yes\" if this class is a top priority or \"no\" otherwise: ";
        cin >> priority;
        prio = priorityCheck(priority);
        cout << "\nEnter number of credits: ";
        cin >> credits;
        cout << "\nHow many sections of " << courseName << " would you like to add? ";
        cin >> numberOfSections;
        for(int j = 0; j < numberOfSections; j++){
            cout << "\nEnter section: ";
            cin >> sect;
            sections[j] = sect;
            cout << "\nEnter class availability in the following form: "
            << "\nM,T,W,R or F for Monday,Tuesday,...,Friday respectively"
            << "\nfollowed by the period number. Separate each period with commas "
            << "\nin the following manner T6,R6,R7: ";
            cin >> time;
            timeAvbl[j] = time;
            processTimeAvbl(time, days, periods); //Convert time availability
            //Creating object for section and adding it to array of Sections
            section[j].set(sect, days, periods);
        }
        //Creating object for course and adding it to array of Courses
        course[i].set(courseName, courseNum, section, prio, credits);
    }
    

}

class Schedule{
private:
    string classSched[14][5];
    bool isOccupied[14][5];
    string incl[5];
    string notIncl[5];
    int numCredits = 0;
    int numCourses = 0;
    int attemptCourses = 0;
    
public:
    Schedule(){
        for (int i = 0; i<14; i++){
            for (int j=0; j<5; j++){
                classSched[i][j] = "";
                isOccupied[i][j] = false;
                incl[j] = "";
                notIncl[j] = "";
            }
        }
    }
    void addClass(Course course, int section){
        //check if all meet times fit in schedule, if not add to notIncl, if they do, add to classSched
        attemptCourses++;
        //first go through and see if there is a conflict with the meeting times
        //if so add to the notIncl list and return
        for (int i = 0; i < 7; i++){
            if (course.getSection(section).getPeriods(i) == -1){    //array will have -1 as values for any unneeded spots
                if (i == 0){
                    notIncl[attemptCourses-numCourses-1] = course.getCourseName();
                    return;
                }
                break;
            }
            if (isOccupied[course.getSection(section).getPeriods(i)][course.getSection(section).getDays(i)]){
                //cout << "Conflict! Cannot add class."<< endl; //for testing purposes, will remove
                notIncl[attemptCourses-numCourses-1] = course.getCourseName();
                return;
            }
        }
        //This will go through and update the schedule with the new course
        int i = 0;
        while(course.getSection(section).getPeriods(i)!=-1){
            classSched[course.getSection(section).getPeriods(i)][course.getSection(section).getDays(i)] = course.getCourseName();
            isOccupied[course.getSection(section).getPeriods(i)][course.getSection(section).getDays(i)] = true;
            i++;
        }
        incl[numCourses++] = course.getCourseName();
        numCredits += course.getCredits();
        
    }
    
    void displaySched(){
        string days [] = {"Monday","Tuesday","Wednesday","Thursday","Friday"};
        cout << "\n\n   ";
        for (int i = 0; i<5; i++){
            cout << setw(12) << days[i];
        }
        //cout << "\n\t" << setw(10) << "Monday" << setw(15) << "Tuesday" << setw(10) <<  "Wednesday" << setw(15)<< "Thursday" << setw(15)<< "Friday";
        cout << "\n\t_____________________________________________________________"<<endl;
        for (int i = 0; i<14; i++){
            cout << (i+1)<<"\t|";
            for (int j=0; j<5; j++){
                cout << setw(10) << classSched[i][j] << " |";   //need to format
            }
            cout << "\n\t_____________________________________________________________"<<endl;
        }
        cout << "\nTotal credits: " << numCredits;
        cout << "\n\nCourses included: ";
        for (int i = 0; i<5; i++)
            cout << incl[i] << " ";
        cout << "\n\nCourses not included: ";
        for (int i = 0; i<5; i++)
            cout << notIncl[i] << " ";
    }
    
};

int main(){
    Course course[10];
    getCourseInfo(course);
    Schedule schedArray[16];
    int count = 0;
    
    for (int i=0; i<2; i++)
        for (int j=0; j<2; j++)
            for (int k=0; k<2; k++)
                for (int l=0; l<2; l++){
                    schedArray[count].addClass(course[0],i);
                    schedArray[count].addClass(course[1],j);
                    schedArray[count].addClass(course[2],k);
                    schedArray[count].addClass(course[3],l);
                    schedArray[count].displaySched();
                    count++;
                }
    return 0;
}


