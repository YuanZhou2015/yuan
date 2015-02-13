/*
 *CIVL 8903 Homework 3
 *Yuan Zhou
 *Feburary 13 2015
 *
 *Reading information from given inputfile. 
 *Showing warnings when there is error in the inputfile. 
 *Processing the read data by using funcitons.
 *Output the information (read and processed) in multi-dimesional arrays
 */

#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

// Functions to find the max and min of the numbers in an anrray.

int MAX (int a[], int size) {
	int i=0, temp=a[0];
    while ( i < size) 
	{
	   if (temp < a[i])
		   temp = a[i];
       i++;
    }
    return temp;
}

int MIN (int a[], int size) {
	int i=0,temp= a[0];
    while ( i < size) 
	{
	   if (temp > a[i])
		   temp = a[i];
       i++;
    }
    return temp;
}

int main () {
    int stationnumber, instrumentnumber, i, j, k, flag1, flag2;    
    int Correct=0;   
    string stationname[100], instrumentname[10], stn, inn;
    string inputfilename, outputfilename, errorfilename;
    ifstream inputfile;
    ofstream outputfile, errorfile;

    //Prompt user for input file name

    cout << "Enter input filename: " ;
    cin  >> inputfilename;

    //Perform sanity checks on file streams (input file, output file, error file)

    inputfile.open(inputfilename.c_str());
    if ( !inputfile.is_open() ){
        cout << "Cannot open input file: "
             << inputfilename
             << endl;
        return 10;
    }

    outputfile.open("yuan.out");
    if ( !outputfile.is_open() ){
        cout << "Cannot open output file: "
             << "yuan.out"
             << endl;
        return 20;
    }

    errorfile.open("yuan.err");
    if (!errorfile.is_open() ){
        cout << "Cannot open error file: "
             << "yuan.err"
             << endl;
        return 30;
    }
    
    // Initializing the record matrix

    int recordnumber[100][10];
    for(i = 0; i < 100; i++)
          for(j = 0; j < 10; j++)
              recordnumber[i][j] = 0;

    //Read information 

    while (!inputfile.eof()){
        inputfile >> stationnumber;
        cout << "Number of Stations: " << stationnumber <<"\n";
        inputfile >> instrumentnumber;
        cout << "Number of instruments: " << instrumentnumber <<"\n";       
       
        // Input the given station name and instrument name into arrays.
        
        cout << "Stations read" << "\n";

        i=0, j=0, k=0;

        outputfile << "Seismic Events Summary Report" << "\n";
        outputfile << setw (11) << left << "Station  ";

        while (i < stationnumber){
            inputfile  >> stationname[i];         
            i++;
        }
        
        cout << "Instruments read" << "\n"; 
        while (j < instrumentnumber){
            inputfile >> instrumentname[j];
            outputfile << setw (16) << right << instrumentname[j] << ' ';
            j++;
        }
        outputfile << "\n";

        // Compare station names, instrument names and then input record number.

        cout << "Reading entries..." << "\n";
        while ( k < stationnumber){
            inputfile >> stn;            
            i=0, flag1=0;         
            while (i < stationnumber){
                if ( stn == stationname[i] ){
                    flag1=1;
                    break;
                }                    
                i++;                    
            }

            inputfile >> inn; 
            j=0,flag2=0;             
            while (j < instrumentnumber){
                if ( inn == instrumentname[j] ){
                    flag2=1;
                    break;
                }                    
                j++;                    
            }
           
            inputfile >> recordnumber[i][j];           
            if (flag1!=0 && flag2!=0 && recordnumber[i][j]>=0)
                Correct= Correct+1;
            if (flag1==0){
                cout << "Entry #" << k <<": "<< stn << ' ' << inn << ' ' << recordnumber[i][j]<< ' ' << " -- Warning: Station does not exist" << "\n"; 
                errorfile << "Entry #" << k <<": "<< stn << ' ' << inn << ' ' << recordnumber[i][j]<< ' ' << " -- Warning: Station does not exist" << "\n"; 
            }
            if (flag2==0){
                cout << "Entry #" << k <<": "<< stn << ' '  << inn << ' ' << recordnumber[i][j]<< ' ' << " -- Warning:Instrument name error." << "\n";  
                errorfile <<"Entry #" << k <<": "<< stn << ' ' << inn << ' ' << recordnumber[i][j]<< ' ' << " -- Warning:Instrument name error." << "\n";
            }
            if (recordnumber[i][j]<0){
                cout << "Entry #" << k <<": "<< stationname[i] << ' ' << instrumentname[j] << ' ' << recordnumber[i][j]<< ' ' << " -- Warning: Negative events" << "\n";
                errorfile <<"Entry #" << k <<": "<< stationname[i] << ' ' << instrumentname[j] << ' ' << recordnumber[i][j]<< ' ' << " -- Warning: Negative events" << "\n";
                recordnumber[i][j]=0;
            }

            k++;
        }
                
        break;
    }
        
    int sumstation[100]={0}, suminstrument[10]={0};

    for (int i=0; i<stationnumber; i++){
        for (int j=0; j< instrumentnumber; j++){
            sumstation[i]= sumstation[i]+recordnumber[i][j];
        }       
    }

   
    for (int j=0; j<instrumentnumber; j++){
        for (int i=0; i< stationnumber; i++){
            suminstrument[j]= suminstrument[j]+recordnumber[i][j];
        }
    }

    cout << "Generating report..."<<"\n";

    for (i=0 ; i<stationnumber ; i++){
        outputfile << setw (11) << left << stationname[i];
        for (j=0; j<instrumentnumber ; j++){
        outputfile << setw (16) << right <<recordnumber[i][j];
        }
        outputfile <<"\n";
    }

    // Output the total number of seismic events recorded across all stations by each type of instrument.

    outputfile << "\n" << "Total number of events per Station" << "\n";
    outputfile << "\n" << setw (11) << left << "Station" << setw(5) << right << "Total" <<"\n";
    for (i=0 ; i<stationnumber ; i++){
        outputfile << setw (11) << left << stationname[i] << setw(5) << right << sumstation[i] << "\n";
    }

    outputfile << "\n" << "Total number of events per instrument" << "\n";
    outputfile << "\n" << setw (16) << left << "Instrument" << setw(5) << right << "Total" <<"\n";
    for (j=0 ; j<instrumentnumber ; j++){
        outputfile << setw (16) << left << instrumentname[j] << setw(5) << right << suminstrument[j] << "\n";
    }

    //Output the station/ instrument with the most/least records and the number.

    outputfile <<"\n" << "Station(s) with the most records is/are:" ;
    int flag = MAX (sumstation, stationnumber);
    i=0;
    while (i<stationnumber){
        if (sumstation[i]==flag)
            outputfile << stationname[i]<< ' ';
        i++;
    }
    outputfile << "with " << MAX (sumstation, stationnumber) << " events";

    outputfile <<"\n" << "Station with the least records is/are:" ;
    flag = MIN (sumstation, stationnumber);
    i=0;
    while (i<stationnumber){
        if (sumstation[i]==flag)
            outputfile << stationname[i]<< ' ';
        i++;
    }
    outputfile << "with " << MIN (sumstation, stationnumber) << " events";

    outputfile <<"\n" <<"\n" << "Instrument(s) with the most records is/are:" ;
    flag = MAX (suminstrument, instrumentnumber);
    i=0;
    while (i<instrumentnumber){
        if (suminstrument[i]==flag)
            outputfile << instrumentname[i]<< ' ';
        i++;
    }
    outputfile << "with " << MAX (suminstrument, instrumentnumber) << " events";

    outputfile <<"\n" << "Instrument(s) with the least records is/are:" ;
    flag = MIN (suminstrument, instrumentnumber);
    i=0;
    while (i<instrumentnumber){
        if (suminstrument[i]==flag)
            outputfile << instrumentname[i]<< ' ';
        i++;
    }
    outputfile << "with " << MIN (suminstrument, instrumentnumber) << " events";

    cout<< "Total of " << Correct << " entries processed correctly" << "\n";
    cout<< "Total of " << stationnumber-Correct << " entries ignored" << "\n";
        
    cout << "Completed"<<"\n";

    //Closing files

    inputfile.close();
    outputfile.close();
    errorfile.close();

    return 0;

}
