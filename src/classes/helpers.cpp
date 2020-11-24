#include <string>
#include <iostream>

#include "../include/helpers.hpp"
using namespace std;

char getLower(char c)
{
    if (c >= 'A' && c <= 'Z')
        return c - ('Z' - 'z');
    return c;
}
string toLowerCase(string text)
{
    string newtext = "";
    for (unsigned int i = 0; i < text.size(); i++)
    {
        if (text[i] == '\0')
            break;
        else if (text[i] == ' ')
            newtext += '_';
        else if ((text[i] >= 'A' && text[i] <= 'Z') || (text[i] >= 'a' && text[i] <= 'z')) //alphabets
            newtext += getLower(text[i]);
        else if (text[i] >= '0' && text[i] <= '9')
            newtext += getLower(text[i]);
    }
    return newtext;
}
// Prints errorline
void printError(int linenumber, string text) {
  cout << "Error at line " << linenumber << ". " << text << endl;
}

string add_ImgRL(string text,bool isImg,unsigned int index)
{
    bool isURL=false;
    bool head_end=false;
    string URL_head="";
    string URL_link="";
    //Sample Image= ![alt text](/src/of/image.jpg "title")
    // Sample URL=[I'm an inline-style link](https://www.google.com)

    for(unsigned int j=index;j< text.size();j++)
    {
        if(head_end==false)
        {
            if(text[j]==']')
            {
                head_end=true;
                j++;
                break;
            }
            else if(text[j]=='(' || text[j]==')' || text[j]=='[')
            {
                isURL=false;
                break;
            }
            else
                URL_head=URL_head+text[j];
        }
        else
        {
            if(text[j]==')')
            {
                isURL=false;
                break;
            }
            else if(text[j]=='(' || text[j]=='[' || text[j]==']')
            {
                isURL=false;
                break;
            }
            else
            {
                URL_link=URL_link+text[j];
            }
        }   
    }
    if(isURL==true)
    {
        if(isImg==true)
        return "<img src='" + URL_link + "' alt='" + URL_head + "'>";
        else
        {
            return "<a href='" + URL_link + "'>" + URL_head + "</a>";
        }
    }  
    else
    {
        return text;
    } 
}


string parseLinks(string text, string path)
{
    path = "";
    string newText = "";
    string label = text;
    bool isImage = false;
    bool isTag=false;

    for (unsigned int j=0;j<text.size();j++)
    {
        // Check if tag
        if (text[j] == '{' && text[j + 1] == '{' && !isTag)
        {
            isTag = true;
            j += 2;
            continue;
        }
        
        // If tag
        if (isTag == true)
        {
            string tag = "";
            while (j < text.size())
            {
                if(text[j] == '}' && text[j+1] == '}'){
                    string filename = toLowerCase(tag);
                    string filepath = filename + ".html";
                    newText += "<a class='tag' href='" + filepath + "'>{{" + tag + "}}</a>";
                    isTag = false;
                    break;
                }
                tag += text[j];
                j += 1;
            }

            //if bad tags
            if(j == text.size() && isTag == true){
                newText += "{{" + tag;
                isTag = false;
            }

            j += 2; // Increment index to new text;
            continue;
        }

        // Enter into linking
        // ![ -> image flag true
        if (text[j] == '!' && text[j + 1] == '[')
        {
            isImage = true;
            newText=newText+ add_ImgRL(text,isImage,j);
        }
        else if (text[j] == '[')
        {
            newText=newText+add_ImgRL(text,isImage,j);
        }
        else
        {
            newText=newText+text[j];
        }
    }
    return newText;
}
