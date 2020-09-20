#include <iostream>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fstream>
#include <math.h>
#include <vector>
#include <string>

using namespace std;
vector<int>street_pointcor;
vector<int>xcol;
vector<int>ycol;
vector<string>streetname;
vector<int>randsegnubcol;

struct Vex{float x;float y;};
struct Vex point;
vector<Vex>vexcol;
class Line{public:Vex start;Vex end;};
class Line line;
vector<vector<Line>>streetcontainer;

int Getrandom() {
    // open /dev/urandom to read
    ifstream urandom("/dev/urandom");
    if (urandom.fail()) {

        return 0;
    }
    unsigned int num = 0;

    urandom.read((char*)&num, 1);
    urandom.close();
    return num;
}
int check_overlap(vector<Vex>point) {
    int flag=0;
    for(unsigned int l=0;l<vexcol.size();l++){
        for(unsigned int f=l+1;f<vexcol.size();f++){
            if(point[l].x==point[f].x and point[l].y==point[f].y){
                flag=1;
            }
        }
    }
    return flag;
}

void streetcollection() {
    vector<Line> singlestreet;
    int cmv = 0;
    for (unsigned int u = 0; u < randsegnubcol.size(); u++) {
        int q=0;
        while (q < randsegnubcol[u]) {
            line.start = vexcol[cmv];
            line.end = vexcol[cmv + 1];
            cmv = cmv + 2;
            q++;
            singlestreet.push_back(line);
        }
        streetcontainer.push_back(singlestreet);
        singlestreet.clear();
    }}
void Process(int streetnumber, int linesegnumber, int rangenumber)
{   int num1 = Getrandom();
    int finalstreetnumber;

    finalstreetnumber= floor(num1*(streetnumber - 2)/256) + 2;
    string s="a";
    for(int z=0; z<finalstreetnumber;z++){
        streetname.push_back(s);
        const char *c="a";
        s.append(c);
    }
    for (int cmt = 0; cmt < finalstreetnumber; cmt++) {
        int num3 = Getrandom();
        int finallineseg;
        finallineseg = floor(num3* (linesegnumber - 1)/256) + 1;
        randsegnubcol.push_back(finallineseg);
        int pointcor;
        for (int count1=0;count1<((finallineseg+1)*2)+4;count1++){
            pointcor=Getrandom();
            pointcor=floor(pointcor*(2*rangenumber)/256)-rangenumber;
            while(street_pointcor.size()>0 && pointcor==street_pointcor.back()){
                pointcor=Getrandom();
                pointcor=floor(pointcor*(2*rangenumber)/256)-rangenumber;
            }
            street_pointcor.push_back(pointcor);
        }
    }
    for(unsigned int i=0; i<street_pointcor.size()/2;i++){
        xcol.push_back(street_pointcor[i]);

    }
    for(unsigned int j=street_pointcor.size()/2;j<street_pointcor.size();j++){
        ycol.push_back(street_pointcor[j]);
    }
    for(unsigned int w=0;w<xcol.size();w++){
        point.x=xcol[w];
        point.y=ycol[w];
        vexcol.push_back(point);
    }
    streetcollection();
}
Line line1;
Line line2;
bool check_selfintersect(){
    for(unsigned int i=0; i<streetcontainer.size();i++){
        for(unsigned int j=0;j<streetcontainer[i].size();j++){
            line1=streetcontainer[i][j];
            for(unsigned int s=j+2;s<streetcontainer[i].size();s++){
                line2=streetcontainer[i][s];

                    float A;
                    float B;
                    float C;
                    float D;
                    A = (line2.start.x - line1.start.x) * (line1.end.y - line1.start.y) - (line2.start.y - line1.start.y) * (
                            line1.end.x - line1.start.x);
                    B = (line2.end.x - line1.start.x) * (line1.end.y - line1.start.y) - (line2.end.y - line1.start.y) * (
                            line1.end.x - line1.start.x);
                    C = (line1.end.x - line2.start.x) * (line2.end.y - line2.start.y) - (line1.end.y - line2.start.y) * (
                            line2.end.x - line2.start.x);
                    D = (line1.start.x - line2.start.x) * (line2.end.y - line2.start.y) - (line1.start.y - line2.start.y) * (
                            line2.end.x - line2.start.x);
                    if ((A * B <= 0) && (C * D <= 0)){
                        return false;}
                }
            }
        }
    return true;
}
bool check_partialoverlap(){
    for(unsigned int i=0; i<streetcontainer.size();i++){
        for(unsigned int j=0;j<streetcontainer[i].size();j++){
            line1=streetcontainer[i][j];
            for(unsigned int m=i+1; m<streetcontainer.size();m++){
                for(unsigned int n=0;n<streetcontainer[m].size();n++){
                    line2=streetcontainer[m][n];
                    if(((line1.start.y==line1.end.y) && (line2.start.y==line2.end.y))and (((line1.start.x>line2.end.x)and(line1.start.x<line2.start.x))or((line1.end.x>line2.end.x)and(line1.end.x<line2.start.x)))){
                        return false;
                    }
                    if(((line1.start.x==line1.end.x)&&( line2.start.x==line2.end.x))and (((line1.start.y>line2.end.y)and(line1.start.y<line2.start.y))or((line1.end.y>line2.end.y)and(line1.end.y<line2.start.y)))){
                        return false;
                    }
                    if(((line1.start.x-line1.end.x)!=0) and ((line2.start.x-line2.end.x)!=0)){
                        if (((line1.start.y-line1.end.y)/(line1.start.x-line1.end.x))==((line2.start.y-line2.end.y)/(line2.start.x-line2.end.x))){
                            if(((line1.start.y-line1.end.y)/(line1.start.x-line1.end.x))*line2.start.x+(line1.start.y-((line1.start.y-line1.end.y)/(line1.start.x-line1.end.x))*line1.start.x)==line2.start.y){
                            return false;}
                            if(((line1.start.y-line1.end.y)/(line1.start.x-line1.end.x))*line2.end.x+(line1.start.y-((line1.start.y-line1.end.y)/(line1.start.x-line1.end.x))*line1.start.x)==line2.end.y){
                                return false;}
                            }
                        }
                    float A;
                    float B;
                    float C;
                    float D;
                    A = (line2.start.x - line1.start.x) * (line1.end.y - line1.start.y) - (line2.start.y - line1.start.y) * (
                            line1.end.x - line1.start.x);
                    B = (line2.end.x - line1.start.x) * (line1.end.y - line1.start.y) - (line2.end.y - line1.start.y) * (
                            line1.end.x - line1.start.x);
                    C = (line1.end.x - line2.start.x) * (line2.end.y - line2.start.y) - (line1.end.y - line2.start.y) * (
                            line2.end.x - line2.start.x);
                    D = (line1.start.x - line2.start.x) * (line2.end.y - line2.start.y) - (line1.start.y - line2.start.y) * (
                            line2.end.x - line2.start.x);
                    if ((A * B <= 0) && (C * D <= 0)){
                        return true;}
                    else{return false;}
                    }
                }
            }
        }return true;
    }

