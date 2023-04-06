#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

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
    File* file1 = new File("code.txt");
    File* file2 = new File("code(coments_removed).txt");
    string text1, text2[500];
    file1->Load(text1);
    int j = 0;
    for (size_t i = 0; i < mystrlen(text1); j++)
    {
        if (text1[i] == '/')
        {
            if (text1[i + 1] == '/')
            {
                while (text1[i] != '\n')
                {
                    i++;
                }
            }
        }
        if (text1[i] == '/')
        {
            if (text1[i + 1] == '*')
            {
                i++;
                while (text1[i] != '/')
                {
                    i++;
                }
                if (text1[i] == '/')
                {
                    i++;
                }
            }
        }
        text2[j] = text1[i];
        i++;
    }
    string text3;
    for (int k = 0; k < j; k++)
    {
        text3 += text2[k];
    }
    file2->Write(text3);
    cout << "Original code:\n" << text1 << endl;
    cout << "Code with comments removed:\n" << text3 << endl;
    return 0;
}