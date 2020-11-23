#include <string>
#include <iostream>

#include "../include/helpers.hpp"
using namespace std;
unsigned int index = 0;


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

string add_ImgRL(string text,bool isImg)
{
    bool isURL=false;
    string URL_head="";
    string URL_link="";
    //Sample Image= ![alt text](/src/of/image.jpg "title")
    // Loop through urltext
    // Sample URL=[I'm an inline-style link](https://www.google.com)
    // Getting the heading
    while (index < text.size() && text[index] != ']' )
    {
        // Broken [text [text](link) case
        if (text[index]-97>26 || text[index]-97<0)
        {
            isURL=false;
            index++;
            break;
        }
        URL_head += text[index];
        index++;
    }
    if(index<text.size() && text[index+1]!='(')
    {
        isURL=false;
    }
    index++;
    // Getting the URL
    while (index < text.size() && text[index] != ')')
    {                    
        // Error [link](abc.com [link](abc.com)
        if (text[index]-97>26 || text[index]-97<0)
        {
            isURL=false;
            index++;
            break;
        }
        URL_link += text[index];
        index++;
    }

    if(isURL==true)
    {
        if(isImg==true)
        return "<img src='" + URL_head + "' alt='" + URL_link + "'>";
        else
        {
            return "<a href='" + URL_head + "'>" + URL_link + "</a>";
        }
    }  
    else
    {
        return URL_head+URL_link;
    } 
}


string parseLinks(string text, string path)
{
    path = "";
    string label = text;
    string newText = "";
    bool isImage = false;
    bool isTag = false;

    for (; index < text.size();)
    {

        // Check if tag
        if (text[index] == '{' && text[index + 1] == '{' && !isTag)
        {
            isTag = true;
            index += 2;
            continue;
        }
        
        // If tag
        if (isTag == true)
        {
            string tag = "";
            while (index < text.size())
            {
                if(text[index] == '}' && text[index+1] == '}'){
                    string filename = toLowerCase(tag);
                    string filepath = filename + ".html";
                    newText += "<a class='tag' href='" + filepath + "'>{{" + tag + "}}</a>";
                    isTag = false;
                    break;
                }
                tag += text[index];
                index += 1;
            }

            //if bad tags
            if(index == text.size() && isTag == true){
                newText += "{{" + tag;
                isTag = false;
            }

            index += 2; // Increment index to new text;
            continue;
        }
        // Enter into linking
        // ![ -> image flag true
        if (text[index] == '!' && text[index + 1] == '[')
        {
            isImage = true;
            //newText=newText+ add_ImgRL(text,isImage);
        }
        else if (text[index] == '[')
        {
            //newText=newText+add_ImgRL(text,isImage);
        }
    }
    return newText;
}