void output(){
    int namecnt = 0;
    for(unsigned int u=0;u<randsegnubcol.size();u++){

        cout<<"a"<<" "<<"\""<<streetname[namecnt]<<"\""<<" ";
        namecnt++;
        int q=0;
        //cout<<"("<<streetcontainer[u][0].start.x<<","<<streetcontainer[u][0].start.y<<")";
        while (q<randsegnubcol[u]){

            cout<<"("<<streetcontainer[u][q].start.x<<","<<streetcontainer[u][q].start.y<<")"<<"("<<streetcontainer[u][q].end.x<<","<<streetcontainer[u][q].end.y<<")";
            q=q+2;
        }
        cout<<endl;
    }cout<<"g"<<endl;
}

int Waiting(int waitingvalue){
    int num2 = Getrandom();
    int finalwait = floor(num2 * (waitingvalue - 5) / 256) + 5;
    return finalwait;
}

int main (int argc, char **argv) {

    int streetquantity = 10;
    int linequantity = 5;
    int waitnumber = 5;
    int rangenumber = 20;

    char *cvalue = NULL;
    int c;
    opterr = 0;
    while ((c = getopt(argc, argv, "s:n:l:c:")) != -1) {
        switch (c) {
            case 's':
                cvalue = optarg;
                streetquantity = atoi(cvalue);
                if (streetquantity < 2) {cerr << "Error: wrong argument" << endl;
                exit(0);}
                break;

            case 'n':
                cvalue = optarg;
                linequantity = atoi(cvalue);
                if (linequantity < 1) {cerr << "Error: wrong argument" << endl;
                    exit(0); }
                break;
            case 'l':
                cvalue = optarg;
                waitnumber = atoi(cvalue);
                if (waitnumber < 5) {cerr << "Error: wrong argument" << endl;
                    exit(0);}
                break;
            case 'c':
                cvalue = optarg;
                rangenumber = atoi(cvalue);
                if (rangenumber < 1) {cerr << "Error: wrong argument" << endl;
                    exit(0);}
                break;
            case '?':
                cerr << "Error: wrong argument" << endl;
                return 0;
            default:
                return 0;
        }
    }


    while (true) {
        int cm = 0;
        Process(streetquantity, linequantity, rangenumber);
        while (check_overlap(vexcol) == 1 || !check_selfintersect()||!check_partialoverlap()) {
            streetcontainer.clear();
            streetname.clear();
            vexcol.clear();
            street_pointcor.clear();
            xcol.clear();
            ycol.clear();
            randsegnubcol.clear();
            Process(streetquantity, linequantity, rangenumber);
            cm = cm + 1;
            if (cm >= 1500) {
                cerr << "Error: failed to generate valid input for 25 simultaneous attempts" << endl;
                exit(0);
            }
        }
            output();
            sleep(Waiting(waitnumber));
            for(unsigned v=0; v<streetname.size();v++){
                cout<<"r"<<" "<<"\""<<streetname[v]<<"\""<<endl;
            }
            streetname.clear();
        }
    }

