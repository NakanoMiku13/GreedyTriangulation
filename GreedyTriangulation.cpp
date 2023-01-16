#include<bits/stdc++.h>
#include "GLib.h"
int main(){
    vector<Pair<float,float>> coordinates = vector<Pair<float,float>>();
    vector<Connection> connections = vector<Connection>();
    graph<Pair<float,float>> coordinatesGraph = graph<Pair<float,float>>();
    int numCoordinates = 0, j = 0;
    maxHeight = maxWidth = 0;
    minHeight = minWidth = 1000;
    cout<<"Type the number of points:"<<endl;
    cin>>numCoordinates;
    if(numCoordinates < 4) return 0;
    for(auto i = 0 ; i < numCoordinates ; i++){
        float x,y;
        cout<<"Type the X coordinate and Y coordinate with a space:\nEg. 5 3\n";
        cin>>x>>y;
        maxHeight = max(maxHeight,y);
        maxWidth = max(maxWidth,x);
        minHeight = min(minHeight,y);
        minWidth = min(minWidth,x);
        coordinatesGraph.push_back(Pair<float,float>(x,y));
        coordinates.push_back(Pair<float,float>(x,y));
    }
    for(auto i = 0 ; i < coordinates.size() ; i++){
        Pair<float,float> first, second;
        if(i + 1 >= coordinates.size()){
            first = coordinates[i];
            second = coordinates[0];
        }else{
            first = coordinates[i];
            second = coordinates[i + 1];
        }
        Connection connection = Connection(first,second);
        connections.push_back(connection);
    }
    vector<complexConnection> possibleConnection, ordered;
    for(auto i : coordinates){
        complexConnection connection = possibleConnections(i,coordinates);
        possibleConnection.push_back(connection);
    }
    complexConnection finalConnections = complexConnection();
    for(auto i : possibleConnection){
        for(auto j : i) finalConnections.push_back(j);
    }
    finalConnections.erase(finalConnections.end());
    vector<doubleConnection> mainConnections = vector<doubleConnection>();
    for(auto i : connections) mainConnections.push_back(doubleConnection(i.getFirst(),i.getLast()));
    finalConnections = filterCoordinates(mainConnections,finalConnections);
    finalConnections = filterInvertedCoordinates(finalConnections);
    finalConnections = orderConnections(finalConnections);
    finalConnections = filterChokeConnections(finalConnections);
    vector<Connection> lines = vector<Connection>();
    for(auto i : finalConnections){
        Pair<float,float> first = i.first.first, second = i.first.second;
        Connection connection = Connection(first,second);
        lines.push_back(connection);
    }
    cout<<"Main connections:"<<endl;
    for(auto i : connections){
        cout<<i<<endl;
    }
    cout<<endl<<endl;
    cout<<"Connections generated:"<<endl;
    for(auto i : lines){
        cout<<i<<endl;
    }
}