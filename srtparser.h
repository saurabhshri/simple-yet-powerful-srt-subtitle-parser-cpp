/*
 * Author   : Saurabh Shrivastava
 * Email    : saurabh.shrivastava54@gmail.com
 * Link     : https://github.com/saurabhshri
 *
 * Based on subtitle-parser by Oleksii Maryshchenko.
 * Email    : young_developer@mail.ru
 * Link     : https://github.com/young-developer/subtitle-parser
 */

#ifndef SRTPARSER_H
#define SRTPARSER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <regex>

class SubtitleWord
{
private:
    std::string _text;
public:
    SubtitleWord(void);
    SubtitleWord(std::string text);
    virtual std::string getText() const;
    ~SubtitleWord(void);
};

class SubtitleItem
{
private:
    long int _startTime; //in milliseconds
    long int _endTime;
    std::string _text;  // actual line, as present in subtitle file
    long int timeMSec(std::string value);

    std::string _startTimeString;
    std::string _endTimeString;
    bool _ignore;
    std::string _justDialogue;
    int _speakerCount;
    std::vector<std::string> _speaker;
    int _nonDialogueCount;
    std::vector<std::string> _nonDialogue;
    int _styleTagCount;
    std::vector<std::string> _styleTag;
    void extractInfo(bool keepHTML = 0, bool doNotIgnoreNonDialogues = 0,  bool doNotRemoveSpeakerNames = 0);
public:
    long int getStartTime() const;
    long int getEndTime() const;
    std::string getText() const;

    std::string getStartTimeString() const;
    std::string getEndTimeString() const;
    bool getIgnoreStatus() const;
    std::string getDialogue(bool keepHTML = 0, bool doNotIgnoreNonDialogues = 0,  bool doNotRemoveSpeakerNames = 0);
    int getSpeakerCount() const;
    int getNonDialogueCount() const;
    int getStyleTagCount() const;
    std::vector<std::string> getSpeakerNames();
    std::vector<std::string> getNonDialogueWords();
    std::vector<std::string> getStyleTags();


    void setStartTime(long int startTime);
    void setEndTime(long int endTime);
    void setText(std::string text);

    SubtitleItem(void);
    SubtitleItem(std::string startTime,std::string endTime, std::string text, bool ignore = false,
                 std::string justDialogue = "" , int speakerCount = 0, int nonDialogueCount = 0,
                 int styleTagCount = 0, std::vector<std::string> speaker = std::vector<std::string>(),
                 std::vector<std::string> nonDialogue = std::vector<std::string>(),
                 std::vector<std::string> styleTags = std::vector<std::string>());
    ~SubtitleItem(void);
};

class SubtitleParser
{
protected:
    std::vector<SubtitleItem*> _subtitles;
    std::string _fileName;
    virtual void parse(std::string fileName) = 0;
public:
    virtual std::vector<SubtitleItem*> getSubtitles();
    std::string getFileData();
    SubtitleParser(void);
    virtual ~SubtitleParser(void);
};

class SubtitleParserFactory
{
private:
    std::string _fileName;
public:
    SubtitleParser* getParser();
    SubtitleParserFactory(std::string fileName);
    ~SubtitleParserFactory(void);
};

class SubRipParser : public SubtitleParser
{
    void parse(std::string fileName);
public:
    SubRipParser(void);
    SubRipParser(std::string fileName);
    ~SubRipParser(void);
};


SubtitleParserFactory::SubtitleParserFactory(std::string fileName)
{
    _fileName = fileName;
}

SubtitleParser* SubtitleParserFactory::getParser()
{
    return new SubRipParser(_fileName);
}

SubtitleParserFactory::~SubtitleParserFactory(void)
{
}

std::vector<SubtitleItem*> SubtitleParser::getSubtitles()
{
    return _subtitles;
}

std::string SubtitleParser::getFileData()
{
    std::ifstream infile(_fileName);
    std::string allData = "";
    std::string line;
    while (std::getline(infile, line))
    {
        std::istringstream iss(line);
        allData += line + "\n";
    }
    return allData;

}

SubtitleParser::SubtitleParser(void)
{

}

