#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <map>

#define FILENAME "week1.txt"
#define RESULTNAME "result1.txt"

using namespace std;

struct result
{
    int time;
    char* channelName;
    int length;

    result(int t, char* c, int e): time(t), channelName(c), length(e){}
};

class interval
{
    char* channelName;
    int weight, time, index;
    bool type;
    //0 - start
    //1 - end

public:

    interval(int s, int i, char* c, int w, bool t): weight(w), index(i), channelName(c), type(t)
    {
        if(!type) time=s;
        else time=s+w;
    }

    int getType(){return type;}
    int getWeight(){return weight;}
    int getTime(){return time;}
    int getIndex(){return index;}
    char* getChannelName(){return channelName;}
};

bool mySort (interval* a, interval* b) { return (a->getTime() < b->getTime()); }
bool mySort2 (result* a, result* b) { return (a->time < b->time); }

int main()
{
    ifstream in(FILENAME);

    vector<interval*> Intervals;

    char* channelName;
    int ind=0;

    while(!in.eof())
    {
        channelName=new char[20];
        in.getline(channelName,20,'\n');

        int n;
        in >> n;

        int s,w;
        for(int i=ind;i<ind+n;i++)
        {
            in >> s >> w;
            interval* tmp=new interval(s,i,channelName,w,0);
            interval* tmp2=new interval(s,i,channelName,w,1);

            Intervals.push_back(tmp);
            Intervals.push_back(tmp2);
        }

        char sorveg[1];
        in.getline(sorveg,1,'\n');

        ind+=n;
    }
    in.close();

    sort(Intervals.begin(), Intervals.end(), mySort);

    vector<int> seged;
    for(int i=0;i<ind;i++)
    {
        seged.push_back(0);
    }

    int temp_max=0;
    int lastInterval=0;

    for(int i=0;i<2*ind;i++)
    {
        if(!Intervals[i]->getType())//startPoint
        {
            seged[Intervals[i]->getIndex()]=temp_max+Intervals[i]->getWeight();
        }
        else//endPoint
        {
            int tmp=seged[Intervals[i]->getIndex()];
            if(tmp>temp_max)
            {
                temp_max=tmp;
                lastInterval=Intervals[i]->getIndex();
            }

        }
    }
    vector<int> vertices;

    while(temp_max>0)
    {
        vertices.push_back(lastInterval);

        bool b=false;
        int i=0;
        while(!b)
        {
            if(Intervals[i]->getIndex() == lastInterval) b=true;
            i++;
        }
        i--;
        temp_max-=Intervals[i]->getWeight();
        i--;

        if(i<=0) break;

        b=false;
        while(!b)
        {
            if(Intervals[i]->getType())
            {
                if(seged[Intervals[i]->getIndex()] == temp_max) b=true;
            }
            i--;
        }
        i++;
        lastInterval=Intervals[i]->getIndex();
    }

    vector<result*> res;
    for(int i=0;i<vertices.size();i++)
    {
        res.push_back(new result(Intervals[vertices[i]]->getTime(),Intervals[vertices[i]]->getChannelName(),Intervals[vertices[i]]->getWeight()));
    }
    sort(res.begin(), res.end(), mySort2);

    ofstream out(RESULTNAME);

    for(int i=0;i<res.size();i++)
    {
        out << res[i]->time << " " << res[i]->channelName << endl;
    }

    out.close();

    return 0;
}
