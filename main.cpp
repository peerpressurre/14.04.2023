#include <iostream>
#include <fstream>
#include <string>
using namespace std;
using std::cout;
using std::istream;
using std::ostream;
using std::fstream;
using std::ios_base;
#define next_line { cout << endl; }

struct File
{
private:
    string path;
    fstream file;
    ios_base::open_mode open_mode;
public:
    //Setters & Getters
    void setPath(string path)
    {
        this->path = path;
    }

    void setOpenMode(ios_base::open_mode open_mode)
    {
        this->open_mode = open_mode;
    }

    ios_base::open_mode getOpenMode()
    {
        return open_mode;
    }

    string getPath()
    {
        return path;
    }


    //Constructors & Destructor 
    File()
    {
        setPath("text.txt");
        setOpenMode(ios::out);
    }
    File(string path) : File()
    {
        setPath(path);
    }
    File(string path, ios_base::open_mode open_mode) : File(path)
    {
        setOpenMode(open_mode);
    }
    ~File()
    {
        path.clear();
        file.close();
        open_mode = 0;
    }
    //Actions 
    bool Write(string text, bool append = false) {
        if (open_mode != ios::out && append == false)
        {
            open_mode = ios::out;
        }
        else if (open_mode != ios::app && append == true)
        {
            open_mode = ios::app;
        }
        file.open(path, open_mode);
        if (file.is_open())
        {
            file << text << endl;
            this->CloseFile();
            return true;
        }
        else {
            return false;
        }
    }
    bool Load(string& text) {
        string buf;
        if (open_mode != ios::in)
        {
            open_mode = ios::in;
        }
        file.open(path, open_mode);
        if (file.is_open())
        {
            while (getline(file, buf))
            {
                text += buf;
                text += "\n";
            }
            this->CloseFile();
            return true;
        }
        else {
            return false;
        }
    }
    bool CreateFile() {
        if (open_mode != ios::out)
        {
            open_mode = ios::out;
        }
        file.open(path, open_mode);
        return (file.is_open()) ? true : false;
    }
    void CloseFile() {
        this->file.close();
    }
};

int mystrlen(string str)
{
    int i = 0;
    int counter = 0;
    while (str[i] != '\0')
    {
        counter++;
        i++;
    }
    return counter;
}

int main()
{
    string name1, name2;
    cout << "Enter name for first file: ";
    cin >> name1;
    cout << "Enter name for second file: ";
    cin >> name2;
    cout << endl;
    File* file1 = new File(name1);
    File* file2 = new File(name2);
    string text1, text2;
    file1->Write("Loving undefeated, on your knees pleading\nBaby you can hit up my line when you need it\nSaid that you tried? Baby you succeeded\n Got a craving, baby can you feed it?");
    file1->Load(text1);
    file2->Write(text1);
    file2->Load(text2);
    cout << name1 << ":\n" << text1 << endl;
    cout << name2 << ":\n" << text2 << endl;
    return 0;
}