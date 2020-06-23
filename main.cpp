#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<fstream>
#include<string.h>
using namespace std;
class Book
{
public:
    int bookid;
    char bookname[100];
    char author[100];
    int price;
    int status;
    void acceptbook()
    {
        cout<<"Enter book id :";
        cin>>bookid;
        fflush(stdin);
        cout<<"Enter book name :";
        gets(bookname) ;
        cout<<"Enter author name :";
        gets(author);
        cout<<"Enter book price :";
        cin>>price;
    }
    void showbook()
    {
        cout<<"Book Id      "<<bookid<<endl;
        cout<<"Book Name    "<<bookname<<endl;
        cout<<"Author Name  "<<author<<endl;
        cout<<"Price        "<<price<<endl;
        if(status ==0)
        {
            cout<<"Status      "<<"Not Issued "<<endl;
        }
        else
        {
            cout<<"Issued To   "<<"member id("<<status <<")"<<endl;
        }
    }
} bookobj;


class Member
{
public:
    int mid;
    char mname[100];
    char mobileno[10];
    int age;
    void acceptmember()
    {
        cout<<"Enter Member ID : ";
        cin>>mid;
        cout<<"Enter Member name : ";
        cin>>mname;
        cout<<"Enter Member's Mobile : ";
        cin>>mobileno;
        cout<<"Enter Member's Age : ";
        cin>>age;
    }
    void viewmember()
    {
        cout<<endl<<"*******************";
        cout<<endl<<"Member ID: "<<mid;
        cout<<endl<<"Member's Name: "<<mname;
        cout<<endl<<"Member's Age: "<<age;
        cout<<endl<<"Member's Mobile: "<<mobileno;
        cout<<endl<<"*******************";
    }

} memberobj;

//function to store book info into a file...
void addbook()
{
    bookobj.acceptbook();
    fstream wr;
    wr.open("d:\\librarydata\\books.txt",ios::app);
    wr.write((char*)&bookobj,sizeof(bookobj));
    cout<<endl<<"Book Added Successfully"<<endl;

}
//view all books
void viewbooks()
{
    fstream rd;
    rd.open("d:\\librarydata\\books.txt",ios::in);
    if(rd)
    {
        int n;
        rd.seekg(0,ios::end);
        int pos = rd.tellg();
        n = pos/ sizeof(bookobj);
        rd.seekg(0,ios::beg);
        for(int i=1; i<=n; i++)
        {
            rd.read((char *)&bookobj,sizeof(bookobj));
            bookobj.showbook();
            cout<<"--------------------------------------"<<endl;
        }
        rd.close();
    }
    else
    {
        cout<<"File not found !!"<<endl;
    }
}
//search a book
void searchbook()
{
    fstream rd;
    rd.open("d:\\librarydata\\books.txt",ios::in);
    if(rd)
    {
        int n;
        int flag = 0;
        rd.seekg(0,ios::end);
        int pos = rd.tellg();
        n = pos/ sizeof(bookobj);
        rd.seekg(0,ios::beg);
        int bid;
        cout<<"Enter bookid to search ";
        cin>>bid;
        for(int i=1; i<=n; i++)
        {
            rd.read((char *)&bookobj,sizeof(bookobj));
            if(bookobj.bookid == bid)
            {
                cout<<"---------------------------"<<endl;
                bookobj.showbook();
                cout<<"---------------------------"<<endl;
                flag = 1;
                break;
            }

        }
        if(flag ==0)
        {
            cout<<"Book not found "<<endl;
        }
        rd.close();
    }
    else
    {
        cout<<"File not found !!"<<endl;
    }
}
//delete a book
void deletebook()
{
    fstream rd,wr;
    rd.open("d:\\librarydata\\books.txt",ios::in);
    wr.open("d:\\librarydata\\temp.txt",ios::out);
    if(rd)
    {
        int n;
        int flag =0;
        rd.seekg(0,ios::end);
        int pos = rd.tellg();
        n = pos /sizeof(bookobj);
        rd.seekg(0,ios::beg);
        int bid;
        cout<<"Enter bookid to delete ";
        cin>>bid;
        for(int i=1; i<=n; i++)
        {
            rd.read((char *)&bookobj,sizeof(bookobj));
            if(bookobj.bookid == bid)
            {
                flag = 1;
            }
            else
            {
                wr.write((char *)&bookobj,sizeof(bookobj));
            }
        }
        if(flag==0)
        {
            cout<<"Book not found "<<endl;
        }
        else
        {
            cout<<"Book Deleted Successfully!!!";
        }
        wr.close();
        rd.close();
        remove("d:\\librarydata\\books.txt");
        rename("d:\\librarydata\\temp.txt","d:\\librarydata\\books.txt");
    }
    else
    {
        cout<<"File not found "<<endl;
    }
}

