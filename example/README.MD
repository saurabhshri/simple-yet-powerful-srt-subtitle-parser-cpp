# Example for srtparser.h : Simple, yet powerful C++ SRT Subtitle Parser Library.

## How to run?

CMakeLists.txt is provided. Simply run using cmake.

The compiled tool needs the subtitle file as input.

`./a.out input.srt`

## Output

A simple example resides in this directory (`main.cpp`). Demo subtitle file (`example.srt`) is also provided.
It's output is located in (`example-output.srt`).

Code Snippet:

```
		myfile<<"BEGIN"<<endl;
        myfile<<"start : "<<element->getStartTime()<<endl;
        myfile<<"end : "<<element->getEndTime()<<endl;
        myfile<<"text : "<<element->getText()<<endl;
        myfile<<"startString : "<<element->getStartTimeString()<<endl;
        myfile<<"endString : "<<element->getEndTimeString()<<endl;
        myfile<<"justDialogue : "<<element->getDialogue()<<endl;
        myfile<<"ignore : "<<element->getIgnoreStatus()<<endl;
        myfile<<"speakerCount : "<<element->getSpeakerCount()<<endl;

        if(element->getSpeakerCount())
        {
            std::vector<std::string> name = element->getSpeakerNames();
            for(std::string display : name)
                myfile<<"speakers : "<<display<<", ";
            myfile<<endl;
        }

        myfile<<"END"<<endl<<endl;
```

Input : 

```
1
00:00:00,520 --> 00:00:03,536
Chris: Elon, hey, welcome back to TED.

2
00:00:03,560 --> 00:00:04,936
It's great to have you here.

3
00:00:04,960 --> 00:00:06,536
Elon: Thanks for having me.

4
00:00:06,560 --> 00:00:09,416
(Applause) Thanks

5
00:00:09,440 --> 00:00:11,256
<i>we're going to spend some time</i>
```

Parsed Output :

```
BEGIN
start : 520
end : 3536
text : 
Chris: Elon, hey, welcome back to TED.


startString : 00:00:00,520
endString : 00:00:03,536
justDialogue : 
Elon, hey, welcome back to TED.


ignore : 0
speakerCount : 1
speakers : Chris, 
END

BEGIN
start : 3560
end : 4936
text : 
It's great to have you here.


startString : 00:00:03,560
endString : 00:00:04,936
justDialogue : 
It's great to have you here.


ignore : 0
speakerCount : 0
END

BEGIN
start : 4960
end : 6536
text : 
Elon: Thanks for having me.


startString : 00:00:04,960
endString : 00:00:06,536
justDialogue : 
Thanks for having me.


ignore : 0
speakerCount : 1
speakers : Elon, 
END

BEGIN
start : 6560
end : 9416
text : 
(Applause) Thanks


startString : 00:00:06,560
endString : 00:00:09,416
justDialogue : 
 Thanks


ignore : 0
speakerCount : 0
END

BEGIN
start : 9440
end : 11256
text : 
<i>we're going to spend some time</i>

startString : 00:00:09,440
endString : 00:00:11,256
justDialogue : 
we're going to spend some time

ignore : 0
speakerCount : 0
END



```