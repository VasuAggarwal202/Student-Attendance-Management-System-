#include<iostream>
#include<fstream>
#include<string.h>
#include<iomanip>
using namespace std;

class student
{
    public:
    int rollno;
    char name[50];
    char fname[50];
    char degree[50];
    int semester;
    public:
    friend void remove_student();
    friend void edit_student();
    void accept()
    {
        cout<<endl<<"Enter Roll Number ";
        cin>>rollno;
        cout<<endl<<"Enter student Name ";
        cin>>name;
        cout<<endl<<"Enter father Name ";
        cin>>fname;
        cout<<endl<<"Enter Degree ";
        cin>>degree;
        cout<<endl<<"Enter Semester ";
        cin>>semester;
    }
    void display()
    {
        cout<<endl<<setw(5)<<rollno;
        cout<<setw(20)<<name;
        cout<<setw(20)<<fname;
        cout<<setw(15)<<degree;
        cout<<setw(10)<<semester;
    }
};
student s1;

void add_student()
{
    s1.accept();
    fstream wr;
    wr.open("mystudents.txt",ios::app);
    wr.write((char *)&s1,sizeof(s1));
    wr.close();
    cout<<endl<<"Student Data Written successfully";
}

void edit_student()
{
    fstream rd;
    rd.open("mystudents.txt",ios::in);
    rd.seekg(0,ios::end);
    int size=rd.tellg();
    int number_student=size/sizeof(s1);
    rd.seekg(0,ios::beg);
    int rno;
    fstream wr;
    wr.open("temp.txt",ios::out);
    cout<<endl<<"Enter Roll Number to be searched & edited";
    cin>>rno;
    for(int i=1;i<=number_student;i++)
    {
        rd.read((char *)&s1,sizeof(s1));
        if(s1.rollno==rno)
        {
            s1.accept();
            wr.write((char *)&s1,sizeof(s1));
        }
        else
        {
            wr.write((char *)&s1,sizeof(s1));
        }
    }
    wr.close();
    rd.close();
    remove("mystudents.txt");
    rename("temp.txt","mystudents.txt");
}

void remove_student()
{
    fstream rd;
    rd.open("mystudents.txt",ios::in);
    rd.seekg(0,ios::end);
    int size=rd.tellg();
    int number_student=size/sizeof(s1);
    rd.seekg(0,ios::beg);
    int rno;
    fstream wr;
    wr.open("temp.txt",ios::out);
    cout<<endl<<"Enter Roll Number to be searched & Removed";
    cin>>rno;
    for(int i=1;i<=number_student;i++)
    {
        rd.read((char *)&s1,sizeof(s1));
        if(s1.rollno==rno)
        {
            cout<<endl<<"Removed";
        }
        else
        {
            wr.write((char *)&s1,sizeof(s1));
        }
    }
    wr.close();
    rd.close();
    remove("mystudents.txt");
    rename("temp.txt","mystudents.txt");
}

void show_student()
{
    fstream rd;
    rd.open("mystudents.txt",ios::in);
    if(rd==NULL)
    {
        cout<<endl<<"Cannot open File";
    }
    else
    {
        rd.seekg(0,ios::end);
        int size=rd.tellg();
        int number_student=size/sizeof(s1);
        rd.seekg(0,ios::beg);
        
        cout<<endl<<setw(5)<<"RollNo";
        cout<<setw(20)<<"Name";
        cout<<setw(20)<<"Father Name";
        cout<<setw(15)<<"Degree";
        cout<<setw(10)<<"Semester";
        cout<<endl<<"-----------------------------------------------------------------------------";
        
        for(int i=1;i<=number_student;i++)
        {
            rd.read((char *)&s1,sizeof(s1));
            s1.display();   
        }

        cout<<endl<<"------------------------------------------------------------------------------";
    }
}

class mark_attendance
{
    int dd,mm,yy;
    int rollno;
    friend void view_attendance_date();
    friend void view_attendancerollno();
    friend void view_attendancedegrew();
    public:
    void init(int d,int m,int y,int r)
    {
        dd=d;
        mm=m;
        yy=y;
        rollno=r;
    }
    void display()
    {
        cout<<endl<<dd<<"-"<<mm<<"-"<<yy<<setw(10)<<rollno;
        fstream rd;
        rd.open("mystudents.txt",ios::in);
        rd.seekg(0,ios::end);
        int size=rd.tellg()/sizeof(s1);
        rd.seekg(0,ios::beg);
        for(int i=1;i<=size;i++)
        {
            rd.read((char *)&s1,sizeof(s1));
            if(rollno==s1.rollno)
            {
                cout<<setw(15)<<s1.name<<" "<<s1.fname<<" "<<s1.degree<<" "<<s1.semester;
            }
        }
    }

    void display(char *p,int s)
    {
        cout<<endl<<dd<<"-"<<mm<<"-"<<yy<<setw(10)<<rollno;
        fstream rd;
        rd.open("mystudents.txt",ios::in);
        rd.seekg(0,ios::end);
        int size=rd.tellg()/sizeof(s1);
        rd.seekg(0,ios::beg);
        for(int i=1;i<=size;i++)
        {
            rd.read((char *)&s1,sizeof(s1));
            if(strcmp(s1.degree,p)==0 && s1.semester==s)
            {
                cout<<setw(15)<<s1.rollno<<" "<<dd<<"-"<<mm<<"-"<<yy<<" "<<s1.name<<" "<<s1.fname<<" "<<s1.degree<<" "<<s1.semester;
            }
        }
    }
};
mark_attendance m1;