void updatebook()
{
    fstream rd,wr;
    rd.open("d:\\librarydata\\books.txt",ios::in);
    wr.open("d:\\librarydata\\temp.txt",ios::out);
    if(rd)
    {
        int n;
        int flag =0;
        rd.seekg(0,ios::end);
        int pos = rd.tellg();
        n = pos /sizeof(bookobj);
        rd.seekg(0,ios::beg);
        int bid;
        cout<<"Enter bookid to edit ";
        cin>>bid;
        for(int i=1; i<=n; i++)
        {
            rd.read((char *)&bookobj,sizeof(bookobj));
            if(bookobj.bookid == bid)
            {
                bookobj.acceptbook();
                wr.write((char *)&bookobj,sizeof(bookobj));
                flag = 1;
            }
            else
            {
                wr.write((char *)&bookobj,sizeof(bookobj));
            }
        }
        if(flag==0)
        {
            cout<<"Book not found "<<endl;
        }
        else
        {
            cout<<"Book Updated Successfully!!!";
        }
        wr.close();
        rd.close();
        remove("d:\\librarydata\\books.txt");
        rename("d:\\librarydata\\temp.txt","d:\\librarydata\\books.txt");
    }
    else
    {
        cout<<"File not found "<<endl;
    }
}

void addmember()
{
    memberobj.acceptmember();
    fstream wr;
    wr.open("d:\\librarydata\\members.txt",ios::app);
    wr.write((char*)&memberobj,sizeof(memberobj));
    cout<<endl<<"Member Added Successfully"<<endl;
}
void viewmembers()
{
    fstream rd;
    rd.open("d:\\librarydata\\members.txt",ios::in);
    rd.seekg(0,ios::end);
    int e=rd.tellg()/sizeof(memberobj);
    rd.seekg(0,ios::beg);
    for (int i=1; i<=e; i++)
    {
        rd.read((char*)&memberobj,sizeof(memberobj));
        memberobj.viewmember();
    }
    rd.close();
}
void searchmember()
{
    fstream rd;
    int flag =0;
    rd.open("d:\\librarydata\\members.txt",ios::in);
    rd.seekg(0,ios::end);
    int f=rd.tellg()/sizeof(memberobj);
    rd.seekg(0,ios::beg);
    char membernm[100];
    cout<<endl<<"Enter Member's Name : ";
    cin>>membernm;
    for (int i=1; i<=f; i++)
    {
        rd.read((char*)&memberobj,sizeof(memberobj));
        if(strcmpi(memberobj.mname,membernm)==0)
        {
            memberobj.viewmember();
            flag = 1;
        }
    }
    if(flag ==0)
    {
        cout<<"Member not found "<<endl;
    }
    rd.close();
}
void editmember()
{
    fstream rd,wr;
    rd.open("d:\\librarydata\\members.txt",ios::in);
    wr.open("d:\\librarydata\\temp.txt",ios::out);
    rd.seekg(0,ios::end);
    int c=rd.tellg()/sizeof(memberobj);
    rd.seekg(0,ios::beg);
    char memname[100];
    cout<<endl<<"Enter member name ";
    cin>>memname;
    for (int i=1; i<=c; i++)
    {
        rd.read((char*)&memberobj,sizeof(memberobj));
        if(strcmpi(memberobj.mname,memname)==0)
        {
            memberobj.acceptmember();
        }
        wr.write((char*)&memberobj,sizeof(memberobj));
    }
    cout<<endl<<"Member edited successfully";
    rd.close();
    wr.close();
    remove("d:\\librarydata\\members.txt");
    rename("d:\\librarydata\\temp.txt","d:\\librarydata\\members.txt");
}
void removemember()
{
    int flag =0;
    fstream rd,wr;
    rd.open("d:\\librarydata\\members.txt",ios::in);
    wr.open("d:\\librarydata\\temp.txt",ios::out);
    rd.seekg(0,ios::end);
    int c=rd.tellg()/sizeof(memberobj);
    rd.seekg(0,ios::beg);
    char memname[100];
    cout<<endl<<"Enter member name ";
    cin>>memname;
    for (int i=1; i<=c; i++)
    {
        rd.read((char*)&memberobj,sizeof(memberobj));
        if(strcmpi(memberobj.mname,memname)==0)
        {
            cout<<endl<<"Member removed Successfully!";
            flag = 1;
            break;
        }
        else
        {
            wr.write((char*)&memberobj,sizeof(memberobj));
        }
    }
    if(flag ==0)
    {
        cout<<"Member not found !!"<<endl;
    }
    rd.close();
    wr.close();
    remove("d:\\librarydata\\members.txt");
    rename("d:\\librarydata\\temp.txt","d:\\librarydata\\members.txt");
}

