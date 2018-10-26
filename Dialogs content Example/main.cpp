#include "../srtparser.h"
using namespace std;

int main(int argc, char *argv[]) {

    // If filename not provided
    if(argc < 2) {
        cout << "Please pass the filename as an argument: ./a.out filename.srt\n";
        return 0;
    }

    SubtitleParserFactory *subParserFactory = new SubtitleParserFactory(argv[1]);
    SubtitleParser *parser = subParserFactory->getParser();

    std::vector<SubtitleItem*> sub = parser->getSubtitles();

    ofstream myfile;
    myfile.open ("out.srt");
    int dialogNumber = 0;

    for(SubtitleItem * element : sub)
    {
        if(element->getSpeakerCount())
        {
            ++dialogNumber;
            std::vector<std::string> name = element->getSpeakerNames();
            myfile << "Dialog #" << dialogNumber << ":" << endl << endl;
            for(std::string display : name)
                myfile<<display<<endl;
            myfile<<endl;
        }

    }

    return 0;
}