class attendance
{
    int dd,mm,yy;
    int arr[50];
    public:
    void accept()
    {   int p;
        cout<<endl<<"Enter date in DD MM YY";
        cin>>dd>>mm>>yy;
        cout<<endl<<"Enter Roll Numbers of Present Student Followed by -1";
        int count=0;
        for(int i=0;i<=49;i++)
        {
            cin>>p;
            if(p==-1)
            {
                break;
            }
            arr[i]=p;
            count++;
        }
        fstream wr;
        wr.open("attendance_data.txt",ios::app);
        for(int j=0;j<=count-1;j++)
        {
            m1.init(dd,mm,yy,arr[j]);
            wr.write((char *)&m1,sizeof(m1));
        }
        wr.close();
    }
};

void view_attendance()
{
    fstream rd;
    rd.open("attendance_data.txt",ios::in);
    rd.seekg(0,ios::end);
    int size=rd.tellg()/sizeof(m1);
    cout<<endl<<"Number of Objects are "<<size<<endl;
    rd.seekg(0,ios::beg);
    cout<<endl<<setw(10)<<"Date";
    cout<<setw(10)<<"rollno";
    for(int i=1;i<=size;i++)
    {
        rd.read((char *)&m1,sizeof(m1));
        m1.display();
    }
}

void view_attendance_date()
{
    int d,m,y;
    cout<<endl<<"Enter Date,Month and Year";
    cin>>d>>m>>y;
    fstream rd;
    rd.open("attendance_data.txt",ios::in);
    rd.seekg(0,ios::end);
    int size=rd.tellg()/sizeof(m1);
    cout<<endl<<"Number of Objects are "<<size<<endl;
    rd.seekg(0,ios::beg);
    cout<<endl<<setw(10)<<"Date";
    cout<<setw(10)<<"rollno";
    for(int i=1;i<=size;i++)
    {
        rd.read((char *)&m1,sizeof(m1));
        if(m1.dd==d && m1.mm==m && m1.yy==y)
        {
            m1.display();
        }
    }
}

void view_attendancerollno()
{
    int r;
    cout<<endl<<"Enter Roll No. ";
    cin>>r;
    fstream rd;
    rd.open("attendance_data.txt",ios::in);
    rd.seekg(0,ios::end);
    int size=rd.tellg()/sizeof(m1);
    cout<<endl<<"Number of Objects are "<<size<<endl;
    rd.seekg(0,ios::beg);
    cout<<endl<<setw(10)<<"Date";
    cout<<setw(10)<<"rollno";
    for(int i=1;i<=size;i++)
    {
        rd.read((char *)&m1,sizeof(m1));
        if(m1.rollno==r)
        {
            m1.display();
        }
    }
}

void view_attendancedegree()
{
    char degree[50];
    int semester;
    cout<<endl<<"Enter Degree name ";
    cin>>degree;
    cout<<endl<<"Enter semester";
    cin>>semester;
    fstream rd;
    rd.open("attendance_data.txt",ios::in);
    rd.seekg(0,ios::end);
    int size=rd.tellg()/sizeof(m1);
    cout<<endl<<"Number of Objects are "<<size<<endl;
    rd.seekg(0,ios::beg);
    cout<<endl<<setw(10)<<"Date";
    cout<<setw(10)<<"rollno";
    for(int i=1;i<=size;i++)
    {
        rd.read((char *)&m1,sizeof(m1));
        m1.display(degree,semester);
    }
}

int main()
{
    int e=0;
    while(e==0)
    {
        cout<<endl<<"******************** Welcome To Attendance Management ************************";
        cout<<endl<<"\t\tPress 1 to Add New Student";
        cout<<endl<<"\t\tPress 2 to View All Students";
        cout<<endl<<"\t\tPress 3 to Remove Student";
        cout<<endl<<"\t\tPress 4 to Update Student";
        cout<<endl<<"\t\tPress 5 to Mark Bulk Attendance";
        cout<<endl<<"\t\tPress 6 to View Attendance";
        cout<<endl<<"\t\tPress 7 to View Attendance by date";
        cout<<endl<<"\t\tPress 8 to View Attendance by Roll no";
        cout<<endl<<"\t\tPress 9 to View Attendance by Degree and semester";
        cout<<endl<<"\t\tPress 10 to Exit";
        cout<<endl<<"*****************************************************************************";
        int choice;
        cin>>choice;
        if(choice==1)
        {
            add_student();
        }
        else if(choice==2)
        {
            show_student();
        }
        else if(choice==3)
        {
            remove_student();
        }
        else if(choice==4)
        {
            edit_student();
        }
        else if(choice==5)
        {
            attendance o1;
            o1.accept();
        }
        else if(choice==6)
        {
            view_attendance();
        }
        else if(choice==7)
        {
            view_attendance_date();
        }
        else if(choice==8)
        {
            view_attendancerollno();
        }
        else if(choice==9)
        {
            view_attendancedegree();
        }
        else
        {
            e=1;
        }
    }
} 