///issue book ///
void issuebook()
{
    int flag =0;
    fstream rd;
    rd.open("d:\\librarydata\\books.txt",ios::in);
    int bid;
    if(rd)
    {
        cout<<"Enter bookid to issue : ";
        cin>>bid;
        rd.seekg(0,ios::end);
        int n = rd.tellg()/sizeof(bookobj);
        rd.seekg(0,ios::beg);
        for(int i=1; i<=n; i++)
        {
            rd.read((char*)&bookobj,sizeof(bookobj));
            if(bookobj.bookid == bid)
            {
                cout<<"-------------------------"<<endl;
                bookobj.showbook();
                cout<<"-------------------------"<<endl;
                flag =1;
                break;
            }
        }
        if(flag ==0)
        {
            cout<<"Invalid book id "<<endl;
            return;
        }
        else if(bookobj.status != 0)
        {
            cout<<"Book is already issued to member id (" << bookobj.status <<")"<<endl;
            return;
        }

        int mid;

        cout<<"Enter member id ";
        cin>>mid;
        int flagm =0;
        fstream rdm;
        rdm.open("d:\\librarydata\\members.txt",ios::in);
        if(rdm)
        {

            rdm.seekg(0,ios::end);
            int nm = rdm.tellg()/sizeof(memberobj);
            rdm.seekg(0,ios::beg);
            for(int j=1; j<=nm; j++)
            {
                rdm.read((char*)&memberobj,sizeof(memberobj));
                if(memberobj.mid == mid)
                {
                    memberobj.viewmember();
                    flagm =1;
                    break;
                }
            }
            if(flagm ==0)
            {
                cout<<"Invalid member id " <<endl;
                return;
            }
            int option;
            cout<<"Enter 1 to issue book : "<<endl;
            cout<<"Enter 0 to main menu : "<<endl;
            cin>>option;
            if(option==1)
            {
                rd.seekg(0,ios::beg);
                fstream wr;
                wr.open("d:\\librarydata\\temp.txt",ios::out);
                for(int k=1; k<=n; k++)
                {
                    rd.read((char *)&bookobj,sizeof(bookobj));
                    if(bookobj.bookid == bid)
                    {
                        bookobj.status = mid;
                        cout<<"Book issued successfully!!!"<<endl;
                    }
                    wr.write((char*)&bookobj,sizeof(bookobj));
                }
                rd.close();
                wr.close();
                rdm.close();
                remove("d:\\librarydata\\books.txt");
                rename("d:\\librarydata\\temp.txt","d:\\librarydata\\books.txt");

                return;
            }
            else
            {
                return;
            }
        }
        else
        {
            cout<<"File Not Found !!!"<<endl;
        }
    }
    else
    {
        cout<<"File not found !!!"<<endl;
    }
}

///return book ///
void returnbook()
{
    fstream rd,wr;
    rd.open("d:\\librarydata\\books.txt",ios::in);
    wr.open("d:\\librarydata\\temp.txt",ios::out);
    if(rd)
    {
        int flag =0;
        int bid;
        cout<<"Enter book id to return : ";
        cin>>bid;
        rd.seekg(0,ios::end);
        int n = rd.tellg()/sizeof(bookobj);
        rd.seekg(0,ios::beg);
        for(int i=1; i<=n; i++)
        {
            rd.read((char*)&bookobj,sizeof(bookobj));
            if(bookobj.bookid == bid && bookobj.status != 0)
            {
                flag =1;
                cout<<"Book issued to member id ("<< bookobj.status <<")"<<endl;
            }

        }
        if(flag ==0)
        {
            cout<<"Invalid book id or book is not issued ";
        }
        else
        {
            int choice;
            cout<<"Enter 1 to return book : "<<endl;
            cout<<"Enter 0 for main menu : ";
            cin >> choice;
            rd.seekg(0,ios::beg);
            for(int j=1; j<=n; j++)
            {
                rd.read((char *)&bookobj,sizeof(bookobj));
                if(choice==1 && bookobj.bookid ==  bid)
                {
                    bookobj.status = 0;
                    cout<<"Book returned successfully!!"<<endl;
                }
                wr.write((char *)&bookobj,sizeof(bookobj));
            }
        }
        rd.close();
        wr.close();
        remove("d:\\librarydata\\books.txt");
        rename("d:\\librarydata\\temp.txt","d:\\librarydata\\books.txt");

    }
    else
    {
        cout<<"File not found !!!"<<endl;
    }
}

int main()
{
    int choice;
    do
    {
        cout<<endl<<endl;
        cout<<"1.Add Book "<<endl;
        cout<<"2.View Books"<<endl;
        cout<<"3.Search Book"<<endl;
        cout<<"4.Edit Book"<<endl;
        cout<<"5.Delete Book"<<endl;
        cout<<"6.Add Member"<<endl;
        cout<<"7.View Members"<<endl;
        cout<<"8.Search Member"<<endl;
        cout<<"9.Edit Member"<<endl;
        cout<<"10.Delete Member"<<endl;
        cout<<"11.Issue Book"<<endl;
        cout<<"12.Return Book"<<endl;
        cout<<"13.Exit"<<endl;
        cout<<"Enter your choice : ";
        cin>>choice;
        switch(choice)
        {
        case 1:
            addbook();
            break;
        case 2:
            viewbooks();
            break;
        case 3:
            searchbook();
            break;
        case 4:
            updatebook();
            break;
        case 5:
            deletebook();
            break;
        case 6:
            addmember();
            break;
        case 7:
            viewmembers();
            break;
        case 8:
            searchmember();
            break;
        case 9:
            editmember();
            break;
        case 10:
            removemember();
            break;
        case 11:
            issuebook();
            break;
        case 12:
            returnbook();
            break;
        case 13:
            exit(0);
            break;
        }
    }
    while(1);


}