SubtitleParser::~SubtitleParser(void)
{
}

SubRipParser::SubRipParser(void)
{
}

void SubRipParser::parse(std::string fileName)
{
    try
    {
        std::string szRegex = "([0-9]+)\n([0-9]{2}:[0-9]{2}:[0-9]{2},[0-9]{3}) --> ([0-9]{2}:[0-9]{2}:[0-9]{2},[0-9]{3})";
        std::regex subRegex (szRegex);
        std::string fileData = getFileData();
        // default constructor = end-of-sequence:
        std::regex_token_iterator<std::string::iterator> rend;
        int submatches[] = {-1,1,2,3};
        std::regex_token_iterator<std::string::iterator> c ( fileData.begin(), fileData.end(), subRegex, submatches );
        std::deque<std::string> match;
        while (c!=rend)
        {
            match.push_back(*c++);
        }
        match.pop_front();
        if(match.size()%4)
        {
            std::cout<<"File is incorrect!";
            return;
        }

        for(int i=0;i != match.size();i+=4)
        {
            _subtitles.push_back(new SubtitleItem(match[i+1],match[i+2],match[i+3]));
        }
    }
    catch(std::regex_error& e) {
        // Syntax error in the regular expression
        std::cout<<e.what()<<std::endl;
    }
}

SubRipParser::SubRipParser(std::string fileName)
{
    _fileName = fileName;
    parse(fileName);
}

SubRipParser::~SubRipParser(void)
{
    for(int i=0;i != _subtitles.size();++i)
    {
        if(_subtitles[i])
            delete _subtitles[i];
    }
}

SubtitleItem::SubtitleItem(void)
{
}

SubtitleItem::SubtitleItem(std::string startTime,std::string endTime, std::string text, bool ignore,
                           std::string justDialogue, int speakerCount, int nonDialogueCount,
                           int styleTagCount, std::vector<std::string> speaker, std::vector<std::string> nonDialogue,
                           std::vector<std::string> styleTags)
{
    _startTime = timeMSec(startTime);
    _endTime = timeMSec(endTime);
    _text = text;

    _startTimeString = startTime;
    _endTimeString = endTime;
    _ignore = ignore;
    _justDialogue = justDialogue;
    _speakerCount = speakerCount;
    _nonDialogueCount = nonDialogueCount;
    _speaker = speaker;
    _styleTagCount = styleTagCount;
    _styleTag = styleTags;
    _nonDialogue = nonDialogue;
}

long int SubtitleItem::timeMSec(std::string value)
{
    std::string szRegex = "([0-9]+):([0-9]{2}):([0-9]{2}),([0-9]{3})";
    std::regex subRegex (szRegex);
    int submatches[] = {1,2,3,4};
    std::regex_token_iterator<std::string::iterator> c ( value.begin(), value.end(), subRegex, submatches );
    std::regex_token_iterator<std::string::iterator> rend;
    std::vector<std::string> parts;
    while (c!=rend)
    {
        parts.push_back(*c++);
    }
    return atoi(parts[0].c_str()) * 3600000 + atoi(parts[1].c_str()) * 60000 + atoi(parts[2].c_str()) * 1000 + atoi(parts[3].c_str());
}

long int SubtitleItem::getStartTime() const
{
    return _startTime;
}
long int SubtitleItem::getEndTime() const
{
    return _endTime;
}

std::string SubtitleItem::getText() const
{
    return _text;
}

void SubtitleItem::setStartTime(long int startTime)
{
    _startTime = startTime;
}
void SubtitleItem::setEndTime(long int endTime)
{
    _endTime = endTime;
}
void SubtitleItem::setText(std::string text)
{
    _text = text;
}

std::string SubtitleItem::getStartTimeString() const
{
    return _startTimeString;
}

std::string SubtitleItem::getEndTimeString() const
{
    return _endTimeString;
}

bool SubtitleItem::getIgnoreStatus() const
{
    if(_ignore)
        return true;

    else
        return false;

}

