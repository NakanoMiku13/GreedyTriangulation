#include<bits/stdc++.h>
using namespace std;
template<typename datatype, typename datatype2>
class Pair{
    public:
        datatype x;
        datatype y;
        Pair(datatype x, datatype2 y){
            this->x = x;
            this->y = y;
        }
        Pair(){
            this->x = (datatype)NULL;
            this->y = (datatype)NULL;
        }
        auto operator==(const auto& other){
            return (this->x == other.x) && (this->y == other.y);
        }
};
auto distanceBetweenTwoPoints(auto vector1, auto vector2)->double{
    double x1 = vector1.x, x2 = vector2.x, y1 = vector1.y, y2 = vector2.y;
    return sqrt(pow((x2-x1),2)+pow((y2-y1),2));
}
/*
 {1,2},{{1,2},{2,3},{3,5}},{}
*/
auto possibleConnections(auto coordinates,auto coordinatesList, auto possibleConnectionsList){
    if(coordinatesList.empty()) return possibleConnectionsList;
    else{
        pair<Pair<double,double>,Pair<double,double>> connection;
        double distance = 0;
        auto first = coordinatesList.front();
        if(coordinates == first){
            coordinatesList.pop_front();
            first = coordinatesList.front();
        }
        distance = distanceBetweenTwoPoints(coordinates,first);
        connection.first = coordinates;
        connection.second = first;
        pair<pair<Pair<double,double>,Pair<double,double>>,double> node;
        //{{{x1,y1},{x2,y2}},dist}
        node.first = connection;
        node.second = distance;
        possibleConnectionsList.push_back(node);
        coordinatesList.pop_front();
        return possibleConnections(coordinates,coordinatesList,possibleConnectionsList);
    }
}
int main(){
    /*
        int arr[];
        map<string,bool> arr;
        arr["hola"] = true;
        arr["adios"] = true;
        arr["hola mundo"] = false;
    */
    //Cambiar el list y anexar la funcion pop_front al vector
    list<Pair<double,double>> coordinates = list<Pair<double,double>>();
    //vector<pair<Pair<double,double>,Pair<double,double>>> connections = vector<pair<Pair<double,double>,Pair<double,double>>>();
    //map<pair<Pair<double,double>,Pair<double,double>>,bool> connectionsMap;
    int numCoordinates = 0;
    cin>>numCoordinates;
    if(numCoordinates < 4) return 0;
    for(auto i = 0 ; i < numCoordinates ; i++){
        double x,y;
        cin>>x>>y;
        Pair<double,double> pairL = Pair<double,double>(x,y);
        coordinates.push_back(pairL);
    }
    int numConnections = numCoordinates;
    cout<<"Coordinates:\n";
    int coord = 0;
    for(auto i : coordinates){
        cout << coord++ << ") X: " << i.x << " Y: " << i.y << endl;
    }
    list<list<pair<pair<Pair<double,double>,Pair<double,double>>,double>>> possibleConnectionsList;
    for(auto i : coordinates){
        auto connection = possibleConnections(i,coordinates,list<pair<pair<Pair<double,double>,Pair<double,double>>,double>>());
        possibleConnectionsList.push_back(connection);
    }
    for(auto i : possibleConnectionsList){
        for(auto j : i){
            auto connection = j.first;
            auto distance = j.second;
            cout<<"X1: "<<connection.first.x<<" Y1: "<<connection.first.y<<" X2: "<<connection.second.x<<" Y2: "<<connection.second.y<<" Distance: "<<distance<<endl;
        }
    }
    /*
        {{x,y},{x,y}} , long
        1) {{-4,1},{-4,2}, 12}
        2) ...
        3) ...
    */
    /*for(auto i = 0 ; i < numConnections ; i++){
        pair<Pair<double,double>,Pair<double,double>> connection = pair<Pair<double,double>,Pair<double,double>>();
        Pair<double,double> firstVector = Pair<double,double>(), secondVector = Pair<double,double>();
        cout<<"Type the first node to connect:\n";
        int n,m;
        cin>>n;
        if(n > numCoordinates) cout<<"Error\n";
        firstVector = coordinates[n];
        cout<<"Type the second node to connect:\n";
        cin>>m;
        if(m > numCoordinates) cout<<"Error\n";
        secondVector = coordinates[m];
        connection.first = firstVector;
        connection.second = secondVector;
        connectionsMap[connection] = true;
        connections.push_back(connection);
    }
    char le = 'a';
    for(auto i : connections){
        cout<<"Connection:\n";
        cout<< le++ <<") x_1: "<<i.first.x<<" y_1: "<<i.first.y<<"\n x_2: "<<i.second.x<<" y_2: "<<i.second.y<<endl;
    }
    */

}