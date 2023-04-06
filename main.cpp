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
    File* file1 = new File("text1");
    File* file2 = new File("text2");
    File* file3 = new File("merged");
    string text1, text2, merged[300];
    file1->Write("You used to call me on my cell phone\nLate night when you need my love\nCall me on my cell phone\nLate night when you need my love");
    file1->Load(text1);
    file2->Write("I know when that hotline bling\nThat could only mean one thing\n\I know when that hotline bling\nThat could only mean one thing");
    file2->Load(text2);
    int i = 0, j = 0, m = 0;
    while (i < mystrlen(text1) || j < mystrlen(text2))
    {
        string line = "";
        while (i < mystrlen(text1) && text1[i] != '\n')
        {
            line += text1[i];
            i++;
        }
        if (line != "")
        {
            merged[m] = line + "\n";
            m++;
        }

        line = "";
        while (j < mystrlen(text2) && text2[j] != '\n')
        {
            line += text2[j];
            j++;
        }
        if (line != "")
        {
            merged[m] = line + "\n";
            m++;
        }
        j++;
        i++;
    }
    stringstream ss;
    for (int k = 0; k < m; k++)
    {
        ss << merged[k];
        if (k < m - 1) ss << "\n";
    }
    string merged_str = ss.str();
    file3->Write(merged_str);
    cout << "Text 1:\n" << text1 << endl;
    cout << "Text 2:\n" << text2 << endl;
    cout << "Merged text:\n";
    for (int k = 0; k < m; k++)
    {
        cout << merged[k];
        if (k < m - 1) cout << endl;
    }
    return 0;
}