void SubtitleItem::extractInfo(bool keepHTML, bool doNotIgnoreNonDialogues, bool doNotRemoveSpeakerNames)
{
    std::string output = _text;

    //stripping HTML tags
    if(!keepHTML)
    {
        /* REGEX Based approach; <! C++ 11
        std::regex tags("<[^<]*>");
        std::regex_replace(std::back_inserter(output), _text.begin(), _text.end(), tags, "");
        */

        /*
         * TODO : Before erasing, extract the words.
         * std::vector<std::string> getStyleTags();
         * int getStyleTagCount() const;
         * std::vector<std::string> _styleTag;
         * int _styleTagCount;
         */

        int countP = 0;
        for(char& c : output)
        {
            if(c=='<')
            {
                countP++;
                c = '~';
            }

            else
            {
                if(countP!=0)
                {
                    if(c != '>')
                        c = '~';

                    else if(c == '>')
                    {
                        c = '~';
                        countP--;
                    }
                }
            }
        }
    }

    //stripping non dialogue data e.g. (applause)

    if(!doNotIgnoreNonDialogues)
    {
        /*
         * TODO : Before erasing, extract the words.
         * std::vector<std::string> getNonDialogueWords();
         * int getNonDialogueCount() const;
         * std::vector<std::string> _nonDialogue;
         * int _nonDialogueCount;
         */

        int countP = 0;
        for(char& c : output)
        {
            if(c=='(')
            {
                countP++;
                c = '~';
            }

            else
            {
                if(countP!=0)
                {
                    if(c != ')')
                        c = '~';

                    else if(c == ')')
                    {
                        c = '~';
                        countP--;
                    }
                }
            }
        }
    }

    //Extracting speaker names
    if(!doNotRemoveSpeakerNames)
    {
        for(int i=0; output[i]!='\0';i++)
        {
            int colonIndex = 0, prevSpaceIndex = 0;
            if(output[i]==':')  //speaker found; travel back
            {
                _speakerCount++;
                colonIndex = i;

                for(int j=i; j>0;j--)
                {
                    if(output[j]== ' ' || output[j]== '\n' )
                    {
                        prevSpaceIndex = j;
                        break;
                    }
                }

                i = prevSpaceIndex; //compensating the removal and changes in index

                //check if there's a space after colon i.e. A: Hello vs A:Hello
                int removeSpace = 0;
                if(output[colonIndex + 1]==' ')
                    removeSpace = 1;

                _speaker.push_back(output.substr(prevSpaceIndex + 1, colonIndex - prevSpaceIndex - 1));
                output.erase(prevSpaceIndex + 1, colonIndex - prevSpaceIndex + removeSpace);
            }

        }

    }

    output.erase(std::remove(output.begin(), output.end(), '~'), output.end());
    //std::cout<<output<<"\n";

    _justDialogue = output;

    if(_justDialogue.empty() || _justDialogue == " ")
        _ignore = true;

}

std::string SubtitleItem::getDialogue(bool keepHTML, bool doNotIgnoreNonDialogues,  bool doNotRemoveSpeakerNames)
{
    if(_justDialogue.empty())
        extractInfo(keepHTML, doNotIgnoreNonDialogues, doNotRemoveSpeakerNames);

    return _justDialogue;
}
int SubtitleItem::getSpeakerCount() const
{
    return _speakerCount;
}
int SubtitleItem::getNonDialogueCount() const
{
    return _nonDialogueCount;
}
int SubtitleItem::getStyleTagCount() const
{
    return _styleTagCount;
}
std::vector<std::string> SubtitleItem::getSpeakerNames()
{
    return _speaker;
}
std::vector<std::string> SubtitleItem::getNonDialogueWords()
{
    return _nonDialogue;
}
std::vector<std::string> SubtitleItem::getStyleTags()
{
    return _styleTag;
}
SubtitleItem::~SubtitleItem(void)
{

}

SubtitleWord::SubtitleWord(void)
{
    _text = "";
}

SubtitleWord::SubtitleWord(std::string text)
{
    _text = text;
}

std::string SubtitleWord::getText() const
{
    return _text;
}

SubtitleWord::~SubtitleWord(void)
{
}


#endif //SRTPARSER_H
